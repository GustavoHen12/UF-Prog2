#include <stdio.h>
#include <string.h>
#include "dicionario.h"

#define MAX 20
//recebe a primeira letra da palavra e devolve a palvra
//retorna o primeiro caracter que nao eh palavra
unsigned char le_palavra(unsigned char letra, unsigned char *string);

int  formataPalavra(unsigned char *string, unsigned char *newString);

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
    
    //LE TEXTO
    unsigned char letra, palavra[MAX], palavraF[MAX];
    while(!feof(stdin))
    {
        letra = getchar();

        if(ehLetra(letra))
        {
            letra = le_palavra(letra, palavra);

            formataPalavra(palavra, palavraF);

            //if(estaDicionario(palavra))
                printf("%s|%s|%c", palavra,palavraF, letra);
            //else 
            //    printf("[%s]", palavra);
        }
        else
        {
            printf("%c", letra);
        }
    }

    return 0;
}

unsigned char le_palavra(unsigned char letra, unsigned char *string)
{
    string[0] = letra;
    letra = getchar();
    int i = 1;
    while(ehLetra(letra) && !feof(stdin))
    {
        string[i] = letra;
        letra = getchar();
        i++;
    }
    string[i] = '\0';
    return letra;
}

int  formataPalavra(unsigned char *string, unsigned char *newString)
{
    if(string[0] > 96)
        newString[0] = string[0] - 32;
    else
        newString[0] = string[0];
    int i = 1;
    while (string[i] != '\0')
    {
        if(string[i] < 96)
            newString[i] = string[i] + 32;
        else
            newString[i] = string[i];
        i++;
    }
    newString[i] = '\0';
    return 1;
}
