//
// Created by Patryk on 2017-03-03.
//

#include "boardGanerator.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int boardGenerator(gameBoard_t * gameBoard)
{
    setBorders(gameBoard->boardSize,gameBoard->fields);
    srand(time);
    for(int i=1;i<gameBoard->boardSize-1;i++){
        for(int j=1;j<gameBoard->boardSize-1;j++){
            gameBoard->fields[i][j]= rand()%2;
        }
    }
}
/*
 *
 * Dopisać opcje wyboru jakie granice
 *
 *
 */
int setBorders(int boardSize,  int ** fields){
    for(int i=0; i< boardSize; i++)
    {
        fields[0][i]=0;
        fields[i][0]=0;
        fields[0][boardSize-1]=0;
        fields[boardSize-1][0]=0;
    }
}