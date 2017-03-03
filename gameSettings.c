//
// Created by Patryk on 2017-03-02.
//
#include "gameSettings.h"

#include <stdio.h>
int loadGameSettings(char * fileName, gameSettings_t * settings)
{
    FILE * file = fopen(fileName,"r");
    settings->countOfAdjacentCells= 4; // liczba sąsiednich komórek opcej: 4 lub 8
    settings->isBoardLoaded=0; // jeżeli 1 to mamy wczytać plik z planszą, jeżeli 0  to losujemy jakąś plansze o wymiarach z settings->deflautBoardSize;
    settings->deflautBoardSize=10;
    settings->edgeSettings=1;


    fclose(file);
    return 0;
}