#include<stdio.h>
#include<stdlib.h>
#include <locale.h>

#define TAM_PALAVRA 30

int main(int argc, char *argv[ ])
{
    setlocale (LC_CTYPE, "pt_BR.ISO-8859-1");

    FILE* dicionario;
    char texto_str[TAM_PALAVRA];
    //dicionario = fopen("/Documentos/UFPR/brazilian", "r");
    dicionario = fopen(argv[1], "r");
    if (dicionario == NULL){
        printf("Erro: nao existe dicionario\n");
        return -1;
    }

    while(fgets(texto_str, TAM_PALAVRA, dicionario) != NULL)
    {
        if(texto_str[0] == 'p')
            printf("<> %s", texto_str);
    }
    fclose(dicionario);
    return 0;
}
