#include <stdio.h>
#include <stdlib.h>

/*Escreva um programa em C para ler um 
arquivo minusc.txt e escrever um arquivo maiusc.txt 
contendo o mesmo texto em maiúsculas.*/

int main(int argc, char *argv[ ])
{
    FILE* read;
    FILE* write;
	read = fopen(argv[1], "r");
    if(!read){
        perror("O arquivo nao existe");
        exit(1);
    }
    write = fopen(argv[2], "w");
    unsigned char letra;

    while(!feof(read))
    {
        letra = getc(read);
        if((letra >= 97) && (letra < 123))
            letra = letra - 32;
        fputc(letra, write);
    }
    return 0;
}