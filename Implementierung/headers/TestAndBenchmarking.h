#include <stdint.h>


//Adds method test() to test the programm with a standard image
//Adds method testIamge(char* path) to test the program with a chosen file.
//The tests will use the method of compare.h and detect differences
//It uses different gamma values. Wrong pixels will be printed.

//calculateTime and calculateCompareTime can be used for benchmarking with special parameters / images.
//showDiagramData is used to create a csv-style data table that shows benchmarking results.

//getTestArray() returns the testArray of TestImage.h with specified width and height.

#ifndef TEAM141_TEST_H
#define TEAM141_TEST_H
int test(float gamma, char* outputPath);
int testImage(char* path, float gamma, char* outputPath);
double calculateTime(uint8_t *arr, int width, int height, float gamma, int iterations);
double calculateCompareTime(uint8_t *arr, int width, int height, float gamma, int iterations);
uint8_t *getTestArray();
void showDiagramData(int useGrayscale, int iterations);
uint8_t *getSquareImage(int useGrayscale, int size);
#endif //TEAM141_TEST_H
