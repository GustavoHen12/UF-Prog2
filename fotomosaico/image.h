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

//writeInImage