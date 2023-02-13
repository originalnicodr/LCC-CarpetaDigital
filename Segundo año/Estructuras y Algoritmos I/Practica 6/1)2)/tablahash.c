#include "tablahash.h"
#include <assert.h>
#include <stdlib.h>

/**
 * Crea una nueva tabla Hash vacía, con la capacidad dada.
 */
TablaHash* tablahash_crear(unsigned capacidad, FuncionHash hash, FuncionIgualdad comparador) {
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
  }

  return tabla;
}

/**
 * Inserta el dato en la tabla, asociado a la clave dada.
 */
void tablahash_insertar(TablaHash* tabla, void* clave, void* dato) {
  // Calculamos la posición de la clave dada, de acuerdo a la función hash.
  unsigned idx = tabla->hash(clave);
  idx = idx % tabla->capacidad; //y esto por que? por si se pasa del maximo y tiene que loopear (al parecer es posible para la tabla hash? por que el resultado de hash no necesariamente te da dentro de los
  //limites del rango, entonces va a ir loopeando hasta que caiga donde caiga)

  // Si el lugar estaba vacío, incrementamos el número de elementos.
  if (tabla->tabla[idx].clave == NULL)
    tabla->numElems++;

  // Almacenamos los datos ingresados.
  tabla->tabla[idx].clave = clave;
  tabla->tabla[idx].dato = dato;
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
  if (!tabla->comparador(tabla->tabla[idx].clave, clave))
    return NULL;

  return tabla->tabla[idx].dato;
}

/**
 * Elimina un elemento de la tabla.
 */
void tablahash_eliminar(TablaHash* tabla, void* clave) {
  // Calculamos la posición de la clave dada, de acuerdo a la función hash.
  unsigned idx = tabla->hash(clave);
  idx = idx % tabla->capacidad;

  // Si el lugar estaba ocupado, decrementamos el número de elementos.
  if (tabla->tabla[idx].clave != NULL)
    tabla->numElems--;

  // Vaciamos la casilla.
  tabla->tabla[idx].clave = NULL;//no seria mejor poner esto dentro del if?
  tabla->tabla[idx].dato = NULL;
}

/**
 * Destruye la tabla.
 */
void tablahash_destruir(TablaHash* tabla) {
  free(tabla->tabla);
  free(tabla);
}
