#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "GammaValues.h"

double* logArray;
double* gammaArray;



//This method uses binary search to find a correct value for ONE input value
uint8_t calculateResult(float gamma, int input) {

    if (input == 0) return 0;
    double logResult = log((double)(input)/255)*gamma;

    int min = 0;
    int max = 256;
    while (min < max) {

        int middle = (min + max) / 2 +1;
        double logSearch = log(((double)(middle))/255);
        if (logSearch > logResult) {
            max = middle - 1;
        } else {
            min = middle;
        }

    }
    return min;
}

    //Test for the method above.
//int main() {
//    int startValue = 1;
//    for (int i = startValue; i < sizeof(gammaValues) / sizeof(float); ++i) {
//        float gammaValue = gammaValues[i];
//        for (int j = 0; j <= 255; ++j) {
//            uint8_t otherResult = pow((double)j / 255, gammaValue) * 255;
//            uint8_t ourResult = calculateResult(gammaValue, j);
//            if (otherResult != ourResult) {
//                printf("\nwrong j: %d result: %d, expected: %d = %d ^ %e\n", j, ourResult,
//                       otherResult, j, gammaValue);
//            }
//        }
//    }
//}


//This method uses a similar algorithm to the merge-algorith of mergesort
//To find all values (1-254) that belong to one gamma
uint8_t* calculateResultArrayFast(float gamma) {
    //In assembler this is done before (in section .data):
    uint8_t* res = malloc(254*sizeof(uint8_t));

    //xor registers
    int gammaCounter = 0;
    int logCounter = 0;

    //WITH SIMD in memory OR WITHOUT memory
    for(int i = 0; i < 254; i++){
        *(gammaArray+i) = *(logArray+i) * gamma;
    }

    while(gammaCounter<255){
        //Maybe the multiplication with gamma should happen directly here?
        if(*(logArray+logCounter)<*(gammaArray+gammaCounter)){
            logCounter++;
        }else{
            res[gammaCounter] = logCounter;
            gammaCounter++;
        }
    }

    return res;
}

    //Test for the method above.
int main() {
    gammaArray = malloc(254 * sizeof(double));

    logArray = malloc(255 * sizeof(double));
    for(int i = 0; i < 254; i++){
        *(logArray+i) = log(((double)(i+1))/255);
    }
    *(logArray+254) = 1.79769e+308;

    int startValue = 1;
    for (int i = startValue; i < sizeof(gammaValues) / sizeof(float); ++i) {
        float gammaValue = gammaValues[i];
        uint8_t* res = calculateResultArrayFast(gammaValue);
        for (int j = 1; j <= 254; ++j) {
            uint8_t otherResult = pow((double)j / 255, gammaValue) * 255;
            if (otherResult != res[j-1]) {
                printf("\nwrong j: %d result: %d, expected: %d = %d ^ %e\n", j, res[j-1],
                       otherResult, j, gammaValue);
            }
        }
    }
}


//This method encrypts the Function so it can be stored in 512 bits.
//Still work in progress.
//Question: Will it ever be faster to decrypt it (~512 comparisons) than a cache hit??
int* calculateResultArrayFastEncrypted(float gamma) {
    int* bits = malloc(508);
    printf("\n");

    int gammaCounter = 0;
    int logCounter = 0;

    //WITH SIMD in memory OR WITHOUT memory
    for(int i = 0; i < 254; i++){
        *(gammaArray+i) = *(logArray+i) * gamma;
    }

    for(int i = 0; i < 508; i++){
        if(*(logArray+logCounter)<*(gammaArray+gammaCounter)){
            //0 an i-te Stelle schreiben
            printf("0");
            bits[i] = 0;
            logCounter++;
        }else{
            //1 and i-te Stelle schreiben
            printf("1");
            bits[i] = 1;
            gammaCounter++;
        }
    }

    printf("\n");
    return bits;
}


    //Test for the method above.
//int main(){
//    gammaArray = malloc(255 * sizeof(double));
//    *(gammaArray+254) = -1.79769e+308;
//
//    logArray = malloc(255 * sizeof(double));
//    for(int i = 0; i < 254; i++){
//        *(logArray+i) = log(((double)(i+1))/255);
//    }
//    *(logArray+254) = 1.79769e+308;
//
//    float gamma = 1;
//    calculateResultArrayFastEncrypted(gamma);
//
//}
