#include <stdint.h>

//Adds method to read an image and create a uint8_t array.
//The size of the image will be stored in width and height.
//Adds method to write uint8_t array back to a PPM file.

#ifndef TEAM141_READANDWRITEPPM_H
#define TEAM141_READANDWRITEPPM_H
typedef u_int8_t uint8_t;
int width;
int height;
uint8_t* readPicture(char* path);
int writePicture(char* path, uint8_t image[]);
#endif //TEAM141_READANDWRITEPPM_H
