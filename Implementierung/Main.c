#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "headers/TestAndBenchmarking.h"
#include "headers/ReadAndWritePPM.h"


extern uint8_t* calculate_asm(uint8_t* picture, int width, int height, float gamma);


//Shows how to use the program and stops it.
void printUsageAndExit(char *name){
    printf("\nThis is %s.\nThe fast grayscale-filter with gamma correction for PPM-files.\n\n", name);

    printf("Usage:\n%s [-i inputPath] [-g gamma] [-o outputPath] [-b iterations] [-t] [-h]\n\n", name);

    printf("Operating modes:\n");
    printf("[]\t\tnormal image processing\n");
    printf("-h:\t\tprint this help page\n");
    printf("-t:\t\ttest optimized implementation\n\t\t(not allowed with -b)\n");
    printf("-b iterations:\tbenchmark implementation \n\t\t(not allowed with -t or -o)\n\n");

    printf("Normal image processing:\n");
    printf("-i inputPath:\tpath of image (Required!)\n");
    printf("-g gamma:\tvalue for gamma > 0 (Required!)\n");
    printf("-o outputPath:\tpath of result image (Optional)\n");
    printf("\t\tStandard: ./GammaResult.ppm\n\n");

    printf("Test opitimized implementation (-t):\n");
    printf("-i inputPath:\ttest image path (Optional)\n");
    printf("\t\tStandard: Small 32x16 test image\n");
    printf("-g gamma:\tvalue for gamma > 0 (Optional)\n");
    printf("\t\tStandard: 10 gamma values between 0.2 and 2\n");
    printf("-o outputPath:\tpath of result image (Optional)\n");
    printf("\t\tStandard: ./TestResult.ppm\n\n");

    printf("Benchmark implementation (-b iterations):\n");
    printf("\t\titerations: specifies number of measurements.\n");
    printf("-i inputPath:\tpath of image for benchmarking (Optional)\n");
    printf("\t\tStandard: Random 4096x4096 image.\n");
    printf("-g gamma:\tvalue for gamma >0 (Optional)\n");
    printf("\t\tStandard: 1.\n");
    printf("If -i and -g are both not specified a csv-style benchmarking-table is created. ");
    printf("This table shows speed of optimized and compare-implementation calculating images from 100x100 to 2000x2000 pixels.\n\n");

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
                //input path parameter
                checkForValidArgument(name, opt);
                inputPath = optarg;
                break;
            case 'o':
                //output path parameter
                checkForValidArgument(name, opt);
                outputPath = optarg;
                break;
            case 'g':
                //gamma parameter
                checkForValidArgument(name, opt);
                gamma = atof(optarg);
                break;
            case 't':
                //test parameter
                testFlag = 1;
                break;
            case 'b':
                //benchmark parameter
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

    //Only benchmarking OR testing is allowed at once, not both.
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
        if (gamma <= 0 && inputPath[0] == '\0') {
            //Only if no gamma and no input path is specified.
            showDiagramData(0,benchmarkIterations);
            exit(EXIT_SUCCESS);
        }

        if(gamma<=0){
            //If gamma not specified but input path specified set gamma to 1.
            gamma = 1;
        }

        uint8_t* arr1;
        uint8_t* arr2;
        if (inputPath[0] != '\0'){
            //test with given image
            arr1 = readPicture(inputPath);
            arr2 = alignArray(arr1);
        }else{
            //test with random 4096x4096 image
            arr1 = getSquareImage(0, 4096);
            arr2 = alignArray(arr1);
        }

        double time = calculateTime(arr2, width, height, gamma, benchmarkIterations) / benchmarkIterations;
        double compareTime = calculateCompareTime(arr1, width, height, gamma, benchmarkIterations) / benchmarkIterations;
        printf("Optimized: %f\nNormal: %f\n",time, compareTime);
        aligned_free(arr2);
        free(arr1);
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
            printUsageAndExit(name);
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
        free(picture);
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


