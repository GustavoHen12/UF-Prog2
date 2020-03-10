#include <stdio.h>
#include <stdlib.h>

/*Escreva um programa em C para informar o número de caracteres presentes em um arquivo de texto.*/
int main(int argc, char *argv[ ])
{
	FILE* arq;
	arq = fopen(argv[1], "r");
	char letra;
	long int quant = 0;
	while(!feof(arq))
	{
		letra = getc(arq);
		if(letra > 33)
			quant++;
	}
	printf("> %ld\n", quant);
	return 0;
}