#include "dicionario.h"

int le_dicionario(char* path,unsigned char*** dici)
{
    FILE* dicionario;
    char texto_str[TAM_PALAVRA];
    dicionario = fopen(path, "r");
    
    if (dicionario == NULL){
        printf("Erro: nao existe dicionario\n");
        return -1;
    }
    int i = 0, tam = 0;
    *dici = (unsigned char**)malloc(TAM_ALOCACAO * sizeof(unsigned char*));
    while(fgets(texto_str, TAM_PALAVRA, dicionario) != NULL)
    {
        if(i > TAM_ALOCACAO){
            *dici = realloc(*dici, (tam+TAM_ALOCACAO) * sizeof(unsigned char *));
            i = 0;
        }
        (*dici)[tam]=(unsigned char*)malloc(40*sizeof(unsigned char));
        strcpy((*dici)[tam], texto_str);
        i++;
        tam++;
    }
    fclose(dicionario);
    return --tam;
}

