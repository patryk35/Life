#include <stdio.h>

#include <stdio.h>
#include "gameSettings.h"
#include "gameOperator.h"
int main() {
    int errorComand=0;
    int setGenerations =10; //pobierac jakos pozniej
    char * settingsFile = "life_ConfigFile.conf";// dodac wczytywanie z parametrami uruchomienia
    char * boardName = "png.png";
    gameSettings_t settings;
    errorComand = loadGameSettings(settingsFile,&settings);
    if(errorComand)
    {

    }
    gameBoard_t gameBoard;
    errorComand = startGame(&gameBoard, settings.boardStart);
    if(errorComand)
    {

    }

    errorComand =  gameSimulation(&gameBoard, settings.countOfAdjacentCells, setGenerations);
    if(errorComand)
    {

    }





//tu bd wczytywanie danych
    return 0;
}