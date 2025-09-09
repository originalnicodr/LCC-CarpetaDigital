#include <stdio.h>

int fuerza_bruta(char* S, char* s, unsigned int L, unsigned int l);


int main(){
  int f;
  char* S="Fuerza Bruta";
  char* s="Fuerza";
  unsigned int L=12;
  unsigned int l=6;
  f=fuerza_bruta(S,s,L,l);
  printf("%d\n",f );
  return 0;
}
