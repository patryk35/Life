#include "gameSettings.h"
#include "gameOperator.h"
#include <stdio.h>
int main() {
    int errorComand=0;
    int generationsCount =20; //pobierac jakos inacej
    char * settingsFile = "life.conf";// dodac wczytywanie z parametrami uruchomienia
    char * boardName = "myLifeGamePlots"; // przenisesc do settings
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

    errorComand =  gameSimulation(&gameBoard, settings, generationsCount);
    if(errorComand)
    {

    }





//tu bd wczytywanie danych
    return 0;
}