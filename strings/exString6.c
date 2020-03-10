#include<stdio.h>
#include<string.h>

#define MAX 100

int main()
{
    char str[MAX+1];
    //le o texto de entrada
    scanf("%[^\n]", str);
    getchar() ;
    str[strcspn (str, "\n")] = '\0';
    int i = 0, j, tam;
    printf("%s \n",str);
    //retira repeticoes
    while(str[i] != '\0')
    {
        if(str[i] == str[i+1])
        {
           tam = strlen(str);
           for(j = i;j < tam; j++)
                str[j] = str[j+1];
        }
        else
        {
            i++;
        }
    }

    printf("->%s \n", str);
    return 0;
}
