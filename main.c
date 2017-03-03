#include "gameSettings.h"
#include "gameOperator.h"
#include <stdio.h>
int main() {
    int errorComand=0;
    int generationsCount =15; //pobierac jakos inacej
    char * settingsFile = "life.conf";// dodac wczytywanie z parametrami uruchomienia
    char * boardName = "./LifePlots/Livell"; // przenisesc do settings
    gameSettings_t settings;
    errorComand = loadGameSettings(settingsFile,&settings);
    if(errorComand)
    {

    }
    gameBoard_t gameBoard;
    gameBoard.boardSize=settings.deflautBoardSize;
    errorComand = startGame(&gameBoard, settings);
    if(errorComand)
    {

    }

    errorComand =  gameSimulation(&gameBoard, settings, generationsCount, boardName);
    if(errorComand)
    {

    }





//tu bd wczytywanie danych
    return 0;
}