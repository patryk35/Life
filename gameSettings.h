#ifndef LIFE_GAMESETTINGS_H
#define LIFE_GAMESETTINGS_H
typedef struct gameSettings{
    int defaultBoardSize;
    int neighborhoodSettings;
    int edgeSettings;
    int isBoardLoaded;
    int cellSize;
    int defaultGenerationCount;
} gameSettings_t;
/*
 * Function read settings from file and puts it into structure settings
 *
 */
int loadGameSettings(char * fileName, gameSettings_t * settings);
#endif //LIFE_GAMESETTINGS_H
