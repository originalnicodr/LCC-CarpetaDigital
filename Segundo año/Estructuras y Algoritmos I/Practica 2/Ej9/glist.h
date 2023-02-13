#ifndef __GLIST_H__
#define __GLIST_H__

#include <stddef.h>

typedef void (*FuncionVisitante) (void*);
typedef int (*FuncionComparadora) (void* dato1, void* dato2);

typedef struct _GNodo {
  void* dato;
  struct _GNodo *sig;
} GNodo;

typedef GNodo* GList;

typedef struct _AGNodo { //va a ser el elemento voy a hacer una lista de punteros a AGList
    GList lista; //tengo que llamar a la lista dato para poder agregar el elemento ..?
    char* nombre;
    
} AGNodo;

typedef AGNodo* AGList;

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
void glist_recorrer(GList lista, FuncionVisitante visit);

void glist_mostrar(GList lista);

#endif /* __GLIST_H__ */
