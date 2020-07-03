#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "Test.h"
#include "ReadAndWritePPM.h"
//#include "AssemblerAlternative.h"

typedef u_int8_t uint8_t;

extern uint8_t* calculate_asm(uint8_t* picture, int width, int height, float gamma);


//Later replaced with Assembler file:
void replaceWithAssembler(uint8_t* picture, int width, int height, float gamma){
    //calculateOptimized(picture,width,height,gamma);
    calculate_asm(picture,width,height,gamma);
}


void printUsageAndExit(char *name){
    //TODO Add more information
    printf("Usage: %s [-i inputPath] [-g gamma] [-o outputPath] [-t] [-b] [-h]\n", name);

    exit(EXIT_FAILURE);
}

void checkForValidArgument(char *programName, char operationName) {
    if (optarg[0] == 45){
        printf("Wrong argument for option: -%c\n", operationName);
        printUsageAndExit(programName);
    }
}

int main(int argc, char *argv[]){
    char *name = argv[0];
    char *inputPath = "";
    char *outputPath = "";
    int testFlag = 0;
    int benchmarkFlag = 0;
    int benchmarkIterations = 100;
    //set gamma to 1 as default value
    float gamma = -1;
    char opt;

    if (argc < 2){
        printUsageAndExit(name);
    }
    while ((opt = getopt(argc, argv, ":i:g:to:b:h")) != -1) {
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
                if (optarg != NULL){
                    checkForValidArgument(name, opt);
                    benchmarkIterations = atoi(optarg);
                }
                break;
            case 'h':
                printUsageAndExit(name);
                break;
            case ':':
                if (optopt != 'b'){
                    printUsageAndExit(name);
                }
                benchmarkFlag = 1;
                break;
            default:
                printUsageAndExit(name);
        }
    }

    if(benchmarkFlag==1 && testFlag==1){
        printf("Please only use -t (for testing) OR -b (for benchmarking)!\n");
        printUsageAndExit(name);
    }

    if(benchmarkFlag==1){

        //Benchmarking:
        if(outputPath[0] != '\0'){
            printf("You can not use an output path while benchmarking.\n");
            printUsageAndExit(name);
        }
        uint8_t* arr;
        if (inputPath[0] != '\0'){
            //test with given image
            arr = readPicture(inputPath);
        }else{
            //test with standard image
            arr = getTestArray();
        }
        //test with standard image

        double time = calculateTime(arr, width, height, gamma, benchmarkIterations);
        double compareTime = calculateCompareTime(arr, width, height, gamma, benchmarkIterations);
        printf("Optimized: %f\nNormal: %f\n",time, compareTime);
        exit(EXIT_SUCCESS);
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
        if (gamma <= 0){
            printf("Please enter a gamma value (-g) that is >= 0\n");
            exit(EXIT_FAILURE);
        }

        uint8_t* picture = readPicture(inputPath);
        replaceWithAssembler(picture, width, height, gamma);
        if(writePicture(outputPath, picture)!=0){
            printf("Error while saving image.\n");
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


