#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
 
#include "image.h"

#define MAX_TILES 1000
#define FILE_NAME_SIZE 100
//image.h 
   //carrega img

//tiles.h

int main (){
    imagePPM *tiles;
    tiles = malloc(sizeof(imagePPM)*MAX_TILES);
    printf("TESTE IMG 1: \n");
    readPPM("image.ppm", &tiles[0]);

    printf("TESTE IMG 2: \n");
    readPPM("image2.ppm", &tiles[1]);

    printf("TESTE IMG 3: \n");
    readPPM("image3.ppm", &tiles[2]);
    
    return 0;
}