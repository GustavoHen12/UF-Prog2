#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define STR_IMAGE_TYPE_SIZE 3
#define MAX_COLOR_RGB 255

typedef struct {
     unsigned char red,green,blue;
} Pixel;

typedef struct {
     char type[STR_IMAGE_TYPE_SIZE];
     int height, width;
     Pixel *data;
} ImagePPM;

/*
* Inicia imagem, com as configurações passadas
* Ou seja, retorna em "image", uma "ImagePPM", do tipo "type"
* com tamanho "height" x "width". Além disso aloca o espaço que sera necessário para preencher
* a imagem
*/
int initImage(ImagePPM *image, char *type, int height, int width);//

/*
* A partir de uma imagem armazenada em "filename", cria uma imagem "image"
* caso a entrada, ou seja, "filename", seja null, tenta ler a imagem a partir
* da entrada padrão
*/
Pixel readPPM(const char *filename, ImagePPM *image);

/*
* Copia para a imagem "imgDest", o máximo possível da imagem "imgSrc", 
* a partir da posição "initialX", "initialY"
* É importante salientar que mesmo que as imagens sejam em essẽncia um vetor, elas são tratadas como matrizes
* portanto a escrita não é nessariamente linear na imagen destino
* Retorna a quantidade de pixels escritos
*/
void writeImage(ImagePPM *imgDest, ImagePPM *imgSrc, int initialX, int initialY);

/*
* Calcula a cor média de uma região em "image", com inicio em "initialX", "initialY"
* e tamanho "offsetX"x"offsetY"
*/
Pixel getAvarageColor(ImagePPM *image,int initialX, int initialY, int offsetX, int offsetY);

/*
* calcula e retorna a distância entre duas cores seguindo a fórmula de distânci RedMean
*/
int distanceBetweenColors(Pixel pxA, Pixel pxB);

/*
* Exporta a imagem "img", em um arquivo "filename"
* se o arquivo for null, a imagem é enviada para a saída padrão
*/
void imageToFile(const char *filename, ImagePPM *img);//imprimir em stdout

/*
* Retorna altura da imagem
*/
int getImageHeight(ImagePPM *image);

/*
* Retorna largura da imagem
*/
int getImageWidth(ImagePPM *image);