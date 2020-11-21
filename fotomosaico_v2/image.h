#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define STR_IMAGE_TYPE_SIZE 3
#define MAX_COLOR_RGB 255

typedef struct {
     unsigned char red,green,blue;
} Pixel_t;

typedef struct {
     char type[STR_IMAGE_TYPE_SIZE];
     int height, width;
     Pixel_t *data;
} ImagePPM_t;

/*
* Inicia imagem, com as configurações passadas
* Ou seja, retorna em "image", uma "ImagePPM", do tipo "type"
* com tamanho "height" x "width". Além disso aloca o espaço que sera necessário para preencher
* a imagem
*/
int initImage(ImagePPM_t *image, char *type, int height, int width);//

/*
* A partir de uma imagem armazenada em "filename", cria uma imagem "image"
* caso a entrada, ou seja, "filename", seja null, tenta ler a imagem a partir
* da entrada padrão
*/
Pixel_t readPPM(const char *filename, ImagePPM_t *image);

/*
* Copia para a imagem "imgDest", o máximo possível da imagem "imgSrc", 
* a partir da posição "initialX", "initialY"
* É importante salientar que mesmo que as imagens sejam um vetor, elas são tratadas como matrizes
* portanto a escrita não é necessariamente linear na imagem destino
* Retorna a quantidade de pixels escritos
*/
void writeImage(ImagePPM_t *imgDest, ImagePPM_t *imgSrc, int initialX, int initialY);

/*
* Calcula a cor média de uma região em "image", com inicio em "initialX", "initialY"
* e tamanho "offsetX"x"offsetY"
*/
Pixel_t getAvarageColor(ImagePPM_t *image,int initialX, int initialY, int offsetX, int offsetY);

/*
* Retorna altura da imagem
*/
int getImageHeight(ImagePPM_t *image);

/*
* Retorna largura da imagem
*/
int getImageWidth(ImagePPM_t *image);

/*
* calcula e retorna a distância entre duas cores seguindo a fórmula de distânci RedMean
*/
int distanceBetweenColors(Pixel_t pxA, Pixel_t pxB);

/*
* Exporta a imagem "img", em um arquivo "filename"
* se o arquivo for null, a imagem é enviada para a saída padrão
*/
void imageToFile(const char *filename, ImagePPM_t *img);//imprimir em stdout