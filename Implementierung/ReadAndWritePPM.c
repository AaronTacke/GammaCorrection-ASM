#include <stdio.h>
#include <stdint.h>
#include<string.h>
#include <stdlib.h>

#define NUMBEROFCHARSPERLINE 100
int width;
int height;

int numberOfColorPortions;
//TODO
//Fehler beheben, wenn die Datei nicht genügend Zeilen enthält
uint8_t* readPicture(char* path){
    char buffer[NUMBEROFCHARSPERLINE];
    FILE *file = fopen(path, "r");

    if(file == NULL){
        printf("Was not able to read file!");
        exit(0);
    }
    //First line
    if(!feof(file)){
        const char format[] = "P3\n";
        fgets(buffer, NUMBEROFCHARSPERLINE, file);
        //If the first line has the wrong format
        if(strcmp(format, buffer) != 0){
            printf("The file has not the ASCII-format!");
            exit(0);
        }
    }else{
        printf("The format of the file is wrong");
        exit(0);
    }
    //second line
    if(!feof(file)){
        fgets(buffer, NUMBEROFCHARSPERLINE, file);
        //If the second line is a comment
        if(buffer[0] == '#'){
            //The next line is read
            if(!feof(file)) {
                fgets(buffer, NUMBEROFCHARSPERLINE, file);
            }else{
                printf("The file has no pixels");
                exit(0);
            }
        }
    }else{
        printf("The format of the file is wrong");
        exit(0);
    }

    //read dimensions
    char delimiter[] = " ";
    char *ptrSpace = strtok(buffer, delimiter);
    width = atoi(ptrSpace);
    ptrSpace = strtok(NULL, delimiter);
    height = atoi(ptrSpace);

    //numberOfColorPortions is set
    if(!feof(file)){
        fgets(buffer, NUMBEROFCHARSPERLINE, file);
        numberOfColorPortions = atoi(buffer);
        //If the image has the not 255 as maxValue
        if(numberOfColorPortions != 255){
            printf("Only the pixel format with minValue = 0 maxValue = 255 is supported got format: %d", numberOfColorPortions);
            exit(0);
        }
    }else{
        printf("The file has the wrong format");
        free(ptrSpace);
        exit(0);
    }

    //creat pixel array
    int counter = 0;
    uint8_t* pixels = (uint8_t*) malloc(width * height * 3 * sizeof(uint8_t));

    //TODO
    //Test if malloc returns null to make sure no SegFaults happen

    while (!feof(file) && counter < width * height * 3){
        fgets(buffer, NUMBEROFCHARSPERLINE, file);
        pixels[counter] = atoi(buffer);
        counter++;
    }
    //Check if counter == numberOfPixels
    if(counter != width * height * 3){
        printf("The format of the image was wrong expected number of values: %d got number values: %d\n",  width * height * 3, counter );
        free(pixels);
        exit(0);
    }
    return pixels;
}
int writePicture(char* path, uint8_t image[]){
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
        return 0;
    } else{
        printf("Error by writing in file");
        return -1;
    }
}

/*
 * Vielleicht ist es doch sinnvolle ein neues Array mit den Grauwerten zu erstellen, weil dies dann nur ein drittel der Pixel
 * enthält
 */
//int main() {
//    uint8_t* pixels = readPicture("C://Test//bild2.ppm");
//    char* path = "C://Test//umgewandelt.ppm";
//    writePicture(path, pixels);
//    free(pixels);
//    return 0;
//}


