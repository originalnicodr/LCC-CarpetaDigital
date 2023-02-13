#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cslist.h"

static void imprimir_entero(int dato) {
  printf("%d ", dato);
}

int cslist_longitud (CSList lista){
	if (lista==NULL) return 0;
	int cont=1;
	CSList temp=lista;
	for(;temp->sig!=lista;temp=temp->sig) cont++;
	return cont;
}

void cslist_concatenar(CSList lista1, CSList lista2){
	if(lista1==NULL) lista1=lista2;
	if(lista2==NULL) return;
	else{
        CSList temp1=lista1;
		for(;temp1->sig!=lista1;temp1=temp1->sig);
		temp1->sig = lista2;

		CSList temp2=lista2;
		for(;temp2->sig!=lista2;temp2=temp2->sig);
		temp2->sig = lista1;
	}
}

CSList cslist_insertar (CSList lista, int posicion, int dato){ //arrancamos desde 0
	if(lista==NULL||posicion==0){
            //printf("Agrego al principio\n");
            return cslist_agregar_inicio(lista,dato);
	}
	if(posicion>=cslist_longitud(lista)){
            //printf("Agrego final\n");
            return cslist_agregar_final(lista,dato);
	}

	SNodo *nuevoNodo = malloc(sizeof(SNodo));
	nuevoNodo->dato = dato;

	CSList inicio=lista;

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

CSList cslist_eliminar (CSList lista, int posicion){
    if(posicion==0){

        CSList temp=lista;
		for(;temp->sig!=lista;temp=temp->sig);
        temp->sig=lista->sig; //saltea el primer elemento

        CSList temp1;
        temp1=lista->sig;
        free(lista);
        return temp1;
    }
    CSList inicio=lista;

    int i=0;
    for(;i<posicion-1;i++){
        lista=lista->sig;
    }
    printf("Estoy en la posicion %d\n",i);
    CSList temp;
    temp=lista->sig->sig;
    free(lista->sig);
    lista->sig=temp;
    return inicio;
    //lista=lista->sig->sig;

}

int cslist_contiene(CSList lista, int dato){
    if(lista==NULL) return 0;
    CSList indice=lista;
    for(;indice->sig!=lista&&indice->dato!=dato;indice=indice->sig);
    if(indice->sig==lista){
        if(indice->dato==dato){
         return 1;
        }
        return 0;
    }
    return 1;
}

int cslist_indice(CSList lista, int dato){
    //assert(lista!=NULL); //APDB
    if(lista==NULL) return -1;
    int cont=0;
    CSList indice=lista;
    for(;indice->sig!=lista;indice=indice->sig){
        if(indice->dato==dato) return cont;
        cont++;
    }
    if(indice->sig==lista&&indice->dato==dato) return cont; //al pedo si ya se que llego al final
    return -1;
}

CSList cslist_intersecar(CSList lista1, CSList lista2){
    CSList listar=cslist_crear();
    if(lista1==NULL||lista2==NULL) return listar;
    CSList inicio2=lista2; //no lo uso nunca, al pedo

    CSList indice1=lista1;
    for(;indice1->sig!=lista1;indice1=indice1->sig){
        if((cslist_contiene(lista2,indice1->dato)==1)&&(cslist_contiene(listar,indice1->dato)==0)){ //si esta en los dos y no lo puse antes, entra
            listar = cslist_agregar_final(listar,indice1->dato);
        }

        /*for(lista2=inicio2;lista2->sig!=NULL;lista2=lista2->sig){
            printf("%d == %d ?\n",lista1->dato,lista2->dato);
            if(lista1->dato==lista2->dato) listar=slist_agregar_final(listar, lista1->dato);
        }
        printf("%d == %d ?\n",lista1->dato,lista2->dato);
        if(lista1->dato==lista2->dato) listar=slist_agregar_final(listar, lista1->dato);*/
    }
    if((cslist_contiene(lista2,indice1->dato)==1)&&(cslist_contiene(listar,indice1->dato)==0)){
            listar = cslist_agregar_final(listar,indice1->dato);
        }
    //printf("%d == %d ?\n",lista1->dato,lista2->dato);
    //if(lista1->dato==lista2->dato) listar=slist_agregar_final(listar, lista1->dato); //comparacion cuando llega al final
    return listar;
}

CSList cslist_ordenar (CSList lista, FuncionComparadora comparar){ //anda maaaaaaaaaaaaaaaaaaal
    CSList listar=cslist_crear();
    CSList indice, indicer;

    listar=cslist_agregar_final(listar,lista->dato); //le asigno el primero para que arranque a comparar, no lo igualo directamente a lista por que me estaria copiando todo
    listar->sig=listar;

    indice=lista;//por que ya ya agregue el primer elemento, no es necesario compararlo...?
    indicer=listar;

    for(;indice->sig!=lista;indice=indice->sig){ //cual seria el problema de usar lista!=NULL?
        int cont=1; //si cont= 0 ordena bien en un sentido, pero no en otro, si es =1 al reves
        indicer=listar;

        printf("Estamos en el elemento %d de la lista original\n",indice->dato);

        if(comparar(indicer->dato,indice->dato)==-1){
            printf("%d es menor que %d, se insertara en posicion 0\n",indice->dato,indicer->dato);
            indicer=cslist_agregar_inicio(indicer,indice->dato); //si es menor que el primero lo agrega al principio
            listar=indicer;
            cslist_recorrer(listar, imprimir_entero);
            puts("");
        }

        for(;indicer->sig!=listar;indicer=indicer->sig,cont++){//chequear si me deja hacer cont++
            printf("cont=%d\n",cont);
            if((comparar(indicer->dato,indice->dato)==1)&&(comparar(indicer->sig->dato,indice->dato)==-1)){
                    printf("%d es menor que %d que es menor que %d, se insertara en posicion %d\n",indicer->dato,indice->dato,indicer->sig->dato, cont);
                    cslist_insertar(listar,cont,indice->dato);
                    cslist_recorrer(listar, imprimir_entero);
                    puts("");
            }
        }
        if((comparar(indicer->dato,indice->dato)==1)&&(indicer->sig==listar)){
                printf("%d mayor que %d en posicion ultima\n",indice->dato,indicer->dato);
                cslist_agregar_final(indicer,indice->dato);//si es mas grande que el elemento final que se agregue al final, medio al pedo ver si el siguiente es NULL
                cslist_recorrer(listar, imprimir_entero);
                puts("");
        }
    }
    //la ultima condicion que el for no hace
    int cont=0; //antes habia arrancado de 1 aproposito, podria cambiar aca no?
    indicer=listar;

    if(comparar(indicer->dato,indice->dato)==-1){
            printf("%d es menor que %d, se insertara en posicion 0 (esto esta fuera del for)\n",indice->dato,indicer->dato);
            indicer=cslist_agregar_inicio(indicer,indice->dato); //si es menor que el primero lo agrega al principio
            listar=indicer;
            cslist_recorrer(listar, imprimir_entero);
            puts("");
    }

    for(;indicer->sig!=listar;indicer=indicer->sig,cont++){//chequear si me deja hacer cont++
            if((comparar(indicer->dato,indice->dato)==1)&&(comparar(indicer->sig->dato,indice->dato)==-1)){
                    printf("%d es menor que %d que es menor que %d, se insertara en posicion %d\n",indicer->dato,indice->dato,indicer->dato, cont);
                    cslist_insertar(indicer,cont,lista->dato);
                    cslist_recorrer(listar, imprimir_entero);
                    puts("");
            }
        }
        if((comparar(indicer->dato,indice->dato)==1)&&(indice->sig==lista)){
                printf("%d mayor que %d en posicion ultima\n",indice->dato,indicer->dato);
                cslist_agregar_final(indicer,indice->dato);
                cslist_recorrer(listar, imprimir_entero);
                puts("");
        }

    return listar;
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

int mayor (int dato1, int dato2){
    if(dato1>dato2) return 1;
    if(dato1<dato2) return -1;
    return 0;
}

CSList cslist_intercalar(CSList lista1, CSList lista2){ //considero que lista2 tiene menos elementos que lista1
    CSList lista3=cslist_crear();

    if(lista2==NULL) return lista1;

    int long1=cslist_longitud(lista1); //los llamo asi por que si los quiero comparar al final ya estan avanzados los "punteros" de lista
    int long2=cslist_longitud(lista2);

    lista3=cslist_agregar_final(lista3,lista1->dato);

    CSList indice2=lista2;
    CSList indice1=lista1;

    printf("Estoy copiando el elemento %d de la lista2\n",indice1->dato);
    puts("");

    for(;indice2->sig!=lista2;indice2=indice2->sig){ //voy a iterar sobre lista1
        printf("Estoy copiando el elemento %d de la lista2\n",indice2->dato);
        puts("");
        lista3=cslist_agregar_final(lista3,lista2->dato);
        if (indice1->sig!=lista1)indice1=indice1->sig; //avanzo en la lista, siempre deberia entrar por que tiene mas elementos que lista2
        printf("Estoy copiando el elemento %d de la lista1\n",indice1->dato);
        puts("");
        lista3=cslist_agregar_final(lista3,indice1->dato);
    }

    //para pasar por el ultimo de lista2
    printf("Estoy copiando el elemento %d de la lista2\n",indice2->dato);
    puts("");
    lista3=cslist_agregar_final(lista3,indice2->dato);
    if (indice1->sig!=lista1)indice1=indice1->sig; //avanzo en la lista, siempre deberia entrar por que tiene mas elementos que lista2
    //lista3=slist_agregar_final(lista3,lista1->dato); //no lo pongo por que sino se copia dos veces, como la parte de abajo

    for(;indice1->sig!=lista1;indice1=indice1->sig){
        printf("Estoy copiando el elemento %d de la lista1\n",indice1->dato);
        puts("");
        lista3=cslist_agregar_final(lista3,indice1->dato);
    }
    //printf("%d == %d?\n",slist_longitud(lista1), slist_longitud(lista2));
    if(long1!=long2){ //solucion crotisima
        printf("Estoy copiando el elemento %d de la lista1 (entro en el if)\n",indice1->dato);
        puts("");
        lista3=cslist_agregar_final(lista3,indice1->dato);
    }

    return lista3;
}

//Reverso recursivo no anda con listas circulares

int main(int argc, char *argv[]) {

  CSList lista = cslist_crear();

  lista = cslist_agregar_inicio(lista, 3);
  lista = cslist_agregar_inicio(lista, 7);
  //lista = cslist_agregar_inicio(lista, 5);
  //lista = cslist_agregar_final(lista, 4);

  CSList lista2 = cslist_crear();

  //lista2 = cslist_agregar_inicio(lista2, 3);
  lista2 = cslist_agregar_inicio(lista2, 2);
  lista2 = cslist_agregar_inicio(lista2, 1);
  //lista2 = cslist_agregar_final(lista2, 4);

  //cslist_concatenar(lista,lista2);

  //printf("longitud: %d\n",cslist_longitud(lista));

  lista=cslist_insertar(lista,0,19);
  //lista=cslist_ordenar(lista,anterior);

  /*CSList lista3=cslist_intersecar(lista,lista2);

  cslist_recorrer(lista3, imprimir_entero);
  puts("");*/

  //printf("Tiene 23?: %d\n",cslist_contiene(lista,23));

  //lista=cslist_eliminar(lista,0);

  //printf("El 3 se encuentra en la posicion %d\n",cslist_indice(lista,3));

  cslist_recorrer(lista, imprimir_entero);
  puts("");
  cslist_recorrer(lista2, imprimir_entero);
  puts("");

  CSList lista3= cslist_intercalar(lista,lista2);

  cslist_recorrer(lista3, imprimir_entero);
  puts("");

  cslist_destruir(lista);
  cslist_destruir(lista2);
  cslist_destruir(lista3);

  //cslist_recorrer(lista, imprimir_entero); //Vamos a suponer que destruye bien la lista

  //assert(lista==NULL);

  return 0;
}
