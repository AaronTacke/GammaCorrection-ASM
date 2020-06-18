#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Test.h"
#include "ReadAndWritePPM.h"


//Later replaced with Assembler file:
#include "compare.h"
void replaceWithAssembler(uint8_t* picture, int width, int height, float gamma){
    calculate(picture,width,height,gamma);
}


void printUsageAndExit(char *name){
    //Add more help information
    printf("Usage: %s [-i inputPath] [-g gamma] [-o outputPath] [-t] [-b]\n", name);
    exit(EXIT_FAILURE);
}

void checkForValidArgument(char *programName, char operationName) {
    if (optarg[0] == 45){
        printf("Missing argument for option: -%c\n", operationName);
        printUsageAndExit(programName);
    }
}

int main(int argc, char *argv[]){
    char *name = argv[0];
    char *inputPath;
    char *outputPath = "GammaResult.ppm";
    int testFlag = 0;
    int benchmarkFlag = 0;
    //set gamma to 1 as default value
    float gamma = 1;
    char opt;

    if (argc < 2){
        printUsageAndExit(name);
    }
    while ((opt = getopt(argc, argv, "i:g:to:b")) != -1) {
        switch (opt) {
            case 'i':
                checkForValidArgument(name, opt);
                inputPath = optarg;
                break;
            case 'o':
                checkForValidArgument(name, opt);
                outputPath = optarg;
                break;
            case 'g':
                checkForValidArgument(name, opt);
                gamma = atof(optarg);
                break;
            case 't':
                testFlag = 1;
                break;
            case 'b':
                benchmarkFlag = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-i inputPath] [-g gamma] [-o outputPath] [-t] [-b]", name);
                exit(EXIT_FAILURE);
        }
    }

    if (testFlag == 0){
        //Normal execution
        if (inputPath[0] == 0){
            printf("No input path specified\n");
            printUsageAndExit(name);
        }
        if (outputPath[0] == 0){
            printf("No output path specified\n");
            printUsageAndExit(name);
        }
        //Check if gamma is valid
        if (gamma < 0){
            printf("gamma value is too small, has to be >= 0\n");
            exit(EXIT_FAILURE);
        }

        uint8_t* picture = readPicture(inputPath);
        replaceWithAssembler(picture, width, height, gamma);
        if(writePicture(outputPath, picture)!=0){
            printf("Error while saving image.");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
    //Test execution
    if (inputPath[0] != 0){
        //test with given image
        testImage(inputPath);
        exit(EXIT_SUCCESS);
    }
    //test with standard image
    test();
    exit(EXIT_SUCCESS);
}


