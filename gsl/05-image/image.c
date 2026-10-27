/*
This is the driver file for the image library. All function definitions live in here
*/

#include <stdlib.h>
#include <string.h>

#include "image.h"

// --------------------------------------------------------------------------
// Image loading/saving functions
// --------------------------------------------------------------------------

uint8_t load_img(char *filepath, Bitmap *bmp) {
    // Opens file if it exists
    if (!(bmp->img = fopen(filepath, "r"))) {
        return LOAD_ERROR;
    }

    // Read in the bitmap file header
    fread(bmp->file_header, sizeof(uint8_t), BMP_FILE_HEADER_SIZE, bmp->img);

    // Get filesize
    bmp->file_size = (bmp->file_header[5] << 8 * 3) | (bmp->file_header[4] << 8 * 2) |
                     (bmp->file_header[3] << 8 * 1) | (bmp->file_header[2]);

    // Get start location of pixel data
    bmp->pxl_data_offset = (bmp->file_header[13] << 8 * 3) | (bmp->file_header[12] << 8 * 2) |
                           (bmp->file_header[11] << 8 * 1) | (bmp->file_header[10]);

    // Get DIB header data
    uint8_t dib_header_size = bmp->pxl_data_offset - BMP_FILE_HEADER_SIZE;
    bmp->dib_header = (uint8_t *)malloc((dib_header_size) * sizeof(uint8_t));
    fread(bmp->dib_header, sizeof(uint8_t), dib_header_size, bmp->img);

    // Get image width
    bmp->img_width = (bmp->dib_header[7] << 8 * 3) | (bmp->dib_header[6] << 8 * 2) |
                     (bmp->dib_header[5] << 8 * 1) | (bmp->dib_header[4]);

    // Get image height
    bmp->img_height = (bmp->dib_header[11] << 8 * 3) | (bmp->dib_header[10] << 8 * 2) |
                      (bmp->dib_header[9] << 8 * 1) | (bmp->dib_header[8]);

    // Get image data
    bmp->pxl_data_size = bmp->img_width * bmp->img_height * 3;
    bmp->pxl_data = (uint8_t *)malloc(sizeof(uint8_t) * bmp->pxl_data_size);
    fread(bmp->pxl_data, sizeof(uint8_t), bmp->pxl_data_size, bmp->img);

    // Create copy of image data for reset
    bmp->pxl_data_cpy = (uint8_t *)malloc(sizeof(uint8_t) * bmp->pxl_data_size);
    bmp->pxl_data_cpy = memcpy(bmp->pxl_data_cpy, bmp->pxl_data, bmp->pxl_data_size);

    // Close the file
    fclose(bmp->img);

    return LOAD_SUCCESS;
}

void reset_pixel_data(Bitmap *bmp) {
    bmp->pxl_data = memcpy(bmp->pxl_data, bmp->pxl_data_cpy, bmp->pxl_data_size);
}

uint8_t save_img(char *imgname, Bitmap *bmp) {
    FILE *save_img;
    if (!(save_img = fopen(imgname, "w"))) {
        fprintf(stderr, "Could not save the file with that name. Change the name and try again.\n");
        return SAVE_ERROR;
    }

    // Write BMP header
    fwrite(bmp->file_header, sizeof(uint8_t), BMP_FILE_HEADER_SIZE, save_img);

    // Write DIB header
    fwrite(bmp->dib_header, sizeof(uint8_t), bmp->pxl_data_offset - BMP_FILE_HEADER_SIZE, save_img);

    // Write pixel data
    fwrite(bmp->pxl_data, sizeof(uint8_t), bmp->pxl_data_size, save_img);

    // Close the file
    fclose(save_img);
    return SAVE_SUCCESS;
}

void close_img(Bitmap *bmp) {
    free(bmp->dib_header);
    free(bmp->pxl_data);
    free(bmp->pxl_data_cpy);
}

// --------------------------------------------------------------------------
// Image manipulation functions
// --------------------------------------------------------------------------

void remove_color_channel(Color color, Bitmap *bmp) {
    // Put code here
    uint32_t area = bmp->img_height * bmp->img_width;
    if(color == GREEN_CHANNEL){
        for(int i = 0; i <= area ; i++){
        bmp->pxl_data[i*3+1] = 0;}
    }
    else if (color == BLUE_CHANNEL){
        for(int i = 0; i <= area ; i++){
        bmp->pxl_data[i*3] = 0;}
    }
    else if(color == RED_CHANNEL){
        for(int i = 0; i <= area ; i++){
        bmp->pxl_data[i*3+2] = 0;}
    }
    
}

void grayscale(Bitmap *bmp) {
    // Put code here
        uint32_t area = bmp->img_height * bmp->img_width;
        for(int i = 0; i <= area ; i++){
            double Y = (bmp->pxl_data[i*3+2] * 0.299) + (bmp->pxl_data[i*3+1] * 0.587) + (bmp->pxl_data[i*3] * 0.114);

            bmp->pxl_data[i*3+2] = Y;
            bmp->pxl_data[i*3+1] = Y;
            bmp->pxl_data[i*3] = Y;
        }
    }
    


void or_filter(Bitmap *bmp) {
    // Put code here
    uint32_t area = bmp->img_height * bmp->img_width;
    for(int i = 0; i <= area ; i++){
        uint8_t top = 0; 
        uint8_t bottom = 0;





        //red   
        uint8_t red = bmp->pxl_data[i*3+2]; 
        uint8_t red_top = bmp->pxl_data[(i*3+2)+bmp->img_width*3];
        uint8_t red_bottom = bmp->pxl_data[(i*3+2)+bmp->img_width*3];
        if(red_top > area){
            red_top = top;
        }
        else if(red_bottom < 0){
            red_bottom = bottom;
        }
        uint8_t red_value = red | red_top | red_bottom;
        bmp->pxl_data[i*3+2] = red_value;






        //green
        uint8_t green = bmp->pxl_data[i*3+1]; 
        uint8_t green_top = bmp->pxl_data[(i*3+1)+bmp->img_width*3];
        uint8_t green_bottom = bmp->pxl_data[(i*3+1)+bmp->img_width*3];
        if(green_top > area){
            green_top = top;
        }
        else if(green_bottom < 0){
            green_bottom = bottom;
        }
        uint8_t green_value = green | green_top | green_bottom;
        bmp->pxl_data[i*3+1] = green_value;





        //blue
        uint8_t blue = bmp->pxl_data[i*3];
        uint8_t blue_top = bmp->pxl_data[(i*3)+bmp->img_width*3];
        uint8_t blue_bottom = bmp->pxl_data[(i*3)+bmp->img_width*3];
        if(blue_top > area){
            blue_top = top;
        }
        else if(blue_bottom < 0){
            blue_bottom = bottom;
        }
        uint8_t blue_value = blue | blue_top | blue_bottom;
        bmp->pxl_data[i*3] = blue_value;
        




        
    }
}

