
/*
Lab 4 - Image
*/

#include <stdint.h>
#include <stdio.h>

#define LOAD_ERROR 1
#define LOAD_SUCCESS 0
#define BMP_FILE_HEADER_SIZE 14
#define SAVE_ERROR 1
#define SAVE_SUCCESS 0

// Pixels in a bitmap file are arranged in the following format. Each pixel is
// three bytes of data, ordered by blue, green, red, with each color as one
// byte.
//
//               pixel x                   pixel x+1
//                   |                          |
//     +-------------+------------+-------------+------------+
//     v                          v                          v
//     +--------+--------+--------+--------+--------+--------+
// ... |   B    |   G    |   R    |   B    |   G    |   R    | ...
//     +--------+--------+--------+--------+--------+--------+
//       1 byte   1 byte   1 byte   1 byte   1 byte   1 byte
//
// To access the blue color in the xth pixel, you would index into pixel data by
// x * 3. To access the green color in the xth pixel, you would index into the
// pixel data by x * 3 + 1. To access the red color in the xth pixel, you would
// index into the pixel data by x * 3 + 2.

typedef enum Color { BLUE_CHANNEL, GREEN_CHANNEL, RED_CHANNEL } Color;

typedef struct {
    FILE *img;
    uint8_t file_header[BMP_FILE_HEADER_SIZE]; // 14 bytes
    uint8_t *dib_header;                       // Variable
    uint8_t *pxl_data;                         // Pixel data for image
    uint8_t *pxl_data_cpy;                     // Copy of pixel data
    uint8_t pxl_data_offset;                   // Location of pxl data in img
    uint32_t img_width;                        // Image width
    uint32_t img_height;                       // Image height
    uint32_t file_size;                        // Size of the file
    uint32_t pxl_data_size;                    // Size of pixel data array
} Bitmap;

// --------------------------------------------------------------------------
// Image loading/saving functions
// --------------------------------------------------------------------------

// Loads a Bitmap file into the bitmap structure. This function returns 1
// (LOAD_ERROR) if there is an error and 0 (LOAD_SUCCESS) if the image was
// loaded successfully.
//
//  filepath - The name of the file that should be loaded. This file should be a
//      bmp file type.
//  bmp - A pointer to the Bitmap structure that will be populated.
uint8_t load_img(char *filepath, Bitmap *bmp);

// Resets the bitmap data to its original state. This should be used after
// modifying and saving the bitmap data to get the image back into its original
// state.
//
//  bmp - A pointer to Bitmap structure.
void reset_pixel_data(Bitmap *bmp);

// Saves the bitmap to a file. Returns an error code to indicate success or
// error.
//
//  imgname - The name of the file that should be saved. This should be
//      different from the original file or else the original file will be
//      overridden.
//  bmp - A pointer to Bitmap structure.
uint8_t save_img(char *imgname, Bitmap *bmp);

// Closes the image file and frees the memory allocated for the bitmap structure.
//
//  bmp - A pointer to the Bitmap structure.
void close_img(Bitmap *bmp);

// --------------------------------------------------------------------------
// Image manipulation functions
// --------------------------------------------------------------------------

// Removes the indicated color from the bitmap data.
//
//  color - The color that should be removed (RED, GREEN, or BLUE)
//  bmp - A pointer to the Bitmap structure that contains the bitmap data
void remove_color_channel(Color color, Bitmap *bmp);

// Grayscales the bitmap image using the following equation:
//
// Y = 0.299 R + 0.587 G + 0.114 B
//
// And Y replaces the old values of R, G, and B.
//
//  bmp - A pointer to the Bitmap structure that contains the bitmap data
void grayscale(Bitmap *bmp);

// Filters the image by or'ing vertically adjacent pixels in the bitmap data. For
// a given pixel, x, this function will OR the top and bottom pixels with x.
// Using the diagram below, the equation will be x | T | B. This function
// handles when on the top and bottom rows of the image.
//   +-+
//   |T|
// +-+-+-+
// |L|x|R|
// +-+-+-+
//   |B|
//   +-+
//
//  bmp - A pointer to the Bitmap structure that contains the bitmap data
void or_filter(Bitmap *bmp);
