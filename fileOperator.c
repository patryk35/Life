#include "fileOperator.h"
#include "boardGenerator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
int readFile(char * fileName, gameBoard_t * gameBoard, int edgeSettings){
    FILE * file = fopen(fileName,"r");
    if(file == NULL)
        return -21; //Error: can not open file
    int tmp;
    if(fscanf(file,"%d",&tmp)!=0)
        gameBoard->boardSize=tmp+2; // +2, cause cells are stored from index 1 to index equal boardSize-1, other space is designed for border
    else
        return -22;//Error: can not read size value
    // malloc space for cells in array
    gameBoard->fields= malloc(sizeof(gameBoard->fields)* gameBoard->boardSize);
    if(gameBoard->fields == NULL)
        return -23; // Error: memory exhaustion
    for(int i =0;i<gameBoard->boardSize;i++){
        gameBoard->fields[i]=malloc(sizeof(gameBoard->fields[i])* gameBoard->boardSize);
        if(gameBoard->fields == NULL)
            return -23; // Error: memory exhaustion
    }
    setBorders(gameBoard->boardSize,gameBoard->fields,edgeSettings);
    //fill array
    for (int i = 1; i < gameBoard->boardSize-1; ++i) {
        for (int j = 1; j < gameBoard->boardSize-1; ++j) {
            if(fscanf(file,"%d",&tmp)!=0)
                gameBoard->fields[i][j]=tmp;
            else
                return -24; //Error: can not read cells value
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
        return -31; //Error: can not open file
    fprintf(file,"%d\n", gameBoard->boardSize-2);
    for(int i=1;i<gameBoard->boardSize-1;i++){
        for (int j = 1; j < gameBoard->boardSize-1; ++j)
            fprintf(file, "%d ",gameBoard->fields[i][j]);
        fprintf(file,"\n");
    }
    fclose(file);
    return 0;
}
void newDirectory(char * name){
    struct stat st = {0};
if (stat(name, &st) == -1) {
    mkdir(name, 0700);
}
}
