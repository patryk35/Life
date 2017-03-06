#include "gameOperator.h"
#include "pngOperator.h"
#include "boardGenerator.h"
#include "fileOperator.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int createBoard(gameBoard_t * gameBoard, gameSettings_t settings, char * saveName, char * readFileName){
    newDirectory(saveName); //creating new file to save generated files
    if(settings.isBoardLoaded == 1) // if isBoardLoaded =0 generate board, if isBoardLoaded =0 load board
        return readFile(readFileName,gameBoard,settings.edgeSettings);
    else if(settings.isBoardLoaded == 0){
        return boardGenerator(gameBoard, settings.edgeSettings,settings.defaultBoardSize);
    }else
        return -33;
}

int gameSimulation(gameBoard_t * gameBoard, gameSettings_t settings, int generationsCount, char * saveName){
    int boardSize = gameBoard->boardSize;
    char fileName[100];
    findFileName(saveName,0,fileName);
    printFile(fileName, gameBoard,settings.cellSize);
    for (int l =0;l < generationsCount; l++) {
        int errorCommand;
        // malloc space for cells in array
        short ** newFields;
        newFields = malloc(sizeof(newFields) * boardSize);
        if(newFields == NULL)
            return -41; // Error: memory exhaustion
        for (int i = 0; i < boardSize; i++) {
            newFields[i] = malloc(sizeof(newFields[i]) * boardSize);
            if(newFields[i] == NULL)
                return -41; // Error: memory exhaustion
        }

        setBorders(boardSize, newFields, settings.edgeSettings);
        //Finding new generation
        for (int i = 1; i < boardSize - 1; i++)      // i=1 and, i < boardSize-1, cause cells are stored from index 1 to
            for (int j = 1; j < boardSize - 1; j++){ // index equal boardSize-1, other space is designed for border
                int aliveNeighbours;
                if (settings.neighborhoodSettings == 1)
                    aliveNeighbours = checkCellMooreNeighborhood(gameBoard->fields, i, j);
                else
                    aliveNeighbours = checkCellVonNeumannNeighborhood(gameBoard->fields, i, j);
                newFields[i][j]=checkAlive(aliveNeighbours,gameBoard->fields[i][j]);
            }
        freeFields(gameBoard); //Free old generation array
        gameBoard->fields=newFields; //puts new generation into struct gameBoard
        findFileName(saveName,l+1,fileName);
        errorCommand=printFile(fileName, gameBoard,settings.cellSize); // generate visualization of generation in PNG format
        if(errorCommand)
            return errorCommand;
    }
    return writeFile(saveName, gameBoard); //write file with last generation
}
int checkAlive(int aliveNeighbours, int isAlive){
    if(isAlive == 1)
        if(aliveNeighbours == 2 || aliveNeighbours == 3)
            return 1;
        else
            return 0;
    else if(isAlive == 0)
        if(aliveNeighbours == 3)
            return 1;
        else
            return isAlive;
    else
        return isAlive;
}
int checkCellMooreNeighborhood(short ** fields, int x, int y){
    int aliveNeighbours = 0;
    for(int i =-1; i <= 1; i++)
        for(int j =-1; j <= 1; j++)
            if(!(i ==0 && j ==0)) //without the cell in the middle(based cell)
                if(fields[x+i][y+j])
                    aliveNeighbours++;
    return aliveNeighbours;

}
int checkCellVonNeumannNeighborhood(short ** fields, int x, int y){
    short aliveNeighbours = fields[x+1][y] + fields[x-1][y] + fields[x][y+1] + fields[x][y+1];
    return aliveNeighbours;
}
void findFileName(char* prefix, int counter, char  source[100]){
    char fileName[100] = "./";
    char generation[4] ="000";
    int i=0;
    while(counter>0)
    {
        generation[2-i]=(counter%10)+48;
        counter=counter/10;
        i++;
    }
    strcat(fileName,prefix);
    strcat(fileName,"/Genration_");
    strcat(fileName,generation);
    strcat(fileName,".png");
    strcpy(source,fileName);
}
void freeFields(gameBoard_t * gameBoard){
    for (int i = 0; i < gameBoard->boardSize; i++) {
        if(gameBoard->fields[i] != NULL)
            free(gameBoard->fields[i]);
    }
    if(gameBoard->fields != NULL)
        free(gameBoard->fields);
}
