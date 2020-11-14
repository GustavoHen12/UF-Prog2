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
   DIR *dirstream;
   struct dirent *direntry;

   //todo: colocar em um struct
   imagePPM *tiles;
   pixel *predominantColor;
   tiles = malloc(sizeof(imagePPM)*MAX_TILES);
   predominantColor = malloc(sizeof(pixel)*MAX_TILES);
  
   char dirname[11] = "./tiles32/";
  
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
      strcat(filename, direntry->d_name);
      predominantColor[i] = readPPM(filename, &tiles[i]);
      i++;
      if(i >= MAX_TILES){  
         count++;
         tiles = realloc(tiles, sizeof(imagePPM)*(MAX_TILES*count));
         predominantColor = realloc(predominantColor, sizeof(imagePPM)*(MAX_TILES*count));
      }
   }
   (void) closedir (dirstream);

   return 0;
}
