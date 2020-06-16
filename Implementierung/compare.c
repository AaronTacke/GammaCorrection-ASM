#include <math.h>
#include <stdint.h>
#include <stdio.h>

//An implementation of the calculation to test and compare our assembly code to.
void calculate(uint8_t *arr, int width, int height, float gamma){
	//Values for a, b and c are going to be stored seperately later. 
	//(And will be adapted again after implementation)
	int a = 5;
	int b = 5;
	int c = 5;
	//We have 3 values for every pixel, so the total number of values is:
	int length = width*height*3;
	for(int i = 0; i < length; i+=3){ //For every pixel:
		//Grayscale filter using formula (1) of the exercise
		uint8_t d = (a * (*(arr+i)) + b * (*(arr+i+1)) + c * (*(arr+i+2))) / (a+b+c);
		//Gamma control using formula (2) of the exercise
		float p = powf((float)d / 255, gamma) * 255;
		//Storing values back to array
		*(arr+i) = (uint8_t) p;
		*(arr+i+1) = (uint8_t) p;
		*(arr+i+2) = (uint8_t) p;
	}
}

//A test implementation that prints the result of calculate
int main(int argc, char** argv) {
	int length = 256;
	float gamma = 1.5;
	uint8_t x[3*length];
	for(int i = 0; i < length; i++){
		x[3*i] = (i/3)*3;
		x[3*i+1] = (i/3)*3;
		x[3*i+2] = (i/3)*3;
	}
	calculate(x, length, 1, gamma);
	for(int i = 0; i < length; i++){
		printf("%u, %u, %u\n", x[3*i],x[3*i+1],x[3*i+2]);
	}
	return 0;
}
