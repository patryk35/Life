#include <stdio.h>

#include <stdio.h>
#include "gameSettings.h"
#include "gameOperator.h"
int main() {
    int errorComand=0;
    int generationsCount =10; //pobierac jakos inacej
    char * settingsFile = "life.conf";// dodac wczytywanie z parametrami uruchomienia
    char * boardName = "png.png";
    gameSettings_t settings;
    errorComand = loadGameSettings(settingsFile,&settings);
    if(errorComand)
    {

    }
    gameBoard_t gameBoard;
    gameBoard.boardSize=settings.deflautBoardSize;
    errorComand = startGame(&gameBoard, settings.isBoardLoaded);
    if(errorComand)
    {

    }

    errorComand =  gameSimulation(&gameBoard, settings.countOfAdjacentCells, generationsCount);
    if(errorComand)
    {

    }





//tu bd wczytywanie danych
    return 0;
}