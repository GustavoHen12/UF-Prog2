#include "image.h"

Pixel readImageData(ImagePPM *image, FILE *file, int type){
     int size = image->height * image->width;
     long int rTotal = 0, gTotal = 0, bTotal = 0;
     int r = 0, g = 0, b = 0;
     Pixel *px;
     Pixel media;
     for(int i = 0; i < size; i++){
          px = &(image->data[i]);
          if(type == 6){
               fread(px, sizeof(Pixel), 1, file);//verficacao
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

void imprimeFoto (ImagePPM *image){
     Pixel *px;
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

int initImage(ImagePPM *image, char *type, int height, int width){
     strcpy(image->type, type);
     image->height = height;
     image->width = width;

     image->data = malloc(image->height * image->width * sizeof(Pixel));
     return 0;
}

Pixel readPPM(const char *filename, ImagePPM *image){
     //informacoes da imagem
     int maxValue = 0;
     FILE *imageFile;
     if(filename == NULL){
          imageFile = stdin;
     }else{
          imageFile = fopen(filename, "r");
          if(!imageFile){
               perror("Não foi possivel abrir a imagem!");
               exit(1);
          }
     }
     //verificar tipo da imagem
     fgets(image->type, STR_IMAGE_TYPE_SIZE, imageFile);

     cleanComents(imageFile);

     if(fscanf(imageFile, "%d %d,", &image->width, &image->height) != 2){
          perror("Erro ao ler tamanho da imagem");
          exit(1);
     }
     
     fscanf(imageFile, "%d", &maxValue);
     if(maxValue != 255){
          perror("Esta imagem não possui um formato valido");
          exit(1);
     }

     image->data = malloc(image->height * image->width * sizeof(Pixel));
     Pixel md;

     while (fgetc(imageFile) != '\n') ;

     if(strcmp(image->type, "P3") == 0){
          md = readImageData(image, imageFile, 3);
     }
     else{
          md = readImageData(image, imageFile, 6);
     }
     
     fclose(imageFile);
     return md;
}

void copyPixel(ImagePPM *image, int pos, Pixel px){
     Pixel *newPx;
     newPx = &(image->data[pos]);
     newPx->red = px.red;
     newPx->blue = px.blue;
     newPx->green = px.green;
}

int writeImage(ImagePPM *imgDest, ImagePPM *imgSrc, int initialX, int initialY){
     int indexSrc = 0;
     Pixel cpPixel;
     int indexDest = initialX + initialY*imgDest->width;
     int limitX = initialX + imgSrc->height;
     int limitY = initialY + imgSrc->width;
 
     if(limitX < initialX || limitY < initialY){
          perror("Ocorreu um erro ao copiar a regiao");
          exit(1);
     }

     int count = 0;
     for(int i = initialY; i < limitY; i++){
          for(int j = initialX; j < limitX; j++){
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
          printf("!!!NENHUM Pixel COPIADO : %d %d %d %d \n", indexDest, indexSrc, limitX, limitY);
     }
     return count;
}

Pixel getAvarageColor(ImagePPM *image,int initialX, int initialY, int offsetX, int offsetY){
     Pixel px;
     long int rTotal = 0, gTotal = 0, bTotal = 0;
     int index = initialX + initialY*image->width;
     for(int i = initialX; i < initialX+offsetX; i++){
          for(int j = initialY; j < initialY+offsetY; j++){
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
     int size = offsetX*offsetY;
     px.red = (int)sqrt(rTotal/size);
     px.green = (int)sqrt(gTotal/size);
     px.blue = (int)sqrt(bTotal/size);

     return px;
}

int distanceBetweenColors(Pixel pxA, Pixel pxB){
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

     return result;
}

void imageToFile(const char *filename, ImagePPM *img)
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
    if(strcmp(img->type, "P6") == 0) 
         fprintf(fp, "P6\n");
     else
          fprintf(fp, "P3\n");

    //image size
    fprintf(fp, "%d %d\n",img->width,img->height);

    // rgb component depth
    fprintf(fp, "%d\n",RGB_COMPONENT_COLOR);

    // Pixel data
    if(strcmp(img->type, "P6") == 0)
         fwrite(img->data, 3 * img->width, img->height, fp);
    else{
          Pixel *px;
          int k = 0;
          for(int i = 0; i < img->height; i++){
               for(int j = 0; j < img->width; j++){
                    px = &(img->data[k]);
                    fprintf(fp, "%d %d %d ", px->red, px->green, px->blue);
                    k++;
               }
               fprintf(fp, "\n");
          }
     }
    fclose(fp);
}

int getImageHeight(ImagePPM *image){
     return image->height;
}

int getImageWidth(ImagePPM *image){
     return image->width;
}