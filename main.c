#include <dirent.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "lib/buttons.h"
#include "lib/camera.h"
#include "lib/client.h"
#include "lib/colors.h"
#include "lib/device.h"
#include "lib/display.h"
#include "lib/fonts/fonts.h"
#include "lib/image.h"
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

// Makes sure to deinitialize everything before program close
void intHandler(int dummy) {
    log_info("Exiting...");
    display_exit();
    exit(0);
}

void getFileExtension(char extension[], char fileName[]) {
    // TODO: Implement this function
    int64_t index = findLastChar('.', fileName);
    int i = index + 1; 
    int j = 0;
    while(fileName[i] != '\0'){
        extension[j] = fileName[i];
        j++;
        i++;
    }
    extension[j] = '\0';

}

void combinePath(char path[], char folderName[], char fileName[]) {
    // TODO: Implement this function 
    int i = 0;
    int j = 0;
    int k = 0;
    while(folderName[i] != '\0'){
        path[j] = folderName[i];
        j++;
        i++;
    }
    path[j] = '/';
    j++; 
    
    while(fileName[k] != '\0'){
        path[j] = fileName[k];
        j++;
        k++;
    }

    path[j] = '\0';
}

/*
 * Takes in a folder, reads the contents of the folder, filtering out any files that do not end with
 * .log or .bmp. This function should check to make sure the folder exists. It fills in the entries
 * array with all of the entries in the folder, up to 8 (MAX_ENTRIES). The function returns the
 * number of entries it put into the entries array.
 */
int get_entries(char *folder, char entries[][MAX_FILE_NAME]) {
    // TODO: Put your code here
    DIR *dp;
    dp = opendir(folder);

    if(dp == NULL){
        return -1;
    }
    struct dirent * entry;
    while((entry = readdir(dp) != NULL)){
        getFileExtension(entry->d_name);
    }


    int i = 0;
    while(i < MAX_ENTRIES){
        
    }


    closedir(dp);
    return -1;
}

/*
 * Draws the menu of the screen. It uses the entries array to create the menu, with the num_entries
 * specifying how many entries are in the entries array. The selected parameter is the item in the
 * menu that is selected and should be highlighted. Use BACKGROUND_COLOR, FONT_COLOR,
 * SELECTED_BG_COLOR, and SELECTED_FONT_COLOR to help specify the colors of the background, font,
 * select bar color, and selected text color.
 */
void draw_menu(char entries[][MAX_FILE_NAME], int num_entries, int selected) {
    // TODO: Put your code here
    uint16_t spacing = 12;
    uint16_t y_spacing = 12;
    int i = 0;
    if(selected > num_entries){
        selected = 0;
    }
    while(entries[i] != '\0'){
        if(selected == i){
            display_draw_string(spacing, (y_spacing * i), entries[i], &Font12, BLUE, WHITE);
        }
        else{
        display_draw_string(spacing, (y_spacing * i), entries[i], &Font12, WHITE, BLACK);
        i++;
        }
    }
}

/*
 * Displays an image or a log file. This function detects the type of file that should be draw. If
 * it is a bmp file, then it calls display_draw_image. If it is a log file, it opens the file, reads
 * 100 characters (MAX_TEXT_SIZE), and displays the text using display_draw_string. Combine folder
 * and file_name to get the complete file path.
 */
void draw_file(char *folder, char *file_name) {
    // TODO: Put your code here
}

int main(void) {

    signal(SIGINT, intHandler);

    log_info("Starting...");

    // Use this to fill in with entries from the directory
    char entries[MAX_ENTRIES][MAX_FILE_NAME];

    // TODO: Initialize the hardware
    display_init();
    buttons_init();

    // TODO: Get directory contents using get_entries function

    // TODO: Draw menu using draw_menu function

    while (true) {
        delay_ms(200);

        // TODO: Put button logic here

        // Example of how to interact with a button
        if (button_up() == 0) {
            // Do something upon detecting button press

            while (button_up() == 0) {
                // Delay while the button is pressed to avoid repeated actions
                delay_ms(1);
            }
        }
    }
    return 0;
}
