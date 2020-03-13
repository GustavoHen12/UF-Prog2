#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TAM_PALAVRA 30
#define TAM_ALOCACAO 10000

//recebe o caminho ate o dicionario
//a lista de strings e passada no "dici"
//retorna a quantidade de palavras se conseguiu concluir e -1 se ocorreu um erro
int le_dicionario(char* path,unsigned char*** dici);

//recebe um unsigned char como pararemtro e retorna true se for letra
int ehLetra(unsigned char caracter);

//int estaDicionario