#include<stdio.h>
#include<string.h>

#define MAX 100

int main()
{
    char str[MAX+1];

    scanf("%[^\n]", str);
    getchar() ;
    str[strcspn (str, "\n")] = '\0';

    int i = 0, j, tam;
    printf("%s \n",str);
    while(str[i] != '\0')
    {
        if((str[i] < 48) || ((str[i] > 57) && (str[i] < 65)) ||
            ((str[i] > 90) && (str[i] < 97)) || (str[i]>123))
        {
           tam = strlen(str);
           for(j = i;j < tam; j++)
           {
                str[j] = str[j+1];
           }
        }
        else
        {
            i++;
        }
    }

    printf("-> %s \n", str);
    return 0;
}
