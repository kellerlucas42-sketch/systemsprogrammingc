#include <dirent.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "lib/buttons.h"
#include "lib/colors.h"
#include "lib/device.h"
#include "lib/display.h"
#include "lib/fonts/fonts.h"
#include "lib/log.h"

#define VIEWER_FOLDER "viewer/"
#define MAX_ENTRIES 8
#define MAX_TEXT_SIZE 400
#define MAX_FILE_NAME 100

// Colors — Feel free to change these to fit your preference
#define BACKGROUND_COLOR WHITE
#define FONT_COLOR BLACK
#define SELECTED_BG_COLOR BYU_BLUE
#define SELECTED_FONT_COLOR BYU_LIGHT_SAND

#define NUM_ENTRIES 5
#define MAX_ENTRY_LENGTH 20

char entries[NUM_ENTRIES][MAX_ENTRY_LENGTH] = {"Clear", "Hello", "Chars", "Stars", "Flag"};

// Makes sure to deinitialize everything before program close
void intHandler(int dummy) {
    log_info("Exiting...");

    // Resets the Screen
    display_clear(BLACK);
    display_draw_string(5, 5, "Goodbye!", &Font16, BLACK, WHITE);

    // Releases control of the display
    display_exit();
    exit(0);
}

// clearScreen
//
//
// Clears the screen to white.
void clearScreen() {
    // TODO: Put your code here
}

// drawHelloWorld
//
// Draws "Hello World!" on the display 10 times
// Make each line a different color
void drawHelloWorld() {
    // TODO: Put your code here
}

// drawChars
//
// Draw chars of different values, sizes, colors, and locations onto the screen
void drawChars() {
    // TODO: Put your code here
}

// drawStars
//
// Draw at least 20 stars on the screen
// TIP: Make a function that uses display_draw_# functions to make the shape of the star,
// Then call that function at multiple locations
void drawStars() {
    // TODO: Put your code here
}

// drawFlag
//
// Use at least 5 other display_draw functions to make any flag you want.
// It must have at least 3 colors, and use 3 unique display_draw functions
void drawFlag() {
    // TODO: Put your code here
}

// draw_menu
//
// Draw the menu of the screen. It uses the entries array to create the menu, with the num_entries
// specifying how many entries are in the entries array. The selected parameter is the item in the
// menu that is selected and should be highlighted. Use BACKGROUND_COLOR, FONT_COLOR,
// SELECTED_BG_COLOR, and SELECTED_FONT_COLOR to help specify the colors of the background, font,
// select bar color, and selected text color.
void drawMenu(char entries[][MAX_ENTRY_LENGTH], int num_entries, int selected) {
    // TODO: Put your code here
}

int main(void) {

    signal(SIGINT, intHandler);

    log_info("Starting...");

    while (true) {
        delay_ms(200);

        if (button_up() == 0) {
            // Do something upon detecting button press

            while (button_up() == 0) {
                // Delay while the button is pressed to avoid repeated actions
                delay_ms(1);
            }
        }
        // Implement other button logic here
    }
    return 0;
}
