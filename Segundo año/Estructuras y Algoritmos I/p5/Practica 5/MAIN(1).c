#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

static void imprimir_entero(int data) {
  printf("%d ", data);
}

int btree_suma_elems(BTree raiz){
	if(!raiz) return 0;
	int cont=raiz->dato;
	if(!raiz->left&&!raiz->right) return raiz->dato;
	if(raiz->left!=NULL) cont+=btree_suma_elems(raiz->left);
	if(raiz->right!=NULL) cont+=btree_suma_elems(raiz->right);
	return cont;
}

int btree_nelems(BTree raiz){
	if(!raiz) return 0;
	int cont=1;
	if(!raiz->left&&!raiz->right) return 1;
	if(raiz->left!=NULL) cont+=btree_nelems(raiz->left);
	if(raiz->right!=NULL) cont+= btree_nelems(raiz->right);
	return cont;
}

int btree_alturaux(BTree raiz, int alturamax){
	if(!raiz) return -1;//caso arbol vacio
	if(!raiz->left&&!raiz->right) return alturamax;
	if((raiz->left!=NULL)&&(raiz->right!=NULL)){
		if(btree_alturaux(raiz->left,alturamax++)>btree_alturaux(raiz->right,alturamax++)) return btree_alturaux(raiz->left,alturamax++);
		else return btree_alturaux(raiz->right,alturamax++);
	}
	if(raiz->left!=NULL) return btree_alturaux(raiz->left,alturamax++);
	else return btree_alturaux(raiz->right,alturamax++);
}

//Hacer el btree recorrer con pilas?

int btree_altura(BTree raiz){
	return btree_alturaux(raiz,0);
}

void imprimir_int(int dato){
  printf("%d ",dato);
}

void visit_suma (int dato, void *contador){
	*(int*)contador+=dato;
}

int btree_sumaextra_elems(BTree raiz){
	int contador=0;
	btree_recorrer_extra(raiz,BTREE_RECORRIDO_PRE,visit_suma, &contador);
	return contador;
}

void visit_contar (int dato, void *contador){
	*(int*)contador++;
}

int btree_nelemsextra(BTree raiz){//no esta contando
	int contador=0;
	btree_recorrer_extra(raiz,BTREE_RECORRIDO_PRE,visit_contar, &contador);
	return contador;
}

//Ver si se puede hacer btree_alturaux con recorrer

void mirror(BTree arbol){
  if(arbol != NULL){
        mirror(arbol->left);
        mirror(arbol->right);
		BTree temp=arbol->left;
		arbol->left=arbol->right;
		arbol->right=temp;
    }
}

 



int main() {
  BTree ll = btree_unir(1, btree_crear(), btree_crear());
  BTree l = btree_unir(2, ll, btree_crear());
  BTree r = btree_unir(3, btree_crear(), btree_crear());
  BTree raiz = btree_unir(4, l, r);
  
  /*BTree ll = btree_unir(1, btree_crear(), btree_crear());
  
  BTree test2= btree_unir(24, btree_crear(), btree_crear());
  BTree test= btree_unir(24, test2, btree_crear());
  
  BTree l = btree_unir(2, ll, test);
  BTree r = btree_unir(3, btree_crear(), btree_crear());
  BTree raiz = btree_unir(4, l, r);
  
  //printf("Test de suma de elementos= %d",btree_suma_elems(raiz));
  //printf("Test de cantidad de elementos= %d",btree_nelems(raiz));
  printf("Test de altura de arbol= %d",btree_altura(raiz));

  //btree_recorrer(raiz, BTREE_RECORRIDO_POST, imprimir_entero);
  puts("");
  btree_destruir(raiz);*/

  /*BTree ll = btree_unir(1, btree_crear(), btree_crear());
  BTree l = btree_unir(2, ll, btree_crear());
  BTree r = btree_unir(3, btree_crear(), btree_crear());
  BTree raiz = btree_unir(4, l, r);

  btree_recorrer(raiz,BTREE_RECORRIDO_PRE,imprimir_int);*/

  //printf("Suma de los elementos: %d",btree_sumaextra_elems(raiz));
  //puts("");
  //printf("Cantidad de elementos: %d",btree_nelemsextra(raiz));

  btree_recorrer(raiz,BTREE_RECORRIDO_PRE,imprimir_int);
  puts("");
  mirror(raiz);
  btree_recorrer(raiz,BTREE_RECORRIDO_PRE,imprimir_int);

  btree_destruir(raiz);

  return 0;
}
