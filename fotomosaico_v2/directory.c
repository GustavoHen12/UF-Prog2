#include "directory.h"

int diretoryInvalid(struct dirent *direntry){
   //verifica se é o diretorio pai ou corrente
   if(strcmp(direntry->d_name,".") == 0)
      return 1;
   if(strcmp(direntry->d_name,"..") == 0)
      return 1;
   //verifica se 
   if(direntry->d_type != DT_REG)
      return 1;
   return 0;
}

void filenameFormat(char **completeFilename, char* dirname, char *filename){
    strcpy(*completeFilename, dirname);
    strcat(*completeFilename, filename);
}

int validDirectoryName(char *dirname){
    int lastChar = strlen(dirname);
    if(dirname[lastChar] == '/')
        return 1;
    return 0;
}