#ifndef LIFE_PNGOPERATOR_H
#define LIFE_PNGOPERATOR_H
#include "gameOperator.h"
/*
 * Function write generated files as PNG file
 *
 * Function return:
 *  0, if everything gone alright
 * -61 for error - can not open file for writting
 * -62 for error - png_create_write_struct failed
 * -63 for error - png_create_info_struct failed
 * -64 for error - error during init_io
 * -65 for error - error during writing header
 * -66 for error - error during writing bytes
 * -67 for error - error during end of write
 */
int printFile(char * fileName, gameBoard_t * gameBoard, int cellSize);
#endif //LIFE_PNGOPERATOR_H
