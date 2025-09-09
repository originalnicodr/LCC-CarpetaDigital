#include <stdio.h>
/**
4) Russian Peasant Algorithm. La multiplicacion de enteros positivos puede
   implementarse con sumas, ands y desplazamientos de bits usando las siguientes identidades:


   Usarlas para implementar una funcion:
   unsigned mult(unsigned a, unsigned b);

        0 si b = 0
        a si b = 1
        2a.k si b = 2k
        2a.k + a si b = 2k + 1
                    (b-1)/2
*/

unsigned mult(unsigned a, unsigned b){
  int res = 0;
  
  while (b > 0) {

     if (b & 1)
         res = res + a;


     a = a << 1;
     b = b >> 1;
 }
  printf("Llegue aqui.\n");
  return res;
}

int main(){
  printf("Resultado: %d\n", mult(120,5));
}
