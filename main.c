#include "gameSettings.h"
#include "errorsComunicats.h"
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
                if(generationsCount<1) {
                    printf("Value \"generationsCount\" must be positive");
                    return 1;
                }
                break;
            default:
                fprintf (stderr,"%s",usage);
                return EXIT_FAILURE;
        }
    }
    if(optind<argc) {
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
        switch(errorCommand){
            case CONFIGURATION_FILE_CAN_NOT_OPEN:
                fprintf(stderr,"Error: in function \"loadGameSettings\" - Configuration file \"%s\" can't be opened.\n",
                        settingsFile);
                break;
            case INVALID_VALUE_NEIGHBORHOOD_SETTINGS:
                fprintf(stderr,"Error: in function \"loadGameSettings\" - Failure in configuration file \"%s\"."
                         "Value \"neighborhoodSettings\" must be 0 or 1. \n", settingsFile);
                break;
            case INVALID_VALUE_DEFAULT_BOARD_SIZE:
                fprintf(stderr,"Error: in function \"loadGameSettings\" - Failure in configuration file \"%s\". "
                        "Value \"defaultBoardSize\" must be positive value.\n", settingsFile);
                break;
            case INVALID_VALUE_EDGE_SETTINGS:
                fprintf(stderr,"Error: in function \"loadGameSettings\" - Failure in configuration file \"%s\"."
                        " Value \"edgeSettings\" must be 0 or 1 or 2.\n", settingsFile);
                break;
            case INVALID_VALUE_DEFAULT_GENERATION_COUNT:
                fprintf(stderr,"Error: in function \"loadGameSettings\" - Failure in configuration file \"%s\". "
                        "Value \"defaultGenerationCount\" must be positive\n", settingsFile);
                break;
            case INVALID_VALUE_CELL_SIZE:
                fprintf(stderr,"Error: in function \"loadGameSettings\" - Failure in configuration file \"%s\". "
                        "Value \"cellSize\" must be positive\n", settingsFile);
                break;
            case FILE_INVALID_COUNT_OF_ARGUMENTS:
                fprintf(stderr,"Error: in function \"loadGameSettings\" - Not enough arguments in "
                        "\"configuration file\" (\"%s\") to start program\n", settingsFile);
            default:
                fprintf(stderr,"Unknown Error: in function \"loadGameSettings\" \n");
        }
        return errorCommand;
    }

    if(generationsCount==0)
        generationsCount=settings.defaultGenerationCount;

    errorCommand = createBoard(&gameBoard, settings, saveName, readFileName);
    if(errorCommand) {
        switch(errorCommand) {
            case FILE_CAN_NOT_OPEN_TO_READ:
                fprintf(stderr,"Error: in function \"readFile\" - can not open file \"%s\" for reading \n",
                        readFileName);
                break;
            case FILE_SIZE_VALUE:
                fprintf(stderr,"Error: in function \"readFile\" - can not read size value in file \"%s\" \n",
                        readFileName);
                break;
            case MEMORY_EXHAUSTION:
                fprintf(stderr,"Error: memory exhaustion \n");
                break;
            case FILE_CELLS_VALUES:
                fprintf(stderr,"Error: in function \"readFile\" - can not read cells value in file \"%s\" \n",
                        readFileName);
                break;
            default:
                fprintf(stderr,"Unknown Error: in function \"createBoard\" \n");
        }
        return errorCommand;
    }
    errorCommand =  gameSimulation(&gameBoard, settings, generationsCount, saveName);
    if(errorCommand) {
        switch(errorCommand) {
            case FILE_CAN_NOT_OPEN_TO_WRITE:
                fprintf(stderr,"Error: in function \"writFile\" - can not open file  \"%s\" for writing \n", saveName);
                break;
            case MEMORY_EXHAUSTION:
                fprintf(stderr,"Error: in function \"gameSimulation\" - memory exhaustion");
                break;
            case PNG_CAN_NOT_OPEN:
                fprintf(stderr,"Error: in function \"printFile\" - can not open file for writting");
                break;
            case PNG_CREATE_WRITE_STRUCT_FAILED:
                fprintf(stderr,"Error: in function \"printFile\" - png_create_write_struct failed");
                break;
            case PNG_CREATE_INFO_STRUCT_FAILED:
                fprintf(stderr,"Error: in function \"printFile\" - png_create_info_struct failed");
                break;
            case PNG_INIT_TO_ERROR:
                fprintf(stderr,"Error: in function \"printFile\" - error during init_io");
                break;
            case PNG_WRITTING_HEADRE_WRITE:
                fprintf(stderr,"Error: in function \"printFile\" - error during writing header");
                break;
            case PNG_WRITING_BYTES:
                fprintf(stderr,"Error: in function \"printFile\" - error during writing bytes");
                break;
            case PNG_END_OF_WRITE_ERROR:
                fprintf(stderr,"Error: in function \"printFile\" - error during end of write");
                break;
            default:
                fprintf(stderr,"Unknown Error: in function \"startGame\" \n");
        }
        return errorCommand;
    }
    freeFields(&gameBoard);
    return EXIT_SUCCESS;
}
