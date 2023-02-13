#include "tablahash.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

//Sera necesario diferenciar las casillas vacıas de las eliminadas. ? lo voy a identificar si la clave NO es igual a null? o el dato?

static int primo(int m){//devuelve 1 si es primo, 0 si no
  int i=1, flag=0;
  for(;i<=m;i++){
    if(m%i==0){
      flag=flag+1;
    }
  }
  if (flag==2) return 1;
  return 0;
}


/**
 * Crea una nueva tabla Hash vacía, con la capacidad dada.
 */
TablaHash* tablahash_crear(unsigned capacidad, FuncionHash hash, FuncionIgualdad comparador) {
  //assert(primo(capacidad));
  // Pedimos memoria para la estructura principal y las casillas.
  TablaHash* tabla = malloc(sizeof(TablaHash));
  tabla->hash = hash;
  tabla->capacidad = capacidad;
  tabla->tabla = malloc(sizeof(CasillaHash) * capacidad);
  tabla->numElems = 0;
  tabla->comparador=comparador;

  // Inicializamos las casillas con datos nulos.
  for (unsigned idx = 0; idx < capacidad; ++idx) {
    tabla->tabla[idx].clave = NULL;
    tabla->tabla[idx].dato = NULL;
    tabla->tabla[idx].eliminado = 0;
  }

  return tabla;
}

/**
 * Inserta el dato en la tabla, asociado a la clave dada.
 */
void tablahash_insertar(TablaHash* tabla, void* clave, void* dato) {//me tira error al intentar acceser al campo .eliminado
  if(tabla->numElems==tabla->capacidad){
    printf("La tabla esta llena\n");
    return;
  }

  // Calculamos la posición de la clave dada, de acuerdo a la función hash.
  unsigned idx = tabla->hash(clave);
  idx = idx % tabla->capacidad; //y esto por que? por si se pasa del maximo y tiene que loopear (al parecer es posible para la tabla hash? por que el resultado de hash no necesariamente te da dentro de los
  //limites del rango, entonces va a ir loopeando hasta que caiga donde caiga)

  // Si el lugar estaba vacío, incrementamos el número de elementos.
  //if (tabla->tabla[idx].clave == NULL)
    //tabla->numElems++;

  //while(idx+i<tabla->capacidad && tabla->tabla[idx+i].sig != NULL){//esta ocupado y estas dentro de la capacidad (lo de la capacidad es para que no se me rompa)
  while ((tabla->tabla[idx].eliminado==0)&&(tabla->tabla[idx].dato!=NULL)){//vamos a encontrar el lugar que tengamos libre
    //idx= (idx+1)% tabla->capacidad;
    idx=1+(idx%(tabla->capacidad-1));
  }

  tabla->numElems++;
  tabla->tabla[idx].clave = clave;
  tabla->tabla[idx].dato = dato;
  tabla->tabla[idx].eliminado=0;

}

/**
 * Busca un elemento dado en la tabla, y retorna un puntero al mismo.
 * En caso de no existir, se retorna un puntero nulo.
 */
void* tablahash_buscar(TablaHash* tabla, void* clave) {//fijarse que estandar tomamos para la eliminacion
  // Calculamos la posición de la clave dada, de acuerdo a la función hash.
  unsigned idx = tabla->hash(clave);
  idx = idx % tabla->capacidad;
  unsigned inicial=idx;

  int registro=-1;//-1 que no se uso, -2 que ya se uso

  if (((tabla->tabla[idx].dato!=NULL)&&(tabla->tabla[idx].clave!=clave))||(tabla->tabla[idx].eliminado==1)) {
	  //Hay un dato con otra clave o hubo un dato eliminado, ahora debería recorrer el arreglo hasta encontrar el dato
      //Es necesario ver si el dato es null, si el dato es null la clave no sería null, ya que en insertar se le asigna dato y clave
      //y en eliminar no se tocan dato y clave, solo se cambia eliminado?
    if((tabla->tabla[idx].eliminado==1)&&(registro==-1)){//habia un dato eliminado
      registro=idx;
    }

    idx= (idx+1)% tabla->capacidad; //un primer if para que el while de abajo no se me salga por ser idx==incial
  }

  if((registro!=-1)&&(registro!=-2)&&(tabla->comparador(tabla->tabla[idx].clave, clave))){//este estaba aparte por que el primer idx va a ser el inicial y se saldria en el while que sigue
    tabla->tabla[registro].dato=tabla->tabla[idx].dato;
    tabla->tabla[registro].clave=tabla->tabla[idx].clave;
    tabla->tabla[registro].eliminado==0;
    tabla->tabla[idx].eliminado==1;
    registro=-2;//ya se uso
  }

  while ((((tabla->tabla[idx].dato!=NULL)&&(tabla->tabla[idx].clave!=clave))||(tabla->tabla[idx].eliminado==1))&&(idx!=inicial)){//!tabla->comparador(tabla->tabla[idx].clave, clave)
    if((registro!=-1)&&(registro!=-2)&&(tabla->comparador(tabla->tabla[idx].clave, clave))){
      tabla->tabla[registro].dato=tabla->tabla[idx].dato;
      tabla->tabla[registro].clave=tabla->tabla[idx].clave;
      tabla->tabla[registro].eliminado==0;
      tabla->tabla[idx].eliminado==1;
      registro=-2;//ya se uso
    }

    if((tabla->tabla[idx].eliminado==1)&&(registro==-1)){
      registro=idx;
    }
    //idx= (idx+1)% tabla->capacidad;
    idx=(1+idx%(tabla->capacidad-1));//Why?
  }

  if((tabla->tabla[idx].eliminado==1)||(tabla->tabla[idx].dato==NULL)||(tabla->tabla[idx].clave!=clave)){//loopeo o llego al final de un cluster (!tabla->comparador(tabla->tabla[idx].clave,clave)
    printf("No encontro el dato con la clave dada\n");
    return NULL;
  }

  if(tabla->comparador(tabla->tabla[idx].clave,clave)) return tabla->tabla[idx].dato;

}

void* tablahash_buscar_fer(TablaHash* tabla, void* clave){//tengo que devolver el dato o la casilla?
	// Calculamos la posición de la clave dada, de acuerdo a la función hash.
  unsigned idx = tabla->hash(clave);
  idx = idx % tabla->capacidad;
  unsigned inicial=idx;
  CasillaHash aux;


  for(;(!((idx+1)%tabla->capacidad==inicial))||(tabla->tabla[idx].clave!=clave)||(tabla->tabla[idx].eliminado==1);idx=(idx+1)%tabla->capacidad);
  if(tabla->tabla[idx].eliminado==1){//Encontré una casilla eliminada
	  aux=tabla->tabla[idx];
	  for(;((idx+1)%tabla->capacidad==inicial)||(tabla->tabla[idx].clave!=clave);idx=(idx+1)%tabla->capacidad);//sigo buscando la clave
	  if(tabla->comparador(tabla->tabla[idx].clave, clave)&&tabla->tabla[idx].eliminado==0){//encontré la clave y verifico que no halla sido eliminada
		  //me cambia la tabla? o debería guardar el indice en un aux?
		  //qué tengo que hacer con la casilla de la cual copio los datos?
		  aux.clave=tabla->tabla[idx].clave;
		  aux.dato=tabla->tabla[idx].dato;
		  aux.eliminado==0;
      tabla->tabla[idx].eliminado=1;
		  return aux.dato;
	  }
	  else{//no encontré la clave o estaba en una casilla eliminada
		  printf("No encontro el dato con la clave dada\n");
		  return NULL;//no encontré la clave o estaba en una casilla eliminada
	  }
  }
  else{//no me tope con una casilla eliminada
	  if(tabla->comparador(tabla->tabla[idx].clave, clave)&&tabla->tabla[idx].eliminado==0) return tabla->tabla[idx].dato;//encontré la clave y verifico que no halla sido eliminada
	  else{//no encontré la clave o estaba en una casilla eliminada
		  printf("No encontro el dato con la clave dada\n");
		  return NULL;//no encontré la clave o estaba en una casilla eliminada
	  }
  }

}



/**
 * Elimina un elemento de la tabla.
 */
void tablahash_eliminar(TablaHash* tabla, void* clave) {//fijarse que estandar tomamos para la eliminacion
  // Calculamos la posición de la clave dada, de acuerdo a la función hash.
  /** No se puede usar la función de buscar para encontrar el dato a eliminar?*/
  unsigned idx = tabla->hash(clave);
  idx = idx % tabla->capacidad;
  unsigned inicial=idx;

  if (((tabla->tabla[idx].dato!=NULL)&&(tabla->tabla[idx].clave!=clave))||(tabla->tabla[idx].eliminado==1)) {
    idx= (idx+1)% tabla->capacidad; //un primer if para que el while de abajo no se me salga por ser idx==incial
  }

  while ((((tabla->tabla[idx].dato!=NULL)&&(!tabla->comparador(tabla->tabla[idx].clave,clave)))||(tabla->tabla[idx].eliminado==1))&&(idx!=inicial)){//!tabla->comparador(tabla->tabla[idx].clave, clave)
    idx= (idx+1)% tabla->capacidad;
  }

  if((tabla->tabla[idx].eliminado==1)||(tabla->tabla[idx].dato==NULL)||(tabla->tabla[idx].clave!=clave)){//loopeo o llego al final de un cluster
    printf("No encontro el dato con la clave dada\n");
  }

  if(tabla->comparador(tabla->tabla[idx].clave,clave)&&(tabla->tabla[idx].eliminado==0)){//Aca recién elimina el dato
    tabla->tabla[idx].eliminado=1;
    tabla->numElems--;
    //No hay que liberar tabla.dato????
  }

}

/**
 * Destruye la tabla.
 */
void tablahash_destruir(TablaHash* tabla) {
  free(tabla->tabla);
  free(tabla);
}
