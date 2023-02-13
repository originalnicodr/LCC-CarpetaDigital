#include "slist.h"
#include <stdio.h>
#include <assert.h>

static void imprimir_entero(int dato) {
  printf("%d ", dato);
}

void slist_insertar(SList* lista, int dato, size_t pos){//pienso en la posicion desde el principio (0) hasta el final
    //assert(pos<lista->capacidad-lista->disponible) //algun modo de asegurarse que este dentro

    if(slist_vacia(lista)||(int)pos==0){
        slist_agregar_inicio(lista,dato); //si es vacia o se pasa lo agrega al final?
        return;
    }
    size_t selector=lista->primero;
    int i;
    SNodo* arr = lista->arr;
    for (i=0;i<(int)pos-1;i++){
        //printf("i=%d < pos=%d\n",i,pos-1);
        selector=arr[selector].sig; //quedo en el anterior al que quiero seleccionar
        printf("Parado en %d, el siguiente es %d\n",arr[selector].dato,arr[arr[selector].sig].dato);
    }

    size_t nuevoNodo = lista->disponible;
    arr[nuevoNodo].dato = dato;

    lista->disponible = arr[nuevoNodo].sig;
    arr[nuevoNodo].sig=arr[selector].sig;//el siguiente al que seleccionaste (osea el que hay que "reemplazar"
    arr[selector].sig=nuevoNodo;//linkeo el anterior al que agrego

}

int main(int argc, char *argv[]) {

  SList* lista = slist_crear(10);

  assert(slist_vacia(lista));
  assert(!slist_llena(lista));

  slist_agregar_inicio(lista, 6);
  slist_agregar_inicio(lista, 5);
  slist_agregar_inicio(lista, 3);
  slist_agregar_inicio(lista, 1);
  slist_agregar_inicio(lista, 2);

  slist_eliminar_inicio(lista);

  slist_agregar_final(lista, 7);

  slist_recorrer(lista, imprimir_entero);
  puts("");

  slist_insertar(lista,49,5);

  slist_recorrer(lista, imprimir_entero);
  puts("");
  //printf("capacidad: %d - primero: %d - disponible: %d\n",lista->capacidad,lista->primero,lista->disponible);


  slist_destruir(lista);

  return 0;
}
