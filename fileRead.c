#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "fileRead.h"


void readOneRow(int *fields,FILE *file,int size){
    int tmpChar;
    int counter=0;
    do
    {
        tmpChar=getc(file);
        fields[counter]=tmpChar-'0';
        if((isspace(tmpChar)||tmpChar==EOF)&&counter<size) {
            int j;
            for (j = counter; j < size; j++){
                fields[counter] = 0;
            }
        }
        counter++;
    }
    while(((tmpChar!='\n'&&tmpChar!=EOF && counter<size)));
    getc(file);
}

int readFile(char * fileName, gameBoard_t *readBoard)
{
    FILE *file = fopen(fileName,"r");
    if(file == NULL){
        fprintf(stderr,"File can not be opened");
    }
    int sizeValue;
    if (fscanf(file,"%d\n",&sizeValue)!=1)
    {
        fprintf(stderr,"Incompatible value in reading file");
        return 1;
    }
    int **field=malloc(sizeValue*sizeof(int*));
    if(**field==NULL){
        fprintf(stderr,"Not enough memory");
        return 2;
    }
    int i;
    for(i=0;i<sizeValue;i++)
    {
        field[i]=malloc(sizeValue*sizeof(int*));
        if(**field==NULL){
            fprintf(stderr,"Not enough memory");
            return 2;
        }
    }
    for(i=0;i<sizeValue;i++)
    {
        readOneRow(field[i],file,sizeValue);

    }
    (*readBoard).boardSize=sizeValue;
    readBoard->fields=field;
    return 0;
}