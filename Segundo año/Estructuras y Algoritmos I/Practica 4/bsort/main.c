#include <stdio.h>
#include "bsort.h"
#include "slist.h"
#include "malloc.h"

#define NELEMS(a) (sizeof((a))/sizeof(int))

typedef int *ARR;

static void swap(int *p, int *q) {
  int t = *p;
  *p = *q;
  *q = t;
}

/*void mostrar_arr(int arr[], int tam){
  int i;
  for (i  = 0; i < tam; ++i)
    printf("%d ", arr[i]);
  puts("");
  return;
}*/

//selection sort: selecciona el menor

void ssort(int arr[], int tam){
  int n=0;
  for(;n<tam-1;n++){
    int i=n+1,j=n;//j sera mi minimo inicial
    for(;i<tam;i++){//i++ = ++i
      if(arr[i]<arr[j]){
        j=i;//guardo la posicion de donde esta el nuevo minimo
      }
    }
    swap(&arr[n],&arr[j]);
    
    int indice;
    for (indice  = 0; indice < tam; ++indice)
      printf("%d ", arr[indice]);
    puts("");

  }
  return;
}

int es_permutacion(int a[], int b[], int tam){//falta ver si se puede hacer mejor
  int i=0;
  int controla, controlb;
  for(;i<tam;i++){//a
    controla=0; //reset
    controlb=0;

    int t=0;
    for(;t<tam;t++){
      if(a[t]==a[i]) controla++;//minimo una vez, cuando i=t
    }
    int j=0;
    for(;j<tam;j++){//b
      if (a[i]==b[j]) controlb++;
    }
    if (controla!=controlb) return 0; //no encontro ese elemento la misma cantidad de veces
  }
  return 1;
}

//insertion sort: inserta el elemento en la parte que voy ordenando

void isort(int arr[], int tam){
  int i=0;//capaz que arranque en 1
  for(;i<tam;i++){
    int j=0;
    for(;j<i;j++){
      if(arr[j]>arr[i]){//si el elemento que estamos verificando es menor al de la posicion que estamos revisando, lo mete ahi
        int k=i;
        int temp=arr[i];
        for(;k>j;k--){
          arr[k]=arr[k-1];
        }
        arr[j]=temp;
        break; //me tengo que fijar si termina el for o el if, sino le pongo j=i y listo
      }
    }
  }
  return;
}

SList ssortl(SList l){
  if(l==NULL) return l;
  if(l->sig==NULL) return l; //llego al final de la lista

  SNodo* menor = l, *antMenor=NULL; //tomo el primer nodo como mi menor inicial

  SNodo* n=l;
  for(; n->sig != NULL; n=n->sig)
  {
    if(n->sig->dato < menor->dato){
      menor= n->sig;
      antMenor=n;//voy a tener el nodo anterior al que voy a cambiar para cuando lo cambie, apuntar a otro lado
    }
  }
  if(antMenor==NULL){
    menor->sig = ssortl(menor->sig);//no necesite reacomodar nada, sigo tranquilo
  }
  else{
    antMenor->sig=menor->sig;
    menor->sig=ssortl(l);
  }
  return menor;
}

static void imprimir_entero(int dato) {
  printf("%d ", dato);
}



void bsort2(int datos[], int tam) {//ordena de menor a mayor
  int i;

  for (i = 0; i < tam - 1; ++i)
    if (datos[i] > datos[i + 1]) {
      swap(&datos[i], &datos[i + 1]);
      i=-1;//si hago un cambiazo, tengo que reiniciar la verificacion
    }
}

//el minimo numero de veces que debe iterarse en el for es la longitud de la lista

/*void ssortg(void *base, int tam, size_t size, CmpFunc cmp){
  size_t n=0;
  for(;n<(tam-1)*size;n=n+size){//size=largo de cada lugar
    size_t i=n+size,j=n;//j sera mi minimo inicial
    for(;i<tam*size;i=i+size){//i++ = ++i
      if(cmp(&base[i],&base[j])){ 
        j=i;//guardo la posicion de donde esta el nuevo minimo
      }
    }
    swap(&base[i],&base[j]);
    
    //size indice;
    //for (indice  = 0; indice < tam; ++indice)
    //  printf("%d ", arr[indice]);
    //puts("");

  }
  return;
}

void bsortg(void *base, int tam, size_t size, CmpFunc cmp) {//ordena de menor a mayor
  int ordenado = 0;
  size_t i;
  while (!ordenado) {
    ordenado = 1;
    for (i = 0; i < (tam - 1)*size; i=i+size)
      if (cmp(&base[i],&base[i + size])) {
        ordenado = 0;
        swap(&base[i], &base[i + size]);
      }
  }
}

void isortg(void *base, int tam, size_t size, CmpFunc cmp){
  size_t i=0;//capaz que arranque en 1
  for(;i<tam*size;i=i+size){
    size_t j=0;
    for(;j<i;j=j+size){
      if(cmp(&base[j],&base[i])){//si el elemento que estamos verificando es menor al de la posicion que estamos revisando, lo mete ahi
        size_t k=i;
        //size_t* temp=&base[i];
        for(;k>j;k=k-size){
          base[k]=base[k-size];
        }
        //base[j]=*temp;
        base[j]=base[i];
        break; //me tengo que fijar si termina el for o el if, sino le pongo j=i y listo
      }
    }
  }
  return;
}*/

void bsortg(void *base, int tam, size_t size, CmpFunc cmp)
{
    int ordenado = 0, i;
    while(!ordenado)
    {
        ordenado = 1;
        for(i = 0; i < tam - 1; ++i)
            if(cmp(base + i * size, base + i * size + 1 * size))
            {
                ordenado = 0;
                swap((base + i * size), (base + i * size + 1 * size));
            }
    }
}

int menor(void* a, void* b){
  return *(int*)a<*(int*)b;
}

//ej 10)

int longitud (SList l){
  SNodo* n;
  int cont=0;
  for(n=l;n!=NULL;n=n->sig){
    cont++;
  }
  return cont;    
}

void particionar (SList l, SList* res1, SList* res2){
  int nelems=(int)(longitud(l)/2);
  //res1=malloc(sizeof(SList));
  //res2=malloc(sizeof(SList));
  //res1=&l;
  SNodo* n=l;
  int i=0;
  for(;i<nelems;i++){
        *res1=slist_agregar_final(*res1,n->dato);//if(cont+1==nelems) res2=&n->sig;
        n= n->sig;
  }
  i++;
  for(;n!=NULL;n=n->sig){
    *res2=slist_agregar_final(*res2,n->dato);
  }
}

SList fusionar(SList l1, SList l2){
  SNodo* n=l1;
  for(;n->sig!=NULL;n=n->sig);
  n->sig=l2;
  return l1;
}

SList fusionaralt(SList l1, SList l2){//funca bien parece
  SList lr=slist_crear();
  lr=malloc(sizeof(SNodo));//es necesario el malloc?


  if(l1->dato<l2->dato){//en lugar de lr usar indice?
      lr=l1;
      l1=l1->sig;//ya guarde el nodo este, ahora avanzo
  }
  else{
      lr=l2;
      l2=l2->sig;//ya guarde el nodo este, ahora avanzo
  }

  SNodo* indice=lr;

  while ((l1!=NULL)&&(l2!=NULL)){
    if(l1->dato<l2->dato){
      indice->sig=l1;
      indice=indice->sig;
      l1=l1->sig;//ya guarde el nodo este, ahora avanzo
    }
    else{
      indice->sig=l2;
      indice=indice->sig;
      l2=l2->sig;//ya guarde el nodo este, ahora avanzo
    }
  }//si salio del while, es por que l1 o l2 llego al final

  if(l1==NULL){//se podrian sacar los if y dejar solo los for?
    for(;l2!=NULL;l2=l2->sig){
      indice->sig=l2;
      indice=indice->sig;
    }
  }
  else if (l2==NULL){
    for(;l1!=NULL;l1=l1->sig){
      indice->sig=l1;
      indice=indice->sig;
    }
  }
  return lr;
}

SList msortl (SList lista){
  if (longitud(lista)==1) return lista;//ya no la puedo ordenar ams
  if (longitud(lista)==2){//caso de llegar a dos elementos
    if(lista->sig->dato<lista->dato){

      //reacomodo, si anda mal revisar esto

      lista->sig->sig=lista;
      lista=lista->sig;
      lista->sig->sig=NULL;

      return lista;
    }
    else return lista; //ya estaba ordenada
  }

  //No llego a los casos base, vamos a seguir separandola entonces

  SList *res1=NULL, *res2=NULL;
  res1=malloc(sizeof(SList));
  res2=malloc(sizeof(SList));
  particionar(lista, res1, res2);
  return fusionaralt(msortl(*res1),msortl(*res2));

}

int cantelems(int* arr[]){
  int i=0;
  for(;arr[i]!='\0';i++);
  return i;
}



void imprimir_arreglo(ARR arr, int tam){
	for(int i = 0; i<tam; i++){
		printf("%d ",arr[i]);
	}
	printf("\n\n");
}

void particionar_arreglo (ARR arr, int tam, ARR *res1, ARR *res2){
	int tamI = tam/2;//trunca
	int tamD = tam - tamI;
	*res1 = malloc(sizeof(int) * tamI);
	*res2 = malloc(sizeof(int) * tamD);
	for(int i = 0; i<tamI; i++) {
		(*res1)[i] = arr[i];
	}
	for(int j = tamI; j<tam; j++){
		(*res2)[j-tamI] = arr[j]; 
	}
	
}

ARR fusionar_arreglo(ARR arreglo1,int longArr1, ARR arreglo2, int longArr2){
	int longTotal = longArr1 + longArr2;
	if(longTotal == 0){
		return NULL;
	}
	else{
		if(longTotal == 1){
			if((longArr1 == 1) && (longArr2 == 0)){
				return arreglo1;
			}
			else{
				return arreglo2;
			}
		}
		else{
			// 
			ARR arregloResultado = malloc(sizeof(int) * longTotal);
			int idI = 0, idD = 0, indice = 0;
			while((idI < longArr1) || (idD < longArr2)){
				if(!(idI < longArr1)){
					// Copio todo lo del arr2. idD++
					arregloResultado[indice] = arreglo2[idD];
					idD++;
					indice++;
				}
				else{
					if(!(idD < longArr2)){
						// Copio todo lo del arr1. idI++
						arregloResultado[indice] = arreglo1[idI];
						idI++;
						indice++;
					}
					else{
						// Comparo y aumento el caso que es menor.
						if(arreglo1[idI] < arreglo2[idD]){
							arregloResultado[indice] = arreglo1[idI];
							idI++;
							indice++;
						}
						else{
							arregloResultado[indice] = arreglo2[idD];
							idD++;
							indice++;
						}
					}
				}
			}
			return arregloResultado;
		}
	}
}


ARR msort (ARR arreglo, int tam){
	if(tam == 0){
		printf("El arreglo esta vacio. \n");
		return NULL;
	}
	else{
		if(tam == 1){
			return arreglo;
		}
		else{
			int tamI = tam/2;
			int tamD = tam - tamI;
			
			ARR izq, der;
			particionar_arreglo(arreglo, tam , &izq, &der);
			izq = msort(izq, tamI);
			der = msort(der, tamD);
			arreglo = fusionar_arreglo(izq, tamI, der, tamD);

      //free(izq);
      //free(der);
			return arreglo;
		}
	}
	
}



int main(void) {
  /*int arr1[] = { 2, 4, 1, 3, 7, 8, 6 };
  int arr2[] = { 2, 4, 1, 7, 7, 8, 3 };
  int i;

  //bsort(arr, NELEMS(arr));
  //ssort(arr,NELEMS(arr));
  //bsort2(arr1, NELEMS(arr1));
  isort(arr1, NELEMS(arr1));

  for (i  = 0; i < NELEMS(arr1); ++i)
    printf("%d ", arr1[i]);
  puts("");*/
  
 /* int arr1[] = { 2, 4, 1, 3, 7, 8, 6 };
  int arr2[] = { 2, 4, 1, 7, 7, 8, 3 };
  int i;

  //bsort(arr, NELEMS(arr));
  //ssort(arr,NELEMS(arr));
  //bsort2(arr1, NELEMS(arr1));
  isortg(arr1, 7, sizeof(int), menor);

  for (i  = 0; i < NELEMS(arr1); ++i)
    printf("%d ", arr1[i]);
  puts("");

  //printf("Es arr1 permutacion de arr2? %d",es_permutacion(arr1, arr2, NELEMS(arr1)));
 */ 

  SList lista=slist_crear();
  lista=slist_agregar_inicio(lista, 6);
  lista=slist_agregar_inicio(lista, 8);
  lista=slist_agregar_inicio(lista, 7);
  lista=slist_agregar_inicio(lista, 3);
  lista=slist_agregar_inicio(lista, 1);
  lista=slist_agregar_inicio(lista, 4);
  lista=slist_agregar_inicio(lista, 2);

  slist_recorrer(lista,imprimir_entero);

  puts("");

  //slist_recorrer(msortl(lista),imprimir_entero);

  /*SList lista2=slist_crear();
  lista2=slist_agregar_inicio(lista2, 13);
  lista2=slist_agregar_inicio(lista2, 17);
  lista2=slist_agregar_inicio(lista2, 12);
  lista2=slist_agregar_inicio(lista2, 0);
  lista2=slist_agregar_inicio(lista2, 5);

  slist_recorrer(lista2,imprimir_entero);

  puts("");

  slist_recorrer(fusionaralt(lista,lista2),imprimir_entero);*/

  /*puts("");
  SList res1=slist_crear(), res2=slist_crear();
  particionar(lista, &res1, &res2);
  slist_recorrer(res1,imprimir_entero);
  puts("");
  slist_recorrer(res2,imprimir_entero);
  puts("");
  SList listaU=fusionaralt(res1, res2);
  slist_recorrer(listaU,imprimir_entero);
  puts("");*/

  lista=ssortl(lista);

  slist_recorrer(lista,imprimir_entero);

  slist_destruir(lista);
  return 0;
}
