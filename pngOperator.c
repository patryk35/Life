//
// Created by Patryk on 2017-03-02.
//

#include "pngOperator.h"
#include "gameOperator.h"
#include <stdio.h>
int printFile(char * fileName, gameBoard_t * gameBoard)
{
    int boardSize = gameBoard->boardSize;
    for(int k=1;k<boardSize-1;k++){
        for(int l=1;l<boardSize-1;l++){
            if(gameBoard->fields[k][l]== 1)
                printf(".");
            else
                printf(" ");
        }
        printf("\n");
    }
    printf("\n\n");
    /*printf("ME\n\n");
    for(int i=0;i<boardSize-0;i++){
        for(int j=0;j<boardSize-0;j++){
            printf("%d %c", gameBoard->fields[i][j], (j==(boardSize-1)?'\n':' '));
        }
    }
    printf("\n\n\n\n\n\n");*/
}