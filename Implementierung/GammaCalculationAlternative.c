#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "GammaValues.h"

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

int main() {
    int startValue = 1;
    for (int i = startValue; i < sizeof(gammaValues) / sizeof(float); ++i) {
        float gammaValue = gammaValues[i];
        for (int j = 0; j <= 255; ++j) {
            uint8_t otherResult = pow((double)j / 255, gammaValue) * 255;
            uint8_t ourResult = calculateResult(gammaValue, j);
            if (otherResult != ourResult) {
                printf("\nwrong j: %d result: %d, expected: %d = %d ^ %e\n", j, ourResult,
                       otherResult, j, gammaValue);
            }
        }
    }
}
