#ifndef LIFE_BOARDGANERATOR_H
#define LIFE_BOARDGANERATOR_H

#include "gameOperator.h"
/*
 * Function to generate random board if program is launched without parameter -l (to load file)
 *
 * Function return:
 * 0, if everything gone alright,
 * -12 for memory exhaustion error
 */
int boardGenerator(gameBoard_t * gameBoard, int edgeSettings, int defaultBoardSize);
/*Function to generate borders. This function generate blank borders if value of edgeSettings equals 0, full if equals
    1, chessboard if equals 2
 */
void setBorders(int boardSize,  short ** fields, int edgeSettings);

#endif
