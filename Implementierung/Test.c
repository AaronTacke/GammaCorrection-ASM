#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "compare.h"
#include "ReadAndWritePPM.h"
#include "TestImage.h"


//Calls method to be tested
void calculateTest(uint8_t *arr, int width, int height, float gamma) {
    calculate(arr, width, height, gamma);
}

//Calls correct method to compare our results to
void compareCalculateTest(uint8_t *arr, int width, int height, float gamma) {
    calculate(arr, width, height, gamma);
}

//Calls method that opens a PPM Image
uint8_t *readPictureTest(char *path) {
    return readPicture(path);
}

//Calls method that saves a PPM Image
int writePictureTest(char *path, uint8_t image[]) {
    return writePicture(path, image);
}

void writeFileIfPathNotEmpty(char* path, uint8_t* arr){
    if(path[0]!='\0'){
        writePictureTest(path, arr);
    }
}

//Generates TestArray that represents nice Image
uint8_t *getTestArray() {
    //Create Test Image with widht=32 and height=16 (512 pixels)
    width = 32;
    height = 16;
    //Place in the memory is allocated to save the image
    uint8_t *memory = (uint8_t *) malloc(width * height * 3 * sizeof(uint8_t));
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
    uint8_t *memory = (uint8_t *) malloc(width * height * 3 * sizeof(uint8_t));
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
    printf("Testing pixels...");
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
    calculateTest(result, width, height, gamma);
    compareCalculateTest(compare, width, height, gamma);
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
    calculateTest(result, width, height, gamma);
    compareCalculateTest(compare, width, height, gamma);
    //Saving the picture to look at it with gamma=1
    writeFileIfPathNotEmpty(outputPath, result);
    //Print information about the test:
    printf("Test with gamma=%f\n", gamma);
    return evaluateTestResults(original, compare, result);
}

//Test the standard image with different gamma values
int test(float gamma, char* outputPath) {
    writePictureTest("./TestOriginal.ppm", getTestArray());
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
    uint8_t *original = readPictureTest(path);
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
/*double calculateTime(){
    int iterations = 100;
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);
    for(int i = 0; i < iterations; i++){
        //Do something
    }
    struct timespec end;
    clock_gettime(CLOCK_MONOTONIC, &end);
    double duration = end.tv_sec - start.tv_sec + 1e-9 *(end.tv_nsec - start.tv_nsec);
    double averageTime = duration / iterations;
    return averageTime;
}*/

//int main(int argc, char** argv){
//    test();
//    testImage("andererTest.ppm");
//    return 0;
//}
