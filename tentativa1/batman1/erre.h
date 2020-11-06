#include<stdio.h>
#include<stdlib.h>

#define MAX 100
//tamanho dos dados
//dados, ordenados, em um vetor de float
typedef struct erre{
    int tam;
    float *data;
} tERRE;

int inicia(tERRE *dados);

int stringToErre(char *str, tERRE* dados);

int quantidadeAmostras(tERRE* dados);

//imprime o dispositivo
//retorna uma matriz com os valores
float **ramoEfolhas(tERRE* dados, int quantRamos);

//imprime o dispositivo
//retorna um vetor com os valores na ordem:
//minino, 1quartil, mediana, 3quartil, maximo 
float **cincoNumeros(tERRE* dados);

float *outliars(tERRE dados);

//imprime o dispositivo
//retorna uma matriz com os valores
float **tabelaDeFrequencia(tERRE dados);

