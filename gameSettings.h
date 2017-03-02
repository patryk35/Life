//
// Created by Patryk on 2017-03-02.
//

#ifndef LIFE_GAMESETTINGS_H
#define LIFE_GAMESETTINGS_H
typedef struct gameSettings{
    /*int size;
    int height;
    int width;*/
    int countOfAdjacentCells;
    int edgeSettings;
    int boardStart;
} gameSettings_t;

int loadGameSettings(char * fileName, gameSettings_t * settings);
#endif //LIFE_GAMESETTINGS_H
