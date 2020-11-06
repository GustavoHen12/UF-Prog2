#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TAM_PALAVRA 30
#define TAM_ALOCACAO 10000

typedef struct dici{
    unsigned char **palavras;
    int tamanho;
} Dicionario;

//recebe o caminho ate o dicionario
//a lista de strings e passada no "dici"
//retorna a quantidade de palavras se conseguiu concluir e -1 se ocorreu um erro
int le_dicionario(char* path, Dicionario* dici);

int iniciaDicionario(Dicionario *dici);

int adicionaDicionario(Dicionario *dici, char *palavra);

int aumentaDicionario(Dicionario *dici);

int tamanhoDici(Dicionario *dici);

int estaDicionario(Dicionario *dici, unsigned char *palavra, int high, int low);

int estaDicionarioIt(Dicionario *dici, unsigned char *palavra, int tam);
