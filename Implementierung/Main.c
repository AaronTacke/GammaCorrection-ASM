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
    //TODO Add more information
    printf("Usage: %s [-i inputPath] [-g gamma] [-o outputPath] [-t] [-b] [-h]\n", name);
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
    char *inputPath = "";
    char *outputPath = "";
    int testFlag = 0;
    int benchmarkFlag = 0;
    //set gamma to 1 as default value
    float gamma = -1;
    char opt;

    if (argc < 2){
        printUsageAndExit(name);
    }
    while ((opt = getopt(argc, argv, "i:g:to:bh")) != -1) {
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
            case 'h':
                printUsageAndExit(name);
            default:
                printUsageAndExit(name);
                //TODO @Philip why did you write this instead of printUsageAndExit(...)?
                //fprintf(stderr, "Usage: %s [-i inputPath] [-g gamma] [-o outputPath] [-t] [-b]", name);
                //exit(EXIT_FAILURE);
        }
    }

    if(benchmarkFlag==1 && testFlag==1){
        printf("Please only use -t (for testing) OR -b (for benchmarking)!");
        printUsageAndExit(name);
    }

    if(benchmarkFlag==1){
        //Benchmarking:
        if(outputPath[0] != '\0'){
            printf("You can not use an output path while benchmarking.");
            printUsageAndExit(name);
        }

        //Benchmarking for different values of inputPath and Gamma!
    }

    if (outputPath[0] == '\0'){
        if(testFlag==0){
            outputPath = "GammaResult.ppm";
        }else{
            outputPath = "TestResult.ppm";
        }
    }

    if (testFlag == 0){
        //Normal execution
        if (inputPath[0] == '\0'){
            printf("No input path specified\n");
            printUsageAndExit(name);
        }
        //Check if gamma is valid
        if (gamma < 0){
            printf("Please enter a gamma value (-g) that is >= 0\n");
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
    if (inputPath[0] != '\0'){
        //test with given image
        testImage(inputPath, gamma, outputPath);
        exit(EXIT_SUCCESS);
    }
    //test with standard image
    test(gamma, outputPath);
    exit(EXIT_SUCCESS);
}


