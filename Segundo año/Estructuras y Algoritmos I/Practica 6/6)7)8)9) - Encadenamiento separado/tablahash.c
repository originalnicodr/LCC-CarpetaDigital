#include "tablahash.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/**
 * Crea una nueva tabla Hash vacía, con la capacidad dada.
 */
TablaHash* tablahash_crear(unsigned capacidad, FuncionHash hash, FuncionIgualdad comparador, float factorDeCarga) {
  assert(factorDeCarga>0&&factorDeCarga<=1);
  // Pedimos memoria para la estructura principal y las casillas.
  TablaHash* tabla = malloc(sizeof(TablaHash));
  tabla->hash = hash;
  tabla->capacidad = capacidad;
  tabla->tabla = malloc(sizeof(CasillaHash) * capacidad);
  tabla->numElems = 0;
  tabla->comparador=comparador;
  tabla->factorDeCarga=factorDeCarga;

  // Inicializamos las casillas con datos nulos.
  unsigned idx = 0;
  for (; idx < capacidad; ++idx) {
    tabla->tabla[idx] = NULL;
    /*tabla->tabla[idx].clave = NULL;
    tabla->tabla[idx].dato = NULL;
    tabla->tabla[idx].sig = NULL;*/
  }

  return tabla;
}

/**
 * Inserta el dato en la tabla, asociado a la clave dada.
 */
void tablahash_insertar(TablaHash* tabla, void* clave, void* dato) {

  if(tabla->numElems/tabla->capacidad>=tabla->factorDeCarga) tablahash_redimensionar(tabla);//me resulta raro que la pueda llamar

  // Calculamos la posición de la clave dada, de acuerdo a la función hash.
  unsigned idx = tabla->hash(clave);
  idx = idx % tabla->capacidad; //y esto por que? por si se pasa del maximo y tiene que loopear (al parecer es posible para la tabla hash? por que el resultado de hash no necesariamente te da dentro de los
  //limites del rango, entonces va a ir loopeando hasta que caiga donde caiga)

  tabla->numElems++; //el numero de elementos deberia incrementar tambien cuando agrego un dato en el area secundaria? si (no se va a llenar en estos casos)

  // Si el lugar estaba vacío, incrementamos el número de elementos.
  if (tabla->tabla[idx] == NULL){
    tabla->tabla[idx]=malloc(sizeof(struct _CasillaHash));
    tabla->tabla[idx]->clave = clave;
    tabla->tabla[idx]->dato = dato;
    return;
  }
  //si estoy aca se que al menos el primero esta ocupado
  CasillaHash indice=tabla->tabla[idx];

  //------------------------------------------------Si las claves son iguales no hacer malloc y pisar el dato

  for (;indice->sig!=NULL;indice=indice->sig); //me va a dar el ultimo casillero ocupado

  CasillaHash nuevaCasilla=malloc(sizeof(struct _CasillaHash));//revisar esto de aca abajo
  nuevaCasilla->dato=dato;
  nuevaCasilla->clave=clave;
  nuevaCasilla->sig=NULL;
  indice->sig=nuevaCasilla;

}

/**
 * Busca un elemento dado en la tabla, y retorna un puntero al mismo.
 * En caso de no existir, se retorna un puntero nulo.
 */
void* tablahash_buscar(TablaHash* tabla, void* clave) {
  // Calculamos la posición de la clave dada, de acuerdo a la función hash.
  unsigned idx = tabla->hash(clave);
  idx = idx % tabla->capacidad;

  // Si el lugar esta vacío, retornamos un puntero nulo.
  //if (tabla->tabla[idx].clave != clave)//en lugar de esto no podrias verificar si es null, o si el dato es null?
  CasillaHash indice=tabla->tabla[idx];

  for (;indice->clave!=NULL&&!tabla->comparador(indice->clave, clave)&&indice->sig!=NULL; indice=indice->sig);//itera mientras las claves sean diferentes o mientras no sea el ultimo, es decir va a largar el ultimo elemento de la lista o el que tiene la misma clave

  if(!tabla->comparador(indice->clave, clave)&&indice->sig==NULL){
    printf("No se encontro el dato con su respectiva clave\n");
    return NULL;
  }

  return indice->dato;
}

/**
 * Elimina un elemento de la tabla.
 */
void tablahash_eliminar(TablaHash* tabla, void* clave) {
  // Calculamos la posición de la clave dada, de acuerdo a la función hash.
  unsigned idx = tabla->hash(clave);
  idx = idx % tabla->capacidad;

  CasillaHash indice=tabla->tabla[idx];
  CasillaHash temp=tabla->tabla[idx];



  for (;indice->clave!=NULL&&!tabla->comparador(indice->clave, clave)&&indice->sig!=NULL; indice=indice->sig){//itera mientras las claves sean diferentes o mientras no sea el ultimo, es decir va a largar el ultimo elemento de la lista o el que tiene la misma clave
    temp=indice;//guardo el anterior al indice para reapuntar
  }

  if(!tabla->comparador(indice->clave, clave)&&indice->sig==NULL){//llego al final y la clave no es la buscada
    printf("No se encontro el dato con su respectiva clave\n");
    return;
  }

  //dos casos quedan, o no esta en el final y tiene la clave buscada o esta en el final y tiene la clave buscada

  tabla->numElems--;

  temp->sig=indice->sig;//quiero saltear el indice, pero si resulta que no se agrego ninguna casilla y temp=indice entonces no pasa nada

  free(indice);

  /*if(temp!=indice) free(indice);//si indice es una casilla agregada entonces para eliminarlo tendremos que hacer un free
  else{//si no se agrego nada entonces no hacemos free y eliminamos cambiando los datos a NULL
    free(indice);

    //indice->dato=NULL;
    //indice->clave=NULL;
  }*/
}

static void borrar_area(CasillaHash casilla){
  if(casilla==NULL) return;
  borrar_area(casilla->sig);
  free(casilla);//me tira error al querer liberar la casilla--------------------------------------------------------------------------------------------------------

}

/**
 * Destruye la tabla.
 */
void tablahash_destruir(TablaHash* tabla) {
  //tengo que pasar por toda la tabla revisando de que no haya una casilla extra a eliminar
  int i=0;
  for(;i<tabla->capacidad;i++){
    if(tabla->tabla[i]!=NULL) borrar_area(tabla->tabla[i]);
    /*if(tabla->tabla[i].sig!=NULL){//tiene casillas extra que eliminar

      CasillaHash *indice=tabla->tabla[i].sig;

      for(;indice!=NULL;){//revisar
        CasillaHash *temp=indice;
        free(temp);
        indice=indice->sig;
      }
    }*/
  }

  free(tabla->tabla);
  free(tabla);
}

void tablahash_redimensionar(TablaHash *tabla){//se rompe por la funcion borrar area secundaria, hay que arreglar eso y deberia andar
  //CasillaHash* temp=malloc(sizeof(CasillaHash)*tabla->numElems);

  TablaHash *th=tablahash_crear(tabla->capacidad*2, tabla->hash, tabla->comparador, tabla->factorDeCarga);

  int i=0; //n=0;
  for(;i<tabla->capacidad;i++){
    if(tabla->tabla[i]!=NULL){//verifico que haya un dato, me fijo si la clave es diferente a null o si el dato es diferente a null
        tablahash_insertar(th, tabla->tabla[i]->clave, tabla->tabla[i]->dato);

      CasillaHash indice=tabla->tabla[i]->sig;
      while(indice!=NULL){//si hay mas datos en el area secundaria los voy a ir agregando
        tablahash_insertar(th, indice->clave, indice->dato);

        indice=indice->sig;
      }
    }
  }

    //swapeo las tablas internas
    CasillaHash *temp=tabla->tabla;
    tabla->tabla=th->tabla;
    th->tabla=temp;

    tabla->capacidad=tabla->capacidad*2;
    th->capacidad=th->capacidad/2;

    tablahash_destruir(th);


}
