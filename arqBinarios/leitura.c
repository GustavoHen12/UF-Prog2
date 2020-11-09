#include<stdio.h>
#include<stdlib.h>
#include <time.h>

#define SIZE 1000000
#define READ_SIZE 10

int main(int argc, char *argv[]){
    printf("inicia\n");
    long int values[READ_SIZE];

    FILE *arq;
    arq = fopen(argv[1], "r");
    if(!arq){
        perror ("Erro ao abrir arquivo") ;
        exit (1) ;
    }
    
    fread(values, sizeof(long int), READ_SIZE, arq); 
    printf("Os 10 primeiros: \n");
    for(int i = 0; i < READ_SIZE; i++)
        printf(" %ld \n", values[i]);

    fseek (arq,  10*sizeof(long int), SEEK_END);
    fread(values, sizeof(long int), READ_SIZE, arq); 
    printf("Os 10 ultimos: \n");
    for(int i = 0; i < READ_SIZE; i++)
        printf(" %ld \n", values[i]);  
    fclose(arq);

    return 0;
}