#include "glist.h"
#include <stddef.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>

GList glist_crear() {
  return NULL;
}

void glist_destruir(GList lista) {//no tendria que
  GNodo *nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->sig;
    //free(nodoAEliminar->dato); //lo comento para que no me haga free en los void*, osea en los RTNodos
    free(nodoAEliminar);
  }
}

int glist_vacia(GList lista) {
  return lista == NULL;
}

GList glist_agregar_final(GList lista, void* dato) {
  GNodo *nuevoNodo = malloc(sizeof(GNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;

  if (lista == NULL)
    return nuevoNodo;

  GList nodo = lista;
  for (;nodo->sig != NULL;nodo = nodo->sig);
  /* ahora 'nodo' apunta al ultimo elemento en la lista */

  nodo->sig = nuevoNodo;
  return lista;
}

GList glist_agregar_inicio(GList lista, void* dato) {
  GNodo *nuevoNodo = malloc(sizeof(GNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = lista;
  return nuevoNodo;
}

void glist_recorrer(GList lista, FuncionVisitante visit) { //funcion visitante recibe int
  for (GNodo *nodo = lista; nodo != NULL; nodo = nodo->sig)
    visit(nodo->dato);
}

void glist_mostrar(GList lista){ //para mostrar ints especificamente
    for(GNodo *recorrer=lista;recorrer!=NULL;recorrer=recorrer->sig){
        printf("%d ",*((int*)recorrer->dato));
    }
}

static void imprimir_enterop(int *dato) {
  printf("%d ", *dato);
}

int glist_longitud (GList lista){
	if (lista==NULL) return 0;
	int cont=1;
	GList temp=lista;
	for(;temp->sig!=NULL;temp=temp->sig) cont++;
	return cont;
}

//vamos a guardar la concatenasion de las listas en lista1
void glist_concatenar(GList lista1, GList lista2){ //despues de concatenar no podes hacer free de la que concatenas no?
	if(lista1==NULL) lista1=lista2;
	if(lista2==NULL) return;
	else{
        GList temp=lista1;
		for(;temp->sig!=NULL;temp=temp->sig);
		temp->sig = lista2;
	}
}

//falta testear con la funcion de recorrer
GList glist_insertar (GList lista, int posicion, void* dato){ //arrancamos desde 0
	if(lista==NULL||posicion==0) return glist_agregar_inicio(lista,dato);

	GNodo *nuevoNodo = malloc(sizeof(GNodo));
	nuevoNodo->dato = dato;

	GList inicio=lista;

    int i;
    for(i=0;i<posicion-1;i++){ // te paras en el anterior que queres agregar
        //printf("i=%d - dato= %d\n",i,lista->dato);
        lista=lista->sig;
        //printf("SALE:  i=%d - dato= %d\n",i,lista->dato);
    }
    nuevoNodo->sig=lista->sig;
    lista->sig=nuevoNodo;
    return inicio;
}

int glist_contiene(GList lista, void* dato, FuncionComparadora f){ //me tira error
    for(GNodo* nodo = lista; nodo!= NULL;nodo= nodo->sig)
    {
        if(f(nodo->dato,dato)) return 1;
    }
    return 0;
}

int IgualPInt (void* d1, void* d2){
    int *n1 = (int*) d1, *n2 =(int*) d2;
    return (*n1==*n2);
}

int glist_indice(GList lista, void* dato, FuncionComparadora f){//tema del void
    //assert(lista!=NULL); //APDB
    int cont=0;
    for(;lista!=NULL;lista=lista->sig){
        if(f(lista->dato,dato)) return cont;
        cont++;
    }
    return -1;
}

GList glist_ordenar (GList lista, FuncionComparadora comparar){
    GList listar=glist_crear();
    GList inicio, inicior;

    listar=glist_agregar_final(listar,lista->dato); //le asigno el primero para que arranque a comparar, no lo igualo directamente a lista por que me estaria copiando todo
    listar->sig=NULL;

    inicio=lista;
    inicior=listar;

    for(;lista->sig!=NULL;lista=lista->sig){ //cual seria el problema de usar lista!=NULL?
        int cont=0;
        listar=inicior;

        //printf("Estamos en el elemento %d de la lista original\n",*((int*)lista->dato));

        if(comparar(listar->dato,lista->dato)==-1){
            //printf("%d es menor que %d, se insertara en posicion 0\n",lista->dato,listar->dato);
            listar=glist_agregar_inicio(listar,lista->dato); //si es menor que el primero lo agrega al principio
            inicior=listar;
            glist_mostrar(inicior);
            puts("");
        }

        for(;listar->sig!=NULL;listar=listar->sig,cont++){//chequear si me deja hacer cont++
            //printf("cont=%d\n",cont);
            if((comparar(listar->dato,lista->dato)==1)&&(comparar(listar->sig->dato,lista->dato)==-1)){
                    //printf("%d es menor que %d que es menor que %d, se insertara en posicion %d\n",listar->dato,lista->dato,listar->dato, cont);
                    glist_insertar(listar,cont,lista->dato);
                    glist_mostrar(inicior);
                    puts("");
            }
        }
        if((comparar(listar->dato,lista->dato)==1)&&(listar->sig==NULL)){
                //printf("%d mayor que %d en posicion ultima\n",lista->dato,listar->dato);
                glist_agregar_final(listar,lista->dato);//si es mas grande que el elemento final que se agregue al final, medio al pedo ver si el siguiente es NULL
                glist_mostrar(inicior);
                puts("");
        }
    }
    //la ultima condicion que el for no hace
    int cont=0;
    listar=inicior;

    if(comparar(listar->dato,lista->dato)==-1){
            //printf("%d es menor que %d, se insertara en posicion 0\n",lista->dato,listar->dato);
            listar=glist_agregar_inicio(listar,lista->dato); //si es menor que el primero lo agrega al principio
            inicior=listar;
            glist_mostrar(inicior);
            puts("");
    }

    for(;listar->sig!=NULL;listar=listar->sig,cont++){//chequear si me deja hacer cont++
            if((comparar(listar->dato,lista->dato)==1)&&(comparar(listar->sig->dato,lista->dato)==-1)){
                    //printf("%d es menor que %d que es menor que %d, se insertara en posicion %d\n",listar->dato,lista->dato,listar->dato, cont);
                    glist_insertar(listar,cont,lista->dato);
                    glist_mostrar(inicior);
                    puts("");
            }
        }
        if((comparar(listar->dato,lista->dato)==1)&&(listar->sig==NULL)){
                //printf("%d mayor que %d en posicion ultima\n",lista->dato,listar->dato);
                glist_agregar_final(listar,lista->dato);
                glist_mostrar(inicior);
                puts("");
        }

    return inicior;
}

int mayorint (void* dato1, void* dato2){
    int *n1=(int*) dato1, *n2=(int*) dato2;   
    if(*n1>*n2) return 1;
    if(*n1<*n2) return -1;
    return 0;
}

/*GList glist_reverso(GList l){//No funca
    if(l==NULL) return l;
    GList s=l->sig;
    GList rev=glist_reverso(s);
    if(l==NULL) return l;
    s->sig = l;
    l->sig=NULL;
    return rev;
}*/

GList glist_intercalar(GList lista1, GList lista2){ //considero que lista2 tiene menos elementos que lista1
    GList lista3=glist_crear();

    int long1=glist_longitud(lista1); //los llamo asi por que si los quiero comparar al final ya estan avanzados los "punteros" de lista
    int long2=glist_longitud(lista2);

    if(lista2==NULL) return lista1;

    lista3=glist_agregar_final(lista3,lista1->dato);

    GList inicio3=lista3;

    //printf("Estoy copiando el elemento %d de la lista2\n",lista2->dato);
    //puts("");

    for(;lista2->sig!=NULL;lista2=lista2->sig){ //voy a iterar sobre lista1
        /*printf("Estoy copiando el elemento %d de la lista2\n",lista2->dato);
        puts("");*/
        lista3=glist_agregar_final(lista3,lista2->dato);
        if (lista1->sig!=NULL)lista1=lista1->sig; //avanzo en la lista, siempre deberia entrar por que tiene mas elementos que lista2
        /*printf("Estoy copiando el elemento %d de la lista1\n",lista1->dato);
        puts("");*/
        lista3=glist_agregar_final(lista3,lista1->dato);
    }

    //para pasar por el ultimo de lista2
    /*printf("Estoy copiando el elemento %d de la lista2\n",lista2->dato);
    puts("");*/
    lista3=glist_agregar_final(lista3,lista2->dato);
    if (lista1->sig!=NULL)lista1=lista1->sig; //avanzo en la lista, siempre deberia entrar por que tiene mas elementos que lista2
    //lista3=GList_agregar_final(lista3,lista1->dato); //no lo pongo por que sino se copia dos veces, como la parte de abajo

    for(;lista1->sig!=NULL;lista1=lista1->sig){
        /*printf("Estoy copiando el elemento %d de la lista1\n",lista1->dato);
        puts("");*/
        lista3=glist_agregar_final(lista3,lista1->dato);
    }
    //printf("%d == %d?\n",GList_longitud(lista1), GList_longitud(lista2));
    if(long1!=long2){ //solucion crotisima
        /*printf("Estoy copiando el elemento %d de la lista1 (entro en el if)\n",lista1->dato);
        puts("");*/
        lista3=glist_agregar_final(lista3,lista1->dato);
    }

    return inicio3;
}
