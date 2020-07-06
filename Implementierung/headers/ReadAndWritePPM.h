#include <stdint.h>

//Adds method to read an image and create a uint8_t array.
//The size of the image will be stored in width and height.
//Adds method to write uint8_t array back to a PPM file.

#ifndef TEAM141_READANDWRITEPPM_H
#define TEAM141_READANDWRITEPPM_H
int width;
int height;
uint8_t* readPicture(char* path);
int writePicture(char* path, uint8_t image[]);
uint8_t *unalignArray(uint8_t *alignedArray);
uint8_t *alignArray(uint8_t *oldArray);
void aligned_free(void *p);
#endif //TEAM141_READANDWRITEPPM_H
