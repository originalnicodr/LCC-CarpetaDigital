#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

static void imprimir_entero(int data) {
  printf("%d ", data);
}

int suma_elems(BTree raiz){
	if(!raiz) return 0;
	
	int cont=raiz->dato;
	if(!raiz->left&&!raiz->right) return raiz->dato;
	if(raiz->left!=NULL) cont+=suma_elems(raiz->left);
	if(raiz->right!=NULL) cont+= suma_elems(raiz->right);
	return cont;
		
}

int main() {
  BTree ll = btree_unir(1, btree_crear(), btree_crear());
  BTree l = btree_unir(2, ll, btree_crear());
  BTree r = btree_unir(3, btree_crear(), btree_crear());
  BTree raiz = btree_unir(4, l, r);
  
  printf("Test de suma de elementos= %d",suma_elems(raiz));

  //btree_recorrer(raiz, BTREE_RECORRIDO_POST, imprimir_entero);
  puts("");
  btree_destruir(raiz);

  return 0;
}
