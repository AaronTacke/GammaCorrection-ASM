#include <stdint.h>

//Implemented Calculation in plain c to compare to assembly code.
//This will be used for testing and measuring.

//According classes would be compareBoth.c, compareGamma.c or compareGrayscale.c
//The makefile should choose the correct one to be compared to the equivalent Assembler method.

#ifndef TEAM141_COMPARE_H
#define TEAM141_COMPARE_H
void calculate(uint8_t *arr, int width, int height, float gamma);
#endif //TEAM141_COMPARE_H
