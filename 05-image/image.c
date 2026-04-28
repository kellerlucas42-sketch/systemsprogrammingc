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
}

void grayscale(Bitmap *bmp) {
    // Put code here
}

void or_filter(Bitmap *bmp) {
    // Put code here
}
