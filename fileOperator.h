#ifndef LIFE_FILEOPERATOR_H
#define LIFE_FILEOPERATOR_H

#include "gameOperator.h"
/*
 * Function read cells from file and save it in as fields in gameBoard
 *
 * Function return:
 *  0, if everything gone alright
 * -21 for error - can not open file
 * -22 for error - can not read size value
 * -23 for error - memory exhaustion
 * -24 for error - can not read cells value
 */
int readFile(char * fileName, gameBoard_t * gameBoard, int edgeSettings);
/*Function write generation configuration for file ,life
 * Function return:
 *  0, if everything gone alright,
 * -31 for error - can not open file
 */
int writeFile(char * fileName, gameBoard_t * gameBoard);
/* Function create new directory */
void newDirectory(char * name);
#endif //LIFE_FILEOPERATOR_H
