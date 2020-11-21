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
   //concatena dirname a um filename
   //completeFilename=[dirname][filename]
   strcpy(*completeFilename, dirname);
   strcat(*completeFilename, filename);
}

int validDirectoryName(char *dirname){
   int lastChar = strlen(dirname);
   //verifica se o ultimo caracter é uma '/'
   if(dirname[lastChar-1] == '/')
      return 1;
   //se não for tenta adicionar
   if(lastChar < STRING_SIZE){
      dirname[lastChar] = '/';
      dirname[lastChar+1] = '\0';
      return 1;
   }
   //se o nome do diretorio nao suportar retorna
   return 0;
}

int filesInDirectory(char *dirname){
   //abre o diretorio
   DIR *dirstream;
   struct dirent *direntry;
   dirstream = opendir (dirname);
   int files = 0;
   //percorre diretorio
   for(;;){
      direntry = readdir (dirstream) ;
      if (! direntry)
        break ;
      //verifica se a entrada possui o tipo correto 
      if(diretoryInvalid(direntry))
         continue;
      //incrementa contador
      files++;
   }
   (void) closedir (dirstream);
   return files;
}