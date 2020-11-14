#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
 
int main (void)
{
   DIR *dirstream;
   struct dirent *direntry;
 
   dirstream = opendir ("./tiles20/");
   if ( ! dirstream )
   {
      perror ("Couldn't open the directory");
      exit (1) ;
   }
   while (direntry = readdir (dirstream))
      puts (direntry->d_name);
   (void) closedir (dirstream);
 
    exit (0);
}