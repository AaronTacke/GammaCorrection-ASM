#include <stdint.h>
#include <stdio.h>
//#include "GammaFunctions.h"
//#include "GammaValues.h"
#include "encodedFunctionsSmall.h"

extern void decodeFunction(long long *compressedFunction, uint8_t *result);
/*
void calculateOptimized(uint8_t *arr, int width, int height, float gamma){
    //BinarySearch for the correct GammaFunction:
    int min = 0;
    int max = 64485;
    int middle;
    while(min<max){
        middle = (min+max)/2+1;
        if(gammaValues[middle]>gamma){
            max = middle-1;
        }else{
            min = middle;
        }
    }


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
        //float p = powf((float)d / 255, gamma) * 255;
        uint8_t p = gammaFunctions[min*256+d];
        //Storing values back to array
        *(arr+i) = (uint8_t) p;
        *(arr+i+1) = (uint8_t) p;
        *(arr+i+2) = (uint8_t) p;
    }
    */
    void decode(uint8_t *result, int indexOfFunction){
        decodeFunction(compressedFunctionsSmall[indexOfFunction * 8], result)
    }
    void main() {
        uint8_t *result[256];
        decode(result, 1);
        for (int i = 0; i < 256; ++i) {
            printf("%d\n", result[i])
        }
    }
}