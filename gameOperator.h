//
// Created by Patryk on 2017-03-02.
//

#ifndef LIFE_GAMEOPERATOR_H
#define LIFE_GAMEOPERATOR_H
#include "gameSettings.h"
typedef struct gameBoard{
    int width;
    int height;
    int **fields; // Fields format [Row1][Row2][Row3] in one line
}   gameBoard_t;

int startGame(gameBoard_t * gameBoard, int boarderStart);
int gameSimulation( gameBoard_t * gameBoard, int countOfAdjacentCells, int setGenerations);
int checkCellMooreNeighborhood(int ** fields, int x, int y); //return 1 if ceil should be alive or 0 if ceil should be dead
int checkCellVonNeumannNeighborhood(int ** fields, int x, int y); // tak jak powyżej
#endif //LIFE_GAMEOPERATOR_H
