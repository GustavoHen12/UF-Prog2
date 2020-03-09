#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int le_dicionario(char* path)
{
    FILE *dicionario;
    char texto_str[20];
    dicionario = fopen(path, "r");
    if (dicionario == NULL)
    {
        printf("ocorreu um problema \n");
        return 0;
    }
    while(fgets(texto_str, 20, dicionario) != NULL)
        printf("%s \n", texto_str);
    fclose(dicionario);
    return 1; 
}

/*no momento so ira testar as funcoes implementadas*/
int main(int argc, char *argv[ ])
{
    //argv[1] e o diretorio do dicionario
    le_dicionario(argv[1]);

}
