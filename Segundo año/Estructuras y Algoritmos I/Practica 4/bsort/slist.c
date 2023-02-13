#include "slist.h"
#include <stdlib.h>
#include <stdio.h>

SList slist_crear() {
  return NULL;
}

void slist_destruir(SList lista) {
  SNodo *nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->sig;
    free(nodoAEliminar);
  }
}

int slist_vacia(SList lista) {
  return lista == NULL;
}

SList slist_agregar_final(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;

  if (lista == NULL)
    return nuevoNodo;

  SList nodo = lista;
  for (;nodo->sig != NULL;nodo = nodo->sig);
  /* ahora 'nodo' apunta al ultimo elemento en la lista */

  nodo->sig = nuevoNodo;
  return lista;
}

SList slist_agregar_inicio(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = lista;
  return nuevoNodo;
}

void slist_recorrer(SList lista, FuncionVisitante visit) {
  SNodo *nodo;
  for (nodo = lista; nodo != NULL; nodo = nodo->sig)
    visit(nodo->dato);
}

SList slist_insertar (SList lista, int posicion, int dato){ //arrancamos desde 0
	if(lista==NULL||posicion==0) return slist_agregar_inicio(lista,dato);

	SNodo *nuevoNodo = malloc(sizeof(SNodo));
	nuevoNodo->dato = dato;

	SList inicio=lista;

    int i;
    for(i=0;i<posicion-1;i++){ // te paras en el anterior que queres agregar
        //printf("i=%d - dato= %d\n",i,lista->dato);
        lista=lista->sig;
        //printf("SALE:  i=%d - dato= %d\n",i,lista->dato);
    }
    nuevoNodo->sig=lista->sig;
    lista->sig=nuevoNodo;
    return inicio;
}

SList slist_eliminar (SList lista, int posicion){
    if(posicion==0){
        SList temp;
        temp=lista->sig;
        free(lista);
        return temp;
    }
    SList inicio=lista;

    int i=0;
    for(;i<posicion-1;i++){
        lista=lista->sig;
    }
    printf("Estoy en la posición %d\n",i);
    SList temp;
    temp=lista->sig->sig;
    free(lista->sig);
    lista->sig=temp;
    return inicio;
    //lista=lista->sig->sig;

}

