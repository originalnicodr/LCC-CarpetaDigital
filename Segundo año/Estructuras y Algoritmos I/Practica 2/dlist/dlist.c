#include "dlist.h"
#include <stdlib.h>

DList dlist_crear() {
  return NULL;
}

void dlist_destruir(DList lista) {
  DNodo *nodoAEliminar;
  while (lista->sig != lista) {
    nodoAEliminar = lista;
    lista = lista->sig;
    lista->ant=lista->ant->ant;

    lista->ant->sig=lista; //enlazo el ultimo con el primero
    free(nodoAEliminar);
  }
  free(lista);
}

int dlist_vacia(DList lista) {
  return lista == NULL;
}

DList dlist_agregar_final(DList lista, int dato) {
  DNodo *nuevoNodo = malloc(sizeof(DNodo));
  nuevoNodo->dato = dato;
  if (lista == NULL){
    nuevoNodo->sig=nuevoNodo;
    nuevoNodo->ant=nuevoNodo;
    return nuevoNodo;
  }

  nuevoNodo->sig = lista;
  nuevoNodo->ant = lista->ant;

  lista->ant->sig=nuevoNodo;
  lista->ant=nuevoNodo;

  return lista;
}

DList dlist_agregar_inicio(DList lista, int dato) {
  DNodo *nuevoNodo = malloc(sizeof(DNodo));
  nuevoNodo->dato = dato;

  if (lista == NULL){
    nuevoNodo->sig=nuevoNodo;
    nuevoNodo->ant=nuevoNodo;
    return nuevoNodo;
  }

  nuevoNodo->sig = lista;
  nuevoNodo->ant = lista->ant;
  lista->ant->sig=nuevoNodo;
  lista->ant=nuevoNodo;
  return nuevoNodo;
}

void dlist_recorrer(DList lista, FuncionVisitante visit, DListOrdenDeRecorrido sentido) {
	if (lista == NULL) return;
	DNodo *nodo;
	if(sentido == DLIST_RECORRIDO_HACIA_ADELANTE){
	  for (nodo = lista; nodo->sig != lista; nodo = nodo->sig)
		visit(nodo->dato);
	  visit(nodo->dato);
  }
  else if(sentido == DLIST_RECORRIDO_HACIA_ATRAS){
	  for (nodo = lista->ant; nodo->ant != lista->ant; nodo = nodo->ant)
		visit(nodo->dato);
	  visit(nodo->dato);
	}
  
}

