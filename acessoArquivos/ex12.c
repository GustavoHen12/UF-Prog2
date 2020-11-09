#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[ ]){
    FILE *arq;

    arq = fopen(argv[1], "r");
    int charTotal = 0;
    char c = getc(arq);
    while (c != EOF){
        charTotal++;
        c = getc(arq);
    }
    fclose(arq);

    printf("> %d \n", charTotal);
    return 0;
}