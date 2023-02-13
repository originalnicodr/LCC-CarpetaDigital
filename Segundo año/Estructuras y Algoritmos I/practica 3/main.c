#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include "slist.h"

#define MAX_PILA 5

typedef struct _Pila {
int datos[MAX_PILA];
int ultimo;
} *Pila; //Pila es un puntero

Pila pila_crear(){
    Pila pilan;
    pilan=malloc(sizeof(struct _Pila));
    pilan->ultimo=-1;
    return pilan;
}

int pila_es_vacia(Pila pila){
    return pila->ultimo==-1;
}

int pila_top(Pila pila){
    assert(!(pila_es_vacia(pila)));
    return pila->datos[pila->ultimo];
}

void pila_push(Pila pila, int dato){
    if(pila->ultimo==MAX_PILA){
        printf("No se pudo agregar por que la lista esta llena\n");
        return;
    }
    pila->ultimo++;
    pila->datos[pila->ultimo]=dato;
    return;
}

void pila_pop(Pila pila){
    assert(!(pila_es_vacia(pila)));
    pila->ultimo--;
    return;
}

void pila_imprimir(Pila pila){
    int i;
    for(i=pila->ultimo;i>=0;i--) printf("%d\n",pila->datos[i]);
    return;
}

void pila_destruir(Pila pila){
    free(pila);
    return;
}

/*int main(){
    Pila LApila = pila_crear();
    printf("es vacia? %d\n",pila_es_vacia(LApila));
    pila_top(LApila);
    pila_push(LApila, 1);
    pila_push(LApila, 2);
    pila_push(LApila, 3);
    pila_push(LApila, 4);
    
    printf("lalala el ultimo: %d \n",pila_top(LApila));
    pila_pop(LApila);
    pila_imprimir(LApila);
    pila_destruir(LApila);

    
    return 1;
}*/

//ej 2

typedef struct _Pilad {
int *datos;
int ultimo, longitud;
} *Pilad; //Pila es un puntero

Pilad pilad_crear(){
    Pilad pilan;
    pilan=malloc(sizeof(struct _Pila));
    pilan->longitud=MAX_PILA;
    pilan->datos=malloc(sizeof(int)*pilan->longitud);
    pilan->ultimo=-1;
    return pilan;
}

int pilad_es_vacia(Pilad pila){
    return pila->ultimo==-1;
}

int pilad_top(Pilad pila){
    assert(!(pilad_es_vacia(pila)));
    return pila->datos[pila->ultimo];
}

void pilad_push(Pilad pila, int dato){
    if(pila->ultimo==pila->longitud){
        pila->longitud*=2;
        pila->datos=realloc(pila->datos,sizeof(int)*pila->longitud);
    }
    pila->ultimo++;
    pila->datos[pila->ultimo]=dato;
    return;
}

void pilad_pop(Pilad pila){
    assert(!(pilad_es_vacia(pila)));
    pila->ultimo--;
    return;
}

void pilad_imprimir(Pilad pila){
    int i;
    for(i=pila->ultimo;i>=0;i--) printf("%d\n",pila->datos[i]);
    return;
}

void pilad_destruir(Pilad pila){
    free(pila->datos);
    free(pila);
    return;
}

/*int main(){
    Pilad pila=pilad_crear();
    printf("Es vacia? %d\n",pilad_es_vacia(pila));
    pilad_push(pila,6);
    pilad_push(pila,5);
    pilad_push(pila,4);
    pilad_push(pila,3);
    pilad_push(pila,2);
    pilad_push(pila,1);
    printf("lalala el ultimo puto %d\n",pilad_top(pila));
    pilad_pop(pila);
    pilad_imprimir(pila);
    pilad_destruir(pila);
    return 0;
}*/

//EJ 3

typedef SList Pilal;

Pilal pilal_crear(){
    Pilal pilan=slist_crear();
    return pilan;
}

int pilal_es_vacia(Pilal pila){
    return slist_vacia(pila);
}

int pilal_top(Pilal pila){
    assert(!(pilal_es_vacia(pila)));
    /*SNodo *nodo;
    for(nodo=pila;nodo!=NULL;nodo=nodo->sig);
    return nodo->dato;*/
    return pila->dato;
}

Pilal pilal_push(Pilal pila, int dato){
    return slist_agregar_inicio(pila,dato); //no deberia ser agregar al final? NO, por que de la forma en que la hice queda asi, revisar sino el pop, pero si estaria mal el imprimir
}

Pilal pilal_pop(Pilal pila){
    assert(!(pilal_es_vacia(pila)));
    SNodo *nodo=pila->sig;
    free(pila);
    return nodo;
}

void pilal_imprimir(Pilal pila){
    SNodo *nodo;
    for(nodo=pila;nodo!=NULL;nodo=nodo->sig) printf("%d\n",nodo->dato);
    return;
}

void pilal_destruir(Pilal pila){
    slist_destruir(pila);
    return;
}

Pilal pilal_reverso(Pilal pila){
    Pilal pilatemp=pilal_crear();
    SNodo *nodo;
    for(nodo=pila;nodo!=NULL;nodo=nodo->sig){
        pilatemp=pilal_push(pilatemp,nodo->dato);
        //printf("Agregue %d\n",nodo->dato);
    }
    return pilatemp;
}

int main (){
    Pilal pila;
    pila=pilal_crear();
    
    pila=pilal_push(pila,6);
    pila=pilal_push(pila,5);
    pila=pilal_push(pila,4);
    pila=pilal_push(pila,3);
    pila=pilal_push(pila,2);
    pila=pilal_push(pila,1);
    printf("Es vacia? %d\n",pilal_es_vacia(pila));
    pila=pilal_pop(pila);
    pilal_imprimir(pila);
    printf("lalala el ultimo puto %d\n",pilal_top(pila));
    Pilal pilar=pilal_reverso(pila);
    pilal_imprimir(pilar);
    pilal_destruir(pila);
    pilal_destruir(pilar);
    return 0;
}



