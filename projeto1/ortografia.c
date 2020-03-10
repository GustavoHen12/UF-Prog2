#include <stdio.h>
#include <string.h>
#include "dicionario.h"
int main(int argc, char *argv[ ])
{
    //LE DICIONARIO
    unsigned char ** dicionario;
    int tamDicionario = 0;
    //verifica se o dicionario foi passado como parametro
    //ou se ja existe no sistema
    if(argc > 0)
        tamDicionario = le_dicionario("/usr/share/dict/brazilian", &dicionario);
    else
        tamDicionario = le_dicionario(argv[1], &dicionario);
    printf("%d \n", tamDicionario);
    //LE TEXTO
    unsigned char letra;
    letra = getchar();
    //for(int i = 0; i < 20; i++)
    while(!feof(stdin))
    {
        printf("%c", letra);
        letra = getchar();
    }

}
