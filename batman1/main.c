#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <locale.h>

#include "erre.h"

#define TAM 400

void readData(char *path, char** str)
{
    char digito;
    int tam = 0, i = 0;
    *str = malloc(TAM * sizeof(char));

    FILE *file;
    file = fopen(path, "r");
    while(!feof(file))
    {
        digito = getc(file);
        if(i >= TAM){
            *str = realloc(*str, (tam+TAM) * sizeof(char));
            i = 0;
        }
        (*str)[tam] = digito;
        tam++;
        i++;
    }
    (*str)[tam] = '\0';
}

int main(int argc, char *argv[ ])
{
    setlocale (LC_CTYPE, "pt_BR.ISO-8859-1");
    //pega arquivo e carrega em memoria
    char *dados;
    readData(argv[1], &dados);
    printf("> %s \n", dados);

    //cria no formato da biblioteca
    tERRE dataset;
    inicia(&dataset);
    stringToErre(dados, &dataset);

    //mostra ramo e folhas
    ramoEfolhas(&dataset, 2);
    //5numeros
}
