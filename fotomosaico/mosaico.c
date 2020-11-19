#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
 
#include "image.h"

#define MAX_TILES 1000
#define FILE_NAME_SIZE 100

typedef struct{
   imagePPM *images;
   pixel *avarageColors;
   int size;
} Tiles_tp;

int diretoryInvalid(struct dirent *direntry){
   if(strcmp(direntry->d_name,".") == 0)
      return 1;
   if(strcmp(direntry->d_name,"..") == 0)
      return 1;
   if(direntry->d_type != DT_REG)
      return 1;
   return 0;
}

int readTiles( Tiles_tp *tiles, char *dirname){
   DIR *dirstream;
   struct dirent *direntry;
   
   tiles->images = malloc(sizeof(imagePPM)*MAX_TILES);
   tiles->avarageColors = malloc(sizeof(pixel)*MAX_TILES);
   
   dirstream = opendir (dirname);
   if ( ! dirstream ){
      perror ("Couldn't open the directory");
      exit (1) ;
   }

   int tilesSize = 0, reallocCount = 1;
   for(;;){
      direntry = readdir (dirstream) ;
      if (! direntry)
        break ;

      if(diretoryInvalid(direntry))
         continue;

      char filename[FILE_NAME_SIZE];
      strcpy(filename, dirname);
      strcat(filename, direntry->d_name); //sprintf (nome_completo, "%s/%s", dir_name, file_name)
      tiles->avarageColors[tilesSize] = readPPM(filename, &(tiles->images[tilesSize]));
      tilesSize++;
      if(tilesSize >= MAX_TILES){  
         reallocCount++;
         tiles->images = realloc(tiles->images, sizeof(imagePPM)*(MAX_TILES*reallocCount));
         tiles->avarageColors = realloc(tiles->avarageColors, sizeof(imagePPM)*(MAX_TILES*reallocCount));
      }
   }
   (void) closedir (dirstream);
   tiles->size = tilesSize;

   return 0;
}

int getProxTile(pixel color, pixel *colorTiles, int size){
   int menorDist = distanceBetweenColors(color, colorTiles[0]), menorIndice = 0, dist = 0;
   for(int i = 0; i < size; i++){
      dist = distanceBetweenColors(color, colorTiles[i]);
      if(dist <= menorDist){
         menorDist = dist;
         menorIndice = i;
      }
   }
   return menorIndice;
}

int main (){
   //INICIA TILES
   Tiles_tp tiles;
   char dirname[11] = "./tiles32/";
   readTiles(&tiles, dirname);

   //LE IMAGEM
   imagePPM image;
   readPPM("wallP65.ppm", &image);

   //cria copia
   imagePPM mosaico;
   createImage(&mosaico, image.type, image.height, image.width);

   int tilesHeight = tiles.images[0].height;
   int tilesWidth = tiles.images[0].width;

   pixel avarageColor;
   int count, countPX;
   //percorre a imagem
   for(int i = 0; i < image.height; i+= tilesHeight){
      for(int j = 0; j < image.width; j+= tilesWidth){
         //calcula media
         avarageColor = getAvarageColor(&image, i, j, tilesWidth, tilesHeight);
         //acha mais proxima  
         int ind = getProxTile(avarageColor, tiles.avarageColors, tiles.size);
         //escreve imagem
         countPX += writeImage(&mosaico, &(tiles.images[ind]), j, i);
         count++;
      }
   }
   //exporta imagem para arquivo
   imageToFile("output.ppm", &mosaico);
   return 0;
}

