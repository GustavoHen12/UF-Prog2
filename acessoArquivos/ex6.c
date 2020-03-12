#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 200
/*o comando grep do UNIX imprime na saída padrão 
(stdout) as linhas de um arquivo de entrada que contenham 
uma determinada string informada como parâmetro. Escreva 
esse programa em C (dica: use a função strstr).*/

int main(int argc, char *argv[ ])
{
    FILE* arq;
	arq = fopen(argv[1], "r");
    if(!arq){
        perror("O arquivo nao existe");
        exit(1);
    }

	char linha[MAX];
    while(!feof(arq))
    {
        fgets (linha, MAX, arq);
        if(strstr(linha, argv[2]))
            printf("%s", linha);
    }
    return 0;
}