#include<stdio.h>
#include<stdlib.h>

//tamanho dos dados
//dados, ordenados, em um vetor de float
typedef struct erre{
    int tam;
    float *data;
} tERRE;

tERRE* stringToErre();

//imprime o dispositivo
//retorna uma matriz com os valores
float **ramoEfolhas(tERRE dados, int quantRamos);

//imprime o dispositivo
//retorna um vetor com os valores na ordem:
//minino, 1quartil, mediana, 3quartil, maximo 
float *cincoNumeros(tERRE dados);

float *outliars(tERRE dados);

//imprime o dispositivo
//retorna uma matriz com os valores
float **tabelaDeFrequencia(tERRE dados);

