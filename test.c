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
    display_init();
    display_clear(WHITE);
}

// drawHelloWorld
//
// Draws "Hello World!" on the display 10 times
// Make each line a different color
void drawHelloWorld() {
    // TODO: Put your code here
    display_init();
    uint16_t spacing = 8;
    display_draw_string(spacing, spacing, "Hello World", &Font8, WHITE, BLACK);
    display_draw_string(spacing, spacing*2, "Hello World", &Font8, BLACK, WHITE);
    display_draw_string(spacing, spacing*3, "Hello World", &Font8, RED, WHITE);
    display_draw_string(spacing, spacing, "Hello World", &Font8, BLUE, BLACK);
    display_draw_string(spacing, spacing, "Hello World", &Font8, PURPLE, BLACK);
    display_draw_string(spacing, spacing, "Hello World", &Font8, ORANGE, BLACK);
    display_draw_string(spacing, spacing, "Hello World", &Font8, VIOLET_RED, WHITE);
    display_draw_string(spacing, spacing, "Hello World", &Font8, PINK, WHITE);
    display_draw_string(spacing, spacing, "Hello World", &Font8, BROWN, WHITE);
    display_draw_string(spacing, spacing, "Hello World", &Font8, TEAL, WHITE);

}

// drawChars
//
// Draw chars of different values, sizes, colors, and locations onto the screen
void drawChars() {
    // TODO: Put your code here
    display_init();
    display_draw_char(10, 10, 'M', &Font16, WHITE, BLACK);
    display_draw_char(25, 25, 'E', &Font12, WHITE, BLUE);
    display_draw_char(35, 35, 'O', &Font8, WHITE, RED);
    display_draw_char(40, 40, 'W', &Font8, WHITE, PURPLE);
    display_draw_char(10, 10, 'M', &Font8, WHITE, ORANGE);
    display_draw_char(100, 100, 'E', &Font12, WHITE, PINK);
    display_draw_char(90, 80, 'O', &Font16, WHITE, GREEN);
    display_draw_char(120, 5, 'W', &Font12, WHITE, TEAL);
    display_draw_char(15, 16, 'M', &Font12, WHITE, BROWN);
    display_draw_char(18, 100, 'E', &Font8, WHITE, VIOLET);
}

// drawStars
//
// Draw at least 20 stars on the screen
// TIP: Make a function that uses display_draw_# functions to make the shape of the star,
// Then call that function at multiple locations
void drawStar(uint16_t x_start, uint16_t y_start, uint16_t color, uint8_t line_weight, uint16_t scale){
    uint16_t x_end = x_start;
    uint16_t y_end = y_start;
    y_end = y_start + (2 * scale);
    x_end = x_start + (1 * scale);
    display_draw_line(x_start, y_start, x_end, y_end, color, line_weight);
    y_end = y_start - (2 * scale);
    x_end = x_start + (1 * scale);
    display_draw_line(x_start, y_start, x_end, y_end, color, line_weight);
    y_end = y_start + (0 * scale);
    x_end = x_start + (2 * scale);
    display_draw_line(x_start, y_start, x_end, y_end, color, line_weight);
    y_end = y_start - (1 * scale);
    x_end = x_start - (2 * scale);
    display_draw_line(x_start, y_start, x_end, y_end, color, line_weight);
    y_end = y_start - (2 * scale);
    x_end = x_start + (1 * scale);
    display_draw_line(x_start, y_start, x_end, y_end, color, line_weight);
    y_end = y_start + (1 * scale);
    x_end = x_start - (2 * scale);
    display_draw_line(x_start, y_start, x_end, y_end, color, line_weight);
    y_end = y_start - (1 * scale);
    x_end = x_start - (2 * scale);
    display_draw_line(x_start, y_start, x_end, y_end, color, line_weight);
    y_end = y_start + (2 * scale);
    x_end = x_start + (1 * scale);
    display_draw_line(x_start, y_start, x_end, y_end, color, line_weight);
    y_end = y_start + (2 * scale);
    x_end = x_start + (1 * scale);
    display_draw_line(x_start, y_start, x_end, y_end, color, line_weight);
    y_end = y_start + (1 * scale);
    x_end = x_start - (2 * scale);
    display_draw_line(x_start, y_start, x_end, y_end, color, line_weight);
    y_end = y_start + (0 * scale);
    x_end = x_start + (2 * scale);
}   

void drawStars() {
    // TODO: Put your code here
    display_init();
    drawStar(5, 5, RED, 1, 1);
    drawStar(56, 55, GREEN, 2, 3);
    drawStar(56, 55, ORANGE, 2, 5);
    drawStar(100, 100, BLUE, 1, 1);
    drawStar(102, 100, BLUE, 1, 1);
    drawStar(104, 100, BLUE, 1, 1);
    drawStar(106, 100, BLUE, 1, 1);
    drawStar(108, 100, BLUE, 1, 1);
    drawStar(109, 100, BLUE, 1, 1);
    drawStar(15, 100, BLUE, 1, 1);
    drawStar(20, 100, BLUE, 1, 1);
    drawStar(30, 100, BLUE, 1, 1);
    drawStar(60, 100, BLUE, 1, 1);
    drawStar(80, 100, BLUE, 1, 1);
    drawStar(90, 100, BLUE, 1, 1);
    drawStar(100, 90, BLUE, 1, 1);
    drawStar(100, 80, BLUE, 1, 1);
    drawStar(100, 70, BLUE, 1, 1);
    drawStar(100, 60, BLUE, 1, 1);
    drawStar(100, 50, BLUE, 1, 1);
    
    
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
        clearScreen();
        delay_ms(200);
        drawHelloWorld();
        delay_ms(200);
        drawChars();
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

//make test
// sudo ./main, sudo ./test