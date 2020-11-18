#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
 
#include "image.h"

#define MAX_TILES 1000
#define FILE_NAME_SIZE 100

imagePPM *readTiles(pixel *predominantColor, char *dirname, int *size){
   DIR *dirstream;
   struct dirent *direntry;
   
   imagePPM *tiles;
   tiles = malloc(sizeof(imagePPM)*MAX_TILES);
   
   dirstream = opendir (dirname);
   if ( ! dirstream )
   {
      perror ("Couldn't open the directory");
      exit (1) ;
   }

   int i = 0;
   int count = 1;
   while (direntry = readdir (dirstream)){
      if(strcmp(direntry->d_name,".") == 0)
         continue;
      if(strcmp(direntry->d_name,"..") == 0)
         continue;
      printf("> %d - %s\n", i, direntry->d_name);
      char filename[FILE_NAME_SIZE];
      strcpy(filename, dirname);
      strcat(filename, direntry->d_name); //sprintf (nome_completo, "%s/%s", dir_name, file_name)
      predominantColor[i] = readPPM(filename, &tiles[i]);
      i++;
      if(i >= MAX_TILES){  
         count++;
         tiles = realloc(tiles, sizeof(imagePPM)*(MAX_TILES*count));
         predominantColor = realloc(predominantColor, sizeof(imagePPM)*(MAX_TILES*count));
      }
   }
   (void) closedir (dirstream);
   *(size) = i;
   return tiles;
}

int getProxTile(pixel color, pixel *colorTiles, int size){
   int menorDist = distanceBetweenColors(color, colorTiles[0]), menorIndice = 0, dist = 0;
   for(int i = 0; i < size; i++){
      dist = distanceBetweenColors(color, colorTiles[i]);
      if(dist < menorDist){
         menorDist = dist;
         menorIndice = i;
      }
   }
   return menorIndice;
}

int main (){
   //INICIA TILES
   //todo: colocar em um struct
   imagePPM *tiles;
   pixel *predominantColor;
   int size;
   tiles = malloc(sizeof(imagePPM)*MAX_TILES);
   predominantColor = malloc(sizeof(pixel)*MAX_TILES);
  
   char dirname[11] = "./tiles32/";
   tiles = readTiles(predominantColor, dirname, &size);
   printf("\n%d\n", size);

   //LE IMAGEM
   imagePPM image;
   readPPM("wallP3.ppm", &image);

   //cria copia
   imagePPM mosaico;
   createImage(&mosaico, image.type, image.height, image.width);

   int tilesHeight = tiles[0].height;
   int tilesWidth = tiles[0].width;//tranformar em funcao
   pixel avarageColor;
   //percorre a imagem
   for(int i = 0; i < image.height; i+= tilesWidth){
      for(int j = 0; j < image.width; j+= tilesWidth){
         //printf("%d %d - ", i, j);
         //calcula media
         avarageColor = getAvarageColor(&image, i, j, tilesWidth, tilesHeight);
         //acha mais proxima  
         int ind = getProxTile(avarageColor, predominantColor, size);
         //printf("> %d \n", ind);
         //escreve imagem
         writeImage(&mosaico, &tiles[ind], i, j);
      }
   }

   //exporta imagem para arquivo
   imageToFile("output.ppm", &mosaico);
   return 0;
}

