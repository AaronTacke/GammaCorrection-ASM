#include <math.h>
#include <stdint.h>
#include <stdio.h>

int calculate(int length, uint8_t *arr){
	int a = 5;
	int b = 7;
	int c = 6;
	float lambda = 0.5;
	for(int i = 0; i < length; i+=3){
		uint8_t d = (a * (*(arr+i)) + b * (*(arr+i+1)) + c * (*(arr+i+2))) / (a+b+c);
		float gamma = powf((float)d / 255, lambda) * 255;
		*(arr+i) = (uint8_t) gamma;
		*(arr+i+1) = (uint8_t) gamma;
		*(arr+i+2) = (uint8_t) gamma;
	}
	return 0;
}

int main(int argc, char** argv) {
	int length = 300;
	uint8_t x[length];
	for(int i = 0; i < length; i++){
		x[i] = ((i*7)%256);
	}
	printf("%i\n",calculate(length, x));
	for(int i = 0; i < length; i++){
		printf("%u\n", x[i]);
	}
	return 0;
}