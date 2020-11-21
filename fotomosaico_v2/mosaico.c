// GRR20190485 Gustavo Henrique da Silva Barbosa 

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <ctype.h>
#include <unistd.h>

#include "image.h"
#include "directory.h"

#define STRING_SIZE 100

typedef struct{
   ImagePPM_t *images;
   Pixel_t *avarageColors;
   int size;
} Tiles_t;

//Lê as pastilhas que serão ultilizadas.
int readTiles( Tiles_t *tiles, char *dirname);

//Faz a busca pela pastilha que possui a cor média mais próxima a de comparação.
int getCloserTile(Pixel_t color, Pixel_t *colorTiles, int size);

//Lê as opções passadas pela linha de comando.
void readOptions(int argc, char *argv[], char **dirname, char **imgname, char **output);


int main (int argc, char *argv[]){
   //Tenta ler as opções de nome do diretório de pastilhas, imagem de entrada e imagem de saída
   char *dirname, *imgname, *output; 
   readOptions(argc, argv, &dirname, &imgname, &output);
   
   //verifica se o nome do diretorio esta correto,ou seja se possui termina com '/' 
   //caso não possua tenta adicionar
   if(!validDirectoryName(dirname)){
      fprintf(stderr,"O diretorio informado não possui um formato válido. Ex: /.../[diretorio]/\n");
      exit(1);
   }

   //Inicia pastilhas e as lê a partir do diretorio "dirname"
   Tiles_t tiles;
   readTiles(&tiles, dirname);

   //Lê imagem que sera utilizada para fazer o mosaico
   ImagePPM_t image;
   readPPM(imgname, &image);
      
   //Cria imagem que sera utilizada como modelo para o mosaico
   //esta possui as mesmas configurações que a imagem original
   ImagePPM_t mosaico;
   initImage(&mosaico, image.type, image.height, image.width);

   //Inicia variaveis que serão utilizadas para o controle ao ser montado o mosaico
   int tilesHeight = getImageHeight(&(tiles.images[0]));
   int tilesWidth = getImageWidth(&(tiles.images[0]));
   Pixel_t avarageColor;

   //Percorre a imagem por blocos de "tilesHeigh"x"tilesWidth"
   for(int i = 0; i < image.height; i+= tilesHeight){
      for(int j = 0; j < image.width; j+= tilesWidth){
         //calcula a cor média do bloco da imagem
         avarageColor = getAvarageColor(&image, i, j, tilesWidth, tilesHeight);
         //Então é feita a busca pela pastilha que possue a cor média mais próxima do bloco  
         int ind = getCloserTile(avarageColor, tiles.avarageColors, tiles.size);
         //Por fim, a pastilha selecionada é escrita na imagem final ("mosaico"),
         //na mesma posição em que foi "extraido" o bloco da imagem original 
         writeImage(&mosaico, &(tiles.images[ind]), j, i);
      }
   }
   //Apos o mosaico ter sido criado ele é "exportado", com base nas informações no header
   imageToFile(output, &mosaico);
   return 0;
}

/*
* As pastilhas lidas, do diretório "dirname", são armazenadas em "tiles"
* Como o tipo tiles (Tiles_t), possui três variáveis, os dados que dizem respeito a elas
* também são preenchidos
*/
int readTiles( Tiles_t *tiles, char *dirname){
   //cria variaveis e tenta abrir o diretorio "dirname"
   DIR *dirstream;
   struct dirent *direntry;
   dirstream = opendir (dirname);
   if ( ! dirstream ){
      perror ("Error ao abrir diretorio");
      exit (1) ;
   }

   //recebe o a quantidade de elementos no diretório
   int dirSize = filesInDirectory(dirname);

   //cria um vetor para as pastilhas e suas cores media, com espaco suficiente pastilhas do diretório
   tiles->images = malloc(sizeof(ImagePPM_t)*dirSize);
   tiles->avarageColors = malloc(sizeof(Pixel_t)*dirSize);
   
   //como ao abrir a imagem é necessario ser utilizado o formato .../diretorio/imagem.ppm
   //e necessario construir o nome do arquivo dinamicamente em filename
   char *filename;
   filename = malloc(sizeof(char)*STRING_SIZE);

   //lê cada entrada do diretório
   int tilesSize = 0;
   for(;;){
      direntry = readdir (dirstream) ;
      if (! direntry)
        break ;
      //verifica se a entrada possui o tipo correto 
      if(diretoryInvalid(direntry))
         continue;

      //formata nome para a imagem poder ser lida
      filenameFormat(&filename, dirname, direntry->d_name);

      //Lê pastilha, que é armazenada na variavel images da struct tiles
      //a cor média da imagem é armazenada em outro vetor, mas ambas possuem o mesmo indice
      tiles->avarageColors[tilesSize] = readPPM(filename, &(tiles->images[tilesSize]));
      tilesSize++;
   }
   (void) closedir (dirstream);

   //preenche com a quantidade de pastilhas
   tiles->size = tilesSize;
   
   return 0;
}

/*
* A cor que será comparada é a "color", que é do tipo Pixel, esta será comparada com
* as cores no vetor "colorTiles", que possui "size" cores.
* A função retorna o indice em que foi encontrada a imagem com a cor mais próxima
*/
int getCloserTile(Pixel_t color, Pixel_t *colorTiles, int size){
   int menorDist = distanceBetweenColors(color, colorTiles[0]), menorIndice = 0, dist = 0;
   //faz uma busca simples em busca da pastilha com a cor mais próxima à região da imagem
   for(int i = 0; i < size; i++){
      dist = distanceBetweenColors(color, colorTiles[i]);
      if(dist <= menorDist){
         menorDist = dist;
         menorIndice = i;
      }
   }
   //como o indice da cor média é igual ao da pastilha correspondente
   //retorna o indice da pastilha encontrada
   return menorIndice;
}

/*
* As opções que ele busca são pelos nome do: diretorio (-p), 
* imagem de entrada (-i) e imagem de saída(-o). Caso os nomes das imagens não
* seja enviado, o ponteiro irá apontar para "NULL", caso o nome do diretório não seja passado
* será usado o default ("./tiles/")
*/
void readOptions(int argc, char *argv[], char **dirname, char **imgname, char **output){
   
   //inicia variaveis e aloca espaco para as opções possiveis
   //as flags são utilizadas para posterior verificação das opções iniciadas
   int iFlag = 0, oFlag = 0, pFlag = 0;
   *dirname = malloc(sizeof(char) * STRING_SIZE);
   *imgname = malloc(sizeof(char) * STRING_SIZE);
   *output = malloc(sizeof(char) * STRING_SIZE);
   
   //lê cada opção, armazenando na variável correspondente
   int option;
   while ((option = getopt (argc, argv, "i:o:p:")) != -1){
      switch (option)
      {
         case 'i':
            iFlag = 1;
            *imgname = optarg;
            break;
         case 'o':
            oFlag = 1;
            *output = optarg;
            break;
         case 'p':
            pFlag = 1;
            *dirname = optarg;
            break;
         default:
            break;
      }
   }

   //caso os nomes das imagens não tenha sido selecionado
   //o ponteiro ira apontal para NULL
   if(!iFlag)
      *imgname = NULL;
   if(!oFlag)
      *output = NULL;
   //caso o diretorio não tenha sido selecionado é setado com o default
   if(!pFlag)
      *dirname = "./tiles/";
}