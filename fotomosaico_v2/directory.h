#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

#define STRING_SIZE 100

/*
* verifica se a entradad do diretorio é invalida
* se for INVALIDA retorna 1, caso contrario 0
*/
int diretoryInvalid(struct dirent *direntry);

/*
* a partir do nome do arquivo e do diretório
* retorna o nome correto no formato .../diretorio/arquivo
*/
void filenameFormat(char **completeFilename, char* dirname, char *filename);

/*
* verifica, se o diretório termina com '/'
*/
int validDirectoryName(char *dirname);