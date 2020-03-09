#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TAM_PALAVRA 30
#define TAM_ALOCACAO 1000

int le_dicionario(char* path, char*** dici)
{
    FILE* dicionario;
    char texto_str[TAM_PALAVRA];
    dicionario = fopen(path, "r");
    
    if (dicionario == NULL){
        printf("ocorreu um problema \n");
        return 0;
    }

    int i = 0;
    *(dici) = (char**)malloc(TAM_ALOCACAO * sizeof(char *));
    while(fgets(texto_str, TAM_PALAVRA, dicionario) != NULL)
    {
        printf("aqui\n");
        *(dici[i]) = (char*)malloc(TAM_PALAVRA * sizeof(char));
        if(i > TAM_ALOCACAO)
                *(dici) = (char**)malloc(TAM_ALOCACAO * sizeof(char *));
        *(dici[i]) = texto_str;
        printf("%s\n", *(dici[i]));
        i++;
    }
    fclose(dicionario);
    
    return 1;
}

/*no momento so ira testar as funcoes implementadas*/
int main(int argc, char *argv[ ])
{
    //argv[1] e o diretorio do dicionario
    char *** dici;
    le_dicionario(argv[1], dici);
    printf("%s\n", dici[0][0]);

}
