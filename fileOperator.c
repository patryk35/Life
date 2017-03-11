#include "fileOperator.h"
#include "boardGenerator.h"
#include "errorsComunicats.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
int readFile(char * fileName, gameBoard_t * gameBoard, int edgeSettings){
    FILE * file = fopen(fileName,"r");
    if(file == NULL)
        return FILE_CAN_NOT_OPEN_TO_READ;
    int tmp;
    if(fscanf(file,"%d",&tmp)!=0)
        gameBoard->boardSize=tmp+2; // +2, cause cells are stored from index 1 to index equal boardSize-1,
    else                           // other space is designed for border
        return FILE_SIZE_VALUE;

    // malloc space for cells in array
    gameBoard->fields= malloc(sizeof(gameBoard->fields)* gameBoard->boardSize);
    if(gameBoard->fields == NULL)
        return MEMORY_EXHAUSTION;
    for(int i =0;i<gameBoard->boardSize;i++){
        gameBoard->fields[i]=malloc(sizeof(gameBoard->fields[i])* gameBoard->boardSize);
        if(gameBoard->fields == NULL)
            return MEMORY_EXHAUSTION;
    }
    setBorders(gameBoard->boardSize,gameBoard->fields,edgeSettings);
    //fill array
    for(int i = 1; i < gameBoard->boardSize-1; ++i) {
        for(int j = 1; j < gameBoard->boardSize-1; ++j) {
            if(fscanf(file,"%d",&tmp)!=0)
                gameBoard->fields[i][j]=tmp;
            else
                return FILE_CELLS_VALUES;
        }
    }
    fclose(file);
    return 0;
}
int writeFile(char * saveName, gameBoard_t * gameBoard){
    char fileName[100];
    FILE * file;

    //creating name and path for file
    strcpy(fileName,"./");
    strcat(fileName,saveName);
    strcat(fileName,"/");
    strcat(fileName,saveName);
    strcat(fileName,".life");
    //writing to file
    file = fopen(fileName,"w");
    if(file == NULL)
        return FILE_CAN_NOT_OPEN_TO_WRITE;
    fprintf(file,"%d\n", gameBoard->boardSize-2);
    for(int i=1;i<gameBoard->boardSize-1;i++){
        for(int j = 1; j < gameBoard->boardSize-1; ++j)
            fprintf(file, "%d ",gameBoard->fields[i][j]);
        fprintf(file,"\n");
    }
    fclose(file);
    return 0;
}
void newDirectory(char * name){
    struct stat st = {0};
    if(stat(name, &st) == -1)
        mkdir(name, 0700);
}
