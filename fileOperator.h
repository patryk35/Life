#ifndef LIFE_FILEOPERATOR_H
#define LIFE_FILEOPERATOR_H

#include "gameOperator.h"
/*Function read cells from file and save it in as fields in gameBoard*/
int readFile(char * fileName, gameBoard_t * gameBoard, int edgeSettings);
/*Function write generation configuration for file ,life*/
int writeFile(char * fileName, gameBoard_t * gameBoard);
/* Function create new directory */
void newDirectory(char * name);
#endif //LIFE_FILEOPERATOR_H
