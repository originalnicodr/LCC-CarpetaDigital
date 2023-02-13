#include <stdio.h>
#include <stdlib.h>
#include "glist.c"
#include <malloc.h>

RTree rtree_insertar(RTree arbol, int dato){
  RTree nuevoNodo;
  nuevoNodo=malloc(sizeof(RTNodo));
  nuevoNodo->dato=dato;
  GList lista=glist_crear();
  nuevoNodo->hijos=lista;

  if(arbol==NULL){
    return nuevoNodo;
  }
  glist_agregar_final(arbol->hijos, nuevoNodo);
  return arbol;
}

RTree rtree_eliminar(RTree arbol, int dato, RTree padre){//vamos a convertir sus hijos en sus hermanos
  if(arbol==NULL){
    printf("No se encontro el dato\n");
    return arbol;
  }
  if(arbol->dato==dato&&padre==NULL){//si tenemos que eliminar la raiz ponemos al primer hijo como nueva raiz
    RTree B=arbol->hijos->dato;
    GList temp=arbol->hijos;
    arbol->hijos=arbol->hijos->sig;//saco el nodo B de la lista
    free(temp);//free del primer lugar de la lista

    glist_concatenar(B->hijos,arbol->hijos);//agrego los hermanos de B como si fueran los hijos
    glist_destruir(arbol->hijos);//creo que me hace free de todos los RTNodo
    free(arbol);//el RTNodo que voy a eliminar
    return B;
  }

  //hacemos caso de raiz que sea el normal o subimos todos los hijos un nivel?

  GList indice=arbol->hijos;
  for (;indice!=NULL;indice=indice->sig){//recursion
    rtree_eliminar(indice->dato, dato, arbol);
  }
}

int rtree_contiene(RTree arbol, int dato){
  if(arbol==NULL||(arbol->hijos==NULL&&arbol->dato!=dato)) return 0;//no lo encontre en esta rama
  if(arbol->dato==dato) return 1;

  GList indice=arbol->hijos;
  int cont=0;
  for(;indice!=NULL;indice=indice->sig){//recursion
    cont+=rtree_contiene(indice->dato,dato);//voy sumando, si no los encontro en todos los indices, entonces dara cero, si esta dara 1;
  }
  return cont;
}

int rtree_nelementos(RTree arbol){
  if(arbol==NULL) return 0;
  if(arbol->hijos==NULL) return 1; //no tiene hijos

  int cont=0;
  GList indice=arbol->hijos;
  for(;indice!=NULL;indice=indice->sig){//recursion
    cont+=rtree_nelementos(indice->dato);//sumo la cantidad de elementos que tiene ese arbol
  }
  return cont;
}

int rtree_altura_aux(RTree arbol,int alturamax){
  if(arbol==NULL) return -1;
  if(arbol->hijos==NULL) return alturamax; //no tiene hijos

  GList indice=arbol->hijos;
  int temp=rtree_altura_aux(indice->dato,alturamax++);//inicial para comparar
  for(indice=indice->sig;indice!=NULL;indice=indice->sig){//el primer indice=indice->sig es para avanzar uno y comparar con el temp inicial
    if(temp<rtree_altura_aux(indice->dato,alturamax++)) temp=rtree_altura_aux(indice->dato,alturamax++);//nuevo maximo
  }
  return temp;
}

int rtree_altura(RTree arbol){
  return rtree_altura_aux(arbol, 0);
}

void rtree_recorrer(RTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitante visit){

}




MTree mtree_crear(){
  return NULL;
}

void mtree_destruir(MTree arbol){
  if(arbol==NULL) return;
  
  if(arbol->bro!=NULL) mtree_destruir(arbol->bro);
  if(arbol->son!=NULL) mtree_destruir(arbol->son);
  free(arbol);
  return;
}

//que dado un dato, agregue una nodo hijo en la posicion indicada. Si la posicion recibida es mayor al numero de hijos,
//procure que el nuevo nodo hijo se agregue al final. Que carajos es el final? como hermano del ultimo hijo o que onda?
MTree mtree_agregar_n_hijo(MTree arbol, int dato, int pos){

}

void mtree_recorrer(MTree arbol, FuncionVisitante visit){//estoy haciendo preorder
  if(arbol==NULL) return;
  visit(arbol);
  if(arbol->son!=NULL) mtree_recorrer(arbol->son, visit);//paso por todos los hermanos, si intercambio estas dos lineas me queda escrito A, B, C como en el ejercicio
  if(arbol->bro!=NULL) mtree_recorrer(arbol->bro, visit);//paso por los hijos
}

void mtree_recorrer_extra(MTree arbol, FuncionVisitanteExtra visit, void* extra){
  if(arbol==NULL) return;
  visit(arbol, extra);
  if(arbol->son!=NULL) mtree_recorrer_extra(arbol->son, visit, extra);//paso por todos los hermanos, si intercambio estas dos lineas me queda escrito A, B, C como en el ejercicio
  if(arbol->bro!=NULL) mtree_recorrer_extra(arbol->bro, visit, extra);//paso por los hijos
}


void visit_contar (int dato, void *contador){
	*(int*)contador=*(int*)contador+1;
}

int mtree_nelems(MTree raiz){
	int contador=0;
	mtree_recorrer_extra(raiz,visit_contar, &contador);
	return contador;
}

int mtree_altura(MTree raiz){

}

MTree convert_to_mtree(RTree arbol){

}

int main() {
  RTree arbol=rtree_insertar(arbol,12);
  arbol=rtree_insertar(arbol,1);
  arbol=rtree_insertar(arbol,2);
  arbol=rtree_insertar(arbol,3);
  arbol=rtree_insertar(arbol->hijos->dato,4);
  arbol=rtree_insertar(arbol->hijos->dato,5);
  arbol=rtree_insertar(arbol->hijos->sig->dato,6);
  //arbol=rtree_insertar(arbol->hijos->dato->hijos->dato,7);
  return 0;
}
