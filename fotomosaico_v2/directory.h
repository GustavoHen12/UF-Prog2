#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

#define STRING_SIZE 100

/*
* Verifica se a entrada do diretorio é invalida
* se for INVALIDA retorna 1, caso contrario 0
*/
int diretoryInvalid(struct dirent *direntry);

/*
* A partir do nome do arquivo e do diretório
* retorna o nome correto no formato .../diretorio/arquivo
*/
void filenameFormat(char **completeFilename, char* dirname, char *filename);

/*
* Verifica, se o diretório termina com '/'
* se o nome do diretório não terminar assim, tenta adicionar
* se isso não for possível retorna 0, caso contrário 1
*/
int validDirectoryName(char *dirname);

/*
* Retorna o número de arquivos válidos em "dirname"
*/
int filesInDirectory(char *dirname);