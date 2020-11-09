#include<stdio.h>
#include<stdlib.h>
#include <time.h>

#define SIZE 10000000

int main(int argc, char *argv[]){
    printf("inicia\n");
    long int values[SIZE];
    FILE *arq;
    arq = fopen(argv[1], "r");
    if(!arq){
        perror ("Erro ao abrir arquivo") ;
        exit (1) ;
    }
    printf("Lendo valores...");
    int res = fread(values, sizeof(long int), SIZE, arq);   
    printf("Lido %d valores.\n", res);
    fclose(arq);

    return 0;
}