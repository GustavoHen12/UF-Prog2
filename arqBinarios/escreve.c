#include<stdio.h>
#include<stdlib.h>
#include <time.h>

#define SIZE 1000000

int main(int argc, char *argv[]){
    printf("inicia\n");
    long int values[SIZE];
    FILE *arq;
    arq = fopen(argv[1], "a");
    if(!arq){
        perror ("Erro ao abrir arquivo") ;
        exit (1) ;
    }
    int tam = sizeof(long int);
    printf("LongInt: %d \n", tam);
    for(int i = 0; i < 10; i++){
        printf("Gerando valores...");
        srand (clock());
        for(int j = 0; j < SIZE; j++)
            values[j] = random() % 10000000;

        printf("Numeros gerados.\n");
        printf("Gravando valores...\n");
        int res = fwrite(values, sizeof(long int), SIZE, arq);
        if(res){
            printf("Foi escrito %d valores em %s\n", res, argv[1]);
        }
    }
    fclose(arq);

    return 0;
}