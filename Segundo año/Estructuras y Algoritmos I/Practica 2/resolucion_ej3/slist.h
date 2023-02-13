#ifndef __SLIST_H__
#define __SLIST_H__

#include "stddef.h"

typedef struct _SNodo {
  int dato; // Dato contenido en el nodo.
  size_t sig; // Indice del siguiente elemento en la lista.
} SNodo;

typedef struct {
  SNodo* arr; // Arreglo de elementos.
  size_t capacidad; // Máxima capacidad del arreglo.
  size_t disponible; // Indice del nodo disponible.
    // (disponible == capacidad, cuando la lista está llena).
  size_t primero; // Indice del primer nodo.
    // (primero == capacidad, cuando la lista es vacía).
} SList;

typedef void (*FuncionVisitante) (int dato);

/**
 * Crea una lista vacía.
 */
SList* slist_crear(size_t capacidad);

/**
 * Destruccion de la lista.
 */
void slist_destruir(SList* lista);

/**
 * Determina si la lista está vacía.
 */
int slist_vacia(SList* lista);

/**
 * Determina si la lista está llena.
 */
int slist_llena(SList* lista);

/**
 * Agrega un elemento al inicio de la lista.
 */
void slist_agregar_inicio(SList* lista, int dato);

/**
 * Elimina un elemento al inicio de la lista.
 */
void slist_eliminar_inicio(SList* lista);

/**
 * Agrega un elemento al final de la lista.
 */
void slist_agregar_final(SList* lista, int dato);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void slist_recorrer(SList* lista, FuncionVisitante visit);

#endif /* __SLIST_H__ */
