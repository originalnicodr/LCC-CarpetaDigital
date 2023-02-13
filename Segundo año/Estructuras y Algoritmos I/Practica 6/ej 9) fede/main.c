#include "basicas.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CANT_CMD 3

comando LISTA_COMANDOS[] = {
	{"imprimir",0,imprimirMenu},
	{"buscar",1,buscar_contacto},
	{"eliminar",1,eliminar_contacto}
};

SList agregarPalabra(SList lista, char *palabra){
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->str = malloc(sizeof(char) * strlen(palabra));
  strcpy(nuevoNodo->str, palabra);
  nuevoNodo->sig = NULL;

  if (lista == NULL){
    return nuevoNodo;
	}
  SList nodo = lista;
  for (;nodo->sig != NULL;nodo = nodo->sig);

  nodo->sig = nuevoNodo;
  return lista;
}

int slist_longitud(SList lista){
	int contador = 0;
	if(lista == NULL){
		return contador;
	}
	for(;lista != NULL;lista = lista->sig){
		contador++;
	}
	return contador;
}


SList parser_comando (char* comando){
	printf("Comando ingresado: %s\n",comando);
	
	SList lista_argumentos = NULL;
	
	char *palabra;
	
	int inicioP = 0, longComando = strlen(comando);

	for (int i = 0; i <= longComando; i++) {
		if ((comando[i] == 0) || (comando[i] == 32)) {
			if (inicioP == i) {
				inicioP == i + 1;
			}
			else {
				palabra = malloc(sizeof(char) * i - inicioP + 1);
				for (int j = inicioP; j < i; j++) {
					palabra[j - inicioP] = comando[j];

				}
				palabra[i - inicioP + 1] = '\0';
				lista_argumentos = agregarPalabra(lista_argumentos, palabra);
				free(palabra);
				inicioP = i + 1;
			}
		}
	}
	return lista_argumentos;
}

void interprete_cmd(TablaHash th, char *cmd){
	SList lista_comando = parser_comando(cmd);
	for(int i=0; i<CANT_CMD; i++){
		if(strcmp(LISTA_COMANDOS[i].cmd, lista_comando->str) == 0){
			if(LISTA_COMANDOS[i].nargs == (slist_longitud(lista_comando) - 1)){
				SList argumentos = lista_comando->sig;
				LISTA_COMANDOS[i].handler(th, argumentos);
				return;
			}
		}
	}
	printf("Comando incorrecto. \n");
}

int main(){
	TablaHash th;
	imprimirMenu();
	char *cmdTemp = malloc(sizeof(char) * 100);
	printf("Ingrese el comando: ");
	gets(cmdTemp);
	interprete_cmd(th, cmdTemp);
}
