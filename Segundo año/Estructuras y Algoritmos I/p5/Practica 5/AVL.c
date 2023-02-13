#include <stdio.h>
#include <stdlib.h>
#include "btree.h"
#include <math.h>
#include <assert.h>
//Esto funciona de borrador porque se me complicaba pensar con tantas cosas escritas, las funciones las copie y probe en main.c
BSTree rotacion_simple(BSTree raiz, BSTree hijo){
	assert((hijo==raiz->left||hijo==raiz->right));
	if(hijo == raiz->left){
		raiz->left=hijo->right;
		hijo->right=raiz;
		return hijo;
	}
	else{
		raiz->right=hijo->left;
		hijo->left=raiz;
		return hijo;
	}
}

BSTree rotacion_doble(BSTree raiz, BSTree hijo){
	assert((hijo==raiz->left||hijo==raiz->right));
	if(hijo == raiz->left){
		hijo=rotacion_simple(hijo,hijo->right);
		padre=rotacion_simple(padre,hijo);
		return padre;
	}
	else{
		hijo=rotacion_simple(hijo, hijo->left);
		padre=rotacion_simple(padre, hijo);
		return padre;
	}
}


BSTree AVTree_insertar(BSTree raiz, int dato){
	raiz = bstree_insertar(raiz,dato);
	if(!bstree_es_balanceadoT(raiz)) raiz=bstree_balancear(raiz);
	return raiz;
}

BSTree bstree_balancear(BSTree arbol){
	if(bstree_es_balanceadoT(arbol))return arbol;
	if(!bstree_es_balanceado(arbol)){
		if(bstree_altura(arbol->left)<bstree_altura(arbol->right)){
			BSTree temp = arbol->right;
			if(bstree_altura(temp->left)<bstree_altura(temp->right)){
				arbol=rotacion_simple(arbol,arbol->right);
				arbol=bstree_balancear(arbol);
			}
			else{
				arbol=rotacion_doble(arbol,arbol->right);
				arbol=bstree_balancear(arbol);
			}
		}
		
		else{
			BSTree temp = arbol->left;
			if(bstree_altura(temp->right)<bstree_altura(temp->left)){
				arbol=rotacion_simple(arbol,arbol->left);
				arbol=bstree_balancear(arbol);
			}
			else{
				arbol=rotacion_doble(arbol,arbol->left);
				arbol=bstree_balancear(arbol);
			}
		}
	}
	arbol->left=bstree_balancear(arbol->left);
	arbol->right=bstree_balancear(arbol->right);
}

int main(int argc, char **argv)
{
	
	return 0;
}

