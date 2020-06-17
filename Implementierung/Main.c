#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Test.h"
#include "ReadAndWritePPM.h"

void printUsage(char *name){
    printf("Usage: %s [-p path] [-g gamma] [-t]\n", name);
}

int main(int argc, char *argv[]){
    char *name = argv[0];
    char* pathToImage = "";
    int testFlag = 0;
    //set gamma to 1 as default value
    float gamma = 1;
    char opt;

    if (argc < 2){
        printUsage(name);
        exit(EXIT_FAILURE);
    }
    while ((opt = getopt(argc, argv, "p:g:t")) != -1) {
        switch (opt) {
            case 'p':
                //avoid reading the next flag as argument; 45 is ascii code for "-"
                if (optarg[0] == 45){
                    //reduce optind so the next flag gets evaluated normally
                    optind --;
                    break;
                }
                pathToImage = optarg;
                break;
            case 'g':
                //avoid reading the next flag as argument; 45 is ascii code for "-"
                if (optarg[0] == 45){
                    //reduce optind so the next flag gets evaluated normally
                    optind --;
                    break;
                }
                gamma = atof(optarg);
                break;
            case 't':
                testFlag = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-p path] [-g gamma] [-t]\n", name);
                exit(EXIT_FAILURE);
        }
    }

    if (testFlag == 0){
        //Normal execution with testFlag = 0
        //Check if path is empty
        if (strcmp(pathToImage, "") == 0) {
            printf("path was not specified\n");
            printUsage(name);
            exit(EXIT_FAILURE);
        }

        //Check if gamma was set correctly
        if (gamma < 0){
            printf("gamma value was not specified or too small, has to be >= 0\n");
            exit(EXIT_FAILURE);
        }

        //int8_t* picture = readPicture(pathToImage);
        //execute the calulations
        //writePicture()

        exit(EXIT_SUCCESS);
    }
    //Test Execution (testFlag = 1)
    if (strcmp(pathToImage, "") != 0){
        //test with given image
        testImage(pathToImage);
        exit(EXIT_SUCCESS);
    }
    //test with standard image
    test();
    exit(EXIT_SUCCESS);
}

