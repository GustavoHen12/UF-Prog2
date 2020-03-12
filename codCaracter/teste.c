#include <stdio.h>
#include <wchar.h>
 
int main ()
{
  wchar_t c ;         // um caractere largo
  wchar_t *s ;        // ponteiro para uma string larga
 
  c = L'a' ;          // caractere constante largo
  s = L"equação" ;    // string constante larga
 
  // escrita de caracteres e strings largas
  printf ("Caractere %lc e string %ls\n", c, s) ;
 
  // número de caracteres de uma string larga
  printf ("A string tem %ld caracteres\n", wcslen (s)) ;
}