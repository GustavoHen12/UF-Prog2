#include <stdio.h>
#include <string.h>

int main()
{
	char palavra[100], novaPalavra[100];
	int tam = 0;
	scanf("%s", palavra);
	tam = strlen(palavra);
	novaPalavra[tam--] = '\0';
	int i = 0;
	while(tam >= 0)
		novaPalavra[tam--]=palavra[i++];

	printf("\n%s\n", novaPalavra);
	return 0;
}