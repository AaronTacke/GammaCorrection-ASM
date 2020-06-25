#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "GammaFunctions.h"
#include "GammaValues.h"

int counterSteps = 0;

double binaryPow(double base, int exponent) {
    if (exponent == 0) {
        return 1;
    }
    if (exponent == 1) {
        return base;
    }
    double result = base;
    int counter = 1;
    while (counter < exponent) {
        result *= result;
        counter *= 2;
        counterSteps++;
    }
    return result;
}

double fastPower(double base, int exponent) {
    if (exponent == 0) {
        return 1;
    }
    if (exponent == 1) {
        return base;
    }
    double result = 1;
    int counter = 1;
    while (exponent > 0) {
        //printf("%d\n", exponent);
        int rest = exponent % 2;
        exponent = exponent / 2;
        if (rest == 1) {
            counterSteps++;
            result *= binaryPow(base, counter);
        }
        counter *= 2;
    }
    return result;
}

int ggT(int a, int b) {
    if (b == 0)
        return a;
    else return ggT(b, a % b);
}

uint8_t calculateResult(float gamma, int input) {
    //TODO maybe later not needed:
    if (input == 0) return 0;

    int n = 1;
    int z = round(gamma);
    double maxErr = 0.00000005;
    while (fabs(gamma - ((double) (z) / n)) > maxErr) {
        n *= 8;
        z = round(gamma * n);
    }

    //used to create smaller values for z and n
    int ggt = ggT(z, n);
    z /= ggt;
    n /= ggt;

    double faktor = (double)(z)/32;
    if(faktor>1){
        z = round((double)(z)/faktor);
        n = round((double)(n)/faktor);
    }

    faktor = (double)(n)/32;
    if(faktor>1){
        z = round((double)(z)/faktor);
        n = round((double)(n)/faktor);
    }

    printf("\n%d/%d\n",z,n);

    //double a = fastPower((double) (input) / 255, z);
    double a = pow((double)(input),z);
    if(z>n) a *= pow((double)(255),n-z);

    int min = 0;
    int max = 256;
    int middle;
    while (min < max) {
        middle = (min + max) / 2 + 1;
        //printf("middle: %d\n", middle);
        //double pow = fastPower((double)(middle) / 255, n);
        double pow1 = pow((double)(middle),n);
        if(n>z) pow1 = pow1 * pow((double)(255),z-n);
        //double pow = powf((double) (middle) / 255, n);
        if (pow1 > a) {
            max = middle - 1;
        } else {
            min = middle;
        }
    }
    //printf("result: %d", min);
    return min;
}

int main() {

    int startValue = 30000;
    int counter = startValue * 256;
    for (int i = startValue; i < sizeof(gammaValues) / sizeof(float); ++i) {
        float gammaValue = gammaValues[i];
        int correct = 1;
        for (int j = 0; j <= 255; ++j) {
            uint8_t ourResult = calculateResult(gammaValue, j);
            if (gammaFunctions[counter] != ourResult) {
                //printf("wrong j: %d result: %d, expected: %d = %d ^ %f\n", j, ourResult,
                  //     gammaFunctions[counter], j, gammaValue);
                  printf("%d\n",ourResult-gammaFunctions[counter]);
                correct = 0;
            } else {
                //printf("correct %d^%f=%d\n", j, gammaValue, ourResult);
                printf(".");
            }
            counter++;
        }
        if (correct == 0) printf("\nWrong with gamma=%f\n", gammaValue);
        else printf("\nCorrect with gamma=%f\n", gammaValue);
    }
}
