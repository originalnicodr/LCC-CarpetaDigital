#include "slist.h"
#include <stdlib.h>
#include <stdio.h>

int slist_longitud (SList lista){
	if (lista==NULL) return 0;
	int cont=1;
	SList temp=lista;
	for(;temp->sig!=NULL;temp=temp->sig) cont++;
	return cont;
}

static void imprimir_entero(int dato) {
  printf("%d ", dato);
}

//vamos a guardar la concatenasion de las listas en lista1
void slist_concatenar(SList lista1, SList lista2){
	if(lista1==NULL) lista1=lista2;
	if(lista2==NULL) return;
	else{
        SList temp=lista1;
		for(;temp->sig!=NULL;temp=temp->sig);
		temp->sig = lista2;
	}
}


//arreglar
SList slist_insertar (SList lista, int posicion, int dato){ //arrancamos desde 0
	if(lista==NULL||posicion==0) return slist_agregar_inicio(lista,dato);

	SNodo *nuevoNodo = malloc(sizeof(SNodo));
	nuevoNodo->dato = dato;

	SList inicio=lista;

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

SList slist_eliminar (SList lista, int posicion){
    if(posicion==0){
        SList temp;
        temp=lista->sig;
        free(lista);
        return temp;
    }
    SList inicio=lista;

    int i=0;
    for(;i<posicion-1;i++){
        lista=lista->sig;
    }
    printf("Estoy en la posición %d\n",i);
    SList temp;
    temp=lista->sig->sig;
    free(lista->sig);
    lista->sig=temp;
    return inicio;
    //lista=lista->sig->sig;

}

int slist_contiene(SList lista, int dato){
    if(lista==NULL) return 0;
    for(;lista->dato!=dato&&lista->sig!=NULL;lista=lista->sig);
    if(lista->sig==NULL){
        if(lista->dato==dato){
         return 1;
        }
        return 0;
    }
    return 1;
}

int slist_indice(SList lista, int dato){
    //assert(lista!=NULL); //APDB
    if(lista==NULL) return -1;
    int cont=0;
    for(;lista->sig!=NULL;lista=lista->sig){
        if(lista->dato==dato) return cont;
        cont++;
    }
    if(lista->sig==NULL&&lista->dato==dato) return cont;
    return -1;
}

SList slist_intersecar(SList lista1, SList lista2){
    SList listar=slist_crear();
    if(lista1==NULL||lista2==NULL) return listar;
    SList inicio2=lista2;
    for(;lista1->sig!=NULL;lista1=lista1->sig){
        if((slist_contiene(lista2,lista1->dato)==1)&&(slist_contiene(listar,lista1->dato)==0)){
            listar = slist_agregar_final(listar,lista1->dato);
        }

        /*for(lista2=inicio2;lista2->sig!=NULL;lista2=lista2->sig){
            printf("%d == %d ?\n",lista1->dato,lista2->dato);
            if(lista1->dato==lista2->dato) listar=slist_agregar_final(listar, lista1->dato);
        }
        printf("%d == %d ?\n",lista1->dato,lista2->dato);
        if(lista1->dato==lista2->dato) listar=slist_agregar_final(listar, lista1->dato);*/
    }
    if((slist_contiene(lista2,lista1->dato)==1)&&(slist_contiene(listar,lista1->dato)==0)){
            listar = slist_agregar_final(listar,lista1->dato);
        }
    //printf("%d == %d ?\n",lista1->dato,lista2->dato);
    //if(lista1->dato==lista2->dato) listar=slist_agregar_final(listar, lista1->dato); //comparacion cuando llega al final
    return listar;
}

/*SList slist_intersecar_custom (SList lista1, SList lista2, FuncionComparadora comparar){ //
    SList listar=slist_crear();
    if(lista1==NULL||lista2==NULL) return listar;  //esto se mantiene?
    SList inicio2=lista2;
    for(;lista1->sig!=NULL;lista1=lista1->sig){
        if((comparar(lista1,lista2))==1)&&(slist_contiene(listar,lista1->dato)==0)){ //igualmente me tengo que fijar que el dato
            listar = slist_agregar_final(listar,lista1->dato);
        }

        for(lista2=inicio2;lista2->sig!=NULL;lista2=lista2->sig){
            printf("%d == %d ?\n",lista1->dato,lista2->dato);
            if(lista1->dato==lista2->dato) listar=slist_agregar_final(listar, lista1->dato);
        }
        printf("%d == %d ?\n",lista1->dato,lista2->dato);
        if(lista1->dato==lista2->dato) listar=slist_agregar_final(listar, lista1->dato);
    }
    printf("%d == %d ?\n",lista1->dato,lista2->dato);
    if(lista1->dato==lista2->dato) listar=slist_agregar_final(listar, lista1->dato); //comparacion cuando llega al final
    return listar;

}*/

SList slist_ordenar (SList lista, FuncionComparadora comparar){
    SList listar=slist_crear();
    SList inicio, inicior;

    listar=slist_agregar_final(listar,lista->dato); //le asigno el primero para que arranque a comparar, no lo igualo directamente a lista por que me estaria copiando todo
    listar->sig=NULL;

    inicio=lista;
    inicior=listar;

    for(;lista->sig!=NULL;lista=lista->sig){ //cual seria el problema de usar lista!=NULL?
        int cont=0;
        listar=inicior;

        printf("Estamos en el elemento %d de la lista original\n",lista->dato);

        if(comparar(listar->dato,lista->dato)==-1){
            printf("%d es menor que %d, se insertara en posicion 0\n",lista->dato,listar->dato);
            listar=slist_agregar_inicio(listar,lista->dato); //si es menor que el primero lo agrega al principio
            inicior=listar;
            slist_recorrer(inicior, imprimir_entero);
            puts("");
        }

        for(;listar->sig!=NULL;listar=listar->sig,cont++){//chequear si me deja hacer cont++
            //printf("cont=%d\n",cont);
            if((comparar(listar->dato,lista->dato)==1)&&(comparar(listar->sig->dato,lista->dato)==-1)){
                    printf("%d es menor que %d que es menor que %d, se insertara en posicion %d\n",listar->dato,lista->dato,listar->dato, cont);
                    slist_insertar(listar,cont,lista->dato);
                    slist_recorrer(inicior, imprimir_entero);
                    puts("");
            }
        }
        if((comparar(listar->dato,lista->dato)==1)&&(listar->sig==NULL)){
                printf("%d mayor que %d en posicion ultima\n",lista->dato,listar->dato);
                slist_agregar_final(listar,lista->dato);//si es mas grande que el elemento final que se agregue al final, medio al pedo ver si el siguiente es NULL
                slist_recorrer(inicior, imprimir_entero);
                puts("");
        }
    }
    //la ultima condicion que el for no hace
    int cont=0;
    listar=inicior;

    if(comparar(listar->dato,lista->dato)==-1){
            printf("%d es menor que %d, se insertara en posicion 0\n",lista->dato,listar->dato);
            listar=slist_agregar_inicio(listar,lista->dato); //si es menor que el primero lo agrega al principio
            inicior=listar;
            slist_recorrer(inicior, imprimir_entero);
            puts("");
    }

    for(;listar->sig!=NULL;listar=listar->sig,cont++){//chequear si me deja hacer cont++
            if((comparar(listar->dato,lista->dato)==1)&&(comparar(listar->sig->dato,lista->dato)==-1)){
                    printf("%d es menor que %d que es menor que %d, se insertara en posicion %d\n",listar->dato,lista->dato,listar->dato, cont);
                    slist_insertar(listar,cont,lista->dato);
                    slist_recorrer(inicior, imprimir_entero);
                    puts("");
            }
        }
        if((comparar(listar->dato,lista->dato)==1)&&(listar->sig==NULL)){
                printf("%d mayor que %d en posicion ultima\n",lista->dato,listar->dato);
                slist_agregar_final(listar,lista->dato);
                slist_recorrer(inicior, imprimir_entero);
                puts("");
        }

    return inicior;
}

int mayor (int dato1, int dato2){
    if(dato1>dato2) return 1;
    if(dato1<dato2) return -1;
    return 0;
}

SList slist_reverso(SList lista){//MAL NO USAR
    return slist_ordenar(lista,mayor);

    /*SList indice,indice2,listr=NULL;
    indice=listr;
    while(lista!=NULL){
        for(indice=lista;indice->sig!=NULL;indice=indice->sig);
        
    }*/
    
}

SList slist_reverso2(SList l){//recursiva
    if(l==NULL) return l;
    SList s=l->sig;
    SList rev=slist_reverso2(s);
    if(l==NULL) return l;
    s->sig = l;
    l->sig=NULL;
    return rev;
}

SList slist_intercalar(SList lista1, SList lista2){ //considero que lista2 tiene menos elementos que lista1
    SList lista3=slist_crear();

    int long1=slist_longitud(lista1); //los llamo asi por que si los quiero comparar al final ya estan avanzados los "punteros" de lista
    int long2=slist_longitud(lista2);

    if(lista2==NULL) return lista1;

    lista3=slist_agregar_final(lista3,lista1->dato);

    SList inicio3=lista3;

    printf("Estoy copiando el elemento %d de la lista2\n",lista2->dato);
    puts("");

    for(;lista2->sig!=NULL;lista2=lista2->sig){ //voy a iterar sobre lista1
        printf("Estoy copiando el elemento %d de la lista2\n",lista2->dato);
        puts("");
        lista3=slist_agregar_final(lista3,lista2->dato);
        if (lista1->sig!=NULL)lista1=lista1->sig; //avanzo en la lista, siempre deberia entrar por que tiene mas elementos que lista2
        printf("Estoy copiando el elemento %d de la lista1\n",lista1->dato);
        puts("");
        lista3=slist_agregar_final(lista3,lista1->dato);
    }

    //para pasar por el ultimo de lista2
    printf("Estoy copiando el elemento %d de la lista2\n",lista2->dato);
    puts("");
    lista3=slist_agregar_final(lista3,lista2->dato);
    if (lista1->sig!=NULL)lista1=lista1->sig; //avanzo en la lista, siempre deberia entrar por que tiene mas elementos que lista2
    //lista3=slist_agregar_final(lista3,lista1->dato); //no lo pongo por que sino se copia dos veces, como la parte de abajo

    for(;lista1->sig!=NULL;lista1=lista1->sig){
        printf("Estoy copiando el elemento %d de la lista1\n",lista1->dato);
        puts("");
        lista3=slist_agregar_final(lista3,lista1->dato);
    }
    //printf("%d == %d?\n",slist_longitud(lista1), slist_longitud(lista2));
    if(long1!=long2){ //solucion crotisima
        printf("Estoy copiando el elemento %d de la lista1 (entro en el if)\n",lista1->dato);
        puts("");
        lista3=slist_agregar_final(lista3,lista1->dato);
    }

    return inicio3;
}

int exactanterior (int dato1, int dato2){
    if(dato1-1==dato2) return 1;
    return 0;
}

int anterior (int dato1, int dato2){
    if(dato1>dato2) return -1;
    if(dato1<dato2) return 1;
    return 0;
}

//Ejercicio 3



int main(){
	SList lista=slist_crear();
	SList lista2=slist_crear();
	SList listaV=slist_crear();


	lista = slist_agregar_inicio(lista, 3);
	lista = slist_agregar_inicio(lista, 2);
	lista = slist_agregar_inicio(lista, 1);
	lista = slist_agregar_final(lista, 4);
	lista2 = slist_agregar_inicio(lista2, 3);
	lista2 = slist_agregar_inicio(lista2, 2);
	lista2 = slist_agregar_inicio(lista2, 1);
	lista2 = slist_agregar_final(lista2, 4);

    //lista=slist_eliminar(lista,0);

	//slist_concatenar(lista,listaV);

	//slist_insertar(lista, 0, 500);

    //printf("indice=%d\n",slist_indice(listaV,1));

    //lista=slist_insertar(lista,4,50);

    slist_recorrer(lista, imprimir_entero);
    puts("");

    SList listai=slist_crear();
    listai=slist_intercalar(lista,lista2);

    slist_recorrer(listai, imprimir_entero);
	puts("");

    //printf("%d %d %d",anterior(1,2),anterior(2,2),anterior(3,2));

    //SList listaor=slist_ordenar(lista,anterior);

	//slist_recorrer(slist_intersecar(lista,lista2), imprimir_entero);
	puts("");
	//printf("La longitud de la lista es %d\n",slist_longitud(lista));

	slist_destruir(lista);
	slist_destruir(lista2);
	slist_destruir(listai);
	//slist_destruir(listaor);

	return 0;
}
