#include "image.h"
//temp

#define MAX_HEIGH 2160
#define MAX_WIDTH 4096
void printLog(char *info, char *str){
     printf("[%s]: %s\n", info, str);
}

void cleanComents(FILE *file){
     char firstChar;
     while (fgetc(file) != '\n');
     firstChar = fgetc(file);
     while ((firstChar == '#')){
          while (fgetc(file) != '\n');
          firstChar = fgetc(file);
     }     
     fseek(file, -1*sizeof(char), SEEK_CUR);
}

int getIndex(int i, int j, int width){
     return j + i*width;
}

void imprimeFoto (imagePPM *image){
     pixel *px;
     int k = 0;
     for(int i = 0; i < image->height; i++){
          for(int j = 0; j < image->width; j++){
               px = &(image->data[k]);
               printf(" %d %d %d |", px->red, px->green, px->blue);
               k++;
          }
          printf("\n");
     }
     printf("\n");
}

int createImage(imagePPM *image, char *type, int height, int width){
     strcpy(image->type, type);
     image->height = height;
     image->width = width;

     image->data = malloc(image->height * image->width * sizeof(pixel));
     return 0;
}
pixel readPPM(const char *filename, imagePPM *image){
     //informacoes da imagem
     int maxValue = 0;
     FILE *imageFile;
     imageFile = fopen(filename, "r");
     if(!imageFile){
          perror("Não foi possivel abrir a imagem!");
          exit(1);
     }
     //verificar tipo da imagem
     fgets(image->type, STR_IMAGE_TYPE_SIZE, imageFile);
     //printLog("TIPO IMAGEM", image->type);
     //printLog("TIPO IMAGEM", image->type);

     // char c;
     // c = getc(imageFile);
     // while (c == '#') {
     //      while (getc(imageFile) != '\n') ;
     //           c = getc(imageFile);
     // }
     // ungetc(c, imageFile);
     cleanComents(imageFile);

     if(fscanf(imageFile, "%d %d,", &image->width, &image->height) != 2){
          perror("Erro ao ler tamanho da imagem");
          exit(1);
     }
     
     //printf("[SIZE]: %d %d - ", image->height, image->width);
     //cleanComents(imageFile);

     fscanf(imageFile, "%d", &maxValue);
     if(maxValue != 255){
          perror("Esta imagem não possui um formato valido");
          exit(1);
     }

     image->data = malloc(image->height * image->width * sizeof(pixel));
     pixel md;

     while (fgetc(imageFile) != '\n') ;

     if(strcmp(image->type, "P3") == 0){
          //printf("LE TIPO P3 \n");
          md = readImageData(image, imageFile, 3);
     }
     else{
          //printf("LE TIPO P6 \n");
          md = readImageData(image, imageFile, 6);
     }
     //imprimeFoto(image);
     //printf("%d %d %d \n", md.red, md.green, md.blue);
     fclose(imageFile);
     return md;
}

pixel readImageData(imagePPM *image, FILE *file, int type){
     int size = image->height * image->width;
     long int rTotal = 0, gTotal = 0, bTotal = 0;
     int r = 0, g = 0, b = 0;
     pixel *px;
     pixel media;
     for(int i = 0; i < size; i++){
          px = &(image->data[i]);
          if(type == 6){
               fread(px, sizeof(pixel), 1, file);//verficacao
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

void copyPixel(imagePPM *image, int pos, pixel px){
     pixel *newPx;
     // newPx = &(image->data[pos]);
     // newPx->red = px.red;
     // newPx->blue = px.blue;
     // newPx->green = px.green;

     newPx = &(image->data[pos]);
     newPx->red = px.red;
     newPx->blue = px.blue;
     newPx->green = px.green;
     //printf(" %d %d %d  - %d %d %d\n", newPx->red,newPx->blue, newPx->green, px.red, px.blue, px.green);
}

int writeImage(imagePPM *imgDest, imagePPM *imgSrc, int initialX, int initialY){
     int indexSrc = 0;
     pixel cpPixel;
     //printf("> %d %d <\n", initialX, initialY);
     int indexDest = initialX + initialY*imgDest->width;
     int i = initialY, j = initialX;
     int limitX = initialX + imgSrc->height, limitY = initialY + imgSrc->width;
     //printf("%d %d - %d %d\n", limitX, limitY, i, j);
     if(limitX < initialX || limitY < initialY){
          perror("Ocorreu um erro ao copiar a regiao");
          exit(1);
     }
     int count = 0;
     for(i = initialY; i < limitY; i++){
          for(j = initialX; j < limitX; j++){
               if(j > imgDest->width || i > imgDest->height)
                    continue;
               indexDest = getIndex(i, j, imgDest->width);//estava imgSrc
               cpPixel = imgSrc->data[indexSrc];
               copyPixel(imgDest, indexDest, cpPixel);
               indexSrc++;
               count++;
          }
     }
     if(count == 0){
          printf("!!!NENHUM PIXEL COPIADO : %d %d %d %d %d %d \n", indexDest, indexSrc, i, j, limitX, limitY);
     }
     return count;
     //printf("%d %d - %d %d\n", indexDest, indexSrc, i, j);
}

pixel getAvarageColor(imagePPM *image,int initialX, int initialY, int limitX, int limitY){
     pixel px;
     long int rTotal = 0, gTotal = 0, bTotal = 0;
     int index = initialX + initialY*image->width;
     for(int i = initialX; i < initialX+limitX; i++){
          for(int j = initialY; j < initialY+limitY; j++){
               if(j > image->width || i > image->height)
                    continue;
               index = getIndex(i, j, image->width);
               //printf("%d \n", index);
               px = image->data[index];
               rTotal += px.red * px.red;
               gTotal += px.green * px.green;
               bTotal += px.blue * px.blue;
          }
     }
     int size = limitX*limitY;
     px.red = (int)sqrt(rTotal/size);
     px.green = (int)sqrt(gTotal/size);
     px.blue = (int)sqrt(bTotal/size);

     //printf("%d %d %d \n", px.red, px.green, px.blue);
     return px;
}

int distanceBetweenColors(pixel pxA, pixel pxB){
     // printf("> %d %d %d \n", pxA.red, pxA.green, pxA.blue);
     // printf("> %d %d %d \n", pxB.red, pxB.green, pxB.blue);
     int dR = pxA.red - pxB.red;
     int dG = pxA.green - pxB.green;
     int dB = pxA.blue - pxB.blue;
     float r = (pxA.red + pxB.red);

     int result;
     if(r > 128){
          result = sqrt((2*dR*dR)+(4*dG*dG)+(3*dB*dB));
     }else{
          result = sqrt((3*dR*dR)+(4*dG*dG)+(2*dB*dB));
     }

     // float et1 = (2+(r/256))*dR*dR;
     // float et2 = 4*dG*dG;
     // float et3 = (2+((255-r)/256))*dB*dB;

     // int result = sqrt(et1+et2+et3);
     return result;
}

void imageToFile(const char *filename, imagePPM *img)
{
    FILE *fp;
    //open file for output
    fp = fopen(filename, "wb");
    if (!fp) {
         fprintf(stderr, "Unable to open file '%s'\n", filename);
         exit(1);
    }

    //write the header file
    //image format
    fprintf(fp, "P6\n");

    //comments
    fprintf(fp, "# Created by \n");

    //image size
    fprintf(fp, "%d %d\n",img->width,img->height);

    // rgb component depth
    fprintf(fp, "%d\n",RGB_COMPONENT_COLOR);

    // pixel data
    fwrite(img->data, 3 * img->width, img->height, fp);
    fclose(fp);
}
