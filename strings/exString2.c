#include<stdio.h>

int main()
{
	char palavra[100];
	scanf("%s", palavra);
	int i = 0;
	while(palavra[i] != '\0')
		i++;

	printf("%d\n", i);
	return 0;
}