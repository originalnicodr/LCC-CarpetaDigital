#include <stdio.h>
#include <stdlib.h>
#include "tablahash.h"

int iguales(void* clave1, void* clave2) {
  int* p = clave1;
  int* q = clave2;
  return *p == *q;
}

unsigned hash(void* clave) {
  int* p = clave;
  return *p;
}

int main(void) {
  int x = 42, y = 42, z = 3;
  TablaHash *th = tablahash_crear(10, hash, iguales);//por que me cambias la tabla crear? modificas la estructura de la tabla para guardar la funcion de comparacion?

  tablahash_insertar(th, &x, &z);

  printf("z : %d\n", *((int *)tablahash_buscar_fer(th, &x)));

  tablahash_eliminar(th, &x);

  tablahash_destruir(th);

  return 0;
}
