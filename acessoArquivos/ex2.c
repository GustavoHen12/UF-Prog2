#include <stdio.h>
#include <stdlib.h>

/*Escreva um programa em C que leia um arquivo com números reais 
(um número por linha) e informe a média dos valores lidos.*/
int main(int argc, char *argv[ ])
{
	FILE* arq;
	arq = fopen(argv[1], "r");
    if(!arq){
        perror("O arquivo nao existe");
        exit(1);
    }
	char dig;
	long int quant = 0, divisor = 1, dez = 1;
    float num = 0.0, total = 0.0, res = 0.0;
	while(!feof(arq))
	{
		dig = getc(arq);
		
        if(dig == 46)
	    {
    		dez = 10;
        }
        else
        {
            if(dig == '\n')
            {
                num = num/divisor;
                printf("%.2f\n", num);
                total = total+num;
                num = 0.0;
                dez = 1;
                divisor = 1;
                quant++;
            } 
            else{
                num = num*10 + (dig - 48);
                divisor = divisor*dez;
            }
        }
	}
    res = total / quant;
	printf("> %.2f\n", res);
	return 0;
}