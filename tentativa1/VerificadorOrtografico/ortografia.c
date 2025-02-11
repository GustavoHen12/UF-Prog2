#include <stdio.h>
#include <string.h>
#include <locale.h>

#include "dicionario.h"

#define MAX 20
//recebe a primeira letra da palavra e devolve a palvra
//retorna o primeiro caracter que nao eh palavra
unsigned char leFormata_palavra(unsigned char letra, unsigned char *string, unsigned char *stringMin);
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
    int resposta;
    if(argc > 0)
        resposta = le_dicionario(argv[1], &dicionario);
    else
        resposta = le_dicionario("/usr/share/dict/brazilian", &dicionario);
    
    if(!resposta)
    {
        perror("nao foi possivel abrir este dicionario");
        exit(1);
    }

    tamDicionario = tamanhoDici(&dicionario);

    //LE TEXTO
    unsigned char letra, palavra[MAX], palavraF[MAX];
    letra = getchar();
    while(!feof(stdin))
    {
        if(ehLetra(letra))
        {
            letra = leFormata_palavra(letra, palavra, palavraF);
            //letra = le_palavra(letra, palavra);
            if(strlen((char*)palavra) > 1)
            {
                //formataPalavra(palavra, palavraF);

                if(estaDicionarioIt(&dicionario, palavraF, tamDicionario))
                //if( estaDicionario(&dicionario, palavraF, tamDicionario-1, 0) != -1)
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

unsigned char leFormata_palavra(unsigned char letra, unsigned char *string, unsigned char *stringMin)
{
    string[0] = letra;
    if((string[0] < 96) || ((string[0] < 223) && (string[0] >= 192)))
        stringMin[0] = string[0] + 32;
    else
        stringMin[0] = string[0];
    letra = getchar();
    int i = 1;
    while(!feof(stdin) && ehLetra(letra))
    {
        string[i] = letra;
        if((string[i] < 96) || ((string[i] < 223) && (string[i] >= 192)))
            stringMin[i] = string[i] + 32;
        else
            stringMin[i] = string[i];
        i++;
        letra = getchar();
    }
    string[i] = '\0';
    stringMin[i] = '\0';
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