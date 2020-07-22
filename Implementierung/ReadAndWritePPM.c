#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define NUMBEROFCHARSPERLINE 100
int width;
int height;

int numberOfColorPortions;

/* This file offers methods to read and write a PPM file.
 *
 * uint8_t readPicture(char* path):
 * It checks if the file is correct and creates a pixel array if so.
 *
 * writePicture(char* path, uint8_t image[])
 * It saves a pixel array into a correct file.
 */


void wrongFormatAndExit(){
    printf("The file has a wrong format.\n"
           "Please only use PPM files with the ASCII-format!\n");
    exit(0);
}

uint8_t* readPicture(char* path){
    char buffer[NUMBEROFCHARSPERLINE];
    FILE *file = fopen(path, "r");

    //Check to stop seg-faults:
    if(file == NULL){
        printf("The file %s was not found.\n", path);
        exit(0);
    }
    //First line
    if(fgets(buffer, NUMBEROFCHARSPERLINE, file) != NULL){
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

    //Get information out of file:
    width = atoi(ptrSpace);
    ptrSpace = strtok(NULL, delimiter);
    height = atoi(ptrSpace);

    //Image has to have pixel:
    if(width<1 || height<1) {
        printf("The image does not specify its width and height\n"
               "Please only use PPM files with the ASCII-format!\n");
        exit(0);
    }

    //numberOfColorPortions is set
    if(fgets(buffer, NUMBEROFCHARSPERLINE, file) != NULL){
        numberOfColorPortions = atoi(buffer);
        //If the image has the not 255 as maxValue an error message is printed
        if(numberOfColorPortions != 255){
            printf("Only the pixel format with maxValue = 255 is supported.\nFound format with maxValue = %d.\n"
                   "Please only use PPM files with the ASCII-format!\n", numberOfColorPortions);
            exit(0);
        }
    }else{
        free(ptrSpace);
        wrongFormatAndExit();
    }

    //creat pixel array //+15 is used as optimization so that the Assembler code doesnt have to check where to end.
    int counter = 0;
    uint8_t* pixels = (uint8_t*) malloc(width * height * 3 * sizeof(uint8_t)+15);

    if(pixels==NULL){
        printf("Was not able to allocate the memory space needed for this image.\n");
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
void writePicture(char* path, uint8_t image[]) {
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
        for (int i = 0; i < lengthOfArray; i++) {
            fprintf(file, "%d\n", image[i]);
        }
        fclose(file);
    } else {
        printf("Saving the image was not possible.\n The program needs access rights for file %s\n", path);
        exit(0);
    }
}


//########################################################################################
    //Code from https://stackoverflow.com/questions/38088732/explanation-to-aligned-malloc-implementation
    //Visited on 6th of July 2020, 17:10.
    //Copied following 2 methods to allocate aligned memory
    void* aligned_malloc(size_t required_bytes, size_t alignment){
        void* p1; // original block
        void** p2; // aligned block
        int offset = alignment - 1 + sizeof(void*);
        if ((p1 = (void*)malloc(required_bytes + offset)) == NULL)
        {
            return NULL;
        }
        p2 = (void**)(((size_t)(p1) + offset) & ~(alignment - 1));
        p2[-1] = p1;
        return p2;
    }
    void aligned_free(void *p){
        free(((void**)p)[-1]);
    }
//#######################################################################################

    //This method is used to align an pixel-array before calculating. This ensures that the read and write operations can be much faster.
    uint8_t *alignArray(uint8_t* oldArray){
        uint8_t* pixels = (uint8_t*) aligned_malloc(1.2 * width * height * 3 * sizeof(uint8_t)+15, 16);
        if(pixels==NULL){
            printf("Error when allocating aligned memory. Please choose smaller image or insert bigger RAM\n");
        }
        int position = 0;
        for(int i = 0; i < width*height*3; i+=15){
            for(int j = 0; j < 16; j++){
                *(pixels + position + j) = *(oldArray + i + j);
            }
            position += 16;
        }
        return pixels;
    }
    //This method is used to unalign an calculated array, to make it comparable to the c implementation.
    uint8_t *unalignArray(uint8_t* alignedArray){
        uint8_t* pixels = (uint8_t*) malloc(width * height * 3 * sizeof(uint8_t)+15);
        if(pixels==NULL){
            printf("Error when allocating aligned memory. Please choose smaller image or insert bigger RAM\n");
        }
        int position = 0;
        for(int i = 0; i < width*height*3; i+=15){
            for(int j = 0; j < 16; j++){
                *(pixels + i + j) = *(alignedArray + position + j);
            }
            position += 16;
        }
        return pixels;
    }




