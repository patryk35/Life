//
// Created by Patryk on 2017-03-02.
//

#include "gameOperator.h"
#include "pngOperator.h"
#include "boardGanerator.h"
#include "fileRead.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/*
 * Error List
 * -1 - [gameOperator] SettingsError -
 * -2
 */

int startGame(gameBoard_t * gameBoard, gameSettings_t settings){
    gameBoard->fields= malloc(sizeof(gameBoard->fields)* gameBoard->boardSize);
    for(int i =0;i<gameBoard->boardSize;i++){
        gameBoard->fields[i]=malloc(sizeof(gameBoard->fields[i])* gameBoard->boardSize);
    }
    if(settings.isBoardLoaded == 1){
        /*
         *
         *
         *
         *
         */
        readFile("");
    }else if(settings.isBoardLoaded == 0){
        boardGenerator(gameBoard, settings.edgeSettings);
    }else{
        return -1;
    }
}

int gameSimulation(gameBoard_t * gameBoard, gameSettings_t settings, int generationsCount, char * boardName){
    int boardSize = gameBoard->boardSize;
    char fileName[200];
    findFileName(boardName,0,fileName);
    printFile(fileName, gameBoard,settings.cellSize);
    for (int l =0;l < generationsCount; l++) {
        int **newFields;
        newFields = malloc(sizeof(newFields) * boardSize);
        for (int i = 0; i < boardSize; i++) {
            newFields[i] = malloc(sizeof(newFields[i]) * boardSize);
        }
        setBorders(boardSize, newFields, settings.edgeSettings);


        for (int i = 1; i < boardSize - 1; i++) // from 1 cause 0 is part of border, and gameBoard.height -1 too
            for (int j = 1; j < boardSize - 1; j++) {
                int aliveNeighbours;
                if (settings.countOfAdjacentCells == 8)
                    aliveNeighbours = checkCellMooreNeighborhood(gameBoard->fields, i, j);
                else
                    aliveNeighbours = checkCellVonNeumannNeighborhood(gameBoard->fields, i, j);

                newFields[i][j]=checkAlive(aliveNeighbours,gameBoard->fields[i][j]);
            }


        gameBoard->fields=newFields; // usunac mallocowanie z tworzenia tego elementu
        findFileName(boardName,l+1,fileName);
        printFile(fileName, gameBoard,settings.cellSize); // generowanie plików

    }
}
int checkAlive(int aliveNeighbours, int isAlive){
    if(isAlive == 1) {
        if(aliveNeighbours == 2 || aliveNeighbours == 3)
            return 1;
        else
            return 0;
    }
    else if(isAlive == 0){
        if(aliveNeighbours == 3)
            return 1;
        else
            return isAlive;
    }
    else
        return isAlive;

}
int checkCellMooreNeighborhood(int ** fields, int x, int y){
    int aliveNeighbours = 0;
    for(int i =-1; i <= 1; i++){
        for(int j =-1; j <= 1; j++){
            if(!(i ==0 && j ==0)) //without that cell
                if(fields[x+i][y+j])
                    aliveNeighbours++;
        }
    }
    return aliveNeighbours;

}
int checkCellVonNeumannNeighborhood(int ** fields, int x, int y){
    int aliveNeighbours = fields[x+1][y] + fields[x-1][y] + fields[x][y+1] + fields[x][y+1];
    return aliveNeighbours;
}
void findFileName(char* prefix, int counter, char  source[200]){
    char fileName[200] = "";
    char generation[4] ="000";
    int i=0;
    while(counter>0)
    {
        generation[2-i]=(counter%10)+48;
        counter=counter/10;
        i++;
    }
    strcpy(fileName,prefix);
    strcat(fileName,"Genration_");
    strcat(fileName,generation);
    strcat(fileName,".png");
    strcpy(source,fileName);
}