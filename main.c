#include "gameSettings.h"
#include "gameOperator.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char ** argv) {
    int errorCommand=0;
    char * settingsFile = "life.conf";
    gameBoard_t gameBoard;
    gameSettings_t settings;
    int generationsCount=0;
    char * saveName = "";
    char * readFileName="";

    //loading parameters

    int opt;
    char *usage =
            "********************************************************************\n"
                    "Usage of Life(John Conway's Game of Life): \n"
                    "-w name of generated generations  \n"
                    "[-l name(with .life) of file to load generation]\n"
                    "[-g the number of generation to generate]\n"
                    "-- other settings can be changed in the file life.conf\n"
                    "********************************************************************\n";
    optind=0;
    settings.isBoardLoaded=0;
    while((opt = getopt (argc, argv, "w:l:g:")) != -1) {
        switch(opt){
            case 'w':
                saveName = optarg;
                break;
            case 'l':
                readFileName = optarg;
                settings.isBoardLoaded=1;
                break;
            case 'g':
                generationsCount = atoi(optarg);
                if(generationsCount<1 || generationsCount > 999)
                {
                    printf("Value \"generationsCount\" must be positive and less than 1000");
                    return 1;
                }
                break;
            default:
                fprintf (stderr,"%s",usage);
                return EXIT_FAILURE;
        }
    }
    if( optind < argc ) {
        fprintf( stderr, "\nWrong parameters!\n" );
        for( ; optind < argc; optind++ )
            fprintf( stderr, "\t\"%s\"\n", argv[optind] );
        fprintf( stderr, "\n" );
        fprintf( stderr, usage);
        exit( EXIT_FAILURE );
    }
    else if(argc < 3 || saveName == "") {
        fprintf( stderr, "\nWrong count of parameters! \n" );
        fprintf( stderr, usage);
        exit( EXIT_FAILURE );
    } else if(argc < 4){
        if(argc > 1){
            if(argv[1][1] != 'w'){
                fprintf( stderr, "\nWrong count of parameters! \n" );
                fprintf( stderr, usage);
                exit( EXIT_FAILURE );
            }
        }
    }
    // end of loading parameters

    errorCommand = loadGameSettings(settingsFile,&settings);
    if(errorCommand) {
        if(errorCommand == -1)
            fprintf(stderr,"Error: in function \"loadGameSettings\" - Configuration file \"%s\" can't be opened.  \n", settingsFile);
        else if(errorCommand == -2)
            fprintf(stderr,"Error: in function \"loadGameSettings\" - Failure in configuration file \"%s\". Value \"countOfAdjacentCells\" must be 0 or 1. \n", settingsFile);
        else if(errorCommand == -3)
            fprintf(stderr,"Error: in function \"loadGameSettings\" - Failure in configuration file \"%s\". Value \"defaultBoardSize\" must be positive value.\n", settingsFile);
        else if(errorCommand == -4)
            fprintf(stderr,"Error: in function \"loadGameSettings\" - Failure in configuration file \"%s\". Value \"edgeSettings\" must be 0 or 1 or 2.\n", settingsFile);
        else if(errorCommand == -5)
            fprintf(stderr,"Error: in function \"loadGameSettings\" - Failure in configuration file \"%s\". Value \"defaultGenerationCount\" must be positive and less than 1000\n", settingsFile);
        else if(errorCommand == -6)
            fprintf(stderr,"Error: in function \"loadGameSettings\" - Failure in configuration file \"%s\". Value \"cellSize\" must be positive\n", settingsFile);
        else if(errorCommand == -7)
            fprintf(stderr,"Error: in function \"loadGameSettings\" - Not enough arguments in \"configuration file\" (\"%s\") to start program\n", settingsFile);
        else
            fprintf(stderr,"Unknown Error: in function \"loadGameSettings\" \n");
        return errorCommand;
    }

    if(generationsCount==0)
        generationsCount=settings.defaultGenerationCount;

    errorCommand = createBoard(&gameBoard, settings, saveName, readFileName);
    if(errorCommand) {
        if(errorCommand == -21)
            fprintf(stderr,"Error: in function \"readFile\" - can not open file \"%s\" for reading \n", readFileName);
        else if(errorCommand == -22)
            fprintf(stderr,"Error: in function \"readFile\" - can not read size value in file \"%s\" \n", readFileName);
        else if(errorCommand == -23)
            fprintf(stderr,"Error: in function \"readFile\" - memory exhaustion \n");
        else if(errorCommand == -24)
            fprintf(stderr,"Error: in function \"readFile\" - can not read cells value in file \"%s\" \n", readFileName);
        else if(errorCommand == -12)
            fprintf(stderr,"Error: in function \"boardGenerator\" - memory exhaustion \n");
        else
            fprintf(stderr,"Unknown Error: in function \"startGame\" \n");
        return errorCommand;
    }
    errorCommand =  gameSimulation(&gameBoard, settings, generationsCount, saveName);
    if(errorCommand) {
        if(errorCommand == -31)
            fprintf(stderr,"Error: in function \"writFile\" - can not open file  \"%s\" for writing \n", saveName);
        else if(errorCommand == -41)
            fprintf(stderr,"Error: in function \"gameSimulation\" - memory exhaustion");
        else if(errorCommand == -61)
            fprintf(stderr,"Error: in function \"printFile\" - can not open file for writting");
        else if(errorCommand == -62)
            fprintf(stderr,"Error: in function \"printFile\" - png_create_write_struct failed");
        else if(errorCommand == -63)
            fprintf(stderr,"Error: in function \"printFile\" - png_create_info_struct failed");
        else if(errorCommand == -64)
            fprintf(stderr,"Error: in function \"printFile\" - error during init_io");
        else if(errorCommand == -65)
            fprintf(stderr,"Error: in function \"printFile\" - error during writing header");
        else if(errorCommand == -66)
            fprintf(stderr,"Error: in function \"printFile\" - error during writing bytes");
        else if(errorCommand == -67)
            fprintf(stderr,"Error: in function \"printFile\" - error during end of write");
        else
            fprintf(stderr,"Unknown Error: in function \"gameSimulation\" \n");
        return errorCommand;
    }
    freeFields(&gameBoard);
    return EXIT_SUCCESS;
}
