//
// Created by Patryk on 2017-03-03.
//

#ifndef LIFE_BOARDGANERATOR_H
#define LIFE_BOARDGANERATOR_H

#include "gameOperator.h"
int boardGenerator(gameBoard_t * gameBoard, int edgeSettings);
int setBorders(int boardSize,  int ** fields, int edgeSettings);

#endif //LIFE_BOARDGANERATOR_H
