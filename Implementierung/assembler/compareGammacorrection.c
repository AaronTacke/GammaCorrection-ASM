#include <math.h>
#include <stdint.h>
#include <stdio.h>

//An implementation of the calculation to test and compare our assembly code to.
void calculate(uint8_t *arr, int width, int height, float gamma){

	//We have 3 values for every pixel, so the total number of values is:
	int length = width*height*3;
	for(int i = 0; i < length; i+=3){ //For every pixel:
		uint8_t d = *(arr+i);
		//Gamma control using formula (2) of the exercise
		float p = powf((float)d / 255, gamma) * 255;
		//Storing values back to array
		*(arr+i) = (uint8_t) p;
		*(arr+i+1) = (uint8_t) p;
		*(arr+i+2) = (uint8_t) p;
	}
}
