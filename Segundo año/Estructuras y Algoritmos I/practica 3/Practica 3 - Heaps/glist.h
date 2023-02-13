#ifndef __GLIST_H__
#define __GLIST_H__

#include <stddef.h>

typedef void (*FuncionVisitantee) (void*);
typedef int (*FuncionComparadora) (void* dato1, void* dato2);

typedef struct _GNodo {
  void* dato;
  struct _GNodo *sig;
} GNodo;

typedef GNodo* GList;

/**
 * Devuelve una lista vacía.
 */
GList glist_crear();

/**
 * Destruccion de la lista.
 */
void glist_destruir(GList lista);

/**
 * Determina si la lista es vacía.
 */
int glist_vacia(GList lista);

/**
 * Agrega un elemento al final de la lista.
 */
GList glist_agregar_final(GList lista, void* dato); //habria que eliminar esta?

/**
 * Agrega un elemento al inicio de la lista.
 */
GList glist_agregar_inicio(GList lista, void* dato);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void glist_recorrer(GList lista, FuncionVisitantee visit);

void glist_mostrar(GList lista);





static void imprimir_enterop(int *dato);

int glist_longitud (GList lista);

void glist_concatenar(GList lista1, GList lista2);

GList glist_insertar (GList lista, int posicion, void* dato);

int glist_contiene(GList lista, void* dato, FuncionComparadora f);

int IgualPInt (void* d1, void* d2);

int glist_indice(GList lista, void* dato, FuncionComparadora f);

GList glist_ordenar (GList lista, FuncionComparadora comparar);

int mayorint (void* dato1, void* dato2);

GList glist_intercalar(GList lista1, GList lista2);



#endif /* __GLIST_H__ */