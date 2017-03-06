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
 * Function return:
 *  0, if everything gone alright
 * -1 for error - Configuration file can't be opened.
 * -2 for error - Failure in configuration file. Value "countOfAdjacentCells" must be 0 or 1.
 * -3 for error - Failure in configuration file. Value \"defaultBoardSize\" must be positive value.
 * -4 for error - Failure in configuration file. Value \"edgeSettings\" must be 0 or 1 or 2.
 * -5 for error - Failure in configuration file. Value "defaultGenerationCount" must be positive
 * -6 for error - Failure in configuration file. Value "cellSize" must be positive
 * -7 for error - Not enough arguments in "configuration file" to start program
 */
int loadGameSettings(char * fileName, gameSettings_t * settings);
#endif //LIFE_GAMESETTINGS_H
