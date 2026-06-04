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
#define BUFFERSIZEMEOW 60000

void clearScreen() {
    // TODO: Put your code here
    display_clear(WHITE);
}

uint32_t getStringLength(char string[]) {
    // TODO: Implement this function
    int j = 0;
    int length = 0;
    while(string[j]){
        length++;
        j++;
    }
    return length;
}


int64_t findLastChar(char charToFind, char string[]) {
    // TODO: Implement this function
    int64_t len = getStringLength(string);
    for(int64_t i = len -1; i >= 0; i--){
        if(string[i] == charToFind){
            return i;
        }
    }
    return -1;
}

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
    //add / back if it doesn't work

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
int get_entries(char *folder, char entries[MAX_ENTRIES][MAX_FILE_NAME]) {
    // TODO: Put your code here
    DIR *dp;
    dp = opendir(folder);
    char extension[20];

    if(dp == NULL){
        closedir(dp);
        return -1;
    }

    struct dirent * entry;
    int i = 0;
    while((entry = readdir(dp)) != NULL){
        getFileExtension(extension, entry->d_name);
        if (strcmp(extension, "log") == 0 || strcmp(extension, "bmp") == 0) {
        strncpy(entries[i], entry->d_name, MAX_FILE_NAME);
        i++;
        }
    }
    closedir(dp);
    return i;
}

/*
 * Draws the menu of the screen. It uses the entries array to create the menu, with the num_entries
 * specifying how many entries are in the entries array. The selected parameter is the item in the
 * menu that is selected and should be highlighted. Use BACKGROUND_COLOR, FONT_COLOR,
 * SELECTED_BG_COLOR, and SELECTED_FONT_COLOR to help specify the colors of the background, font,
 * select bar color, and selected text color.
 */
void drawMenu(char entries[][MAX_FILE_NAME], int num_entries, int selected) {
    // TODO: Put your code here
    uint16_t spacing = 12;
    uint16_t y_spacing = 12;
    uint8_t i = 0;
    display_draw_rectangle(0,0,128,128, WHITE, true, 2);
    while(i < num_entries){
        if(selected == i){
            display_draw_rectangle(0, (y_spacing*i) + 12, 128, (y_spacing*i) + 24, BLUE, true, 1);
            display_draw_string(spacing, (y_spacing * i) + 12, entries[i], &Font12, BLUE, WHITE);
        }
        else{
        display_draw_string(spacing, (y_spacing * i) + 12, entries[i], &Font12, WHITE, BLACK);
            }
        i++;
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
    char path[MAX_FILE_NAME];
    char extension[MAX_FILE_NAME];
    combinePath(path, folder, file_name);
    getFileExtension(extension, path);

     if(strcmp(extension, "log")== 0){
        FILE *fp;
        fp = fopen(path, "r");
        char contents[MAX_FILE_NAME];
        int result = 0;
        result = fread(contents, 1, 100, fp);
        contents[result] = '\0';
        display_draw_string(12, 12, contents, &Font12, WHITE, BLACK);
     }
     
    else if(strcmp(extension, "bmp")== 0){
        display_draw_image(path);
        }
    }

    
    void camera_menu(uint8_t *buf, Bitmap bmp){
    while(true){
        
            if(button_right() == 0){
                clearScreen();
                delay_ms(200);
                Bitmap temp1 = bmp;
                create_bmp(&temp1, buf);
                remove_color_channel(RED_CHANNEL, &temp1);
                display_draw_image_data(temp1.pxl_data, 128, 128);
                destroy_bmp(&temp1);
                while(button_right() == 0){
                    delay_ms(1);
                }
            }

            if(button_left() == 0){ 
                clearScreen();
                delay_ms(200);
                Bitmap temp2 = bmp;
                create_bmp(&temp2, buf);
                remove_color_channel(BLUE_CHANNEL, &temp2);
                display_draw_image_data(temp2.pxl_data, 128, 128);
                destroy_bmp(&temp2);

                while(button_left() == 0){
                    delay_ms(1);
                }
            }

            if(button_up() == 0){
                clearScreen();
                delay_ms(200);
                Bitmap temp3 = bmp;
                create_bmp(&temp3, buf);
                remove_color_channel(GREEN_CHANNEL, &temp3);
                display_draw_image_data(temp3.pxl_data, 128, 128);
                destroy_bmp(&temp3);

                while(button_up() == 0){
                    delay_ms(1);
                }
            }

            if(button_down() == 0){
                clearScreen();
                delay_ms(200);
                Bitmap temp4 = bmp;
                create_bmp(&temp4, buf);
                or_filter(&temp4);
                display_draw_image_data(temp4.pxl_data, 128, 128);
                destroy_bmp(&temp4);

                while(button_down() == 0){
                    delay_ms(1);
                }
            }

            if(button_center() == 0){
                delay_ms(200);
                clearScreen();

                const Config con = {"2240", "ecen224.byu.edu", buf, BUFFERSIZEMEOW,"AC61BDF31"};
                int sockfd = client_connect(&con);
                client_send_image(sockfd, &con);
                client_receive_response(sockfd);
                client_close(sockfd);
                
                while(button_center() == 0){
                    delay_ms(1);
                }
                break;
            }
            
        }
        
    }
    
    int main(void) {
        
        signal(SIGINT, intHandler);
        
        log_info("Starting...");
        
        // Use this to fill in with entries from the directory
        int i = 0;
        char entries[MAX_ENTRIES][MAX_FILE_NAME];
        
        size_t bufsize = 128 * 128 * 3 + 14;
        uint8_t *buf = malloc(sizeof(uint8_t) * bufsize);
    //main
    
    // TODO: Initialize the hardware
    display_init();
    buttons_init();
    
    // TODO: Get directory contents using get_entries function
    int num_entries = get_entries(VIEWER_FOLDER, entries);
    // TODO: Draw menu using draw_menu function
    drawMenu(entries, num_entries, i);
    
    
    while (true) {
        
        if (button_down() == 0) {
            // Do something upon detecting button press
            i++;
            if(i > (num_entries - 1)){
                i = 0;
            }
            clearScreen();
            drawMenu(entries, num_entries, i);
            
            while(button_down() == 0) {
                // Delay while the button is pressed to avoid repeated actions
                delay_ms(1);
            }
            
        }
        
        if (button_up() == 0) {
            // Do something upon detecting button press
            i--;
            if(i < 0){
                i = (num_entries - 1);
            }
            clearScreen();
            drawMenu(entries, num_entries, i);
            
            while(button_up() == 0) {
                // Delay while the button is pressed to avoid repeated actions
                delay_ms(1);
            }
            
        }
        
        if (button_right() == 0) {
            // Do something upon detecting button press
            clearScreen();
            delay_ms(200);
            draw_file(VIEWER_FOLDER, entries[i]);
            
            
            delay_ms(1200);
            clearScreen();
            drawMenu(entries, MAX_ENTRIES, i);
            
            while(button_right() == 0) {
                // Delay while the button is pressed to avoid repeated actions
                delay_ms(1);
            }
            
        }
        
        
        
        
        if (button_center() == 0) {
            // Do something upon detecting button press
            clearScreen();
            display_draw_string(0, 16, "Picture Picture :)", &Font16, BLACK, WHITE);
            delay_ms(400);
            camera_capture_data(buf, bufsize);
            
            Bitmap bmp;
            create_bmp(&bmp, buf);
            display_draw_image_data(bmp.pxl_data, bmp.img_width, bmp.img_height);
            
            camera_menu(buf, bmp);
            
            camera_save_to_file(buf, bufsize, "viewer/doorbell.bmp");
            destroy_bmp(&bmp);
            
            drawMenu(entries, MAX_ENTRIES, i);
            
            
            while(button_center() == 0) {
                // Delay while the button is pressed to avoid repeated actions
                delay_ms(1);
            }
        }
        
        
    }
    
    free(buf);
    return 0;
}


// make test
//  sudo ./main, sudo ./test