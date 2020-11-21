#include "image.h"

//A partir um arquivo de imagem "file", carrega em "image.data"
Pixel_t readImageData(ImagePPM_t *image, FILE *file){
     //inicia as variaveis que serao utilizadas para calcular e retornar a cor média da imagem lida
     //e o ponteiro para o pixel da imagem a ser lido
     long int rTotal = 0, gTotal = 0, bTotal = 0;
     Pixel_t avrgColor;
     Pixel_t *px;
     //a variavel type é utilizada para saber se a leitura sera de uma imagem tipo p6 ou p3
     int type = strcmp(image->type, "P3") == 0 ? 3 : 6;
     //cria a variavel size, com a quantidade de pixels que sera lida
     int size = image->height * image->width;
     for(int i = 0; i < size; i++){
          //seleciona o pixel a ser lido
          px = &(image->data[i]);
          //le o pixel dependendo do tipo da imagem
          if(type == 6){
               if(fread(px, sizeof(Pixel_t), 1, file) != 1){
                    fprintf(stderr,"Ocorreu um erro ao carregar a imagem !");
                    exit(1);
               }
          }
          else{
               if(fscanf(file, "%hhd %hhd %hhd", &px->red, &px->green, &px->blue) != 3){
                    fprintf(stderr,"Ocorreu um erro ao carregar a imagem !");
                    exit(1);
               }
          }
          //aramazena o quadrado do valor RGB para calculo da cor média
          rTotal += px->red*px->red;
          gTotal += px->green*px->green;
          bTotal += px->blue*px->blue;
     }

     //calcula e retorna o valor da cor média
     avrgColor.red = (int)sqrt(rTotal/size);
     avrgColor.green = (int)sqrt(gTotal/size);
     avrgColor.blue = (int)sqrt(bTotal/size);
     return avrgColor;
}

//vai ate o final da linha atual, ou seja, consome o linha até o \n
void gotoNextLine(FILE *file){
     while (fgetc(file) != '\n') ;
}

//funcao para "pular" os possivei comentarios
void cleanComents(FILE *file){
     //vai para a próxima linha
     gotoNextLine(file);
     //verifica se a linha comeca com #, ou seja, se é comentario
     //se sim vai para a próxima linha e verifica novamente
     char firstChar;
     firstChar = fgetc(file);
     while ((firstChar == '#')){
          gotoNextLine(file);
          firstChar = fgetc(file);
     }
     //se a linha não for comentário, coloca o cursor no caracter inicial novamente     
     fseek(file, -1*sizeof(char), SEEK_CUR);
}

//a partir de uma valor de i(eixo Y), j(eixo X) e o tamanho da imagem
//retorna a posição do vetor que possui esta em (j, i) 
int getIndex(int i, int j, int width){
     return j + i*width;
}

//A partir de um ponteiro para uma imagem ppm "image"
//seta seu tipo e tamanho, e aloca espaço para os pixels 
int initImage(ImagePPM_t *image, char *type, int height, int width){
     //copia o tipo para a imagem (P3 ou P6)
     strcpy(image->type, type);
     //seta a altura e largura da imagem
     image->height = height;
     image->width = width;
     //aloca espaço para posterior leitura dos pixels da imagem
     image->data = malloc(image->height * image->width * sizeof(Pixel_t));
     return 0;
}

Pixel_t readPPM(const char *filename, ImagePPM_t *image){
     //informacoes da imagem
     int maxValue, imgHeight, imgWidth;
     char imgType[STR_IMAGE_TYPE_SIZE];

     //Tenta abrir o arquivo da imagem, cujo nome é "filename"
     //caso o "filename" seja nulo, a leitura sera realizada a partir da entrada padão
     FILE *imageFile;
     if(filename == NULL){
          imageFile = stdin;
     }else{
          imageFile = fopen(filename, "r");
          if(!imageFile){
               fprintf(stderr,"Não foi possivel abrir a imagem!\n");
               exit(1);
          }
     }

     //HEADER
     //Lê o formato da imagem e verifica se é valido
     fgets(imgType, STR_IMAGE_TYPE_SIZE, imageFile);
     if((strcmp(imgType, "P6") != 0) && (strcmp(imgType, "P3") != 0)){
          fprintf(stderr,"Erro, formato de imagem inválido\n");
          exit(1);
     }
     //Pula os possíveis comentários
     cleanComents(imageFile);

     //Lê e verifica o tamanho da imagem
     if(fscanf(imageFile, "%d %d,", &imgWidth, &imgHeight) != 2){
          fprintf(stderr,"Erro ao ler tamanho da imagem");
          exit(1);
     }
     
     //Lê o valor máximo de pixel da imagem
     fscanf(imageFile, "%d", &maxValue);
     if(maxValue != MAX_COLOR_RGB){
          fprintf(stderr,"Esta imagem não possui um formato valido, verifique se a imagem é de 8bits");
          exit(1);
     }

     //inicia a imagem, salvando os valores do header
     initImage(image, imgType, imgHeight, imgWidth);
     
     //DATA
     //vai para próxima linha para leitura dos pixels da imagem
     gotoNextLine(imageFile);
     
     //Lê os pixels da imagem, e salva o valor da cor média, em "md" que será o retorno da função
     Pixel_t avarageColor;
     avarageColor = readImageData(image, imageFile);
     
     //fecha o arquivo e retorna a cor média
     fclose(imageFile);
     return avarageColor;
}

int getImageHeight(ImagePPM_t *image){
     //retorna largura da imagem
     return image->height;
}

int getImageWidth(ImagePPM_t *image){
     //retorna largura da imagem
     return image->width;
}

//copia o pixel "px" para a posicao "pos" de "image"
void copyPixel(ImagePPM_t *image, int pos, Pixel_t px){
     Pixel_t *newPx;
     newPx = &(image->data[pos]);
     newPx->red = px.red;
     newPx->blue = px.blue;
     newPx->green = px.green;
}

void writeImage(ImagePPM_t *imgDest, ImagePPM_t *imgSrc, int initialX, int initialY){
     Pixel_t cpPixel;
     //Faz calculo da posicao inicial na imagem fonte e destino
     int indexDest = initialX + initialY*imgDest->width, indexSrc = 0;
     //calcula os limite da região a ser copiada
     int limitX = initialX + imgSrc->height;
     int limitY = initialY + imgSrc->width;
 
     if(limitX < initialX || limitY < initialY){
          fprintf(stderr,"Ocorreu um erro ao copiar a regiao");
          exit(1);
     }

     for(int i = initialY; i < limitY; i++){
          for(int j = initialX; j < limitX; j++){
               //caso a região seja maior que a imagem
               if(j > imgDest->width || i > imgDest->height)
                    continue;
               //para cada pixel, calcula o indice na imagem fonte com base na posição
               indexDest = getIndex(i, j, imgDest->width);
               cpPixel = imgSrc->data[indexSrc];
               //copia pixel da imagem fonte para a destino
               copyPixel(imgDest, indexDest, cpPixel);
               indexSrc++;
          }
     }
}

Pixel_t getAvarageColor(ImagePPM_t *image,int initialX, int initialY, int offsetX, int offsetY){
     //px corresponde ao pixel com a cor media da região
     Pixel_t px;
     //variaveis que corresponderão a soma dos quadrados das cores da imagem
     long int rTotal = 0, gTotal = 0, bTotal = 0;
     //index correspondente a posicao no vetor, com relação a "matriz" da imagem
     int index = initialX + initialY*image->width;
     for(int i = initialX; i < initialX+offsetX; i++){
          for(int j = initialY; j < initialY+offsetY; j++){
               if(j > image->width || i > image->height)
                    continue;
               //calcula o indice e seleciona o pixel
               index = getIndex(i, j, image->width);
               px = image->data[index];
               //soma o quadrado do valor de cada pixel para calculo da cor média
               rTotal += px.red * px.red;
               gTotal += px.green * px.green;
               bTotal += px.blue * px.blue;
          }
     }
     //realiza calculo e retorna o valor
     int size = offsetX*offsetY;
     px.red = (int)sqrt(rTotal/size);
     px.green = (int)sqrt(gTotal/size);
     px.blue = (int)sqrt(bTotal/size);
     return px;
}

int distanceBetweenColors(Pixel_t pxA, Pixel_t pxB){
     //calcula os deltas
     int dR = pxA.red - pxB.red;
     int dG = pxA.green - pxB.green;
     int dB = pxA.blue - pxB.blue;
     //calculo de gama
     float gama = (pxA.red + pxB.red) / 2;

     //calculo redmean
     int result = sqrt(((2+(gama/256))*dR*dR)+(4*dG*dG)+((2+((255-gama)/256))*dB*dB));
     return result;
}

void imageToFile(const char *filename, ImagePPM_t *img)
{
    FILE *file;
    //Abre arquivo que será exportada a imagem
    //caso filename seja null escreve na saida padrão
    if(filename == NULL){
         file = stdout;
    }else{
          file = fopen(filename, "wb");
          if (!file) {
               fprintf(stderr, "Não foi possível abrir o arquivo '%s'\n", filename);
               exit(1);
          }
    }

     //Escreve cabeçao com o formato da imagem
     if(strcmp(img->type, "P6") == 0) 
         fprintf(file, "P6\n");
     else
          fprintf(file, "P3\n");

    //Escreve o tamanho da imagem
    fprintf(file, "%d %d\n",img->width,img->height);

    //Escreve o tamanho máximo de cada cor
    fprintf(file, "%d\n",MAX_COLOR_RGB);

    //Escre dados das imagens
    if(strcmp(img->type, "P6") == 0){
         fwrite(img->data, 3 * img->width, img->height, file);
     }else{
          //caso a imagem seja do tipo P3, escreve os pixels individualmente
          Pixel_t *px;
          int k = 0;
          for(int i = 0; i < img->height; i++){
               for(int j = 0; j < img->width; j++){
                    px = &(img->data[k]);
                    fprintf(file, "%d %d %d ", px->red, px->green, px->blue);
                    k++;
               }
               fprintf(file, "\n");
          }
     }
    fclose(file);
}

