#include "slist.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

SList* slist_crear() { //capacidad basica 4
  SList* lista = malloc(sizeof(SList));
  assert(lista);

  lista->arr = malloc(4 * sizeof(SNodo));
  assert(lista->arr);

  lista->capacidad =(size_t) 4;
  lista->disponible = 0;
  lista->primero = lista->capacidad;

  size_t i = 0;
  for (; i < 4; ++i)
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
  //assert(lista->disponible < lista->capacidad);

  if (lista->disponible==lista->capacidad){
	  printf("Esta realojando eaeae \n");
	  size_t i = lista->primero;
      size_t j= lista->capacidad;
      for(;lista->arr[i].sig!=lista->capacidad;i=lista->arr[i].sig);


	  lista->capacidad=lista->capacidad*2;
      lista->arr[i].sig=lista->capacidad;//apunta al nuevo lista->capacidad
	  lista->arr = realloc(lista->arr,(int)lista->capacidad*sizeof(SNodo));
	  for (; j != lista->capacidad; ++j){
		//printf("Lugar %d tiene al siguiente %d\n",(int)j, (int)j+1);
		lista->arr[j].sig = j + 1;
	  }
  }

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
  //assert(lista->disponible < lista->capacidad);

  size_t nuevoNodo = lista->disponible;

  if (slist_vacia(lista)){
        lista->primero = nuevoNodo;// Si la lista está vacía actualizamos el índice del primer elemento.
  }
  else {
        if (slist_llena(lista)){ //falta revisarlo
          printf("Esta realojando eaeae \n");
          size_t i = lista->primero;
          size_t j= lista->capacidad;
          for(;lista->arr[i].sig!=lista->capacidad;i=lista->arr[i].sig);//i me va a quedar en el ultimo de la lista

          lista->capacidad=lista->capacidad*2;
          lista->arr[i].sig=lista->capacidad;//apunta al nuevo lista->capacidad
          lista->arr = realloc(lista->arr,(int)lista->capacidad*sizeof(SNodo));
          for (; j != lista->capacidad; ++j){
            //printf("Lugar %d tiene al siguiente %d\n",(int)j, (int)j+1);
            lista->arr[j].sig = j + 1;
          }
      }
      SNodo* arr = lista->arr;
      lista->disponible = arr[nuevoNodo].sig;
      arr[nuevoNodo].sig = lista->capacidad;
      arr[nuevoNodo].dato = dato;

      // Si no está vacía, buscamos el último nodo.
      size_t i= lista->primero;
      for (; lista->arr[i].sig != lista->capacidad; i = lista->arr[i].sig); //buscamos el i denuevo y no usamos el del otro if por que ese i solo lo tenemos cuando realojamos
      lista->arr[i].sig = nuevoNodo;//el i que tenia antes
  }
  /*else {
    // Si no está vacía, buscamos el último nodo.
    size_t i= lista->primero;
    for (; lista->arr[i].sig != lista->capacidad; i = lista->arr[i].sig);
    lista->arr[i].sig = nuevoNodo;
  }*/
}

void slist_recorrer(SList* lista, FuncionVisitante visit) {
  assert(lista);
  size_t i = lista->primero;
  for (; i != lista->capacidad; i = lista->arr[i].sig){
    visit(lista->arr[i].dato);
    /*printf("i==%d, = disponible==%d?\n",(int)i,(int)lista->disponible);
    char t;
    scanf("%c",&t);*/
  }
}
