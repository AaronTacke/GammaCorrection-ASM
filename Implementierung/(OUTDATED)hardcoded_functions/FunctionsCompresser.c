#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "GammaFunctions.h"
unsigned long long encodedFunctions[64484][8];
void convertFunction(uint8_t function[], int indexOfFunction){
    bool binaryArray[512];

    int indexInBinaryArray = 0;
    //The Value at position 0 is encoded too
    for(int i = 0; i < 255; i++){
        uint8_t difference = function[i+1] - function[i];
        binaryArray[indexInBinaryArray] = 1;
        indexInBinaryArray++;
        for(int j = 0; j < difference; j++){
            binaryArray[indexInBinaryArray] = 0;
            indexInBinaryArray++;
        }
        //printf("%d\n", binaryArray[indexInBinaryArray]);
    }
    //To encode the last Value
    binaryArray[indexInBinaryArray] = 1;

    unsigned long long currentPowerOfTwo = 1;
    encodedFunctions[indexOfFunction][0] = 0;
    encodedFunctions[indexOfFunction][1] = 0;
    encodedFunctions[indexOfFunction][2] = 0;
    encodedFunctions[indexOfFunction][3] = 0;
    encodedFunctions[indexOfFunction][4] = 0;
    encodedFunctions[indexOfFunction][5] = 0;
    encodedFunctions[indexOfFunction][6] = 0;
    encodedFunctions[indexOfFunction][7] = 0;
    for(int i = 63; i >=0; i--){
        encodedFunctions[indexOfFunction][0] += currentPowerOfTwo * binaryArray[i];
        encodedFunctions[indexOfFunction][1] += currentPowerOfTwo * binaryArray[i + 64];
        encodedFunctions[indexOfFunction][2] += currentPowerOfTwo * binaryArray[i + 128];
        encodedFunctions[indexOfFunction][3] += currentPowerOfTwo * binaryArray[i + 192];
        encodedFunctions[indexOfFunction][4] += currentPowerOfTwo * binaryArray[i + 256];
        encodedFunctions[indexOfFunction][5] += currentPowerOfTwo * binaryArray[i + 320];
        encodedFunctions[indexOfFunction][6] += currentPowerOfTwo * binaryArray[i + 384];
        encodedFunctions[indexOfFunction][7] += currentPowerOfTwo * binaryArray[i + 448];
        currentPowerOfTwo *= 2;
        printf("%llu\n", encodedFunctions[indexOfFunction][0]);
    }
}
void writeEncodedFunctions() {
    FILE *file = fopen("encodedFunctions.txt", "a+");
    if (file != NULL) {
        for(int i = 0; i < 64484; i++) {
            for (int j = 0; j < 8; j++) {
                fprintf(file, "%llu,", encodedFunctions[i][j]);
            }
            fprintf(file, "\n");
        }
        fclose(file);
    } else {
        printf("Saving the values was not possible.\n The program needs access rights for file\n");
        exit(0);
    }
}
int main() {

    int counter = 0;
    uint8_t function[256];

    for(int i = 0; i < 64484; i++){
        for(int j = 0; j < 256; j++){
            function[j] = gammaFunctions[counter];
            counter++;
        }
        convertFunction(function, i);
    }
    writeEncodedFunctions();

    return 0;
}



