#include<stdio.h>
#include<string.h>

#define MAX 100

int main()
{
    char str[MAX*2+1];
    //le a entrada
    scanf("%[^\n]", str);
    getchar() ;
    str[strcspn (str, "\n")] = '\0';
    //coloca entre colchetes
    int i = 0, j, tam;
    printf("%s \n",str);
    while(str[i] != '\0')
    {
        if(((str[i] < 48) || ((str[i] > 57) && (str[i] < 65)) ||
            ((str[i] > 90) && (str[i] < 97)) || (str[i]>123)) && (str[i]!= 32))
        {
           tam = strlen(str);
           for(j = tam; j > i; j--)
                str[j+2] = str[j];

           str[i+1] = str[i];
           str[i] = '[';
           str[i+2]=']';
           i = i + 2;
        }
        i++;
    }

    printf("->%s \n", str);
    return 0;
}
