#include <math.h>
#include <stdint.h>
#include <stdio.h>

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

int main() {
    float result = fastPower(5.19, 9);
    printf("%f\n", result);
    printf("%d", counterSteps);
}
