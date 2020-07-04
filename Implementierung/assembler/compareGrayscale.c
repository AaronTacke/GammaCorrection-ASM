#include <math.h>
#include <stdint.h>
#include <stdio.h>

//An implementation of the calculation to test and compare our assembly code to.
void calculate(uint8_t *arr, int width, int height, float gamma){
	//Values for a, b and c are going to be stored seperately later. 
	//(And will be adapted again after implementation)
	int a = 77;
	int b = 151;
	int c = 28;
	//We have 3 values for every pixel, so the total number of values is:
	int length = width*height*3;
	for(int i = 0; i < length; i+=3){ //For every pixel:
		//Grayscale filter using formula (1) of the exercise
		uint8_t d = (a * (*(arr+i)) + b * (*(arr+i+1)) + c * (*(arr+i+2))) / (a+b+c);
		//Storing values back to array
		*(arr+i) = (uint8_t) d;
		*(arr+i+1) = (uint8_t) d;
		*(arr+i+2) = (uint8_t) d;
	}
}
