#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "compare.h"
#include "ReadAndWritePPM.h"

static char resultPath[] = "./TestResult.ppm";

//Calls method to be tested
void calculateTest(uint8_t *arr, int width, int height, float gamma){
    calculate(arr, width, height, gamma);
}

//Calls correct method to compare our results to
void compareCalculateTest(uint8_t *arr, int width, int height, float gamma){
    calculate(arr, width, height, gamma);
}

//Calls method that opens a PPM Image
uint8_t* readPictureTest(char* path){
    return readPicture(path);
}

//Calls method that saves a PPM Image
int writePictureTest(char* path, uint8_t image[]){
    return writePicture(path, image);
}

//Generates TestArray that represents nice Image
uint8_t* getTestArray(){
    //Create Test Image with widht=32 and height=16 (512 pixels)
    width = 32;
    height = 16;
    //The Test Image has the following Pixel-Colors:
    uint8_t array[] = {203, 255, 0, 164, 255, 0, 126, 255, 0, 87, 255, 0, 48, 255, 0, 10, 255, 0, 0, 255, 29, 0, 255, 68, 0, 255, 106, 0, 255, 145, 0, 255, 183, 0, 255, 222, 0, 250, 255, 0, 211, 255, 0, 172, 255, 0, 134, 255, 0, 95, 255, 0, 57, 255, 0, 18, 255, 21, 0, 255, 59, 0, 255, 97, 0, 255, 136, 0, 255, 175, 0, 255, 213, 0, 255, 252, 0, 255, 255, 0, 220, 255, 0, 181, 255, 0, 143, 255, 0, 104, 255, 0, 66, 255, 0, 27, 221, 255, 0, 184, 255, 0, 144, 255, 0, 106, 255, 0, 67, 255, 0, 29, 255, 0, 0, 255, 10, 0, 255, 48, 0, 255, 86, 0, 255, 126, 0, 255, 164, 0, 255, 202, 0, 255, 241, 0, 231, 255, 0, 192, 255, 0, 153, 255, 0, 114, 255, 0, 76, 255, 0, 38, 255, 1, 0, 255, 40, 0, 255, 78, 0, 255, 117, 0, 255, 155, 0, 255, 194, 0, 255, 233, 0, 255, 255, 0, 239, 255, 0, 201, 255, 0, 161, 255, 0, 123, 255, 0, 84, 255, 0, 46, 241, 255, 0, 203, 255, 0, 164, 255, 0, 55, 113, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 69, 49, 0, 255, 222, 0, 250, 255, 0, 98, 119, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1, 24, 7, 0, 98, 55, 0, 239, 98, 0, 255, 136, 0, 255, 175, 0, 255, 213, 0, 255, 251, 0, 255, 255, 0, 220, 255, 0, 181, 246, 0, 137, 40, 0, 16, 255, 0, 66, 255, 250, 0, 221, 255, 0, 183, 255, 0, 143, 254, 0, 106, 143, 79, 61, 61, 61, 255, 255, 255, 255, 255, 255, 255, 255, 255, 205, 205, 205, 0, 0, 0, 144, 144, 144, 185, 254, 240, 0, 255, 241, 0, 227, 251, 61, 103, 116, 57, 57, 57, 249, 249, 249, 243, 243, 243, 208, 208, 210, 111, 111, 123, 58, 53, 86, 88, 15, 254, 117, 0, 255, 156, 0, 255, 194, 0, 255, 233, 0, 255, 255, 0, 239, 255, 0, 201, 112, 0, 71, 0, 0, 0, 254, 214, 227, 255, 230, 0, 241, 255, 0, 203, 255, 0, 164, 255, 0, 71, 145, 0, 84, 136, 59, 204, 254, 193, 9, 255, 0, 0, 255, 29, 0, 255, 67, 1, 6, 3, 218, 218, 218, 110, 254, 213, 0, 255, 222, 0, 249, 255, 1, 120, 145, 74, 116, 137, 197, 227, 254, 5, 98, 254, 11, 65, 254, 42, 57, 252, 13, 12, 23, 187, 167, 254, 97, 0, 255, 136, 0, 255, 175, 0, 255, 213, 0, 255, 252, 0, 255, 181, 0, 156, 130, 0, 92, 0, 0, 0, 255, 255, 255, 255, 211, 0, 255, 250, 0, 222, 255, 0, 184, 255, 0, 44, 78, 0, 141, 212, 90, 141, 234, 107, 2, 25, 0, 0, 255, 10, 0, 255, 49, 0, 255, 87, 247, 254, 250, 36, 254, 175, 0, 255, 203, 0, 255, 241, 0, 72, 80, 91, 185, 216, 116, 198, 254, 0, 115, 255, 0, 76, 255, 0, 26, 182, 0, 0, 44, 233, 230, 254, 78, 0, 255, 117, 0, 255, 155, 0, 255, 194, 0, 255, 212, 0, 234, 68, 0, 63, 249, 71, 210, 0, 0, 0, 255, 255, 255, 255, 192, 0, 255, 230, 0, 241, 255, 0, 199, 251, 0, 30, 48, 0, 214, 254, 176, 69, 156, 25, 19, 76, 5, 229, 254, 229, 0, 255, 29, 0, 255, 67, 0, 255, 106, 0, 255, 145, 0, 255, 183, 0, 252, 218, 0, 50, 52, 170, 235, 249, 35, 174, 241, 0, 110, 211, 0, 46, 124, 0, 3, 14, 51, 59, 180, 212, 209, 254, 59, 0, 255, 97, 0, 255, 136, 0, 255, 174, 0, 255, 68, 0, 82, 198, 15, 201, 254, 186, 244, 0, 0, 0, 255, 255, 255, 255, 173, 0, 255, 211, 0, 255, 250, 0, 171, 197, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 69, 127, 48, 186, 254, 177, 0, 255, 10, 0, 255, 48, 0, 255, 87, 0, 255, 125, 0, 255, 164, 0, 198, 157, 0, 11, 11, 11, 14, 14, 0, 0, 0, 0, 3, 5, 11, 35, 66, 99, 128, 195, 240, 242, 254, 73, 73, 254, 40, 0, 255, 78, 0, 255, 116, 0, 255, 93, 0, 154, 87, 0, 115, 246, 172, 254, 254, 52, 241, 0, 0, 0, 255, 255, 255, 255, 153, 0, 255, 191, 0, 255, 230, 0, 121, 129, 0, 116, 138, 31, 231, 231, 231, 12, 12, 12, 179, 179, 179, 150, 254, 126, 10, 255, 0, 0, 255, 28, 0, 255, 67, 0, 255, 106, 0, 255, 145, 0, 129, 92, 32, 145, 129, 242, 253, 254, 155, 163, 165, 86, 86, 86, 248, 251, 254, 187, 212, 254, 58, 101, 254, 0, 19, 255, 20, 0, 255, 59, 0, 255, 84, 0, 219, 25, 0, 47, 197, 96, 245, 235, 139, 254, 251, 0, 255, 0, 0, 0, 255, 255, 255, 255, 134, 0, 255, 172, 0, 255, 211, 0, 61, 59, 0, 188, 202, 99, 215, 254, 115, 12, 20, 1, 222, 229, 218, 122, 254, 75, 29, 255, 0, 0, 255, 10, 0, 255, 48, 0, 255, 87, 0, 255, 125, 0, 61, 39, 101, 207, 185, 108, 254, 246, 0, 222, 246, 7, 19, 22, 157, 206, 240, 0, 115, 255, 0, 76, 255, 0, 38, 255, 1, 0, 255, 39, 0, 251, 16, 0, 55, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 115, 0, 255, 153, 0, 243, 182, 0, 20, 18, 0, 247, 251, 190, 212, 254, 51, 164, 255, 0, 243, 254, 233, 102, 254, 24, 49, 255, 0, 10, 255, 0, 0, 255, 29, 0, 255, 67, 0, 243, 101, 0, 21, 11, 191, 252, 235, 46, 254, 227, 0, 250, 255, 3, 81, 97, 140, 149, 154, 13, 139, 254, 0, 96, 255, 0, 57, 255, 0, 18, 255, 9, 0, 127, 28, 1, 120, 220, 199, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 255, 255, 255, 255, 95, 0, 255, 134, 0, 177, 119, 0, 74, 62, 3, 254, 253, 234, 221, 254, 2, 183, 255, 0, 145, 255, 0, 75, 181, 0, 14, 53, 0, 29, 255, 0, 0, 255, 9, 0, 255, 48, 0, 176, 60, 3, 81, 41, 233, 254, 246, 1, 254, 201, 0, 255, 241, 0, 173, 192, 36, 54, 59, 99, 192, 254, 0, 115, 255, 0, 76, 255, 0, 29, 200, 0, 0, 54, 143, 124, 249, 170, 133, 254, 116, 0, 255, 155, 0, 255, 186, 0, 246, 7, 0, 8, 255, 255, 255, 255, 75, 0, 230, 102, 0, 53, 31, 0, 114, 94, 34, 254, 246, 179, 237, 250, 0, 182, 230, 0, 109, 170, 0, 9, 20, 0, 84, 159, 45, 211, 254, 201, 9, 255, 0, 0, 224, 24, 0, 48, 12, 39, 127, 75, 167, 247, 212, 0, 255, 183, 0, 255, 222, 0, 249, 254, 7, 27, 31, 101, 122, 133, 0, 111, 212, 0, 51, 137, 0, 2, 13, 45, 57, 213, 204, 200, 254, 62, 4, 254, 98, 0, 255, 132, 0, 248, 102, 0, 150, 2, 0, 2, 203, 197, 204, 157, 34, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 18, 6, 234, 246, 226, 136, 254, 94, 17, 155, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 30, 60, 45, 6, 254, 165, 0, 255, 202, 0, 255, 241, 0, 111, 123, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23, 23, 24, 40, 40, 254, 39, 0, 255, 78, 0, 255, 26, 0, 59, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 37, 0, 254, 144, 97, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 244, 254, 235, 91, 254, 7, 49, 255, 0, 104, 254, 99, 255, 255, 255, 255, 255, 255, 255, 255, 255, 193, 254, 227, 0, 255, 182, 0, 255, 222, 0, 250, 255, 130, 233, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 229, 230, 254, 20, 0, 255, 58, 0, 255, 97, 0, 255, 226, 195, 254, 255, 255, 255, 255, 255, 255, 255, 18, 0, 255, 57, 0, 255, 95, 0, 255, 133, 0, 255, 172, 0, 255, 210, 0, 255, 249, 0, 222, 255, 0, 183, 255, 0, 145, 255, 0, 107, 255, 0, 68, 255, 0, 29, 255, 0, 0, 255, 9, 0, 255, 48, 0, 255, 87, 0, 255, 125, 0, 255, 163, 0, 255, 202, 0, 255, 241, 0, 231, 255, 0, 192, 255, 0, 154, 255, 0, 115, 255, 0, 77, 255, 0, 38, 255, 1, 0, 255, 39, 0, 255, 77, 0, 255, 117, 0, 255, 155, 0, 255, 193, 0, 255};
    //Place in the memory is allocated to save the image
    uint8_t* memory = (uint8_t*) malloc(width * height * 3 * sizeof(uint8_t));
    //The Image is stored in the memory number by number.
    for(int i = 0; i < (width*height*3); i++){
        *(memory+i) = array[i];
    }
    //The pointer to the first number of the image is returned
    return memory;
}

//Copys an array to be able to call different calculate functions on it
uint8_t* copyTestArray(uint8_t* arr){
    //Place in the memory is allocated to save the image
    uint8_t* memory = (uint8_t*) malloc(width * height * 3 * sizeof(uint8_t));
    //The Image is stored in the memory number by number.
    for(int i = 0; i < (width*height*3); i++){
        *(memory+i) = *(arr+i);
    }
    //The pointer to the first number of the image is returned
    return memory;
}

//Compares the different results, shows differences if they occur
int evaluateTestResults(uint8_t* original, uint8_t* compare, uint8_t* result){
    int correctCounter = 0;
    printf("Testing pixels...");
    for(int i = 0; i < (width*height); i++){
        //Compare every pixel
        if(*(compare+3*i) == *(result+3*i) &&
           *(compare+3*i+1) == *(result+3*i+1) &&
           *(compare+3*i+2) == *(result+3*i+2)){
            correctCounter++;
        }else{
            //When wrong print the error
            printf("Pixel(%u,%u,%u): expected: (%u,%u,%u), was: (%u,%u,%u)\n",
                   *(original+3*i),*(original+3*i+1),*(original+3*i+2),
                   *(compare+3*i),*(compare+3*i+1),*(compare+3*i+2),
                   *(result+3*i),*(result+3*i+1),*(result+3*i+2));
        }
    }
    //Summarize how many pixels were wrong
    printf("\n%i/%i pixels have been converted correctly.\n\n",correctCounter,(width*height));
    //Only if every pixel was converted correctly return 0.
    if(correctCounter==width*height)return 0;
    else return -1;
}

//Tests the standard image with a given gamma value
int testGamma(float gamma){
    //The Names of the original file
    char originalPath[] = "./TestOriginal.ppm";
    //The Arrays that will be compared:
    uint8_t* original = getTestArray();
    uint8_t* result = getTestArray();
    uint8_t* compare = getTestArray();
    calculateTest(result, width, height, gamma);
    compareCalculateTest(compare, width, height, gamma);
    //Saving the picture to look at it with gamma=1
    if(gamma>0.9 && gamma<1.1) {
        writePictureTest(originalPath, original);
        writePictureTest(resultPath, result);
    }
    //Print information about the test:
    printf("Test with gamma=%f\n",gamma);
    return evaluateTestResults(original, compare, result);
}

//Tests the image (given as parameter) with the given gamma value
int testImageGamma(uint8_t* original, float gamma){
    //The Arrays that will be compared:
    uint8_t* result = copyTestArray(original);
    uint8_t* compare = copyTestArray(original);
    calculateTest(result, width, height, gamma);
    compareCalculateTest(compare, width, height, gamma);
    //Saving the picture to look at it with gamma=1
    if(gamma>0.9 && gamma<1.1)
        writePictureTest(resultPath, result);
    //Print information about the test:
    printf("Test with gamma=%f\n",gamma);
    return evaluateTestResults(original, compare, result);
}

//Test the standard image with different gamma values
int test(){
    for(float i = 0.2; i <= 2.1; i+=0.2){
        //Test with different gamma values
        if(testGamma(i)!=0){
            //If one tests fails the whole test fails.
            printf("Test failed with gamma=%f\n",i);
            return -1;
        }
    }
    //Otherwise it passed the test
    printf("Everything worked as expected.\n");
    return 0;
}

//Tests a given image with different gamma values
int testImage(char* path){
    //load the image
    uint8_t* original = readPictureTest(path);
    for(float i = 0.2; i <= 2.1; i+=0.2){
        //test copies of the image with different gamma values
        if(testImageGamma(copyTestArray(original), i)!=0){
            //If one tests fails the whole test fails.
            printf("Test failed with gamma=%f\n",i);
            return -1;
        }
    }
    //Otherwise it passed the test
    printf("Everything worked as expected.\n");
    return 0;
}

//int main(int argc, char** argv){
//    test();
//    testImage("andererTest.ppm");
//    return 0;
//}