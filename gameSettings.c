
#include "gameSettings.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BufferSize 1024

int loadGameSettings(char * fileName, gameSettings_t * settings)
{
    FILE * file = fopen(fileName,"r"); // Opening file path
    if(file == NULL) {
        fprintf(stderr,"Configuration file can't be opened.");
        return 1;
    }                       // Checking failure of opening
    int counterofcalling=0;
    char tmpFirstString[BufferSize];
    char tmpSecondString[BufferSize];
    while(fscanf(file,"%s = %s",tmpFirstString,tmpSecondString)!=0){ //Reading a file and saving in structure
        if(strcmp(tmpFirstString,"countOfAdjacentCells")==0){
            int ValueTmp = atoi(tmpSecondString);
            if(ValueTmp!=4 && ValueTmp != 8)
            {
                fprintf(stderr,"Failure in configuration file. Value \"countOfAdjacentCells\" must be 4 or 8.");
                return 2;
            }
            settings->countOfAdjacentCells=ValueTmp;
            counterofcalling++;
        }
        if(strcmp(tmpFirstString,"BoardLoaded")==0){
            int ValueTmp = atoi(tmpSecondString);
            if(ValueTmp!=0 && ValueTmp!=1)
            {
                fprintf(stderr,"Failure in configuration file. Value \"isBoardLoaded\" must be 0 or 1.");
                return 2;
            }
            settings->isBoardLoaded=ValueTmp;
            counterofcalling++;
        }
        if(strcmp(tmpFirstString,"deflautBoardSize")==0){
            int ValueTmp = atoi(tmpSecondString);
            if(ValueTmp<=0)
            {
                fprintf(stderr,"Failure in configuration file. Value \"deflautBoardSize\" must be positive value.");
                return 2;
            }
            settings->deflautBoardSize=ValueTmp;
            counterofcalling++;
        }
        if(strcmp(tmpFirstString,"edgeSettings")==0){
            int ValueTmp = atoi(tmpSecondString);
            if(ValueTmp!=0 && ValueTmp!=1 && ValueTmp==2)
            {
                fprintf(stderr,"Failure in configuration file. Value \"edgeSettings\" must be 0 or 1 or 3.");
                return 2;
            }
            settings->edgeSettings = ValueTmp;
            counterofcalling++;
        }
        if(strcmp(tmpFirstString,"generationCount")==0){
            int ValueTmp = atoi(tmpSecondString);
            if(ValueTmp<0)
            {
                fprintf(stderr,"Failure in configuration file. Value \"generationCount\" must be positive");
                return 2;
            }
            settings->generationCount = ValueTmp;
            counterofcalling++;
        }

        int c;
        while((c=fgetc(file))!='\n' && c!=EOF);
        if(c==EOF) break;
    }
    if(counterofcalling<5 ){
        fprintf(stderr,"Not enough arguments to start program");
        return 1;
    }
    fclose(file);
    return 0;
}