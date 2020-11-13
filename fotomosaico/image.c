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

void imprimeFoto (imagePPM *image){
     pixel *px;
     int k = 0;
     for(int i = 0; i < image->height; i++){
          for(int j = 0; j < image->width; j++){
               px = &(image->data[k]);
               printf("( %d %d %d )", px->red, px->green, px->blue);
               k++;
          }
          printf("\n");
     }
     printf("\n");
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
     pixel md;
     if(strcmp(image->type, "P3") == 0){
          printf("LE TIPO P3 \n");
          md = readImageData(image, imageFile, 3);
     }
     else{
          printf("LE TIPO P6 \n");
          md = readImageData(image, imageFile, 6);
     }
     //imprimeFoto(image);
     printf("%d %d %d \n", md.red, md.green, md.blue);
     fclose(imageFile);
     return image;
}

pixel readImageData(imagePPM *image, FILE *file, int type){
     int size = image->height * image->width;
     long long int rTotal = 0, gTotal = 0, bTotal = 0;
     int r = 0, g = 0, b = 0;
     pixel *px;
     pixel media;
     for(int i = 0; i < size; i++){
          px = &(image->data[i]);
          if(type == 6){
               fread(px, sizeof(pixel), 1, file);
          }
          else{
               if(fscanf(file, "%d %d %d", &r, &g, &b) != 3){
                    perror("Ocorreu um erro ao carregar a imagem !");
                    exit(1);
               }
               px->red = r;
               px->green = g;
               px->blue = b;
          }

          rTotal += px->red*px->red;
          gTotal += px->green*px->green;
          bTotal += px->blue*px->blue;
     }
     media.red = (int)sqrt(rTotal/size);
     media.green = (int)sqrt(gTotal/size);
     media.blue = (int)sqrt(bTotal/size);
     
     return media;
}

imagePPM *P3read(imagePPM *image, FILE *file){
     int size = image->height * image->width;
     long long int rTotal = 0, gTotal = 0, bTotal = 0;
     int r = 0, g = 0, b = 0;
     pixel *px;
     for(int i = 0; i < size; i++){
          if(fscanf(file, "%d %d %d", &r, &g, &b) != 3){
               perror("Ocorreu um erro ao carregar a imagem !");
               exit(1);
          }
          px = &(image->data[i]);
          px->red = r;
          px->green = g;
          px->blue = b;
 
          rTotal += px->red*px->red;
          gTotal += px->green*px->green;
          bTotal += px->blue*px->blue;
     }
     return image;
}

imagePPM *P6read(imagePPM *image, FILE *file){
     int size = image->height * image->width;
     long long int rTotal = 0, gTotal = 0, bTotal = 0;
     pixel *px;
     for(int i = 0; i < size; i++){
          px = &(image->data[i]);
          rTotal += px->red*px->red;
          gTotal += px->green*px->green;
          bTotal += px->blue*px->blue;
     }

    return image;
}
