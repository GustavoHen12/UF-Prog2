#include<stdio.h>
#include<stdlib.h>

/*O arquivo mapa.txt contém o mapa de um nível do jogo Boulder Dash.
Escreva um programa em C que carregue esse mapa em uma matriz de caracteres.*/

int main(int argc, char *argv[ ])
{
    FILE *mapa;
    mapa =  fopen(argv[1], "r");
    if(!mapa){
        perror("O arquivo nao existe");
        exit(1);
    }
    char **newMap;
    int lin, col,i,j;
    fscanf(mapa,"%d %d", &lin, &col);
    fgetc(mapa);//para pegar o \n
    printf("> %d %d\n", lin, col);
    
    //ALOCA
    newMap = malloc(lin*sizeof(char*));
    for(i = 0; i < col; i++)
        newMap[i] = malloc(col*sizeof(char));
    
    //COPIA MAPA    
    for(int i = 0; i < lin; i++)
    {
        for(int j = 0; j < col; j++)
            newMap[i][j] = fgetc(mapa);
        fgetc(mapa);//para pegar o \n
    }

    //IMPRIME MAPA
    for(i = 0; i < lin; i++)
    {
        for(j= 0; j < col; j++)
            printf("%c", newMap[i][j]);
        printf("\n");
    }

    return 0;
}