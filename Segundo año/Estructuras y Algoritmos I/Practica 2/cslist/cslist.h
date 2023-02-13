#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h>

typedef void (*FuncionVisitante) (int dato);
typedef int (*FuncionComparadora) (int dato1, int dato2);

typedef struct _SNodo {
  int dato;
  struct _SNodo *sig;
} SNodo;

typedef SNodo *CSList;

/**
 * Devuelve una lista vacía.
 */
CSList cslist_crear();

/**
 * Destruccion de la lista.
 */
void cslist_destruir(CSList lista);

/**
 * Determina si la lista es vacía.
 */
int cslist_vacia(CSList lista);

/**
 * Agrega un elemento al final de la lista.
 */
CSList cslist_agregar_final(CSList lista, int dato);

/**
 * Agrega un elemento al inicio de la lista.
 */
CSList cslist_agregar_inicio(CSList lista, int dato);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void cslist_recorrer(CSList lista, FuncionVisitante visit);

#endif /* __SLIST_H__ */
