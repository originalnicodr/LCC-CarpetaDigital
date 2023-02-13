#include <stdio.h>
#include <stdlib.h>
#include "tablahash.h"

unsigned hash(void* clave) {
  int* p = clave;
  return *p;//te devuelve la misma clave?
}

int punteros_comparar(void *a, void *b){
  return (hash((int*)a)==hash((int*)b));
}

//Si ejecuto el tabla hash insertar dos veces con la misma clave me va a pisar el dato guardado anteriormente

int main(void) {
  int x = 42, y = 42, z = 3;
  TablaHash *th = tablahash_crear(10, hash, punteros_comparar);

  tablahash_insertar(th, &x, &z);

  printf("z : %d\n", *((int *)tablahash_buscar(th, &x)));
  printf("z : %d\n", *((int *)tablahash_buscar(th, &y)));//se crashea aca, por que? si la funcion de hash devuelve el mismo dato con la clabe

  tablahash_eliminar(th, &x);

  tablahash_destruir(th);

  return 0;
}
