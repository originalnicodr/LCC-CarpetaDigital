#ifndef __BTREE_H__
#define __BTREE_H__
typedef void (*FuncionVisitante) (int dato);

typedef void (*FuncionVisitanteExtra) (int dato, void *extra);

typedef enum {
  BTREE_RECORRIDO_IN,
  BTREE_RECORRIDO_PRE,
  BTREE_RECORRIDO_POST
} BTreeOrdenDeRecorrido;

typedef struct _Nacc {//Estructura auxiliar para el acceder (idea del profe que me funcionó), 
	int pos;//posición de nodo
	int dato;//dato del nodo (arbol->dato)
} Nacc;

typedef Nacc *NaccP; 

typedef struct _BTNodo {
  int dato;
  struct _BTNodo *left;
  struct _BTNodo *right;
} BTNodo;

typedef BTNodo *BTree;
typedef BTNodo *BSTree;

typedef struct _CBTree{
	int *dato;
	int nelems;
} CBTree;

typedef struct _SNodo {
  BTree dato;
  struct _SNodo *sig;
} SNodo;

typedef struct _Colas{
	SNodo* primero;
	SNodo* ultimo;
} *Colas;



/**
 * Devuelve un arbol vacío.
 */
BTree btree_crear();

/**
 * Destruccion del árbol.
 */
void btree_destruir(BTree nodo);

/**
 * Crea un nuevo arbol, con el dato dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_unir(int dato, BTree left, BTree right);

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */
void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitante visit);

void btree_recorrer_extra(BTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitanteExtra visit, void* extra);

#endif /* __BTREE_H__ */
