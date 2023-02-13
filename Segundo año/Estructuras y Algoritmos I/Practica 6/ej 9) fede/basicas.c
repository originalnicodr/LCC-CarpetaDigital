#include "basicas.h"
#include <stdio.h>
#include <stdlib.h>

void imprimirMenu(){
	printf(" ____________________________\n");
	printf("|____________MENU____________|\n");
	printf("|                            |\n");
	printf("| 1) Agregar nuevo contacto. |\n");
	printf("| 2) Eliminar contacto.      |\n");
	printf("| 3) Editar contacto.        |\n");
	printf("| 4) Buscar.                 |\n");
	printf("| 5) Cargar archivo.         |\n");
	printf("| 6) grabar archivo.         |\n");
	printf("|                            |\n");
	printf("| 0) Salir                   |\n");
	printf("|____________________________|\n");
	printf("\n\n");
} /** Imprime el menu. */ 

void imprimirBusqueda(Contacto *contacto);

void buscar_contacto(TablaHash th, SList comando){

	printf("Buscando contacto...\n");
}

void insertar_contacto(Contacto contacto, TablaHash th);

void eliminar_contacto(TablaHash th, SList comando){
	printf("Eliminando contacto...\n");
}

void editar_contacto();

void cargar_archivo();

void grabar_archivo();
