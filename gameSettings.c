#include "gameSettings.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BufferSize 512

int loadGameSettings(char * fileName, gameSettings_t * settings)
{
    FILE * file = fopen(fileName,"r"); // Opening file path
    if(file == NULL)    // Checking failure of opening
        return -1; //Error: Configuration file can't be opened.
    int counterofcalling=0;
    char tmpFirstString[BufferSize];
    char tmpSecondString[BufferSize];
    //Reading a file and saving in structure
    while(fscanf(file,"%s = %s",tmpFirstString,tmpSecondString)!=0){
        if(strcmp(tmpFirstString,"neighborhoodSettings")==0){
            int ValueTmp = atoi(tmpSecondString);
            if(ValueTmp!=0 && ValueTmp != 1)
                return -2; //Error: Failure in configuration file. Value "countOfAdjacentCells" must be 0 or 1.
            settings->neighborhoodSettings=ValueTmp;
            counterofcalling++;
        }
        if(strcmp(tmpFirstString,"defaultBoardSize")==0){
            int ValueTmp = atoi(tmpSecondString);
            if(ValueTmp<=0)
                return -3; //"Error: Failure in configuration file. Value \"defaultBoardSize\" must be positive value.
            settings->defaultBoardSize=ValueTmp+2; // +2, cause cells are stored from index 1 to index equal boardSize-1, other space is designed for border
            counterofcalling++;
        }
        if(strcmp(tmpFirstString,"edgeSettings")==0){
            int ValueTmp = atoi(tmpSecondString);
            if(ValueTmp!=0 && ValueTmp!=1 && ValueTmp!=2)
                return -4;//Error: Failure in configuration file. Value \"edgeSettings\" must be 0 or 1 or 2.
            settings->edgeSettings = ValueTmp;
            counterofcalling++;
        }
        if(strcmp(tmpFirstString,"defaultGenerationCount")==0){
            int ValueTmp = atoi(tmpSecondString);
            if(ValueTmp<1 || ValueTmp>999)
                return -5; // Error: Failure in configuration file. Value "defaultGenerationCount" must be positive and less than 1000
            settings->defaultGenerationCount = ValueTmp;
            counterofcalling++;
        }
        if(strcmp(tmpFirstString,"cellSize")==0){
            int ValueTmp = atoi(tmpSecondString);
            if(ValueTmp<0)
                return 2; //Error: Failure in configuration file. Value "cellSize" must be positive
            settings->cellSize = ValueTmp;
            counterofcalling++;
        }
        int c;
        while((c=fgetc(file))!='\n' && c!=EOF);
        if(c==EOF) break;
    }
    if(counterofcalling<5 )
        return -7; // Error: Not enough arguments in "configuration file" to start program
    fclose(file);
    return 0;
}