#include "image.h"
//temp

#define MAX_HEIGH 2160
#define MAX_WIDTH 4096
void printLog(char *info, char *str){
     printf("[%s]: %s\n", info, str);
}

void cleanComents(FILE *file){
     char firstChar;
     firstChar = fgetc(file);
     while ((firstChar == '#') || (firstChar == '\n')){
          while(firstChar != '\n')
               firstChar = fgetc(file);
          firstChar = fgetc(file);
     }     
     fseek(file, -1*sizeof(char), SEEK_CUR);
}

imagePPM *readPPM(const char *filename){
     //informacoes da imagem
     int maxValue = 0;
     imagePPM *image;
     //PPMImage *img;
     FILE *imageFile;
     imageFile = fopen(filename, "r");
     if(!imageFile){
          perror("Não foi possivel abrir a imagem!");
          exit(1);
     }
     image = malloc(sizeof(imagePPM));
     //verificar tipo da imagem
     fgets(image->type, STR_IMAGE_TYPE_SIZE, imageFile);
     printLog("TIPO IMAGEM", image->type);

     cleanComents(imageFile);
     
     fscanf(imageFile, "%d", &image->height);
     fscanf(imageFile, "%d", &image->width);

     cleanComents(imageFile);

     fscanf(imageFile, "%d", &maxValue);
     if(maxValue != 255){
          perror("Esta imagem não possui um formato valido");
          exit(1);
     }

     cleanComents(imageFile);
     image->data = malloc(image->height * image->width * sizeof(pixel));
     if(strcmp(image->type, "P3") == 0){
          printf("LE TIPO P3 \n");
     }
     else{
          printf("LE TIPO P6 \n");
     }
     fclose(imageFile);
     return image;
}

imagePPM *P6read(imagePPM *image, FILE *file){
     if (fread(image->data, 3 * image->height, image->width, file) != image->height) {
         fprintf(stderr, "Error loading image \n");
         exit(1);
    }
}
