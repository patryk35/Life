//
// Created by Patryk on 2017-03-02.
//
/*
#include "pngOperator.h"
#include "gameOperator.h"
#include <stdio.h>


int printFile(char * fileName, gameBoard_t * gameBoard)
{
    int boardSize = gameBoard->boardSize;
    for(int k=1;k<boardSize-1;k++){
        for(int l=1;l<boardSize-1;l++){
            if(gameBoard->fields[k][l]== 1)
                printf(".");
            else
                printf(" ");
        }
        printf("\n");
    }
    printf("\n\n");
    /*printf("ME\n\n");
    for(int i=0;i<boardSize-0;i++){
        for(int j=0;j<boardSize-0;j++){
            printf("%d %c", gameBoard->fields[i][j], (j==(boardSize-1)?'\n':' '));
        }
    }
    printf("\n\n\n\n\n\n");
}*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <png.h>
#include "gameOperator.h"

void printFile(char * fileName, gameBoard_t * gameBoard, int cellSize) {
    int pictureSize=(gameBoard->boardSize-2)*cellSize;
    png_byte color_type = PNG_COLOR_TYPE_GRAY;
    png_byte bit_depth = 8;
    png_structp png_ptr;
    png_infop info_ptr;
    int number_of_passes = 7;
    png_bytep * row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * pictureSize);

    for (int y=0; y<pictureSize; y++)
        row_pointers[y] = (png_byte*) malloc(sizeof(png_byte) * pictureSize);

    for (int y=0; y<pictureSize; y++) {
        png_byte* row = row_pointers[y];
        for (int x=0; x<pictureSize; x++) {
            row[x] = gameBoard->fields[(y+16)/cellSize][(x+16)/cellSize]? 0 : 255;
        }
    }


    FILE *fp = fopen(fileName, "wb");
    if (!fp)
        printf("[write_png_file] File %s could not be opened for writing", fileName);
    int inn = sqrt(2);
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png_ptr)
        printf("[write_png_file] png_create_write_struct failed");

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
        printf("[write_png_file] png_create_info_struct failed");

    if (setjmp(png_jmpbuf(png_ptr)))
        printf("[write_png_file] Error during init_io");

    png_init_io(png_ptr, fp);

    if (setjmp(png_jmpbuf(png_ptr)))
        printf("[write_png_file] Error during writing header");

    png_set_IHDR(png_ptr, info_ptr, pictureSize, pictureSize,
                 bit_depth, color_type, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(png_ptr, info_ptr);

    if (setjmp(png_jmpbuf(png_ptr)))
        printf("[write_png_file] Error during writing bytes");

    png_write_image(png_ptr, row_pointers);

    if (setjmp(png_jmpbuf(png_ptr)))
        printf("[write_png_file] Error during end of write");

    png_write_end(png_ptr, NULL);

    for (int y=0; y<pictureSize; y++)
        free(row_pointers[y]);
    free(row_pointers);

    fclose(fp);
}