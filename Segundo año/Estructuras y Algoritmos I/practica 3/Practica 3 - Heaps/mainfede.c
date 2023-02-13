#include <stdio.h>
#include <stdlib.h>
#include "cola_prioridad_arreglo.h"
#define MAX_COLA 5

/* Crear cola.	*/
PCola pcola_crear(){
	PCola nuevaCola = malloc(sizeof(PCola));
	nuevaCola->datos = malloc(sizeof(Nodo) * MAX_COLA);
	nuevaCola->primero = -1;
	nuevaCola->ultimo = -1;
	return nuevaCola;
	}

/* Crea un nodo. */
Nodo nodo_crear(int dato, int prioridad){
	Nodo nuevoNodo;
	nuevoNodo.dato = dato;
	nuevoNodo.prioridad = prioridad;
	return nuevoNodo;
	}


/* Inserta un dato con cierta prioridad. */	
PCola pcola_insertar(PCola c, int dato, int prioridad){
	if(cola_cantElementos(c->primero, c->ultimo) == MAX_COLA){						// Caso cola llena.
		printf("La cola esta llena. \n");
		return c;
	}
	Nodo nuevoNodo = nodo_crear(dato,prioridad);
	
	if(cola_prioridad_es_vacia(c)){																				// Caso cola vacia.
		c->datos[0] = nuevoNodo;
		c->ultimo = 0;
		c->primero = 0;
		return c;
	}
	else{																																	// Caso != lleno y != vacia. Insercion.
		int indice_insertar = cola_indice_insertar(c, prioridad);			
		if(indice_insertar == c->ultimo){
			c->datos[cola_siguiente_id(c->ultimo)] = nuevoNodo;
			c->ultimo = cola_siguiente_id(c->ultimo);
			return c;
		}
		else{
			cola_hacer_espacio(c, indice_insertar);
			c->datos[indice_insertar] = nuevoNodo;
			return c;
		}
	}
}

/* Devuelve el minimo de la cola de prioridad.	*/
int cola_prioridad_obtener_minimo(PCola c){
	return c->datos[c->primero].dato;
}


/* Elimina el minimo de la cola de prioridad. */
void cola_prioridad_eliminar_minimo(PCola c){
	if(cola_cantElementos(c->primero, c->ultimo) == 0){
		printf("La cola de prioridad esta vacia.\n");
		return;
	}
	if(cola_cantElementos(c->primero, c->ultimo) == 1){
		c->primero = -1;
		c->ultimo = -1;
		return;
	}
	else{
		c->primero = cola_siguiente_id(c->primero);
		return;
	}
}

/* Devuelve si la cola es vacia o no. */
int cola_prioridad_es_vacia(PCola c){
	return c->primero == -1;
}

/* 	Devuelve la cantidad de elementos en un intervalo. */
int cola_cantElementos(int primero, int ultimo){
	if((primero == -1) || (ultimo == -1)){
		return 0;
	}
	if(primero <= ultimo){
		return ultimo - primero + 1;
	}
	else{
		return ((MAX_COLA - primero) + (ultimo + 1));
	}
}


/*	Devuelve el siguiente indice del arreglo.	*/
int cola_siguiente_id (int id){
	return (id+1)%MAX_COLA;
}

/*  Devuelve el indice donde habra que insertar el elemento.	*/
int cola_indice_insertar (PCola c, int prioridad){
	if (prioridad < c->datos[c->primero].prioridad){
		return c->primero;
	}
	if (prioridad > c->datos[c->ultimo].prioridad){
		return c->ultimo;
	}
	
	int i, j;
	for(i=c->primero, j=0;j<cola_cantElementos(c->primero, c->ultimo);j++){
		i=cola_siguiente_id(i);
		if( prioridad < c->datos[i].prioridad){
			return i;
		}		
	}
}

/* Imprimo todo. Indices del arreglo, sus datos y prioridades. */

void cola_imprimir(PCola cola){
	int i, j, cantElementos;
	if(!(cola_prioridad_es_vacia(cola))){
		cantElementos = cola_cantElementos(cola->primero, cola->ultimo);
		
		printf("| ");
		for(i=cola->primero, j=0; j<cantElementos;i = cola_siguiente_id(i), j++){
			printf("%d ", i);
		}
		printf(" | Indices arreglo.\n");
				
		printf("| ");
		for(i=cola->primero, j=0; j<cantElementos;i = cola_siguiente_id(i), j++){
			printf("%d ", cola->datos[i].dato);
		}
		printf(" | Datos del arreglo.\n");
		
		printf("| ");
		for(i=cola->primero, j=0; j<cantElementos;i = cola_siguiente_id(i), j++){
			printf("%d ", cola->datos[i].prioridad);
		}
		printf(" | Prioridades del arreglo.\n");
	}
}

int cola_anterior_id (int id){
	if(id==0) return MAX_COLAP-1;
	return id-1;
}

void cola_hacer_espacio (PCola c, int indice){
	int j, i, cantElementos = cola_cantElementos(c->primero,c->ultimo);
	if(indice == c->primero){
		for(i=c->ultimo, j=0; j<cantElementos; i=cola_anterior_id(i), j++){
			c->datos[cola_siguiente_id(i)] = c->datos[i];

		}
		c->ultimo = cola_siguiente_id(c->ultimo);
		return;
	}
	
	else{
		return;
	}
}