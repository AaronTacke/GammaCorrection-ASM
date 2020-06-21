#include <stdint.h>

//Implemented Calculation in plain c to compare to assembly code.
//This will be used for testing and measuring.

#ifndef TEAM141_COMPARE_H
#define TEAM141_COMPARE_H
typedef u_int8_t uint8_t;
void calculate(uint8_t *arr, int width, int height, float gamma);
#endif //TEAM141_COMPARE_H
