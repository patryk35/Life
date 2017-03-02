//
// Created by Patryk on 2017-03-02.
//

#include "gameOperator.h"
#include "gameSettings.h"
#include <stdlib.h>
#include <stdio.h>
/*
 * Error List
 * -1 - SettingsError
 *
 */

int startGame(gameBoard_t * gameBoard, int boarderStart){
    //granice to 0,0 0,1 0,2 0,3 1,0 , itp, tu zrobic ich obsluge, pamietac ze zapisywac bez granic
    int width =15;
    gameBoard->fields= malloc(sizeof(gameBoard->fields)* width);
    for(int i =0;i<width;i++){
        gameBoard->fields[i]=malloc(sizeof(gameBoard->fields[i])* width);
    }
    /*for(int i=0;i<width;i++){
        for(int j=0;j<width;j++){
            gameBoard->fields[i][j]= 0;
        }
    }*/
    gameBoard->width=width;
    gameBoard->height=width;

    for(int i=0; i< gameBoard->height; i++)
    {
        gameBoard->fields[0][i]=0;
        gameBoard->fields[i][0]=0;
        gameBoard->fields[0][gameBoard->width-1]=0;
        gameBoard->fields[gameBoard->width-1][0]=0;
    }








    for(int i=1;i<width-1;i++){
        for(int j=1;j<width-1;j++){
            gameBoard->fields[i][j]= rand()%2;
            printf("%d %c", gameBoard->fields[i][j], (j==(width-2)?'\n':' '));
        }
    }
    printf("\n\n\n\n\n\n");




    for(int i=1;i<width;i++){
        for(int j=1;j<width;j++){
            if(gameBoard->fields[i][j]== 1)
                printf(".");
            else
                printf(" ");
        }
        printf("\n");
    }





    if(boarderStart == 1){
        //wczy
        //fileReader();
    }else if(boarderStart == 2){
        //boardGenerator();
    }else{
        return -1;
    }

}

int gameSimulation(gameBoard_t * gameBoard, int countOfAdjacentCells, int setGenerations){

    for (int l =0;l < setGenerations; l++){
        int ** newFields;
        newFields= malloc(sizeof(newFields)* gameBoard->width);
        for(int i =0;i<gameBoard->width;i++){
            newFields[i]=malloc(sizeof(newFields[i])* gameBoard->width);
        }
        for(int i=0; i< gameBoard->height; i++) /* Nie koniecznie potrzebne */
        {
            newFields[0][i]=0;
            newFields[i][0]=0;
            newFields[0][gameBoard->width-1]=0;
            newFields[gameBoard->width-1][0]=0;
        }
        printf("ME\n\n");
        for(int i=1;i<15-1;i++){
            for(int j=1;j<15-1;j++){
                gameBoard->fields[i][j]= rand()%2;
                printf("%d %c", gameBoard->fields[i][j], (j==(15-2)?'\n':' '));
            }
        }
        printf("\n\n\n\n\n\n");
        for(int i =1;i<gameBoard->height-1;i++){ // from 1 cause 0 is part of border, and gameBoard.height -1 too
            for(int j =1;j<gameBoard->width-1;j++) {
                if(countOfAdjacentCells==8)
                {
                    newFields[i][j]=checkCellMooreNeighborhood(gameBoard->fields, i, j);
                    printf("%d %c", newFields[i][j], (j==(gameBoard->width-2)?'\n':' '));
                }else {
                    newFields[i][j]=checkCellVonNeumannNeighborhood(gameBoard->fields, i, j);
                    printf("%d %c", newFields[i][j], (j==(gameBoard->width-2)?'\n':' '));
                }
            }
        }
        gameBoard->fields=newFields; // usunac mallocowanie z tworzenia tego elementu
        //generowanie obrazów
        int width = gameBoard->height;
        for(int k=1;k<width;k++){
            for(int l=1;l<width;l++){
                if(gameBoard->fields[k][l]== 1)
                    printf(".");
                else
                    printf(" ");
            }
            printf("\n");
        }
        printf("\n\n\n\n\n\n");
    }
}

int checkCellMooreNeighborhood(int ** fields, int x, int y){
    int lifeStatus = fields[x][y];
    int aliveNeighbours = 0;
    for(int i =-1; i <= 1; i++){
        for(int j =-1; j <= 1; j++){
            if(!(i ==0 && j ==0)) //without that cell
            {
                if(x == 3 && y ==2)
                {
                    printf(" <%d>[%d %d] \n", fields[x+i][y+j],x+i,y+j);
                }
                if(fields[x+i][y+j])
                    aliveNeighbours++;
            }
        }
    }

   // printf("%d %d \n",x,y);
   // printf("%d \n",fields[x][y]);
   // printf("an %d n1 %d n2 %d n3 %d n4 %d \n", aliveNeighbours);
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