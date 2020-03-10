#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TAM_PALAVRA 30
#define TAM_ALOCACAO 10000

int le_dicionario(char* path,unsigned char*** dici)
{
    FILE* dicionario;
    char texto_str[TAM_PALAVRA];
    dicionario = fopen(path, "r");
    
    if (dicionario == NULL){
        printf("ocorreu um problema \n");
        return 0;
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
    return 1;
}

/*no momento so ira testar as funcoes implementadas*/
int main(int argc, char *argv[ ])
{
    //argv[1] e o diretorio do dicionario
    unsigned char ** dici;
    le_dicionario(argv[1], &dici);
    printf("%s\n", dici[0]);

}
