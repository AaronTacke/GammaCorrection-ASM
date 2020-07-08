#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "headers/TestAndBenchmarking.h"
#include "headers/ReadAndWritePPM.h"


extern uint8_t* calculate_asm(uint8_t* picture, int width, int height, float gamma);


//Shows how to use the program and stops it.
void printUsageAndExit(char *name){
    //TODO Add more information
    printf("Usage: %s [-i inputPath] [-g gamma] [-o outputPath] [-b iterations] [-t] [-h]\n", name);

    exit(EXIT_FAILURE);
}

//Parameter is not allowed to start with 45 ('-'), otherwise it could be another argument.
void checkForValidArgument(char *programName, char operationName) {
    if (optarg[0] == 45){
        printf("Wrong argument for option: -%c\n", operationName);
        printUsageAndExit(programName);
    }
}

//Main method that is invoked when starting the program:
int main(int argc, char *argv[]){
    char *name = argv[0];
    //Set arguments to standard values:
    char *inputPath = "";
    char *outputPath = "";
    int testFlag = 0;
    int benchmarkFlag = 0;
    int benchmarkIterations = -1;
    //To know wether a gamma was specified gamma starts with -1 (illegal state).
    float gamma = -1;
    char opt;

    if (argc < 2){
        printUsageAndExit(name);
    }
    //Go through arguments and set parameters accordingly.
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
                checkForValidArgument(name, opt);
                benchmarkFlag = 1;
                benchmarkIterations = atoi(optarg);
                break;
            case 'h':
                //Show "Help page"
                printUsageAndExit(name);
                break;
            default:
                printUsageAndExit(name);
        }
    }

    //Only Bencharking OR testing is allowed at once, not both.
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
        //Print diagram if no gamma is set.
        if (gamma <= 0){
            showDiagramData(0,benchmarkIterations);
            exit(EXIT_SUCCESS);
        }

        uint8_t* arr1;
        uint8_t* arr2;
        if (inputPath[0] != '\0'){
            //test with given image
            arr1 = readPicture(inputPath);
            arr2 = alignArray(arr1);
        }else{
            //test with standard image
            //TODO Benchmark with big random array, not little test array.
            arr1 = getTestArray();
            arr2 = alignArray(arr1);
        }
        //test with standard image

        double time = calculateTime(arr2, width, height, gamma, benchmarkIterations) / benchmarkIterations;
        double compareTime = calculateCompareTime(arr1, width, height, gamma, benchmarkIterations) / benchmarkIterations;
        printf("Optimized: %f\nNormal: %f\n",time, compareTime);
        aligned_free(arr2);
        exit(EXIT_SUCCESS);
    }

    //If no output path is specified, use standard paths:
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
            printf("Please enter a gamma value (-g) that is > 0\n");
            exit(EXIT_FAILURE);
        }

        //Read, calculate and write picture.
        uint8_t* picture = readPicture(inputPath);
        uint8_t* alignedPicture = alignArray(picture);
        calculate_asm(alignedPicture, width, height, gamma);
        free(picture);
        picture = unalignArray(alignedPicture);
        aligned_free(alignedPicture);
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


