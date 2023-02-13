#include <stdio.h>
#include <stdlib.h>
#include "glist.h"
#include <malloc.h>

void imprimir_dato_rtree(void* arbol){
	printf("%d\n",((RTree)arbol)->dato);
	}

RTree rtree_insertar(RTree arbol, int dato){
  RTree nuevoNodo;
  nuevoNodo=malloc(sizeof(RTNodo));
  nuevoNodo->dato=dato;
  GList lista=glist_crear();
  nuevoNodo->hijos=lista;

  if(arbol==NULL){
    return nuevoNodo;
  }
  arbol->hijos = glist_agregar_final(arbol->hijos, nuevoNodo);
  return arbol;
}

/*RTree rtree_eliminar_aux(RTree arbol, int dato, RTree padre){//vamos a convertir sus hijos en sus hermanos
  if(arbol==NULL){
    //printf("No se encontro el dato\n");//no lo imprimo por que me va a estar imprimiendo cada vez que llega a un final
    return arbol;
  }
  if(arbol->dato==dato&&padre==NULL){//si tenemos que eliminar la raiz ponemos al primer hijo como nueva raiz
    RTree B=arbol->hijos->dato;
    GList temp=arbol->hijos;
    arbol->hijos=arbol->hijos->sig;//saco el nodo B de la lista
    free(temp);//free del primer lugar de la lista

    glist_concatenar(B->hijos,arbol->hijos);//agrego los hermanos de B como si fueran los hijos
    glist_destruir(arbol->hijos);//creo que me hace free de todos los RTNodo -------------------------------------- si algo no funca chequear esto
    free(arbol);//el RTNodo que voy a eliminar
    return B;
  }

  //hacemos caso de raiz que sea el normal o subimos todos los hijos un nivel?

  GList indice=arbol->hijos;
  for (;indice!=NULL;indice=indice->sig){//recursion
    rtree_eliminar_aux(indice->dato, dato, arbol);
  }
}

RTree rtree_eliminar(RTree arbol, int dato){
  rtree_eliminar_aux(arbol, dato, NULL);
}*/



/*GList glist_eliminar(GList lista, int dato) {//no le hago free cuando lo "elimino", eso lo hago dentro de la funcion rtree_eliminar2
  if(((RTree)lista->dato)->dato==dato){ //analiza si es el primer nodo
    GNodo *temp=lista;
    lista=lista->sig;
    free(temp);//hago free del GNodo
    return lista;
  }
  GNodo *nodo = lista;
  for (; nodo != NULL; nodo = nodo->sig){
    if(((RTree)nodo->dato)->dato==dato){
      GNodo *temp=nodo->sig;
      nodo->sig=nodo->sig->sig;
      free(temp);//hago free del GNodo
      return lista;//corta si lo encuentra
    }
  }
  printf("No se ha encontrado el dato\n");
  return lista;//corta si no lo encontro
}



void rtree_eliminar2_aux(RTree arbol, int dato, RTree padre){//vamos a convertir sus hijos en sus hermanos, NO SE PUEDE ELIMINAR LA RAIZ, TE QUEDARIAN DOS SUBARBOLES, por eso es void
  if(arbol==NULL){
    //printf("No se encontro el dato\n");//no lo imprimo por que me va a estar imprimiendo cada vez que llega a un final
    return;
  }
  if(arbol->dato==dato&&padre!=NULL){//voy a pasar los hijos del arbol para que sean los hijos del padre
    glist_eliminar(padre->hijos,dato);//elimino el Gnodo de la lista de hijos del padre
    glist_concatenar(padre->hijos,arbol->hijos);//uno la lista de hijos del arbol a la lista de hijos del padre, los hijos del arbol me van a quedar al final de los hijos del padre
    //si eliminas un nodo que tiene hermanos a izquierda y derecha, y agregas los hijos del nodo que eliminaste no van a quedar entre los hermanos del nodo a eliminar, van a estar al final

    free(arbol);
    return;
  }

  //hacemos caso de raiz que sea el normal o subimos todos los hijos un nivel?

  GList indice=arbol->hijos;
  for (;indice!=NULL;indice=indice->sig){//recursion para seguir buscando el dato
    rtree_eliminar2_aux(indice->dato, dato, arbol);
  }
}

void rtree_eliminar2(RTree arbol, int dato){
  return rtree_eliminar2_aux(arbol, dato, NULL);
}*/



int rtree_contiene(RTree arbol, int dato){
  if(arbol==NULL||(arbol->hijos==NULL&&arbol->dato!=dato)) return 0;//no lo encontre en esta rama
  if(arbol->dato==dato) return 1;

  GList indice=arbol->hijos;
  int cont=0;
  for(;indice!=NULL;indice=indice->sig){//recursion
    cont+=rtree_contiene(indice->dato,dato);//voy sumando, si no los encontro en todos los indices, entonces dara cero, si esta dara 1
  }
  return cont;
}

int rtree_nelementos(RTree arbol){
  if(arbol==NULL) return 0;
  //if(arbol->hijos==NULL) return 1; //no tiene hijos

  int cont=1;
  GList indice=arbol->hijos;
  for(;indice!=NULL;indice=indice->sig){//recursion
		
    cont+=rtree_nelementos(indice->dato);//sumo la cantidad de elementos que tiene ese arbol
  }
  return cont;
}
/*
int rtree_altura_aux(RTree arbol,int alturamax){
  if(arbol==NULL) return -1;
  if(arbol->hijos==NULL) return alturamax++; //no tiene hijos

  GList indice=arbol->hijos;
  //alturamax++;
  int temp=rtree_altura_aux(indice->dato,++alturamax);//inicial para comparar
  for(indice=indice->sig;indice!=NULL;indice=indice->sig){//el primer indice=indice->sig es para avanzar uno y comparar con el temp inicial
    if(temp<rtree_altura_aux(indice->dato,++alturamax)) temp=rtree_altura_aux(indice->dato,++alturamax);//nuevo maximo
  }
  return temp;
}

int rtree_altura(RTree arbol){
  return rtree_altura_aux(arbol, 0);
}*/

/*int rtree_altura_(RTree arbol){
	if(arbol == NULL) return -1;
	int cont == 0;
	if(arbol->hijos != NULL){
		GList indice = arbol->hijos;
		for(;indice=indice->sig;indice!=NULL){
			if(cont=rtree_altura_(indice->datos)<cont
			}
	}
}*/

int rtree_altura_aux(RTree arbol, int nivel){//Cortecia de fede
  static int mayorAltura=0;
  if(arbol!=NULL){
    if(nivel>mayorAltura) mayorAltura=nivel;
    int temp;
    if(arbol->hijos!=NULL){
      for(GNodo *nodo = arbol->hijos; nodo!=NULL; nodo=nodo->sig){
        temp=rtree_altura_aux((RTree)nodo->dato, nivel+1);
      }
    }
  }
  return mayorAltura;
}

int rtree_altura (RTree arbol){
  return rtree_altura_aux(arbol,0);
}


void rtree_recorrer(RTree arbol, FuncionVisitante visit){//funcion visitante en RTree
  if(arbol!=NULL){//existe el recorrido de derecha a izquierda, pero para hacerlo deberia tener una lista doblemente enlazada en lugar de una simplemente enlazada
    visit(arbol);
    GList indice=arbol->hijos;
    for(;indice!=NULL;indice=indice->sig){//recursion para recorrer los hijos de izquierda a derecha
      rtree_recorrer(indice->dato, visit);
    }
  }
}



MTree mtree_crear(){
  return NULL;
}

void mtree_destruir(MTree arbol){
  if(arbol==NULL) return;
  
  if(arbol->son!=NULL) mtree_destruir(arbol->son);
  if(arbol->bro!=NULL) mtree_destruir(arbol->bro);
  free(arbol);
  return;
}

void visit_contar (int dato, void *contador){
	*(int*)contador=*(int*)contador+1;
}

void mtree_recorrer(MTree arbol, FuncionVisitante visit){//estoy haciendo preorder
  if(arbol==NULL) return;
  visit(arbol);
  if(arbol->son!=NULL) mtree_recorrer(arbol->son, visit);//paso por todos los hermanos, si intercambio estas dos lineas me queda escrito A, B, C como en el ejercicio
  if(arbol->bro!=NULL) mtree_recorrer(arbol->bro, visit);//paso por los hijos
}

void mtree_recorrer_extra(MTree arbol, FuncionVisitanteExtra visit, void* extra){
  if(arbol==NULL) return;
  visit(arbol->dato, extra);
  if(arbol->son!=NULL) mtree_recorrer_extra(arbol->son, visit, extra);//paso por todos los hermanos, si intercambio estas dos lineas me queda escrito A, B, C como en el ejercicio
  if(arbol->bro!=NULL) mtree_recorrer_extra(arbol->bro, visit, extra);//paso por los hijos
}

int mtree_nelems(MTree raiz){
	int contador=0;
	mtree_recorrer_extra(raiz,visit_contar, &contador);
	return contador;
}

//-------------------------------------------------no tiene la funcion en si, quedan muchas cosas indefinidas

//que dado un dato, agregue una nodo hijo en la posicion indicada. Si la posicion recibida es mayor al numero de hijos,
//procure que el nuevo nodo hijo se agregue al final. Que carajos es el final? como hermano del ultimo hijo o que onda?
MTree mtree_agregar_n_hijo_aux(MTree arbol, int dato, int pos, int cont){//agregarlo al final si se pasa
  if(arbol!=NULL){
    if(cont==pos){
    MTNodo* nuevoNodo=malloc(sizeof(MTNodo));
    nuevoNodo->dato=dato;
    nuevoNodo->son=NULL;
    nuevoNodo->bro=arbol->bro;
    arbol->bro=nuevoNodo;
    }
    else {
      arbol->son=mtree_agregar_n_hijo_aux(arbol->son, dato, pos, cont+1);
      arbol->bro=mtree_agregar_n_hijo_aux(arbol->bro, dato, pos, cont+1);
    }
  }
  return arbol;
}

MTree mtree_agregar_n_hijo(MTree arbol, int dato, int pos){
  if(pos==0){//por si inserto en la raiz, paso el arbol original al hijo
    MTNodo* nuevoNodo=malloc(sizeof(MTNodo));
    nuevoNodo->dato=dato;
    nuevoNodo->son=arbol;
    nuevoNodo->bro=NULL;

    return nuevoNodo;
  }

  if(mtree_nelems(arbol)<=pos){//si la posicion es mayor a la cantidad de elementos del arbol entonces lo agrego como ultimo hijo de la raiz (por que asi es el recorrido) (tambien podia agregarlo como hijo del ultimo hijo de la raiz)
    MTNodo* nuevoNodo=malloc(sizeof(MTNodo));
    nuevoNodo->dato=dato;
    nuevoNodo->son=NULL;
    nuevoNodo->bro=NULL;
    
    MTNodo* indice=arbol;
    for(;indice->son!=NULL;indice=indice->son);
    indice->son=nuevoNodo;
    return arbol;
  }
  return mtree_agregar_n_hijo_aux(arbol, dato, pos, 0);
}

//-------------------------------------------------------


int mtree_altura_aux(MTree arbol, int altura){
  int mayorAltura = altura;
  if(arbol != NULL){
    MTree indice=arbol->son;//esto a lo sumo te daria null
    for(;indice!=NULL;indice=indice->bro){
      if (mayorAltura<mtree_altura_aux(indice,altura+1)) mayorAltura=mtree_altura_aux(indice,altura+1);
    }
  }
  return mayorAltura;
}



int mtree_altura(MTree arbol){
  return mtree_altura_aux(arbol, 0);
}

void convert_to_mtree_aux(GList hijos, MTree padre){//el objetivo sera enlazar al padre con estos hijos
  MTNodo* nuevoNodo=malloc(sizeof(MTNodo));
  nuevoNodo->dato=((RTree)(hijos->dato))->dato;//el primer hijo

  padre->son=nuevoNodo;

  //ahora nos tenemos que fijar los hijos de este nuevo nodo
  if(((RTree)(hijos->dato))->hijos!=NULL) convert_to_mtree_aux(((RTree)(hijos->dato))->hijos,nuevoNodo);
  else nuevoNodo->son=NULL;
  
  GList indice=hijos->sig;//arranco en el siguiente para no volver a guardar el primer hijo
  MTree temp=nuevoNodo;//indice para ir enlazando hermanos
  for(;indice!=NULL;indice=indice->sig){//vamos a enlazar los hermanos

    MTree nuevoHermano=malloc(sizeof(MTNodo));
    nuevoHermano->dato=((RTree)(indice->dato))->dato;
    if(((RTree)(indice->dato))->hijos!=NULL){//si tengo que poner hijos tengo que hacer recursion
      convert_to_mtree_aux(((RTree)(indice->dato))->hijos,nuevoHermano);
    }
    else nuevoHermano->son=NULL;

    temp->bro=nuevoHermano;
    temp=nuevoHermano;
    
  }
  temp->bro=NULL; //al ultimo hermano lo mando a NULL
  

}

MTree convert_to_mtree(RTree arbol){
  if(arbol==NULL) return NULL;
  
  MTNodo* raiz=malloc(sizeof(MTNodo));
  raiz->dato=arbol->dato;
  raiz->bro=NULL;

  MTNodo* primerhijo=malloc(sizeof(MTNodo));
  primerhijo->dato=((RTree)(arbol->hijos->dato))->dato;

  if(((RTree)(arbol->hijos->dato))->hijos!=NULL){//como esta fuera del for tenia que ponerlo en algun lado
    convert_to_mtree_aux(((RTree)(arbol->hijos->dato))->hijos,primerhijo);
  }
  else primerhijo->son=NULL;

  raiz->son=primerhijo;

  GList indice=arbol->hijos->sig;//arranco de siguiente para que no me vuelva a guardar el mismo que puse como hijo del padre
  MTree temp=primerhijo;//indice para ir enlazando hermanos
  for(;indice!=NULL;indice=indice->sig){
    MTree nuevoHermano=malloc(sizeof(MTNodo));
    nuevoHermano->dato=((RTree)indice->dato)->dato;
    if(((RTree)(indice->dato))->hijos!=NULL){//si tengo que poner hijos tengo que hacer recursion
      convert_to_mtree_aux(((RTree)indice->dato)->hijos,nuevoHermano);
    }
    else nuevoHermano->son=NULL;

    temp->bro=nuevoHermano;
    temp=nuevoHermano;
    
  }
  temp->bro=NULL; //al ultimo hermano lo mando a NULL

  return raiz;
}

void visit_imprimir(void* arbol){
  printf("%d \n",((MTree)arbol)->dato);
}


int main() {
  RTree arbol=NULL;
  arbol=rtree_insertar(arbol,12);
  arbol=rtree_insertar(arbol,1);
  arbol=rtree_insertar(arbol,2);
  arbol=rtree_insertar(arbol,3);
  arbol->hijos->dato=rtree_insertar(arbol->hijos->dato,4);
  arbol->hijos->dato=rtree_insertar(arbol->hijos->dato,5);
  arbol->hijos->sig->dato=rtree_insertar(arbol->hijos->sig->dato,6);
	((RTree)arbol->hijos->dato)->hijos->dato=rtree_insertar(((RTree)arbol->hijos->dato)->hijos->dato,7);
	
	//printf("altura: %d, nelems: %d, contiene 5?: %d\n", rtree_altura(arbol), rtree_nelementos(arbol), rtree_contiene(arbol, 5));
  printf("altura: %d  \n", rtree_altura(arbol));
  rtree_recorrer(arbol,imprimir_dato_rtree);
  puts("");

  MTree marbol=mtree_crear();
  marbol=convert_to_mtree(arbol);
  /*arbol=mtree_agregar_n_hijo(arbol, 12,0);
  arbol=mtree_agregar_n_hijo(arbol, 1,1);
  arbol=mtree_agregar_n_hijo(arbol, 4,2);
  arbol=mtree_agregar_n_hijo(arbol, 7,3);
  arbol=mtree_agregar_n_hijo(arbol, 2,1);
  arbol=mtree_agregar_n_hijo(arbol, 3,2);
  arbol=mtree_agregar_n_hijo(arbol, 5,3);*/


  mtree_recorrer(marbol, visit_imprimir);
  puts("");

  printf("altura: %d  \n", mtree_altura(marbol));

  //printf("altura del arbol: %d",mtree_altura(arbol));

  //printf("test %d",arbol->son->son->son->dato);
  


  return 0;
}
