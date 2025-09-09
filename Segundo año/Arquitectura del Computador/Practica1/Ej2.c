#include <stdio.h>

/**
Rotar los valores de dos variables sin utilizar variables auxiliares.
A = A+B
B = A-B
A = A-B
*/

/* ROTAR VARIABLES USANDO XOR*/

void bp(int valor){
  for(int i=31; i>=0; i--){
    if((i+1)%8 == 0){
      printf(" ");
      }
      (valor&(1<<i)) ? printf("1"):printf("0");
    }
  printf(" =  %d\n", valor);
}

void rotarXOR(int *a, int *b){//se trabaja con punteros por que tiene que "devolver" dos valores
  *a = (*a)^(*b);
  *b = (*b)^(*a);
  *a = (*b)^(*a);
}

int main() {
  int a=2,b=5;
  printf("El valor de a: %d y de b: %d\n",a,b);
  rotarXOR(&a,&b);
  printf("El valor de a: %d y de b: %d\n",a,b);

}
