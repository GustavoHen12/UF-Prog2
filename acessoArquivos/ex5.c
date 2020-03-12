#include<stdio.h>
#include<stdlib.h>

/*Escreva um programa mycp para fazer a cópia de um arquivo em outro:
 mycp arq1 arq2. Antes da cópia, arq1 deve existir e arq2 não deve existir. Mensagens de erro devem
 ser geradas caso essas condições não sejam atendidas ou o nome dado a arq2 seja inválido*/

int main(int argc, char *argv[ ])
{
    FILE* read;
    FILE* write;
	read = fopen(argv[1], "r");
    if(!read){
        perror("O arquivo a ser copiado nao existe");
        exit(1);
    }

    write = fopen(argv[2], "r");//verifica se ja existe o arquivo
    if(write != NULL){
        perror("Nome invalido");
        exit(1);
    }

    write = fopen(argv[2], "w");

    while(!feof(read))
        fputc(getc(read), write);

    return 0;
}