#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void writeFunction(uint8_t function[]) {
    FILE *file = fopen("functionValuesResult.txt", "a+");
    if (file != NULL) {
        for (int i = 0; i < 254; i++) {
            fprintf(file, "%d,", function[i]);
        }
        fprintf(file, "\n");
        fclose(file);
    } else {
        printf("Saving the image was not possible.\n The program needs access rights for file\n");
        exit(0);
    }
}

void writeFloat(double f) {
    FILE *file = fopen("floatValuesResult.txt", "a+");
    if (file != NULL) {
        fprintf(file, "%e,\n", f);
        fclose(file);
    } else {
        printf("Saving the image was not possible.\n The program needs access rights for file\n");
        exit(0);
    }
}

uint8_t *getFunction(double gamma) {
    uint8_t *pixels = (uint8_t *) malloc(254 * sizeof(uint8_t));
    for (int i = 1; i < 255; i++) {
        if(gamma!=0) pixels[i - 1] = pow(((double) (i) / 255), gamma) * 255;
        else pixels[i-1] = 255;
    }
    return pixels;
}

int functionsEqual(uint8_t function1[], uint8_t function2[]) {
    for (int i = 0; i < 254; i++) {
        if (function1[i] != function2[i]) return 0;
    }
    return 1;
}

int main() {
    double min = 0;
    writeFloat(min);
    uint8_t *oldFunction = getFunction(min);
    writeFunction(oldFunction);
    double max = nextafter(min, 1);


    while(1) {

        uint8_t* function = getFunction(max);

        while (functionsEqual(oldFunction, function)) {
            free(function);
            max *= 2;
            function = getFunction(max);
        }
        free(function);

        while (max > min*1.00000001) {
            double middle = (min + max) / 2;
            function = getFunction(middle);
            if (functionsEqual(oldFunction, function)) {
                min = middle;
            } else {
                max = middle;
            }
            free(function);
        }


        printf("%e\n", max);

        writeFloat(max);
        free(oldFunction);
        oldFunction = getFunction(max);
        writeFunction(oldFunction);

        min = max;
    }

    return 0;
}