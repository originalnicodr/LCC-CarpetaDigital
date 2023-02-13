#include "glist.h"
#include <stddef.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>

GList glist_crear() {
  return NULL;
}

void glist_destruir(GList lista) {
  GNodo *nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->sig;
    free(nodoAEliminar);
  }
}

int glist_vacia(GList lista) {
  return lista == NULL;
}

GList glist_agregar_final(GList lista, void* dato) {
  GNodo *nuevoNodo = malloc(sizeof(GNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;

  if (lista == NULL)
    return nuevoNodo;

  GList nodo = lista;
  for (;nodo->sig != NULL;nodo = nodo->sig);
  /* ahora 'nodo' apunta al ultimo elemento en la lista */

  nodo->sig = nuevoNodo;
  return lista;
}

GList glist_agregar_inicio(GList lista, void* dato) {
  GNodo *nuevoNodo = malloc(sizeof(GNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = lista;
  return nuevoNodo;
}

void glist_recorrer(GList lista, FuncionVisitantee visit) { //funcion visitante recibe int
  for (GNodo *nodo = lista; nodo != NULL; nodo = nodo->sig)
    visit(nodo->dato);
}

void glist_mostrar(GList lista){ //para mostrar ints especificamente
    for(GNodo *recorrer=lista;recorrer!=NULL;recorrer=recorrer->sig){
        printf("%d ",*((int*)recorrer->dato));
    }
}

