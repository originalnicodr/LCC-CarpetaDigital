//1)
//a) balanceado en altura y en cantidad
//b) Completo, lleno, balanceadon en altura y en cantidad
//c) Completo, balanceado?
//d) Balanceado en cantidad y en altura

#include "btree.h"
#include <stdlib.h>

BTree btree_crear() {
  return NULL;
}

void btree_destruir(BTree nodo) {
  if (nodo != NULL) {
    btree_destruir(nodo->left);
    btree_destruir(nodo->right);
    free(nodo);
  }
}

BTree btree_unir(int dato, BTree left, BTree right) {
  BTree nuevoNodo = malloc(sizeof(BTNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->left = left;
  nuevoNodo->right = right;
  return nuevoNodo;
}

void btree_recorrer (BTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitante visit){
  if(arbol != NULL){
    switch (orden){
      case BTREE_RECORRIDO_IN:
        btree_recorrer(arbol->left, orden, visit);
        visit(arbol->dato);
        btree_recorrer(arbol->right, orden, visit);
        break;
      case BTREE_RECORRIDO_POST:
        btree_recorrer(arbol->left, orden, visit);
        btree_recorrer(arbol->right, orden, visit);
        visit(arbol->dato);
        break;
      case BTREE_RECORRIDO_PRE:
        visit(arbol->dato);
        btree_recorrer(arbol->left, orden, visit);
        btree_recorrer(arbol->right, orden, visit);
        break;
    }
  }
}

void btree_recorrer_extra(BTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitanteExtra visit, void* extra){//puntero a void
  if(arbol != NULL){
    switch (orden){
      case BTREE_RECORRIDO_IN:
        btree_recorrer_extra(arbol->left, orden, visit, extra);
        visit(arbol->dato, extra);
        btree_recorrer_extra(arbol->right, orden, visit, extra);
        break;
      case BTREE_RECORRIDO_POST:
        btree_recorrer_extra(arbol->left, orden, visit, extra);
        btree_recorrer_extra(arbol->right, orden, visit, extra);
        visit(arbol->dato, extra);
        break;
      case BTREE_RECORRIDO_PRE:
        visit(arbol->dato, extra);
        btree_recorrer_extra(arbol->left, orden, visit, extra);
        btree_recorrer_extra(arbol->right, orden, visit, extra);
        break;
    }
  }
}