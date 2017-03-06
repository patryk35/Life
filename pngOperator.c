#include "gameOperator.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <png.h>


int printFile(char * fileName, gameBoard_t * gameBoard, int cellSize) {
    int pictureSize=(gameBoard->boardSize-2)*cellSize;
    png_byte color_type = PNG_COLOR_TYPE_GRAY;
    png_byte bit_depth = 8;
    png_structp png_ptr;
    png_infop info_ptr;
    png_bytep * row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * pictureSize);
    FILE *file = fopen(fileName, "wb");
    if (file == NULL)
        return -61;     //Error: can not open file for writting

    for (int y=0; y<pictureSize; y++)
        row_pointers[y] = (png_byte*) malloc(sizeof(png_byte) * pictureSize);
    for (int y=0; y<pictureSize; y++) {
        png_byte* row = row_pointers[y];
        for (int x=0; x<pictureSize; x++) {
            row[x] = gameBoard->fields[(y+cellSize)/cellSize][(x+cellSize)/cellSize] ? 0 : 255;
        }
    }

    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr)
        return -62;     //Error:  png_create_write_struct failed

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
        return -63;     //Error:  png_create_info_struct failed

    if (setjmp(png_jmpbuf(png_ptr)))
        return -64;     //Error: error during init_io

    png_init_io(png_ptr, file);
    if (setjmp(png_jmpbuf(png_ptr)))
        return -65;     //Error: error during writing header

    png_set_IHDR(png_ptr, info_ptr, pictureSize, pictureSize,
                 bit_depth, color_type, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(png_ptr, info_ptr);
    if (setjmp(png_jmpbuf(png_ptr)))
        return -66;     //Error: error during writing bytes

    png_write_image(png_ptr, row_pointers);
    if (setjmp(png_jmpbuf(png_ptr)))
        return -67;     //Error: error during end of write

    png_write_end(png_ptr, NULL);

    for (int y=0; y<pictureSize; y++)
        free(row_pointers[y]);
    free(row_pointers);
    fclose(file);
}