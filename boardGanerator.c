//
// Created by Patryk on 2017-03-03.
//

#include "boardGanerator.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int boardGenerator(gameBoard_t * gameBoard, int edgeSettings) {
    setBorders(gameBoard->boardSize,gameBoard->fields, edgeSettings);
    srand(time(NULL));
    for(int i=1;i<gameBoard->boardSize-1;i++){
        for(int j=1;j<gameBoard->boardSize-1;j++){
            gameBoard->fields[i][j]= rand()%2;
        }
    }
    /*   for(int i=1;i<gameBoard->boardSize-1;i++){
           for(int j=1;j<gameBoard->boardSize-1;j++){
               gameBoard->fields[i][j]=0;
           }
       }

       gameBoard->fields[1][8]=1;
       gameBoard->fields[1][9]=1;
       gameBoard->fields[2][6]=1;
       gameBoard->fields[2][11]=1;
       gameBoard->fields[3][5]=1;
       gameBoard->fields[3][12]=1;
       gameBoard->fields[4][4]=1;
       gameBoard->fields[4][13]=1;
       gameBoard->fields[5][4]=1;
       gameBoard->fields[5][13]=1;
       gameBoard->fields[6][4]=1;
       gameBoard->fields[6][13]=1;
       gameBoard->fields[7][5]=1;
       gameBoard->fields[7][12]=1;
       gameBoard->fields[8][6]=1;
       gameBoard->fields[8][11]=1;
       gameBoard->fields[9][8]=1;
       gameBoard->fields[9][9]=1;*/


}
/*
 *
 * Dopisać opcje wyboru jakie granice
 *
 *
 */
int setBorders(int boardSize,  int ** fields, int edgeSettings){
    if(edgeSettings == 0){ //granice puste
        for(int i=0; i< boardSize; i++)
        {
            fields[0][i]=0;
            fields[i][0]=0;
            fields[i][boardSize-1]=0;
            fields[boardSize-1][i]=0;
        }
    }else if(edgeSettings == 1){ //granice pełne
        for(int i=0; i< boardSize; i++)
        {
            fields[0][i]=1;
            fields[i][0]=1;
            fields[i][boardSize-1]=1;
            fields[boardSize-1][i]=1;
        }
    }else if(edgeSettings == 2){ //granice szachownica
        for(int i=0; i< boardSize; i++)
        {
            fields[0][i]=i%2;
            fields[i][0]=i%2;
            fields[i][boardSize-1]=(i+1)%2;
            fields[boardSize-1][i]=(i+1)%2;
        }
    }else if(edgeSettings == 3){ //granice przenoszone góra-dół, lewa-prawa
        for(int i=0; i< boardSize; i++)
        {
            fields[0][i]=i%2;
            fields[i][0]=i%2;
            fields[i][boardSize-1]=(i+1)%2;
            fields[boardSize-1][i]=(i+1)%2;
        }
    }else
        return -1;

}