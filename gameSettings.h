//
// Created by Patryk on 2017-03-02.
//

#ifndef LIFE_GAMESETTINGS_H
#define LIFE_GAMESETTINGS_H
typedef struct gameSettings{
    char *boardName;
    int deflautBoardSize;
    int countOfAdjacentCells;
    int edgeSettings;
    int isBoardLoaded;
    int generationCount;
} gameSettings_t;

int loadGameSettings(char * fileName, gameSettings_t * settings);
#endif //LIFE_GAMESETTINGS_H
