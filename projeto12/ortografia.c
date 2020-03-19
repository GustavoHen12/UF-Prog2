#include <stdio.h>
#include <string.h>
#include <locale.h>

#include "dicionario.h"

#define MAX 20
//recebe a primeira letra da palavra e devolve a palvra
//retorna o primeiro caracter que nao eh palavra
unsigned char le_palavra(unsigned char letra, unsigned char *string);

void  formataPalavra(unsigned char *string, unsigned char *newString);

int ehLetra(unsigned char caracter);

int main(int argc, char *argv[ ])
{
    setlocale (LC_CTYPE, "pt_BR.ISO-8859-1");
    
    //LE DICIONARIO
    Dicionario dicionario;
    int tamDicionario;

    //verifica se o dicionario foi passado como parametro
    //ou se ja existe no sistema
    iniciaDicionario(&dicionario);

    if(argc > 0)
        le_dicionario("/usr/share/dict/brazilian", &dicionario);
    else
        le_dicionario(argv[1], &dicionario);
    
    tamDicionario = tamanhoDici(&dicionario);

    //LE TEXTO
    unsigned char letra, palavra[MAX], palavraF[MAX];
    letra = getchar();
    while(!feof(stdin))
    {
        if(ehLetra(letra))
        {
            letra = le_palavra(letra, palavra);
            if(strlen((char*)palavra) > 1)
            {
                formataPalavra(palavra, palavraF);

                if( estaDicionarioIt(&dicionario, palavraF, tamDicionario) != -1)
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

void formataPalavra(unsigned char *string, unsigned char *newString)
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
}

int ehLetra(unsigned char caracter)
{
    if((((caracter >= 65) && (caracter <= 90)) ||
        ((caracter >= 97) && (caracter <= 122)) ||
        ((caracter >= 192) && (caracter <= 255))) &&
        ((caracter != 215) && (caracter != 247)))
        return 1;
    return 0;
}