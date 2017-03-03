//
// Created by Patryk on 2017-03-02.
//

#include "gameOperator.h"
#include "pngOperator.h"
#include "boardGanerator.h"
#include "fileRead.h"
#include <stdlib.h>
/*
 * Error List
 * -1 - [gameOperator] SettingsError -
 * -2
 */

int startGame(gameBoard_t * gameBoard, int isBoardLoaded){
    gameBoard->fields= malloc(sizeof(gameBoard->fields)* gameBoard->boardSize);
    for(int i =0;i<gameBoard->boardSize;i++){
        gameBoard->fields[i]=malloc(sizeof(gameBoard->fields[i])* gameBoard->boardSize);
    }
    if(isBoardLoaded == 1){
        /*
         *
         *
         *
         *
         */
        readFile("");
    }else if(isBoardLoaded == 0){
        boardGenerator(gameBoard);
    }else{
        return -1;
    }

    /*
     *
     *
     * granice to 0,0 0,1 0,2 0,3 1,0 , itp, tu zrobic ich obsluge, pamietac ze zapisywac bez granic
     *
     */

}

int gameSimulation(gameBoard_t * gameBoard, int countOfAdjacentCells, int generationsCount){
    int boardSize = gameBoard->boardSize;
    printFile("", gameBoard);
    for (int l =0;l < generationsCount; l++){
        int ** newFields;
        newFields= malloc(sizeof(newFields)* boardSize);
        for(int i =0;i<boardSize;i++){
            newFields[i]=malloc(sizeof(newFields[i])* boardSize);
        }
        setBorders(boardSize,newFields);





        for(int i =1;i<boardSize-1;i++){ // from 1 cause 0 is part of border, and gameBoard.height -1 too
            for(int j =1;j<boardSize-1;j++) {
                if(countOfAdjacentCells==8)
                    newFields[i][j]=checkCellMooreNeighborhood(gameBoard->fields, i, j);
                else
                    newFields[i][j]=checkCellVonNeumannNeighborhood(gameBoard->fields, i, j);
            }
        }
        gameBoard->fields=newFields; // usunac mallocowanie z tworzenia tego elementu
        //generowanie obrazów

    }
}

int checkCellMooreNeighborhood(int ** fields, int x, int y){
    int lifeStatus = fields[x][y];
    int aliveNeighbours = 0;
    for(int i =-1; i <= 1; i++){
        for(int j =-1; j <= 1; j++){
            if(!(i ==0 && j ==0)) //without that cell
                if(fields[x+i][y+j])
                    aliveNeighbours++;
        }
    }

    if(lifeStatus == 1){
        if(aliveNeighbours == 2 || aliveNeighbours == 3)
        {
            return 0;
        } else if(aliveNeighbours == 3){
            return 1;
        }
    }else{
        return lifeStatus;
    }




}
int checkCellVonNeumannNeighborhood(int ** fields, int x, int y){
    int lifeStatus = fields[x][y];
    int aliveNeighbours = fields[x+1][y] + fields[x-1][y] + fields[x][y+1] + fields[x][y+1];

    if(lifeStatus == 1){
        if(aliveNeighbours == 2 || aliveNeighbours == 3)
        {
            return 0;
        } else if(aliveNeighbours == 3){
            return 1;
        }
    }else{
        return lifeStatus;
    }
}