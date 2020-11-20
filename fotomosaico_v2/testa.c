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
//so pra testar o commit
int main (){
    // ImagePPM *tiles;
    // tiles = malloc(sizeof(ImagePPM)*MAX_TILES);
    // printf("TESTE IMG 1: \n");
    // readPPM("image.ppm", &tiles[0]);

    // printf("TESTE IMG 2: \n");
    // readPPM("image2.ppm", &tiles[1]);

    // printf("TESTE IMG 3: \n");
    // readPPM("image3.ppm", &tiles[2]);

    // printf("COPIA IMG 2 NA 3: \n");
    // writeImage(&tiles[0], &tiles[1], 0, 0);

    // printf("TESTA COR MEDIA\n");
    // imagePPM image;
    // readPPM("wallP3.ppm", &image);

    // //cria copia
    // imagePPM mosaico;
    // createImage(&mosaico, image.type, image.height, image.width);

    // int tilesHeight = tiles[0].height;
    // int tilesWidth = tiles[0].width;//tranformar em funcao
    // pixel avarageColor;
    // avarageColor = getAvarageColor(&image, 0, 0, tilesWidth, tilesHeight);

    // printf("TESTA DISTANCIA ENTRE CORES\n");
    // pixel px;
    // px.red = 0;
    // px.green = 0;
    // px.blue = 0;
    // int result = distanceBetweenColors(tiles[0].data[5], px);
    // printf("%d\n", result);


    // printf("TESTA ESCRITA \n");
    // //672 896 - 547
    // printf("\n %d %d \n", tiles[0].height, tiles[0].width);
    // writeImage(&mosaico, &tiles[547], 672, 547);

    printf("TESTE LEITURA P6\n");
    ImagePPM image;
    //Pixel px;
    readPPM("wallP33.ppm", &image);
    imageToFile(NULL, &image);
    return 0;
}
