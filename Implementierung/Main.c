#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Test.h"
#include "ReadAndWritePPM.h"


//Later replaced with Assembler file:
#include "compare.h"
void replaceWithAssembler(uint8_t* picture,int width,int height,float gamma){
    calculate(picture,width,height,gamma);
}



void printUsage(char *name){
    //Add more help information
    printf("Usage: %s [-p path] [-g gamma] [-t]\n", name);
}

int main(int argc, char *argv[]){
    char *name = argv[0];
    char* pathToImage = "";
    int testFlag = 0;
    float gamma = -1;
    char opt;

    if (argc < 2){
        printUsage(name);
        exit(EXIT_FAILURE);
    }
    while ((opt = getopt(argc, argv, "p:g:t")) != -1) {
        switch (opt) {
            case 'p':
                pathToImage = optarg;
                break;
            case 'g':
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
        //Check if path is empty or another flag (45 is ascii code for "-")
        if (strcmp(pathToImage, "") == 0 || pathToImage[0] == 45) {
            printf("no path specified\n");
            printUsage(name);
            exit(EXIT_FAILURE);
        }

        //Check if gamma was set correctly
        if (gamma < 0){
            printf("gamma value was too small, has to be >= 0");
            exit(EXIT_FAILURE);
        }

        uint8_t* picture = readPicture(pathToImage);
        replaceWithAssembler(picture, width, height, gamma);
        char path[] = "./result.ppm";
        //TODO Later replaced with resultPath flag.
        if(writePicture(path, picture)!=0){
            printf("Error when saving imgae.");
            exit(EXIT_FAILURE);
        }
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

