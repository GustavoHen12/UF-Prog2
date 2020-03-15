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
    letra = getchar();
    while(!feof(stdin))
    {
        if(ehLetra(letra))
        {
            letra = le_palavra(letra, palavra);
            if(strlen(palavra) > 1)
            {
                formataPalavra(palavra, palavraF);

                int res = estaDicionario(dicionario, palavraF, tamDicionario, 0);
                if( res != -1)
                    printf("%s%c", palavra, letra);
                else 
                    printf("[%s]%c", palavra, letra);
            }
            else
            {
                printf("%s%c", palavra, letra);
            }   
        }
        else
        {
            printf("%c", letra);
        }
        
        letra = getchar();
    }
    return 0;
}

unsigned char le_palavra(unsigned char letra, unsigned char *string)
{
    string[0] = letra;
    letra = getchar();
    int i = 1;
    while(!feof(stdin) && ehLetra(letra))
    {
        string[i] = letra;
        i++;
        letra = getchar();
    }
    string[i] = '\0';
    if(feof(stdin))
        return 0;
    return letra;
}

int  formataPalavra(unsigned char *string, unsigned char *newString)
{
    int i = 0;
    while (string[i] != '\0')
    {
        if((string[i] < 96) || ((string[i] < 223) && (string[i] >= 192)))
            newString[i] = string[i] + 32;
        else
            newString[i] = string[i];
        i++;
    }
    newString[i] = '\0';
    return 1;
}
