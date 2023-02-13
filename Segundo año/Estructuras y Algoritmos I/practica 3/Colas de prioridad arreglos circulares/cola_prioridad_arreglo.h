#ifndef _COLAP_H
#define _COLAP_H

#include <stddef.h>
#define MAX_COLA 5

typedef struct _Nodo{
	int dato;
	int prioridad;
	} Nodo;


typedef struct _PCola {
	Nodo *datos;
	int primero, ultimo;
	} *PCola;

int cola_cantElementos(int primero, int ultimo);

PCola pcola_crear();

PCola pcola_insertar(PCola c, int dato, int prioridad);

/* : obtiene el elemento proritario. */
int cola_prioridad_obtener_minimo(PCola);

/* Elimina al elemento de minima prioridad. */
void cola_prioridad_eliminar_minimo(PCola);

int cola_prioridad_es_vacia(PCola);

int cola_siguiente_id (int id);

Nodo nodo_crear(int dato, int prioridad);

int cola_indice_insertar (PCola c, int prioridad);

void cola_hacer_espacio(PCola c, int indice);

void cola_imprimir(PCola cola);

#endif /* _COLAP_H */
