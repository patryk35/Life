#include "boardGenerator.h"
#include "errorsComunicats.h"
#include <stdlib.h>
#include <time.h>

int boardGenerator(gameBoard_t * gameBoard, int edgeSettings, int defaultBoardSize) {
    gameBoard->boardSize=defaultBoardSize;

    // malloc space for cells in array
    gameBoard->fields= malloc(sizeof(gameBoard->fields)* gameBoard->boardSize);
    if(gameBoard->fields == NULL)
        return MEMORY_EXHAUSTION;
    for(int i =0;i<gameBoard->boardSize;i++){
        gameBoard->fields[i]=malloc(sizeof(gameBoard->fields[i])* gameBoard->boardSize);
        if(gameBoard->fields[i] == NULL)
            return MEMORY_EXHAUSTION;
    }

    setBorders(gameBoard->boardSize, gameBoard->fields, edgeSettings);

    //generating random cells
    srand(time(NULL));
    for(int i = 1; i < gameBoard->boardSize - 1; i++)
        for(int j = 1; j < gameBoard->boardSize - 1; j++)
            gameBoard->fields[i][j] = (rand() % 4)== 1?1:0;
    return 0;
}
void setBorders(int boardSize,  short ** fields, int edgeSettings){
    if(edgeSettings == 0){ //blank borders
        for(int i=0; i< boardSize; i++)
        {
            fields[0][i]=0;
            fields[i][0]=0;
            fields[i][boardSize-1]=0;
            fields[boardSize-1][i]=0;
        }
    }else if(edgeSettings == 1){ //full borders
        for(int i=0; i< boardSize; i++)
        {
            fields[0][i]=1;
            fields[i][0]=1;
            fields[i][boardSize-1]=1;
            fields[boardSize-1][i]=1;
        }
    }else if(edgeSettings == 2){ //chessboard borders
        for(int i=0; i< boardSize; i++)
        {
            fields[0][i]=i%2;
            fields[i][0]=i%2;
            fields[i][boardSize-1]=(i+1)%2;
            fields[boardSize-1][i]=(i+1)%2;
        }
    }
}