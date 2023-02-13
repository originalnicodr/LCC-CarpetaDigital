#include <stdio.h>
#include <stdlib.h>
#include "dlist.h"

static void imprimir_entero(int dato) {
  printf("%d ", dato);
}

int main(int argc, char *argv[]) {

  DList lista = dlist_crear();

  lista = dlist_agregar_inicio(lista, 3);
  lista = dlist_agregar_inicio(lista, 2);
  lista = dlist_agregar_inicio(lista, 1);
  lista = dlist_agregar_final(lista, 4);

  dlist_recorrer(lista, imprimir_entero, DLIST_RECORRIDO_HACIA_ADELANTE);
  puts("");
  dlist_recorrer(lista, imprimir_entero, DLIST_RECORRIDO_HACIA_ATRAS);
  puts("");

  dlist_destruir(lista);

  return 0;
}

//Ej 6
//a) Si, puedo recorrer la lista en ambas direcciones, pero para recorrerla del final hacia el principio necesitamos el un puntero apuntando al nodo final

typedef struct _Nodo {//no pueden ser circulares
  int dato;
  uintptr_t xor;
} Nodo;

typedef Nodo* XList;

/*Las ventaja serian la posibilidad de guardar dos punteros en un solo dato, ahorrando asi memoria.
Las desventajas serian que no se podria tener una lista circular por que no podriamos diferenciar los dos punteros almacenados en el xor. Y si quisiera recorrer la lista desde el final hacia el
principio deberia tener el puntero del ultimo nodo, ya sea por que se lo dio de antemano o recorriendo la lista primero del inicio al final

