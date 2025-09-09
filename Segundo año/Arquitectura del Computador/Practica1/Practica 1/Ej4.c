#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
//Ej4

unsigned mult(unsigned a, unsigned b){
  int r = 0;
  while (b > 0) {//si no entra retorna 0
     if (b & 1) r = r + a;
     a = a << 1;
     b = b >> 1;
 }
  return r;
}
 int main(){
   puts("\nEjercicio 4");
   int d=2;
   printf("%d x %d = %d\n",d,d,mult(d,d));
   int e=3;
   printf("%d x %d = %d\n",d,e,mult(d,e));
   return 0;
 }
