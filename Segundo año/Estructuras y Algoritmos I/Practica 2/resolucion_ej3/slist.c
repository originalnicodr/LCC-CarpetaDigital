#include "slist.h"
#include <assert.h>
#include <stdlib.h>

SList* slist_crear(size_t capacidad) {
  SList* lista = malloc(sizeof(SList));
  assert(lista);

  lista->arr = malloc(capacidad * sizeof(SNodo));
  assert(lista->arr);

  lista->capacidad = capacidad;
  lista->disponible = 0;
  lista->primero = capacidad;

  for (size_t i = 0; i < capacidad; ++i)
    lista->arr[i].sig = i + 1;

  return lista;
}

void slist_destruir(SList* lista) {
  assert(lista);
  free(lista->arr);
  free(lista);
}

int slist_vacia(SList* lista) {
  assert(lista);
  return lista->primero == lista->capacidad;
}

int slist_llena(SList* lista) {
  assert(lista);
  return lista->disponible == lista->capacidad;
}

void slist_agregar_inicio(SList* lista, int dato) {
  assert(lista);
  assert(lista->disponible < lista->capacidad);

  SNodo* arr = lista->arr; //trabajo sobre un arreglo creado (por que no trabajamos sobre el que ya esta creado?)
  size_t nuevoNodo = lista->disponible;

  lista->disponible = arr[nuevoNodo].sig;//lo mismo que poner el siguiente del disponible
  arr[nuevoNodo].sig = lista->primero;
  arr[nuevoNodo].dato = dato;
  lista->primero = nuevoNodo;
}

void slist_eliminar_inicio(SList* lista) {
  assert(lista);

  if (slist_vacia(lista))
    return;

  SNodo* arr = lista->arr;
  size_t tmp = lista->primero;

  lista->primero = arr[tmp].sig;
  arr[tmp].sig = lista->disponible;
  lista->disponible = tmp;
}

void slist_agregar_final(SList* lista, int dato) {
  assert(lista);
  assert(lista->disponible < lista->capacidad);

  SNodo* arr = lista->arr;
  size_t nuevoNodo = lista->disponible;

  lista->disponible = arr[nuevoNodo].sig;
  arr[nuevoNodo].sig = lista->capacidad;
  arr[nuevoNodo].dato = dato;

  if (lista->primero == lista->capacidad)
    // Si la lista está vacía actualizamos el índice del primer elemento.
    lista->primero = nuevoNodo;
  else {
    // Si no está vacía, buscamos el último nodo.
    size_t i;
    for (i = lista->primero; lista->arr[i].sig != lista->capacidad;
         i = lista->arr[i].sig)
      ;
    lista->arr[i].sig = nuevoNodo;
  }
}

void slist_recorrer(SList* lista, FuncionVisitante visit) {
  assert(lista);

  for (size_t i = lista->primero; i != lista->capacidad; i = lista->arr[i].sig)
    visit(lista->arr[i].dato);
}
