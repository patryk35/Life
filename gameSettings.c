//
// Created by Patryk on 2017-03-02.
//
#include "gameSettings.h"

#include <stdio.h>
int loadGameSettings(char * fileName, gameSettings_t * settings)
{
    FILE * file = fopen(fileName,"r");
    settings->countOfAdjacentCells= 8;
    settings->boardStart=1;
    settings->edgeSettings=1;


/* boarderStart 1- for new, 2 - for load
 * if()
    {

    }else if(){

    }else{

    }*/
    fclose(file);
    return 0;
}