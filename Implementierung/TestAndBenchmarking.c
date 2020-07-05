#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "headers/compare.h"
#include "headers/ReadAndWritePPM.h"
#include "headers/TestImage.h"

extern uint8_t* calculate_asm(uint8_t* picture, int width, int height, float gamma);

void writeFileIfPathNotEmpty(char* path, uint8_t* arr){
    if(path[0]!='\0'){
        writePicture(path, arr);
    }
}

//Generates TestArray that represents nice Image
uint8_t *getTestArray() {
    //Create Test Image with widht=32 and height=16 (512 pixels)
    width = 32;
    height = 16;
    //Place in the memory is allocated to save the image
    uint8_t *memory = (uint8_t *) malloc(width * height * 3 * sizeof(uint8_t)+15);
    if(memory==NULL){
        printf("The test was not executed because the program is not able to make use of sufficient memory.\nPlease choose a smaller image.\n");
    }
    //The Image is stored in the memory number by number.
    for (int i = 0; i < (width * height * 3); i++) {
        *(memory + i) = testImageArray[i];
    }
    //The pointer to the first number of the image is returned
    return memory;
}

//Copys an array to be able to call different calculate functions on it
uint8_t *copyTestArray(uint8_t *arr) {
    //Place in the memory is allocated to save the image
    uint8_t *memory = (uint8_t *) malloc(width * height * 3 * sizeof(uint8_t)+15);
    if(memory==NULL){
        printf("The test was not executed because the program is not able to make use of sufficient memory.\nPlease choose a smaller image.\n");
    }
    //The Image is stored in the memory number by number.
    for (int i = 0; i < (width * height * 3); i++) {
        *(memory + i) = *(arr + i);
    }
    //The pointer to the first number of the image is returned
    return memory;
}

//Compares the different results, shows differences if they occur
int evaluateTestResults(uint8_t *original, uint8_t *compare, uint8_t *result) {
    int correctCounter = 0;
    printf("Testing pixels...\n");
    for (int i = 0; i < (width * height); i++) {
        //Compare every pixel
        if (*(compare + 3 * i) == *(result + 3 * i) &&
            *(compare + 3 * i + 1) == *(result + 3 * i + 1) &&
            *(compare + 3 * i + 2) == *(result + 3 * i + 2)) {
            correctCounter++;
        } else {
            //When wrong print the error
            printf("Pixel(%u,%u,%u): expected: (%u,%u,%u), was: (%u,%u,%u)\n",
                   *(original + 3 * i), *(original + 3 * i + 1), *(original + 3 * i + 2),
                   *(compare + 3 * i), *(compare + 3 * i + 1), *(compare + 3 * i + 2),
                   *(result + 3 * i), *(result + 3 * i + 1), *(result + 3 * i + 2));
        }
    }
    //Summarize how many pixels were wrong
    printf("\n%i/%i pixels have been converted correctly.\n\n", correctCounter, (width * height));
    //Only if every pixel was converted correctly return 0.
    if (correctCounter == width * height)return 0;
    else return -1;
}

//Tests the standard image with a given gamma value
int testGamma(float gamma, char* outputPath) {
    //The Arrays that will be compared:
    uint8_t *original = getTestArray();
    uint8_t *result = getTestArray();
    uint8_t *compare = getTestArray();
    calculate_asm(result, width, height, gamma);
    calculate(compare, width, height, gamma);
    //Saving the picture to look at it with gamma=1
    writeFileIfPathNotEmpty(outputPath, result);
    //Print information about the test:
    printf("Test with gamma=%f\n", gamma);
    return evaluateTestResults(original, compare, result);
}

//Tests the image (given as parameter) with the given gamma value
int testImageGamma(uint8_t *original, float gamma, char* outputPath) {
    //The Arrays that will be compared:
    uint8_t *result = copyTestArray(original);
    uint8_t *compare = copyTestArray(original);
    calculate_asm(result, width, height, gamma);
    calculate(compare, width, height, gamma);
    //Saving the picture to look at it with gamma=1
    writeFileIfPathNotEmpty(outputPath, result);
    //Print information about the test:
    printf("Test with gamma=%f\n", gamma);
    return evaluateTestResults(original, compare, result);
}

//Test the standard image with different gamma values
int test(float gamma, char* outputPath) {
    writePicture("./TestOriginal.ppm", getTestArray());
    if (gamma >= 0) {
        //Just test with given gamma value
        if (testGamma(gamma, outputPath) != 0) {
            printf("Test failed with gamma=%f\n", gamma);
            return -1;
        }
    } else {
        for (float i = 0.2; i <= 2.1; i += 0.2) {
            //Test with different gamma values
            int testResult;
            if(i>0.9 && i<1.1){
                testResult = testGamma(i, outputPath);
            }else{
                testResult = testGamma(i, "");
            }
            if (testResult != 0) {
                //If one tests fails the whole test fails.
                printf("Test failed with gamma=%f\n", i);
                return -1;
            }
        }
    }
    //Otherwise it passed the test
    printf("Everything worked as expected.\n");
    return 0;
}

//Tests a given image with different gamma values
int testImage(char *path, float gamma, char* outputPath) {
    //load the image
    uint8_t *original = readPicture(path);
    if (gamma >= 0) {
        //Just test with given gamma value
        if (testImageGamma(original, gamma, outputPath) != 0) {
            printf("Test failed with gamma=%f\n", gamma);
            return -1;
        }
    } else {
        //Test with different gamma values
        for (float i = 0.2; i <= 2.1; i += 0.2) {
            int testResult;
            if(i>0.9 && i<1.1){
                testResult = testImageGamma(copyTestArray(original), i, outputPath);
            }else{
                testResult = testImageGamma(copyTestArray(original), i, "");
            }
            if (testResult != 0) {
                //If one tests fails the whole test fails.
                printf("Test failed with gamma=%f\n", i);
                return -1;
            }
        }
    }
    //Otherwise it passed the test
    printf("Everything worked as expected.\n");
    return 0;
}

double calculateTime(uint8_t *arr, int width, int height, float gamma, int iterations){
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);
    for(int i = 0; i < iterations; i++){
        calculate_asm(arr, width, height, gamma);
    }
    struct timespec end;
    clock_gettime(CLOCK_MONOTONIC, &end);
    double duration = end.tv_sec - start.tv_sec + 1e-9 *(end.tv_nsec - start.tv_nsec);
    //double averageTime = duration / iterations;
    return duration;
}

double calculateCompareTime(uint8_t *arr, int width, int height, float gamma, int iterations){
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);
    for(int i = 0; i < iterations; i++){
        calculate(arr, width, height, gamma);
    }
    struct timespec end;
    clock_gettime(CLOCK_MONOTONIC, &end);
    double duration = end.tv_sec - start.tv_sec + 1e-9 *(end.tv_nsec - start.tv_nsec);
    //double averageTime = duration / iterations;
    return duration;
}

uint8_t *getSquareImage(int useGrayscale, int size){
    width = size;
    height = size;
    uint8_t *arr = (uint8_t *) malloc(width * height * 3 * sizeof(uint8_t)+15);
    if(arr==NULL){
        printf("The benchmark was not executed because the program is not able to make use of sufficient memory.\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < width*height*3; i+=3){
        if(useGrayscale!=0){
            uint8_t r = rand()%256;
            *(arr + i) = r;
            *(arr + i + 1) = r;
            *(arr + i + 2) = r;
        }else{
            *(arr + i) = rand()%256;
            *(arr + i + 1) = rand()%256;
            *(arr + i + 2) = rand()%256;
        }
    }
    return arr;
}

void showDiagramData(int useGrayscale, int iterations){
    printf("ImageSize;durationC;durationASM\n");
    for(int i = 100; i <= 2000; i+=100){
        uint8_t* originalArray = getSquareImage(useGrayscale,i);
        double cTime = 0;
        double asmTime = 0;
        for(float g = 0.2; g < 2.1; g+=0.2){
            uint8_t* copyArray = copyTestArray(originalArray);
            cTime += calculateCompareTime(copyArray,width,height,g, iterations);
            free(copyArray);
            copyArray = copyTestArray(originalArray);
            asmTime += calculateTime(copyArray,width,height,g,iterations);
            free(copyArray);
        }
        cTime = cTime/(iterations*8);
        asmTime = asmTime/(iterations*8);
        printf("%d;%f;%f\n",i,cTime,asmTime);
        free(originalArray);
    }
}