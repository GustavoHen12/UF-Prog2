#include "erre.h"

int inicia(tERRE *dados)
{
    dados->tam = 0;
    printf("1");
    (*dados).data = malloc(MAX * sizeof(float));
    // printf("2");
    // if(dados->data == NULL) return 0;
    printf("\naqui \n");
    return 1;
}

int stringToErre(char *str, tERRE *dados)
{
    char num[10];

    int i = 0, j = 0, tam = 0;
    printf("aqui1\n");
    while(str[i] != '\0')
    {
        j = 0;
        while((((str[i] >= 48) && (str[i] <= 57)) || (str[i] == 36)) && (str[i] != '\0')){
            num[j] = str[i];
            j++;
            i++;
        }
        num[j] = '\0';
        printf("%s \n", num);
        if(j > 0)
        {
            dados->data[dados->tam] = atof(num);
            dados->tam++;
            tam++;
            if(tam > MAX)
            {
                dados->data = realloc(dados->data, (dados->tam + MAX) * sizeof(float));
                tam = 0;
            }
        }
        i++;
    }
    printf("\n %d \n", dados->tam);
    for(i = 0; i < dados->tam; i++)
        printf("%.2f ", dados->data[i]);
    return 1;
}