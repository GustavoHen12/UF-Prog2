#include <stdio.h>

#define MAX 100

int main()
{
    char palavra[MAX];
    
    scanf("%s", palavra);
    int i = 0;
    while(palavra[i] != '\0')
    {
        if (palavra[i] >= 97)
            palavra[i] -= 32;
        i++;
    }

    printf("-> %s \n", palavra); 
    return 0;
}
