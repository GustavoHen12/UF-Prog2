#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
int main(int argc, char *argv[ ])
{
	unsigned char letra;
	char conv[256];
	int i = 0;
	for(i = 192; i <= 197; i++) conv[i] = 'A';
	for(i = 200; i <= 203; i++) conv[i] = 'E';
	for(i = 204; i <= 207; i++) conv[i] = 'I';
	for(i = 210; i <= 214; i++) conv[i] = 'O';
	for(i = 217; i <= 220; i++) conv[i] = 'U';
	for(i = 224; i <= 229; i++) conv[i] = 'a';
	for(i = 232; i <= 235; i++) conv[i] = 'e';
	for(i = 236; i <= 239; i++) conv[i] = 'i';
	for(i = 242; i <= 246; i++) conv[i] = 'o';
	for(i = 249; i <= 252; i++) conv[i] = 'u';
	conv[199] = 'C';
	conv[231] = 'c';
	conv[206] = 'N';
	conv[241] = 'n';
	
	setlocale (LC_CTYPE, "pt_BR.ISO-8859-1") ;
	
	while(!feof(stdin))
	{
		letra = getchar();
		if(letra > 160)
			letra = conv[letra];
		printf("%c", letra);
	}
	return 0;
}