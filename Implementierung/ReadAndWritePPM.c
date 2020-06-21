#include <stdio.h>
#include <stdint.h>
#include<string.h>
#include <stdlib.h>

#define NUMBEROFCHARSPERLINE 100
int width;
int height;

int numberOfColorPortions;


void wrongFormatAndExit(){
    printf("The file has a wrong format.\n"
           "Please only use PPM files with the ASCII-format!\n");
    exit(0);
}

//TODO
//There can be errors, if there are not two values for the width and height
uint8_t* readPicture(char* path){
    char buffer[NUMBEROFCHARSPERLINE];
    FILE *file = fopen(path, "r");

    if(file == NULL){
        printf("The file %s was not found.\n", path);
        exit(0);
    }
    //First line
    if(fgets(buffer, NUMBEROFCHARSPERLINE, file) != NULL){
        //TODO what if there is a space after the P3?
        const char format[] = "P3\n";
        //If the first line has the wrong format
        if(strcmp(format, buffer) != 0){
            wrongFormatAndExit();
        }
    }else{
        wrongFormatAndExit();
    }
    //second line
    if(fgets(buffer, NUMBEROFCHARSPERLINE, file) != NULL){
        //If the second line is a comment
        if(buffer[0] == '#'){
            //The next line is read
            if(fgets(buffer, NUMBEROFCHARSPERLINE, file) == NULL){
                printf("The image has no pixels.\n"
                       "Please only use PPM files with the ASCII-format!\n");
                exit(0);
            }
        }
    }else{
        wrongFormatAndExit();
    }

    //read dimensions
    char delimiter[] = " ";
    if(strlen(buffer) < 3){
        printf("The image does not specify its width and height\n"
               "Please only use PPM files with the ASCII-format!\n");
        exit(0);
    }
    char *ptrSpace = strtok(buffer, delimiter);

    width = atoi(ptrSpace);
    ptrSpace = strtok(NULL, delimiter);
    height = atoi(ptrSpace);

    if(width<1 || height<1) {
        printf("The image does not specify its width and height\n"
               "Please only use PPM files with the ASCII-format!\n");
        exit(0);
    }

    //numberOfColorPortions is set
    if(fgets(buffer, NUMBEROFCHARSPERLINE, file) != NULL){
        numberOfColorPortions = atoi(buffer);
        //If the image has the not 255 as maxValue
        if(numberOfColorPortions != 255){
            printf("Only the pixel format with maxValue = 255 is supported.\nFound format with maxValue = %d.\n"
                   "Please only use PPM files with the ASCII-format!\n", numberOfColorPortions);
            exit(0);
        }
    }else{
        free(ptrSpace);
        wrongFormatAndExit();
    }

    //creat pixel array
    int counter = 0;
    uint8_t* pixels = (uint8_t*) malloc(width * height * 3 * sizeof(uint8_t));

    if(pixels==NULL){
        //TODO Check if other circumstances (other than a big file) can lead to pixels==null
        printf("The image is too big. Please choose another file.\n");
        exit(0);
    }

    while (fgets(buffer, NUMBEROFCHARSPERLINE, file) != NULL){
        if(counter < width * height * 3) {
            pixels[counter] = (uint8_t)(atoi(buffer));
        }
        counter++;
    }
    //Check if counter == numberOfPixels
    if(counter != width * height * 3){
        printf("The format of the image was wrong. Expected number of values: %d got number values: %d\n"
               "Please only use PPM files with the ASCII-format!\n",  width * height * 3, counter );
        free(pixels);
        exit(0);
    }

    return pixels;
}
void writePicture(char* path, uint8_t image[]){
    FILE *file = fopen(path, "w");
    if (file != NULL) {
        //Write first two lines in file
        fprintf(file, "P3\n#GreyScaledImage\n");
        //Write width and height to file
        fprintf(file, "%d ", width);
        fprintf(file, "%d\n", height);
        //Write numberOfColorPortions
        fprintf(file, "255\n");
        //Write all new RGB Values
        int lengthOfArray = width * height * 3;
        for(int i = 0; i < lengthOfArray; i++) {
            fprintf(file, "%d\n", image[i]);
        }
        fclose(file);
    } else{
        //TODO is this error message correct?
        printf("Saving the image was not possible.\n The program needs access rights for file %s\n", path);
        exit(0);
    }
}

//int main() {
//    uint8_t* pixels = readPicture("C://Test//bild2.ppm");
//    char* path = "C://Test//umgewandelt.ppm";
//    writePicture(path, pixels);
//    free(pixels);
//    return 0;
//}



