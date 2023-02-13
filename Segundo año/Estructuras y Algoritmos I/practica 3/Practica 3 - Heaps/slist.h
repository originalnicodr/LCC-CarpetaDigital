#ifndef __SLIST_H__
#define __SLIST_H__
#define MAX_COLA 5
#define MAX_HEAP 7

#include <stddef.h>

typedef struct _PDato{
  int dato;
  int prioridad;
}PDato;

#define MAX_COLAP 7

typedef struct _PColarreglo{
	PDato datos[MAX_COLAP];
	int primero, ultimo;
}*PColarreglo;

typedef struct _Cola{
	int datos[MAX_COLA];
	int primero, ultimo;
} *Cola;

typedef struct _SNodo {
  int dato;
  struct _SNodo *sig;
} SNodo;

typedef struct _Colas{
	SNodo* primero;
	SNodo* ultimo;
} *Colas;

typedef struct _BHeap {//minheap
    int datos[MAX_HEAP];
    int nelems;
} *BHeap;

typedef struct _BHeapd {//minheap
    PDato* datos;
    int nelems;
    int memoria;
} *BHeapd;

typedef struct _BHeapdin {//minheap
    int* datos;
    int nelems;
    int memoria;
} *BHeapdin;

typedef SNodo *SList;

typedef void (*FuncionVisitante) (int dato);

typedef int (*FuncionIgualdadVisitante) (int dato1, int dato2);

typedef int (*FuncionCompararVisitante) (int dato1, int dato2);

SList slist_reverso(SList lista);

SList slist_intercalar(SList lista1, SList lista2);

SList slist_ordenar(SList lista, FuncionCompararVisitante comparador);

SList slist_intersecar_custom(SList lista1, SList lista2, FuncionIgualdadVisitante visit);

SList slist_intersecar(SList lista1,SList lista2);

int slist_indice(SList lista, int dato);

int slist_contiene(SList lista, int dato);

SList slist_insertar(SList lista,int pos, int dato);

SList slist_concatenar(SList lista1, SList lista2);

int slist_longitud(SList lista);

SList slist_eliminar(SList lista, int pos);

/**
 * Devuelve una lista vacia.
 */
SList slist_crear();

/**
 * Destruccion de la lista.
 */
void slist_destruir(SList lista);

/**
 * Determina si la lista es vacia.
 */
int slist_vacia(SList lista);

/**
 * Agrega un elemento al final de la lista.
 */
SList slist_agregar_final(SList lista, int dato);

/**
 * Agrega un elemento al inicio de la lista.
 */
SList slist_agregar_inicio(SList lista, int dato);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void slist_recorrer(SList lista, FuncionVisitante visit);

#endif /* __SLIST_H__ */
