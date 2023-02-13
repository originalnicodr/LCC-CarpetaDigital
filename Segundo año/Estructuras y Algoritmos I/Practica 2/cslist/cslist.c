#include "cslist.h"
#include <stdlib.h>
#include <stdio.h> //para imprimir y hacer debuging

CSList cslist_crear() {
  return NULL;
}

void cslist_destruir(CSList lista) {
    if(lista==NULL) return;
  SNodo *nodo;
  while (lista->sig != lista) {

    for (nodo = lista; nodo->sig != lista; nodo = nodo->sig); //voy a terminar con el nodo parado en el anterior al primero, es decir el ultimo

    nodo->sig = lista->sig;//linkeo el ultimo con el segundo, salteo el primero
    free(lista);
    lista=nodo->sig;
  }
  free(lista); //el free del ultimo elemento
}

int cslist_vacia(CSList lista) {
  return lista == NULL;
}

CSList cslist_agregar_final(CSList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;


  if (lista == NULL){
    nuevoNodo->sig=nuevoNodo;
    return nuevoNodo;
  }

  SNodo *nodo;
  for (nodo = lista;nodo->sig != lista;nodo = nodo->sig); //puedo arrancar con nodo->sig por que filtre antes que lista sea diferente a NULL
  /* ahora 'nodo' apunta al ultimo elemento en la lista */
  printf("El ultimo elemento detectado es el %d\n",nodo->dato);

  nodo->sig = nuevoNodo;
  nuevoNodo->sig = lista;
  return lista;
}

CSList cslist_agregar_inicio(CSList lista, int dato) {//me queda casi igual a agregar al final
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = lista;

  if (lista == NULL){
    nuevoNodo->sig=nuevoNodo;
    return nuevoNodo;
  }

  CSList nodo = lista;
  for (;nodo->sig != lista;nodo = nodo->sig);//puedo arrancar con nodo->sig por que filtre antes que lista sea diferente a NULL
  nodo->sig=nuevoNodo;
  //mepa que aca va un nuevoNodo->sig=lista;

  return nuevoNodo; //como devuelve CSList no tengo que hacer lista=nuevoNodo, eso lo hago en el main
}

void cslist_recorrer(CSList lista, FuncionVisitante visit) {
    if (lista == NULL) return;
    SNodo *nodo;
    for (nodo=lista; nodo->sig != lista; nodo = nodo->sig)
        visit(nodo->dato);
    visit(nodo->dato);
    return;
}

