#include <stdint.h>


//Adds method test() to test the programm with a standard image
//Adds method testIamge(char* path) to test the program with a chosen file.
//The tests will use the method of compare.h and detect differences
//It uses different gamma values. Wrong pixels will be printed.

#ifndef TEAM141_TEST_H
#define TEAM141_TEST_H
int test(float gamma, char* outputPath);
int testImage(char* path, float gamma, char* outputPath);
double calculateTime(uint8_t *arr, int width, int height, float gamma, int iterations);
double calculateCompareTime(uint8_t *arr, int width, int height, float gamma, int iterations);
uint8_t *getTestArray();
void showDiagramData(int useGrayscale, int iterations);
#endif //TEAM141_TEST_H
