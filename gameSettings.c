#include "gameSettings.h"
#include "errorsComunicats.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BufferSize 512

int loadGameSettings(char * fileName, gameSettings_t * settings)
{
    FILE * file = fopen(fileName,"r"); // Opening file path
    if(file == NULL)    // Checking failure of opening
        return CONFIGURATION_FILE_CAN_NOT_OPEN;
    int counterOfCalling=0;
    char tmpFirstString[BufferSize];
    char tmpSecondString[BufferSize];
    //Reading a file and saving in structure
    while(fscanf(file,"%s = %s",tmpFirstString,tmpSecondString)!=0){
        if(strcmp(tmpFirstString,"neighborhoodSettings")==0){
            int ValueTmp = atoi(tmpSecondString);
            if(ValueTmp!=0 && ValueTmp != 1)
                return INVALID_VALUE_NEIGHBORHOOD_SETTINGS;
            settings->neighborhoodSettings=ValueTmp;
            counterOfCalling++;
        }
        else if(strcmp(tmpFirstString,"defaultBoardSize")==0){
            int ValueTmp = atoi(tmpSecondString);
            if(ValueTmp<=0)
                return INVALID_VALUE_DEFAULT_BOARD_SIZE;
            settings->defaultBoardSize=ValueTmp+2; // +2, cause cells are stored from index 1 to index equal
                                                   // boardSize-1, other space is designed for border
            counterOfCalling++;
        }
        else if(strcmp(tmpFirstString,"edgeSettings")==0){
            int ValueTmp = atoi(tmpSecondString);
            if(ValueTmp!=0 && ValueTmp!=1 && ValueTmp!=2)
                return INVALID_VALUE_EDGE_SETTINGS;
            settings->edgeSettings = ValueTmp;
            counterOfCalling++;
        }
        else if(strcmp(tmpFirstString,"defaultGenerationCount")==0){
            int ValueTmp = atoi(tmpSecondString);
            if(ValueTmp<1)
                return INVALID_VALUE_DEFAULT_GENERATION_COUNT;
            settings->defaultGenerationCount = ValueTmp;
            counterOfCalling++;
        }
        else if(strcmp(tmpFirstString,"cellSize")==0){
            int ValueTmp = atoi(tmpSecondString);
            if(ValueTmp<0)
                return INVALID_VALUE_CELL_SIZE;
            settings->cellSize = ValueTmp;
            counterOfCalling++;
        }
        int c;
        while((c=fgetc(file))!='\n' && c!=EOF);
        if(c==EOF) break;
    }
    if(counterOfCalling<5)
        return FILE_INVALID_COUNT_OF_ARGUMENTS;
    fclose(file);
    return 0;
}