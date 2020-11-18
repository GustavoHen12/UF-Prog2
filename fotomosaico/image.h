#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define STR_IMAGE_TYPE_SIZE 3
#define RGB_COMPONENT_COLOR 255

typedef struct {
     unsigned char red,green,blue;
} pixel;

typedef struct {
     char type[STR_IMAGE_TYPE_SIZE];
     int height, width;
     pixel *data;
} imagePPM;

pixel readPPM(const char *filename, imagePPM *image);

pixel readImageData(imagePPM *image, FILE *file, int type);

int writeImage(imagePPM *imgDest, imagePPM *imgSrc, int initialX, int initialY);

int createImage(imagePPM *image, char *type, int height, int width);
// void imageToFile();

pixel getAvarageColor(imagePPM *image,int initialX, int initialY, int limitX, int limitY);

int distanceBetweenColors(pixel pxA, pixel pxB);

void imageToFile(const char *filename, imagePPM *img);

void imprimeFoto (imagePPM *image);