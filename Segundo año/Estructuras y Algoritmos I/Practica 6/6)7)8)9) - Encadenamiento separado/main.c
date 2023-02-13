#include <stdio.h>
#include <stdlib.h>
#include "tablahash.h"

unsigned hash(void* clave) {
  int* p = clave;
  return *p;//te devuelve la misma clave?
}

int punteros_comparar(void *a, void *b){
  return a==b;
}

//Si ejecuto el tabla hash insertar dos veces con la misma clave me va a pisar el dato guardado anteriormente

int main(void) {
  int x = 42, y = 42, z = 3, w=5, a=42, b=7, c=15, d=11;
  TablaHash *th = tablahash_crear(2, hash, punteros_comparar,1);

  tablahash_insertar(th, &x, &z);
  tablahash_insertar(th, &y, &w);
  //printf("tamaño de tabla: %d\n",th->capacidad);
  tablahash_insertar(th, &a, &b);
  //printf("tamaño de tabla: %d\n",th->capacidad);
  tablahash_insertar(th, &c, &d);

  printf("z : %d\n", *((int *)tablahash_buscar(th, &x)));
  printf("w : %d\n", *((int *)tablahash_buscar(th, &y)));
  printf("b : %d\n", *((int *)tablahash_buscar(th, &a)));
  printf("d : %d\n", *((int *)tablahash_buscar(th, &c)));
  
  //tablahash_eliminar(th, &y);

  tablahash_redimensionar(th);

  printf("z : %d\n", *((int *)tablahash_buscar(th, &x)));
  printf("w : %d\n", *((int *)tablahash_buscar(th, &y)));
  printf("b : %d\n", *((int *)tablahash_buscar(th, &a)));
  printf("d : %d\n", *((int *)tablahash_buscar(th, &c)));

  //tablahash_eliminar(th, &y);

  //printf("w : %d\n", *((int *)tablahash_buscar(th, &x)));
  //printf("b : %d\n", *((int *)tablahash_buscar(th, &a)));

  tablahash_destruir(th);

  return 0;
}
