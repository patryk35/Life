#ifndef LIFE_GAMEOPERATOR_H
#define LIFE_GAMEOPERATOR_H
#include "gameSettings.h"
typedef struct gameBoard{
    int boardSize;
    short **fields;
}   gameBoard_t;

/* Function create new Board according settings
 *
 * Function return:
 *  0, if everything gone alright
 * -12 for function "boardGenerator" error
 *  values from -21 to -24 for function "readFile" errors
 */
int createBoard(gameBoard_t * gameBoard, gameSettings_t  settings, char * boardName, char * loadName);

/* Function do John Conway's Game of Life simulation
 *
 * Function return:
 *  0, if everything gone alright
 * -41 for memory exhaustion error
 * -31 for function "writeFile" error
 * values from -61 to -67 for function "readFile" errors
 */
int gameSimulation( gameBoard_t * gameBoard, gameSettings_t settings, int generationsCount,char * boardName);

/* Function return count of life cells around the cell on position (x,y) using Moore Neighborhood*/
int checkCellMooreNeighborhood(short ** fields, int x, int y);

/* Function return count of life cells around the cell on position (x,y) using VonNeumann Neighborhood*/
int checkCellVonNeumannNeighborhood(short ** fields, int x, int y);

/*Function analise if ceil wihth is alive will be dead in next generation or if dead cell will be alive in next generation*/
int checkAlive(int aliveNeighbours, int isAlive);

/*Function finding name for PNG files */
void findFileName(char* prefix, int counter, char * source);
/*Function to free space of old generation cells */
void freeFields(gameBoard_t *  gameBoard);
#endif //LIFE_GAMEOPERATOR_H
