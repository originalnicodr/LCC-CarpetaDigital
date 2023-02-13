#include "slist.h"
#include <stdlib.h>
#include <stdio.h>

SList slist_crear() {
  return NULL;
}

void slist_destruir(SList lista) {
  SNodo *nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->sig;
    free(nodoAEliminar);
  }
}

int slist_vacia(SList lista) {
  return lista == NULL;
}

SList slist_agregar_final(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;

  if (lista == NULL)
    return nuevoNodo;

  SList nodo = lista;
  for (;nodo->sig != NULL;nodo = nodo->sig);
  /* ahora 'nodo' apunta al ultimo elemento en la lista */

  nodo->sig = nuevoNodo;
  return lista;
}

SList slist_agregar_inicio(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = lista;
  return nuevoNodo;
}

void slist_recorrer(SList lista, FuncionVisitante visit) {
	SNodo *nodo;
  for (nodo = lista; nodo != NULL; nodo = nodo->sig)
    visit(nodo->dato);
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

SList slist_concatenar(SList lista1, SList lista2){
	if (lista1 == NULL) { return lista2; }
	if (lista2 == NULL) { return lista1; }
	else{
		SList nodo = lista1;
		for (;nodo->sig != NULL;nodo = nodo->sig);
		nodo->sig = lista2;
		return lista1;
		}
}

SList slist_insertar(SList lista,int pos, int dato){
	int longLista = slist_longitud(lista);
	if(lista == NULL) {
		lista = slist_agregar_inicio(lista,dato);
		return lista;
	}
	if(pos < 0){
		lista = slist_agregar_inicio(lista,dato);
		return lista;
	}
	if(pos > longLista){
		lista = slist_agregar_final(lista,dato);
		return lista;
	}
	else{
		int contador = 1;
		SNodo *nuevoNodo = malloc(sizeof(SNodo));
		nuevoNodo->dato = dato;
		SList nodo = lista;
		for ( ; contador<pos; nodo = nodo->sig){
			contador++;
		}
		nuevoNodo->sig = nodo->sig;
		nodo->sig = nuevoNodo;
		return lista;
	}
}

SList slist_eliminar(SList lista, int pos){
	int longLista = slist_longitud(lista);
	if( (lista == NULL) || (pos < 0) || (pos > longLista) ) { return lista; }
	else{
		int contador = 1;
		SNodo *temp = malloc(sizeof(SNodo));
		SList nodo = lista;
		for ( ; contador<pos; nodo = nodo->sig){
			contador++;
		}
		temp = nodo->sig;
		nodo->sig = temp->sig;
		free(temp);
		return lista;
	}
}

int slist_contiene(SList lista, int dato){
	if (lista == NULL) { 
		return 0; 
		}
		
	SList nodo = lista;
	if (nodo->dato == dato){
		return 1;
	}
	
	for(; nodo != NULL; nodo = nodo->sig){
		if(nodo->dato == dato){
			return 1;
		}
	}
	return 0;
}

int slist_indice(SList lista, int dato){
	if (lista == NULL) { return -1; }
	int contador = 0;
	SList nodo = lista;
	for(; nodo->sig != NULL; nodo = nodo->sig){
		if(nodo->dato == dato){
			return contador;
		}
		contador++;
	}
	return -1;
}

SList slist_intersecar(SList lista1,SList lista2){
	SList nuevaLista = slist_crear();
	SList nodo1 = lista1;
	
	for( ; nodo1->sig != NULL; nodo1 = nodo1->sig){
		if((slist_contiene(nuevaLista,nodo1->dato) == 0) && (slist_contiene(lista2,nodo1->dato) == 1)){
				nuevaLista = slist_agregar_final(nuevaLista,nodo1->dato);
			}
		}
	return nuevaLista;
	}

SList slist_intersecar_custom(SList lista1, SList lista2, FuncionIgualdadVisitante visit){
	SList nuevaLista = slist_crear();
	SList nodo1 = lista1;
	SList nodo2 = lista2;
	
	for( ; nodo1 != NULL; nodo1 = nodo1->sig){
		for( ; nodo2 != NULL; nodo2 = nodo2->sig){	
			if(slist_contiene(nuevaLista,nodo1->dato) == 0){
				if(visit(nodo1->dato,nodo2->dato) == 1){
					
					nuevaLista = slist_agregar_final(nuevaLista,nodo1->dato);
				}
			}
		}
		nodo2 = lista2;
	}
return nuevaLista;
}

// La funcion comparar debe tener el mismo funcionamiento que el strcmp. (Retorna 1 si el elemento a > b, 0 si a = b y -1 si a < b)

/*SList slist_ordenar(SList lista, FuncionCompararVisitante comparador){
	SList listaOrdenada = slist_crear();
	SList nodo = lista;
	
	for( ; nodo != NULL ; nodo = nodo->sig){
		if(listaOrdenada == NULL){
			listaOrdenada = slists_agregar_inicio(listaOrdenada,nodo->dato);
		}
		else{
			if(comparador(nodo->dato,nodo->sig->dato) == 0){
				listaOrdenada = slist_agregar_final(listaOrdenada,nodo->dato);
			}
			if(comparador(nodo->dato,nodo->sig->dato) > 0){
				listaOrdenada = slist_agregar_final(listaOrdenada,nodo->dato);
			}
			else{
				listaOrdenada = slist_agregar_inicio(listaOrdenada,nodo->dato);
			}
		}
	}
	return listaOrdenada;
}*/

SList slist_intercalar(SList lista1, SList lista2){
	SList lista_resto = slist_crear();
	SList lista_intercalada = slist_crear();
	SNodo *aux1, *aux2;
	int longLista1 = slist_longitud(lista1), longLista2 = slist_longitud(lista2);
	int i;
	if(longLista1 < longLista2){
		aux1 = lista1;
		aux2 = lista2;
		for(i=0 ; i<longLista1; i++, aux1 = aux1->sig, aux2 = aux2->sig){
			lista_intercalada = slist_agregar_final(lista_intercalada,aux1->dato);
			lista_intercalada = slist_agregar_final(lista_intercalada,aux2->dato);
		}
		
		for(i=0; i<longLista2-longLista1; i++, aux2 = aux2->sig){
			lista_intercalada = slist_agregar_final(lista_intercalada,aux2->dato);
		}
	}
	if(longLista1 > longLista2){
		aux1 = lista1;
		aux2 = lista2;
		for(i=0 ; i<longLista2; i++, aux1 = aux1->sig, aux2 = aux2->sig){
			lista_intercalada = slist_agregar_final(lista_intercalada,aux1->dato);
			lista_intercalada = slist_agregar_final(lista_intercalada,aux2->dato);
		}
		
		for(i=0; i<longLista1-longLista2; i++, aux1 = aux1->sig){
			lista_intercalada = slist_agregar_final(lista_intercalada,aux1->dato);
		}
	}
	else{
		aux1 = lista1;
		aux2 = lista2;
		for(i=0 ; i<longLista2; i++, aux1 = aux1->sig, aux2 = aux2->sig){
			lista_intercalada = slist_agregar_final(lista_intercalada,aux1->dato);
			lista_intercalada = slist_agregar_final(lista_intercalada,aux2->dato);
		}
	}
	return lista_intercalada;
}

SList slist_reverso(SList lista) {
  SNodo* reversa = NULL;
  SNodo* it;
  for (it = lista; it != NULL;) {
    SNodo* resto = it->sig;
    it->sig = reversa;
    reversa = it;
    it = resto;
  }
  return reversa;
}
