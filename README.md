# ECEN 225 README #2

**Author:** Lucas Keller

**Last Updated:** 06-11-2026

A Raspberry Pi Zero 2W-based smart doorbell with an LCD display, camera, and network upload — built across six labs covering GPIO hardware, C file I/O, networking, threading, and system services.

---

## Overview

This repository documents the second half of ECEN 225. Each lab adds a new layer to a working smart doorbell:

- **Display** — draws to an LCD screen and reads button input
- **File Viewer** — scans a directory and renders `.bmp` images and `.log` files
- **Camera** — captures photos, applies image filters, and saves `.bmp` files
- **Client** — sends captured images over a network socket to a remote server
- **Threaded Client** — moves network upload to a background thread with a live status bar
- **Doorbell** — ties everything together as a `systemd` daemon that runs on boot

**Entry points:**

- Hardware display/button setup → `lib/display.h`, `lib/buttons.h`
- Image processing → `image.c`
- Camera capture → `camera.c`
- Network upload → `client.c`
- Main doorbell program → `main.c`
- System service → `/etc/systemd/system/doorbell.service`


---

## Installation

### Install the BCM2835 Library

The BCM2835 library is required to interface with the Pi's GPIO pins and drive the LCD HAT.

```bash
cd ~
wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.71.tar.gz
tar xvfz bcm2835-1.71.tar.gz
cd bcm2835-1.71
./configure
make
sudo make install
```

### Clone the Repository

```bash
[git clone](https://github.com/byu-ecen-224-classroom/dsl-kellerlucas42-sketch.git)
cd dsl-kellerlucas42-sketch.git
```

### Build the Project

All labs use a provided `Makefile`. To compile:

```bash
sudo make main        # builds main.c → ./main
sudo make test   # builds test.c → ./test
```

### Run the Program

Hardware access requires elevated permissions:

```bash
sudo ./main
```

### Run as a System Service

```bash
sudo systemctl start doorbell.service   # start manually
sudo systemctl enable doorbell.service  # start on every boot
sudo systemctl status doorbell.service  # check logs and status
```

---

## Lab 06 - Display

### Description

Introduced the Waveshare 1.44" LCD HAT, the BCM2835 GPIO library, and the Make build system. The lab involved drawing shapes, text, and images to the LCD screen and responding to d-pad button input.

### Usage Instructions

#### Initialize Hardware

Both `display_init()` and `buttons_init()` must be called at the start of `main()`, in that order:

```c
display_init();
buttons_init();
```

> **Note:** Calling `buttons_init()` before `display_init()` causes a segmentation fault.

#### Drawing Functions (`lib/display.h`)

The screen coordinate origin `(0, 0)` is the top-left corner. Screen dimensions are `DISPLAY_WIDTH` × `DISPLAY_HEIGHT`, defined in `display.h`. Colors are defined in `lib/colors.h`.

Example shape draw:

```c
display_draw_rectangle(0, 5, 128, 15, BYU_ORANGE, true, 1);
```

Example string draw (font size must be passed by address):

```c
display_draw_string(10, 10, "Hello, World!", &Font8, WHITE, BLACK);
```

Available fonts: `Font8`, `Font12`, `Font16`, `Font20`, `Font24`.

#### Button Input (`lib/buttons.h`)

Buttons return `0` when pressed and `1` when released. Always debounce with a `delay_ms()` inner loop:

```c
if (button_up() == 0) {
    // handle press
    while (button_up() == 0) {
        delay_ms(1);
    }
}
```

#### `clearScreen`

Fills the screen with white.

#### `drawHelloWorld`

Draws "hello world" 10 times in different colors across the screen.

#### `drawChars`

Draws 10 characters in varied sizes, colors, and positions.

#### `drawStars`

Draws at least 20 stars onto the screen.

#### `drawFlag`

Draws a flag using at least 5 `display_draw_###` functions, 3 of which are unique.

#### Menu (`drawMenu`)

The menu displays entries from a string array with one entry highlighted. D-pad behavior:

- **Up / Down** — move the highlight bar, wrapping from top to bottom
- **Right** — run the function associated with the selected entry; wait 2 seconds, then redraw the menu

#### Verify

```bash
make test
sudo ./test
```

- Screen should initialize without a segfault
- Each draw function renders correctly
- Menu responds to all button inputs

---

## Lab 07 - File Viewer

### Description

Extended the menu from Lab 06 into a working file browser. The program scans a `viewer/` directory, filters for `.bmp` and `.log` files, and renders the selected file on the LCD.

### Usage Instructions

#### `get_entries` — Scan the Directory
Uses `opendir()` / `readdir()` / `closedir()` to list the `viewer/` folder. Only files ending in `.bmp` or `.log` are kept (up to 8). Uses `getFileExtension()` from Lab 04 to filter:

```c
DIR *dp = opendir("viewer");
struct dirent *entry;

while ((entry = readdir(dp)) != NULL) {
    // filter by extension, add to entries[]
}
closedir(dp);
```

#### `draw_file` — Render a Selected File

- **`.bmp`** — displays the image for 2 seconds using `display_draw_image_data()`
- **`.log`** — displays the first 100 characters of the file for 2 seconds using `display_draw_string()`

File is opened with `fopen()` and read with `fread()`:

```c
FILE *fp = fopen(filepath, "r");
char data[256];
fread(data, 1, 100, fp);
fclose(fp);
```

#### Verify

Place a `.bmp` and a `.log` file into `viewer/`. Run the program and confirm:

- Both files appear in the menu (other files are hidden)
- Right-pressing a `.bmp` entry shows the image for 2 seconds
- Right-pressing a `.log` entry shows its first 100 characters for 2 seconds
- Menu redraws with the highlight on the previously selected entry

---

## Lab 08 - Camera

### Description

Integrated the Pi camera module. Pressing the center button captures a photo, saves it as `viewer/doorbell.bmp`, and displays it with live filter controls.

### Usage Instructions

#### Verify the Camera

```bash
rpicam-still -n --immediate -e bmp --width 128 --height 128 -o camera-test.bmp
```

A file `camera-test.bmp` should appear. If you see a "camera not found" error, reseat the ribbon cable.

#### `camera_save_to_file`

Writes the raw `uint8_t *` buffer returned by `camera_capture_data()` to a `.bmp` file:

```c
FILE *fp = fopen("viewer/doorbell.bmp", "wb");
fwrite(buffer, 1, buffer_size, fp);
fclose(fp);
```

#### Center Button Flow

1. Clear screen and display a "Say Cheese!" message
2. Call `camera_capture_data()` to fill a `malloc`'d buffer
3. Call `camera_save_to_file()` to write `viewer/doorbell.bmp`
4. Call `create_bmp()` to parse the BMP header and get a `Bitmap` struct
5. Call `display_draw_image_data()` to show the image

```c
uint8_t *buf = malloc(sizeof(uint8_t) * IMAGE_SIZE);
camera_capture_data(buf);
camera_save_to_file(buf, IMAGE_SIZE);
Bitmap *bmp = create_bmp(buf, IMAGE_SIZE);
display_draw_image_data(bmp->pxl_data);
```

#### Filter Controls (while image is displayed)

| Button | Effect |
| ------ | ------ |
| Right | Remove red channel |
| Left | Remove blue channel |
| Up | Remove green channel |
| Down | Apply OR filter |
| Center | Exit to menu |

#### Memory Management

Every `malloc` must have a matching `free`. After exiting the image view:

```c
destroy_bmp(bmp);
free(buf);
```

#### Verify

- Camera capture produces a visible image on screen
- Each d-pad direction applies the correct filter
- No memory leaks (valgrind or manual review of every `malloc` / `free` pair)

---

## Lab 09 - Client

### Description

Added network upload. After viewing the captured photo, pressing the center button sends the image to `ecen224.byu.edu:2240` using a TCP socket.

### Usage Instructions

#### Config Struct (`client.h`)

```c
typedef struct Config {
    char *port;
    char *host;
    uint8_t *payload;
    uint32_t payload_size;
    char *hw_id;
} Config;
```

#### `client_send_image`

Combines the homework ID and image data into one buffer with `memcpy`, then sends it all using a `send()` loop that retries until every byte is delivered:

```c
int total_sent = 0;
while (total_sent < total_size) {
    int sent = send(socket, data + total_sent, total_size - total_sent, 0);
    if (sent < 0) break;
    total_sent += sent;
}
```

#### `client_close`

Closes the socket file descriptor with `close(socket_fd)`.

#### Center Button Flow (updated)

1. Connect: `client_connect(config)`
2. Send: `client_send_image(config)`
3. Receive response: `client_receive_response(config)`
4. Close: `client_close(config)`
5. Show menu

#### View Uploaded Photos

Results are visible at `http://ecen224.byu.edu:2241/<hw_id>` while on the campus network.

#### Verify

- Upload succeeds and the response prints to the terminal
- Photo appears at the results URL
- All resources freed: `malloc` → `free`, `fopen` → `fclose`, `opendir` → `closedir`

---

## Lab 10 - Threaded Client

### Description

Moved the network upload into a background POSIX thread so the menu stays responsive during the slow send. Added a status bar at the bottom of the screen showing upload state.

### Usage Instructions

#### Required Headers and Compile Flag

```c
#include <pthread.h>
#include <unistd.h>
```

Add to `CFLAGS` in the `Makefile`:

```makefile
CFLAGS += -pthread
```

#### `send_image` Thread Function

Handles the full upload sequence: connect → send → receive response → close. Signature must match `pthread_create`'s expectations (`void *` argument and return):

```c
void *send_image(void *arg) {
    Config *config = (Config *) arg;
    // connect, send, receive, close
    return NULL;
}
```

#### Spawning the Thread

```c
pthread_t upload_thread;
pthread_create(&upload_thread, NULL, send_image, (void *) config);
```

> **Warning:** Do not call any `display_*` functions inside the thread — the display library is not thread-safe.

#### Status Bar

A highlight-bar-sized strip at the bottom of the screen shows upload state, driven by a global status variable:

| State | Color | Text |
| ----- | ----- | ---- |
| Sending | Blue | `"Sending…"` |
| Done | Green | `"Sent!"` (for 2 seconds, then hidden) |

#### Verify

```bash
make
sudo ./main
```

- Menu is navigable immediately after pressing center (no blocking)
- Status bar turns blue, then green, then disappears
- Upload still succeeds on the server

---

## Lab 11 - Doorbell

### Description

Finalized the smart doorbell by replacing the file-browser default UI with a welcome screen and converting the program into a `systemd` daemon that starts automatically on boot.

### Usage Instructions

#### Normal Operation

1. On boot, a **welcome message** is shown on the LCD
2. Pressing **center** rings the doorbell:
   - In a background thread: capture photo, save to `viewer/`, upload to server
   - Display **"Ding dong!"** for 2 seconds, then return to the welcome screen
3. Pressing **Up → Up → Down** opens the hidden file browser menu
4. Pressing **Left** from the file browser returns to the welcome screen

#### Service File

`/etc/systemd/system/doorbell.service`:

```ini
[Unit]
Description=ECEN 225 Smart Doorbell

[Service]
WorkingDirectory=/home/YOUR_NETID/YOUR_REPO
ExecStart=/home/YOUR_NETID/YOUR_REPO/main

[Install]
WantedBy=multi-user.target
```

> **Note:** A 15-second `sleep(15)` at the start of `main()` prevents a display conflict with the IP-address boot program.

#### Enable on Boot

```bash
sudo systemctl enable doorbell.service
sudo reboot
```

After reboot, the welcome screen should appear automatically after ~15 seconds.

#### Verify

```bash
sudo systemctl status doorbell.service   # should show "active (running)"
```

- Welcome screen appears on boot without SSH interaction
- Center button rings the doorbell and uploads a photo
- Hidden menu is reachable with Up → Up → Down
- Left button from menu returns to welcome screen

---

## Project Structure

```txt
YOUR_REPO/
├── main.c
├── test.c
├── image.c
├── camera.c
├── client.c
├── Makefile
├── viewer/
│   └── doorbell.bmp
└── lib/
    ├── display.h
    ├── buttons.h
    ├── device.h
    ├── colors.h
    ├── log.h
    ├── log.c
    └── fonts/
        ├── font8.c
        ├── font12.c
        ├── font16.c
        ├── font20.c
        └── font24.c
```

---

## Changelog

All notable changes are documented below, organized by lab.

### Lab 11 — 2026-06-11

#### Additions

- Welcome screen displayed on program start
- "Ding dong!" message shown for 2 seconds on center button press
- Hidden file browser menu triggered by Up → Up → Down sequence
- Left button exits file browser back to welcome screen
- `doorbell.service` systemd service file for automatic boot startup
- 15-second startup delay to avoid display conflict with IP-address program

### Lab 10 — 2026-06-04

#### Additions

- `send_image` POSIX thread function for non-blocking network upload
- Status bar at bottom of screen: blue "Sending…" while uploading, green "Sent!" for 2 seconds after completion
- `-pthread` flag added to Makefile `CFLAGS`

#### Changes

- Center button no longer blocks the main loop during upload
- Deferred `free()` calls to after thread completion to prevent use-after-free

### Lab 09 — 2026-05-28

#### Additions

- `client_send_image`: combines hw_id and image data, sends via `send()` loop until all bytes delivered
- `client_close`: closes the socket file descriptor
- Center button (while viewing image) triggers full upload to `ecen224.byu.edu:2240`

### Lab 08 — 2026-05-21

#### Additions

- `camera_save_to_file`: writes raw camera buffer to `viewer/doorbell.bmp`
- Center button captures photo, saves file, and displays image on LCD
- D-pad filter controls: red/green/blue removal and OR filter while viewing image
- `create_bmp` / `destroy_bmp` calls for proper BMP header parsing and memory cleanup
- Copied `remove_color_channel` and `or_filter` from Image Lab into `image.c`

### Lab 07 — 2026-05-14

#### Additions

- `get_entries`: scans `viewer/` directory, filters to `.bmp` and `.log` files (max 8)
- `draw_file`: renders `.bmp` images or first 100 chars of `.log` files for 2 seconds
- Migrated menu from `test.c` to `main.c` as the primary interface

### Lab 06 — 2026-05-07

#### Additions

- BCM2835 library installed and integrated
- `clearScreen`, `drawHelloWorld`, `drawChars`, `drawStars`, `drawFlag` display functions
- `drawMenu` with highlight bar, up/down navigation, wrap-around, and right-button dispatch
- `test.c` established as hardware test harness
