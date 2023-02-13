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

int claves_comparar(void *a, void *b){
  return *((int*)a)==*((int*)b);
}

//Si ejecuto el tabla hash insertar dos veces con la misma clave me va a pisar el dato guardado anteriormente

int main(void) {
  int x = 42, y = 42, z = 3, w =5, v=7, a=42;
  TablaHash *th = tablahash_crear(11, hash, punteros_comparar);

  tablahash_insertar(th, &x, &z);
  tablahash_insertar(th, &y, &w);
  tablahash_insertar(th, &a, &v);

  printf("z : %d\n", *((int *)tablahash_buscar(th, &x)));
  printf("w : %d\n", *((int *)tablahash_buscar(th, &y)));//se crashea aca, por que? si la funcion de hash devuelve el mismo dato con la clave
  printf("v : %d\n", *((int *)tablahash_buscar(th, &a)));

  tablahash_eliminar(th, &x);

  printf("w : %d\n", *((int *)tablahash_buscar(th, &y)));

  tablahash_destruir(th);

  return 0;
}