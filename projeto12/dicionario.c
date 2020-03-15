#include "dicionario.h"
int iniciaDicionario(Dicionario *dici)
{
    dici->palavras = malloc(TAM_ALOCACAO * sizeof(unsigned char*));
    if(!dici->palavras)
        return 0;
    dici->tamanho = 0;
    return 1;
}

int aumentaDicionario(Dicionario *dici)
{
    dici->palavras = realloc(dici->palavras, (dici->tamanho+TAM_ALOCACAO) * sizeof(unsigned char *));
    return 1;
}

int adicionaDicionario(Dicionario *dici, unsigned char *palavra)
{
    if(tamanhoDici(dici) > TAM_ALOCACAO){
            aumentaDicionario(dici);
    }
    dici->palavras[dici->tamanho] = malloc(TAM_PALAVRA*sizeof(unsigned char));
    int i = 0;
    while(palavra[i] != '\0')
    {
        dici->palavras[dici->tamanho][i] = palavra[i];
        i++;
    }
    dici->tamanho += 1;
    return 1;
}

int tamanhoDici(Dicionario *dici)
{
    return dici->tamanho;
}

int le_dicionario(char* path, Dicionario* dici)
{
    FILE* dicionario;
    char texto_str[TAM_PALAVRA];
    dicionario = fopen(path, "r");
    
    if (dicionario == NULL){
        perror("nao foi possivel abrir este dicionario");
        return -1;
    }
    while(fgets(texto_str, TAM_PALAVRA, dicionario) != NULL)
    {
        
        texto_str[strcspn (texto_str, "\n")] = 0;
        adicionaDicionario(dici, texto_str);
    }

    fclose(dicionario);
    return 1;
}



int estaDicionario(Dicionario *dici, unsigned char *palavra, int high, int low)
{
    if(low <= high)
    {
        int meio = low + (high-low)/2;
        int comp = strcmp(palavra, dici->palavras[meio]);
        //printf("%s - %s # %d %d\n", dici->palavras[meio], palavra, meio, comp);
        if(comp == 0)
            return 1;
        else if (comp > 0)
            return estaDicionario(dici, palavra, high, meio+1);
        else
            return estaDicionario(dici, palavra, meio-1, low);
    }
    return -1;
} 