#include "gameOperator.h"
#include "errorsComunicats.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <png.h>


int printFile(char * fileName, gameBoard_t * gameBoard, int cellSize) {
    int pictureSize=(gameBoard->boardSize-2)*(cellSize) + gameBoard->boardSize-3; // gameBoard->boardSize-3
                                                                                  // to set space between cells
    png_byte color_type = PNG_COLOR_TYPE_GRAY;
    png_byte bit_depth = 8;
    png_structp png_ptr;
    png_infop info_ptr;
    png_bytep * row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * pictureSize);
    FILE *file = fopen(fileName, "wb");
    int spacesX;//counter of spaces between cells on axis X
    int spacesY;//counter of spaces between cells on axis Y

    if(file == NULL)
        return PNG_CAN_NOT_OPEN;

    for(int y=0; y<pictureSize; y++)
        row_pointers[y] = (png_byte*) malloc(sizeof(png_byte) * pictureSize);


    spacesY=0;
    for(int y=0; y<pictureSize; y++) {
        png_byte* row = row_pointers[y];
        if(y%(cellSize+1)==cellSize){ // if it is true - set spaces
            for(int x=0; x<pictureSize; x++)
                row[x]=255;
            spacesY++;
        }else{
            spacesX=0;
            for(int x=0; x<pictureSize; x++){
                if(x%(cellSize+1)==cellSize){// if it is true - set spaces
                    row[x]=255;
                    spacesX++;
                }
                else
                    row[x] = gameBoard->fields[(y-spacesY+cellSize)/cellSize][(x-spacesX+cellSize)/cellSize] ? 0 : 255;
            }
        }
    }

    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if(!png_ptr)
        return PNG_CREATE_WRITE_STRUCT_FAILED;

    info_ptr = png_create_info_struct(png_ptr);
    if(!info_ptr)
        return PNG_CREATE_INFO_STRUCT_FAILED;

    if(setjmp(png_jmpbuf(png_ptr)))
        return PNG_INIT_TO_ERROR;

    png_init_io(png_ptr, file);
    if(setjmp(png_jmpbuf(png_ptr)))
        return PNG_WRITTING_HEADRE_WRITE;

    png_set_IHDR(png_ptr, info_ptr, pictureSize, pictureSize,
                 bit_depth, color_type, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(png_ptr, info_ptr);
    if(setjmp(png_jmpbuf(png_ptr)))
        return PNG_WRITING_BYTES;

    png_write_image(png_ptr, row_pointers);
    if(setjmp(png_jmpbuf(png_ptr)))
        return PNG_END_OF_WRITE_ERROR;

    png_write_end(png_ptr, NULL);

    for(int y=0; y<pictureSize; y++)
        free(row_pointers[y]);
    free(row_pointers);
    fclose(file);
}