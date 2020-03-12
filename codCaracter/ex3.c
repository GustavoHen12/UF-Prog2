#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
/*escreva um programa em C para converter um 
texto em ISO-8859-1 para UTF-8.

0xxx-xxxx
110x-xxxx 10xx-xxxx
11000011 10111111
*/
int main(int argc, char *argv[ ])
{
	FILE* arq;
	arq = fopen(argv[1], "r");//le arq iso
	unsigned int convASCII = 0b01111111, convH = 0b11000011, convL = 0b10111111; 
	unsigned char letra, low, high;
	wchar_t letraL;
	setlocale (LC_CTYPE, "") ;
	while(!feof(arq))
	{
		letra = getc(arq);
		letraL = 'B';
		printf("%lc", letraL);
// 		if(letra < 126)
// 		{
// 			letra = letra & convASCII;
// 			printf("%c", letra);
// 		}
// 		else
// 		{
// 			low = (letra & 0b00111111) | convL;
// //			letraL = letraL | low;
// 			high = (letra >> 5) | convH;
// //			letraL = letraL | ((convH | high) << 8);
// 			printf("%lc", letraL);
// 		}
	}
	printf("\n");
	return 0;
}