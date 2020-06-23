#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include "GammaFunctions.h"
#include "GammaValues.h"

int counterSteps = 0;

float binaryPow(float base, int exponent){
    if(exponent == 0) {
        return 1;
    }
    if(exponent == 1) {
        return base;
    }
    float result = base;
    int counter = 1;
    while(counter < exponent){
        result *= result;
        counter *= 2;
        counterSteps++;
    }
    return result;
}

float fastPower(float base, int exponent){
    if(exponent == 0) {
        return 1;
    }
    if(exponent == 1) {
        return base;
    }
    float result = 1;
    int counter = 1;
    while (exponent > 0){
        printf("%d\n", exponent);
        int rest = exponent % 2;
        exponent = exponent / 2;
        if(rest == 1){
            counterSteps++;
            result *= binaryPow(base, counter);
        }
        counter*=2;
    }
    return result;
}

int ggT(int a, int b){
    if(b == 0)
        return a;
    else return ggT(b, a % b);
}

uint8_t calculateResult(float gamma, int input){
    int n = 1;
    int z = round(gamma);
    float maxErr = 0.00005;
    while (gamma - z > maxErr){
        gamma *= 10;
        z = round(gamma);
        n *= 10;
    }
    //used to create smaller values for z and n
    int ggt = ggT(z, n);
    z /= ggt;
    n /= ggt;
    //printf("z: %d n: %d\n", z, n);
    float a = fastPower((float)input / 255, z);

    uint8_t min = 0;
    uint8_t max = 255;
    int middle;
    while(min < max){
        middle = (min+max)/2+1;
        //printf("middle: %d\n", middle);
        if(fastPower((float)middle / 255, n) > a){
            max = middle - 1;
        }else{
            min = middle;
        }
    }
    //printf("result: %d", min);
    return min;
}

int main() {
    int counter = 0;
    for (int i = 0; i < sizeof(gammaValues) / sizeof(uint8_t); ++i) {
        for (int j = 0; j <= 255; ++j) {
            uint8_t ourResult = calculateResult(gammaValues[i], j);
            if (gammaFunctions[counter] != ourResult) {
                printf("wrong result, our Result: %d, actual result: %d counter %d\n", ourResult,
                       gammaFunctions[counter], counter);
            }
            counter++;
        }

    }
}
