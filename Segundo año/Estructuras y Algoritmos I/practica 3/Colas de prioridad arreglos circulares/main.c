#include "cola_prioridad_arreglo.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	PCola c = pcola_crear();
	Nodo n0 = nodo_crear(4,10);
	Nodo n1 = nodo_crear(1,4);
	Nodo n2 = nodo_crear(2,6);
	Nodo n3 = nodo_crear(3,8);
	c->datos[0] = n0;
	c->datos[2] = n1;
	c->datos[3] = n2;
	c->datos[4] = n3;
	c->primero = 2;
	c->ultimo = 0;
	
	cola_imprimir(c);
	
	printf("Indice a insertar un elemento de prioridad %d es : %d \n",20,cola_indice_insertar(c, 20));
	
	pcola_insertar(c, -2,20);
	cola_imprimir(c);
	
	return 0;
}

