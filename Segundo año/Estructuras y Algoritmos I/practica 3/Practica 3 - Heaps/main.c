#include <stdio.h>
#include <stdlib.h>
#include "slist.h"
#include "glist.h"
#include <malloc.h>
#include <assert.h>

#define MAX_COLAP 7


//#define MAX_HEAP 7

static void swap(int *p, int *q) {
  int t = *p;
  *p = *q;
  *q = t;
}

static void imprimir_entero(int dato){
  printf("%d\n", dato);
}

static int igualdad_func(int dato1, int dato2){
	if(dato1-2 == dato2){
		return 1;
	}
	return 0;
}



Cola cola_crear(){
	Cola a=malloc(sizeof(struct _Cola));
	a->primero=-1;
	a->ultimo=-1;
	return a;
}

int cola_es_vacia(Cola a){
	return !a||a->primero==-1;
}

void cola_encolar(Cola c, int dato){
	if(c==NULL)	c=cola_crear();
	if(cola_es_vacia(c)){
		c->primero=0;
		c->datos[c->primero]=dato;
		c->ultimo=1;
		return;
	}
	if(c->primero!=c->ultimo){
		c->datos[c->ultimo]=dato;
		c->ultimo=(c->ultimo+1)%MAX_COLA;//resto te "resetea" a 0 cuando llega al final del arreglo
		printf("La posicion del ultimo es: %d\n",c->ultimo);
	} else printf("La cola esta llena\n");
	return;
}

void cola_desencolar(Cola c){
	if(cola_es_vacia(c)) return;
	int pos=c->primero;
	c->primero=(c->primero+1)%MAX_COLA;
	if(c->primero==c->ultimo) c->primero=-1;
	return;
}

int cola_primero(Cola c){
	return c->datos[c->primero];
}

void cola_imprimir(Cola c){
	if(cola_es_vacia(c)){
		printf("La cola esta vacia\n");
	}
	int i=c->primero;
	printf("%d\n",c->datos[i]);//se hace la primera iteracion afuera por que si esta llena no nos va a imprimir nada, ya que el primero va a ser igual al ultimo
	i=(i+1)%MAX_COLA;

	for(;i!=c->ultimo;i=(i+1)%MAX_COLA){
		printf("%d\n",c->datos[i]);
	}
	return;
}

void cola_destruir(Cola c){
	free(c);
}

Colas colas_crear(){
	Colas c=malloc(sizeof(struct _Colas));
	c->primero=NULL;
	c->ultimo=NULL;
	return c;
}

int colas_es_vacia(Colas c){
	return slist_vacia(c->primero)&&slist_vacia(c->ultimo);
}

int colas_primero(Colas c){
	return c->primero->dato;
}

void colas_encolar(Colas c, int dato){
	//slist_agregar_final(c->primero);
	if(colas_es_vacia(c)){
		c->primero=slist_agregar_inicio(c->primero,dato);
		c->ultimo=c->primero;
		return;
	}
	//slist_agregar_final(c->ultimo, dato);
	slist_agregar_final(c->primero,dato);///no faltaria hacer c->ultimo=c->ultimo->sig?
	return;
}

void colas_desencolar(Colas c){
	if(colas_es_vacia(c)){
		printf("La cola estaba vacia\n");
		return;
	}
	SNodo* temp;
	temp=c->primero;
	c->primero=c->primero->sig;//que pasa si solo queda un elemento? en el caso que se vuelva vacio habria que mandarlo a null?
	free(temp);
}

void colas_imprimir(Colas c){
	slist_recorrer(c->primero, imprimir_entero);
	return;
}

void colas_destruir(Colas c){
	slist_destruir(c->primero);
	//slist_destruir(c->ultimo);
	free(c);
	return;
}

BHeap bheap_crear(){
    BHeap h=malloc(sizeof(struct _BHeap));
    h->nelems=0;
    return h;
}

int bheap_es_vacio(BHeap h){
    return !h||h->nelems==0;
}

int bheap_minimo(BHeap h){
    assert(!bheap_es_vacio(h));
    return h->datos[0];
}

int min(int x, int y){
    if(x>y) return y;
    return x;
}

void bheap_eliminar_minimo(BHeap h){
    if(bheap_es_vacio(h)){
        printf("La lista esta vacia, no hay minimo\n");
        return;
    }
    h->nelems--; //le vamos a sacar un elemento, sirve tambien para manejar la posicion del ultimo elemento
    h->datos[0]=h->datos[h->nelems];//guarda el ultimo en la raiz
    int pos=0;
    for(;pos<h->nelems;){
        if(2*pos+1>h->nelems-1) return;//si no tiene mas hijos
        if(2*pos+2>h->nelems-1){//si no tiene segundo hijo
            if(h->datos[pos]>h->datos[2*pos+1]){//si el primero es menor que el padre
                int n=h->datos[pos];
                h->datos[pos]=h->datos[2*pos+1];
                h->datos[2*pos+1]=n;

				pos=2*pos+1;
                //se podria poner un return
            }
            else return;
        }
        else if(h->datos[pos]>h->datos[2*pos+1]||h->datos[pos]>h->datos[2*pos+2]){
            if(h->datos[2*pos+1]<h->datos[2*pos+2]){
                int n=h->datos[pos];
                h->datos[pos]=h->datos[2*pos+1];
                h->datos[2*pos+1]=n;

				pos=2*pos+1;
            }
            else{
                int n=h->datos[pos];
                h->datos[pos]=h->datos[2*pos+2];
                h->datos[2*pos+2]=n;

				pos=2*pos+2;
            }
        }
        else return; //los dos hijos son mayores al padre
    }
}

void bheap_insertar(BHeap h, int dato){
    if(h->nelems==MAX_HEAP){//se puede cambiar por la longitud del array en lugar de la constante? para que solo este declarada en el header
        printf("El heap esta lleno\n");
        return;
    }
    h->datos[h->nelems]=dato;//el lugar que tengo libre
    h->nelems++;
	int pos=h->nelems-1;
	for(;pos>0;){//h->nelems-1 donde meti el elemento
		if(pos==0) return; //no pongo bheap_es_vacio(h) por que estoy sumando a nelems antes //no hay nada en la raiz, no hay nada para comparar //no deberia ni entrar
		if(((pos)-1)/2==(int)((pos)-1)/2){//si el resultado es entero, es decir si es el primer hijo (distincion si es la raiz?)
			if( h->datos[((pos)-1)/2] > h->datos[pos]){//si el elemento agregado es menor al padre
				int n=h->datos[pos];
				h->datos[pos]=h->datos[((pos)-1)/2];
				h->datos[((pos)-1)/2]=n;
				pos=(pos-1)/2;
			}
			else return; //si el elemento es menor al padre esta bien ordenado
		}
		else if(((pos)-2)/2==(int)((pos)-2)/2){//Es necesario fijarte que sea hijo del segundo? con un else no basta?
				if( h->datos[((pos)-2)/2] > h->datos[pos]){//si el elemento agregado es menor al padre
					int n=h->datos[pos];
					h->datos[pos]=h->datos[((pos)-2)/2];
					h->datos[((pos)-2)/2]=n;
					pos=(pos-2)/2;
				}
				else return; //si el elemento es menor al padre esta bien ordenado
		}
	}
	return;
}

int aux(int n, int i){
	if(i==0) return 1;
	int cont=0;
	int acumulador=1;
	for(;cont<i;cont++){
		acumulador=acumulador*n;
	}
	return acumulador+aux(n,i-1);
}

void bheap_imprimir(BHeap h){
	int i=0;
	int n=0;
	for(;i<h->nelems;i++){
		printf("%d ",h->datos[i]);
		if(i+1==aux(2,n)){
			printf("\n");
			n++;
		}
	}
}

void bheap_destruir(BHeap h){
	free(h);
	return;
}
    
//8)a)

int cola_prioridad_es_vacia_arr(PColarreglo cola){
	return !cola||cola->primero==-1;
}

int cola_prioridad_obtener_minimo_arr(PColarreglo cola){
	return cola->datos[cola->primero].dato;
}

void cola_prioridad_eliminar_minimo_arr(PColarreglo cola){
	if (cola_prioridad_es_vacia_arr(cola)==1) return;
	cola->primero=(cola->primero+1)%MAX_COLAP;
	if(cola->primero==cola->ultimo) cola->primero=-1;//se vacio
	return;
}

int retroceder(int i){
	if(i==0) return MAX_COLAP-1;
	return i-1;
}

//
//NO ANDA
//
void cola_prioridad_insertar_arr(PColarreglo cola, PDato dato){
	if(cola==NULL){//se diferencia del caso que sigue que alojo memoria antes, nada mas
		cola=malloc(sizeof(struct _PColarreglo));
		printf("alojo memoria\n");
		cola->primero=0;
		cola->datos[cola->primero]=dato;
		cola->ultimo=1;
		return;
	}
	printf("no se rompio\n");
	if (cola_prioridad_es_vacia_arr(cola)==1){//no esta entrando
		cola->primero=0;
		cola->datos[cola->primero]=dato;
		cola->ultimo=1;
		return;
	}
	if(cola->primero!=cola->ultimo){

		int i=cola->primero;

		if(dato.prioridad<cola->datos[i].prioridad){//primer caso a parte
			int j=cola->ultimo;
			for(;j!=cola->primero;j=retroceder(j)){
				cola->datos[(j+1)%MAX_COLAP]=cola->datos[j];
			}
			cola->datos[i]=dato;
			cola->ultimo=(cola->ultimo+1)%MAX_COLAP;
			return;
		}

		i=(i+1)%MAX_COLAP;

		for(;i!=cola->ultimo;i=(i+1)%MAX_COLAP){
			if(dato.prioridad<cola->datos[i].prioridad){//resto
				int j=cola->ultimo;
				for(;j!=cola->primero;j=retroceder(j)){
					cola->datos[(j+1)%MAX_COLAP]=cola->datos[j];
				}
				cola->datos[i]=dato;
				cola->ultimo=(cola->ultimo+1)%MAX_COLAP;
				return;
			}
		}


		/*cola->datos[cola->ultimo]=dato;
		cola->ultimo=(cola->ultimo+1)%MAX_COLA;//resto te "resetea" a 0 cuando llega al final del arreglo*/
		printf("La posicion del ultimo es: %d\n",cola->ultimo);
	} else printf("La cola esta llena\n");
	return;
}

void cola_prioridad_imprimir_arr(PColarreglo c){
	if(cola_prioridad_es_vacia_arr(c)){
		printf("La cola esta vacia\n");
		return;
	}
	int i=c->primero;
	printf("%d\n",c->datos[i].dato);
	i=(i+1)%MAX_COLAP;

	for(;i!=c->ultimo;i=(i+1)%MAX_COLAP){
		printf("%d\n",c->datos[i].dato);
	}
	return;
}

//8)b) //cola definida como GList

int cola_prioridad_es_vacia_list(GList cola){
	return cola==NULL;
}

int cola_prioridad_obtener_minimo_list(GList cola){
	return ((PDato*)cola->dato)->dato;
}

GList cola_prioridad_eliminar_minimo_list (GList cola){
	GList temp=cola;
	cola=cola->sig;
	free(temp->dato);
	free(temp);
	return cola;
}

GList cola_prioridad_insertar_list (GList cola, int dato, int prioridad){
	PDato* nuevo=NULL;
	nuevo=malloc(sizeof(struct _PDato));
	nuevo->dato=dato;
	nuevo->prioridad=prioridad;
	

	if ((cola_prioridad_es_vacia_list(cola))||(prioridad<((PDato*)cola->dato)->prioridad)) return glist_agregar_inicio(cola, nuevo);//priroriedad es menor que la "raiz", agregar al principio

	GNodo* nuevoNodo=NULL;
	nuevoNodo=malloc(sizeof(GNodo));
	nuevoNodo->dato=nuevo;

	GList indice;
	for(indice=cola;indice!=NULL;indice=indice->sig){
		if((indice->sig==NULL)||(prioridad<((PDato*)indice->sig->dato)->prioridad)){//o es menor al elemento de la cola, o es el ultimo elemento de la cola
			nuevoNodo->sig=indice->sig;
			indice->sig=nuevoNodo;
			return cola;
		}
	}
}

void imprimir_dato_prioridad (void* dato){
	printf("%d|%d\t",((PDato*)dato)->dato ,((PDato*)dato)->prioridad);
	return;
}

//8)c)

int cola_prioridad_es_vacia_h(BHeapd h){
	return !h||h->nelems==0;//por si h es null
}

int cola_prioridad_obtener_minimo_h(BHeapd h){
	return h->datos[0].dato;
}

void cola_prioridad_eliminar_minimo_h(BHeapd h){
	if(cola_prioridad_es_vacia_h(h)){
        printf("La lista esta vacia, no hay minimo\n");
        return;
    }
    h->nelems--; //le vamos a sacar un elemento, sirve tambien para manejar la posicion del ultimo elemento
    h->datos[0]=h->datos[h->nelems];//guarda el ultimo en la raiz
    int pos=0;
    for(;pos<h->nelems;){/// <- EU aca nunca se modifica el pos no?
        if(2*pos+1>h->nelems-1) return;//si no tiene mas hijos
        if(2*pos+2>h->nelems-1){//si no tiene segundo hijo
            if(h->datos[pos].prioridad>h->datos[2*pos+1].prioridad){//si el primero es menor que el padre
                PDato n=h->datos[pos];
                h->datos[pos]=h->datos[2*pos+1];
                h->datos[2*pos+1]=n;

				pos=2*pos+1;
                //se podria poner un return...?
            }
            else return;
        }
        else if(h->datos[pos].prioridad>h->datos[2*pos+1].prioridad||h->datos[pos].prioridad>h->datos[2*pos+2].prioridad){
            if(h->datos[2*pos+1].prioridad<h->datos[2*pos+2].prioridad){
                PDato n=h->datos[pos];
                h->datos[pos]=h->datos[2*pos+1];
                h->datos[2*pos+1]=n;

				pos=2*pos+1;
            }
            else{
                PDato n=h->datos[pos];
                h->datos[pos]=h->datos[2*pos+2];
                h->datos[2*pos+2]=n;

				pos=2*pos+2;
            }
        }
        else return; //los dos hijos son mayores al padre
    }
}

BHeapd bheapd_crear(){
    BHeapd h=malloc(sizeof(struct _BHeapd));
    h->nelems=0;
	h->memoria=0;
	//no tengo nada en datos
    return h;
}

void cola_prioridad_insertar_h(BHeapd h, int numero, int prioridad){ //puse numero en lugar de dato para no cambiar algunas cosas
	//printf("es cola vacia? %d",cola_prioridad_es_vacia_h(h));
	PDato dato;
	dato.dato=numero;
	dato.prioridad=prioridad;
	
	if(cola_prioridad_es_vacia_h(h)){
		/*if(h==NULL){
			h=malloc(sizeof(struct _BHeapd));
			printf("malloc en h\n");
		}*/
		h->datos=malloc(sizeof(PDato)*MAX_HEAP);//uso como base el max heap
		h->memoria=MAX_HEAP;
		printf("malloc en datos\n");

		h->datos[0]=dato;
		h->nelems=1;
		return;
	}
	//printf("salteo el es vacia?\n");
	if(h->nelems==h->memoria){//se puede cambiar por la longitud del array en lugar de la constante? para que solo este declarada en el header
        h->memoria=h->memoria*2;
		h->datos=(PDato*) realloc(h->datos, sizeof(PDato)*h->memoria);//realojo al doble (lo cambie en la linea de arriba)
    }

    h->datos[h->nelems]=dato;//el lugar que tengo libre
    h->nelems++;
	int pos=h->nelems-1;
	for(;pos>0;){//h->nelems-1 donde meti el elemento
		if(pos==0) return; //no pongo bheap_es_vacio(h) por que estoy sumando a nelems antes //no hay nada en la raiz, no hay nada para comparar //no deberia ni entrar
		if(((pos)-1)/2==(int)((pos)-1)/2){//si el resultado es entero, es decir si es el primer hijo (distincion si es la raiz?)
			if( h->datos[((pos)-1)/2].prioridad > h->datos[pos].prioridad){//si el elemento agregado es menor al padre
				PDato n=h->datos[pos];
				h->datos[pos]=h->datos[((pos)-1)/2];
				h->datos[((pos)-1)/2]=n;
				pos=(pos-1)/2;
			}
			else return; //si el elemento es menor al padre esta bien ordenado
		}
		else if(((pos)-2)/2==(int)((pos)-2)/2){//Es necesario fijarte que sea hijo del segundo? con un else no basta?
				if( h->datos[((pos)-2)/2].prioridad > h->datos[pos].prioridad){//si el elemento agregado es menor al padre
					PDato n=h->datos[pos];
					h->datos[pos]=h->datos[((pos)-2)/2];
					h->datos[((pos)-2)/2]=n;
					pos=(pos-2)/2;
				}
				else return; //si el elemento es menor al padre esta bien ordenado
		}
	}
	return;
}

void bheapd_imprimir(BHeapd h){
	int i=0;
	int n=0;
	for(;i<h->nelems;i++){
		printf("%d|%d\t",h->datos[i].dato,h->datos[i].prioridad);
		if(i+1==aux(2,n)){
			printf("\n");
			n++;
		}
	}
}

//Conclusion
//Utilizar un arreglo circular ordenado es mucho menos eficiente que usar listas enlazadas, que a la vez es menos eficiente que usar heaps

void heapify(int arr[], size_t tamanio){
	int pos=0;
	int nivel=0;//nivel va a ser 2^nivel

	//para saber cuantos padres con hijos tengo que revisar tengo que hacer 2^(nivel+1)
	while(2*pos+1<tamanio){//original: pos<tamanio

		if(arr[pos]>arr[2*pos+1]){//revisar que no se fije mas arriba dle padre
			swap(&arr[pos],&arr[2*pos+1]);
			//int n=arr[pos];
			//arr[pos]=arr[2*pos+1];
			//arr[2*pos+1]=n;
			if(pos!=0){//que no sea el padre
				if(((pos)-1)/2==(int)((pos)-1)/2){//si el resultado es entero, es decir si es el primer hijo (distincion si es la raiz?)
					pos=(pos-1)/2;
				}
				else if(((pos)-2)/2==(int)((pos)-2)/2){//Es necesario fijarte que sea hijo del segundo? con un else no basta?
					pos=(pos-2)/2;
				}
			}
		}
		else if(arr[pos]>arr[2*pos+2]){//un else, por que si cambio algo quiero que vuelva arriba y revise hacia abajo los hijos denuevo
			swap(&arr[pos],&arr[2*pos+2]);
			//int n=arr[pos];
			//arr[pos]=arr[2*pos+2];
			//arr[2*pos+2]=n;
			if(pos!=0){//que no sea el padre
				if(((pos)-1)/2==(int)((pos)-1)/2){//si el resultado es entero, es decir si es el primer hijo (distincion si es la raiz?)
					pos=(pos-1)/2;
				}
				else if(((pos)-2)/2==(int)((pos)-2)/2){//Es necesario fijarte que sea hijo del segundo? con un else no basta?
					pos=(pos-2)/2;
				}
			}
			
		}
		else pos++;//suponiendo que esta bien ordenado con los hijos, paso al siguiente elemento del arreglo y sus hijos
	//aca ya tengo ordenado el primer par
	}
}

 BHeapdin bheapd_merge(BHeapdin heap1, BHeapdin heap2){//en lugar de sacar un elemento de un hep y agregarlo a otro puede que sea menos proceso sumar los dos array y ordenarlo
	BHeapdin h3=malloc(sizeof(struct _BHeapdin));
	h3->memoria=heap1->nelems+heap2->nelems;
	h3->nelems=h3->memoria;
	h3->datos=malloc(sizeof(int)*(h3->memoria));
	int i=0;
	for(;i<h3->memoria;i++){
		if(i<heap1->nelems) h3->datos[i]=heap1->datos[i];
		else h3->datos[i]=heap2->datos[i-heap1->nelems];
	}

	/*int j=0;
	int n=0;
	for(;j<h3->nelems;j++){//prineto lo que tengo en el arreglo nomas
		printf("%d ",h3->datos[j]);
	}
	puts("");*/

	heapify(h3->datos,h3->nelems);
	return h3;
 }

int main(int argc, char *argv[]) {
	/*Cola c;
	c=cola_crear();
	printf("Cola es vacia? %d\n",cola_es_vacia(c));
	cola_encolar(c,1);
	cola_encolar(c,2);
	cola_encolar(c,3);
	cola_encolar(c,4);
	cola_encolar(c,5);
	cola_imprimir(c);
	printf("Primer elemento= %d\n",cola_primero(c));
	cola_desencolar(c);
	cola_encolar(c,66);
	printf("Primer elemento del arreglo= %d\n",c->datos[0]);
	cola_imprimir(c);
	
	cola_destruir(c);*/
	
	/*Colas c;
	c=colas_crear();
	printf("Cola es vacia? %d\n",colas_es_vacia(c));
	colas_encolar(c,1);
	colas_encolar(c,2);
	colas_encolar(c,3);
	colas_encolar(c,4);
	colas_encolar(c,5);
	printf("Primer elemento= %d\n",colas_primero(c));
	colas_imprimir(c);
	
	colas_desencolar(c);
	printf("Primer elemento= %d\n",colas_primero(c));
	colas_imprimir(c);
	colas_encolar(c,66);

	printf("Primer elemento= %d\n",colas_primero(c));
	colas_imprimir(c);
	
	colas_destruir(c);*/
	
	/*BHeap h;
	h=bheap_crear();
	printf("Es vacio? %d\n",bheap_es_vacio(h));
	bheap_insertar(h, 1);
	bheap_insertar(h, 2);
	bheap_insertar(h, 3);
	bheap_insertar(h, 4);
	bheap_insertar(h, 5);
	bheap_insertar(h, 6);
	bheap_insertar(h, 7);
	bheap_imprimir(h);
	puts("");
	
	//bheap_imprimir(h);
	//puts("");
	bheap_eliminar_minimo(h);
	bheap_imprimir(h);
	puts("");
	printf("el primer elemento es: %d\n",bheap_minimo(h));
	
	bheap_destruir(h);
	
	return 0;*/

	/*PColarreglo cola=NULL;
	printf("Esta vacia? %d\n",cola_prioridad_es_vacia_arr(cola));
	PDato dato;
	dato.dato=1;
	dato.prioridad=7;
	cola_prioridad_insertar_arr(cola,dato);
	printf("el inicio de cola es la posicion %d y el final es &d\n",cola->primero,cola->ultimo);
	dato.dato=2;
	dato.prioridad=6;*/
	//cola_prioridad_insertar_arr(cola,dato);
	//cola_prioridad_imprimir_arr(cola);
	/*cola=malloc(sizeof(struct _PColarreglo));
	printf("Esta vacia? %d\n",cola_prioridad_es_vacia_arr(cola));*/

	/*GList cola=glist_crear();
	printf("Esta la cola vacia? %d\n",cola_prioridad_es_vacia_list(cola));
	cola=cola_prioridad_insertar_list(cola, 5, 1);
	cola=cola_prioridad_insertar_list(cola, 4, 2);
	cola=cola_prioridad_insertar_list(cola, 3, 3);
	cola=cola_prioridad_insertar_list(cola, 2, 4);
	cola=cola_prioridad_insertar_list(cola, 1, 5);
	printf("\tdato/prioridad\n");
	glist_recorrer(cola, imprimir_dato_prioridad);
	puts("");
	cola=cola_prioridad_eliminar_minimo_list(cola);
	glist_recorrer(cola, imprimir_dato_prioridad);
	puts("");
	cola=cola_prioridad_insertar_list(cola, -5, 100);
	cola=cola_prioridad_insertar_list(cola, 1, 10);
	glist_recorrer(cola, imprimir_dato_prioridad);
	puts("");
	cola=cola_prioridad_insertar_list(cola, 5, 1);
	glist_recorrer(cola, imprimir_dato_prioridad);
	puts("");
	printf("el minimo de la lista es: %d\n",cola_prioridad_obtener_minimo_list(cola));
	free(cola);*/
	/*BHeapd h=NULL;
	h=bheapd_crear();
	printf("Es h vacia? %d",cola_prioridad_es_vacia_h(h));
	printf("bheapd\n");
	cola_prioridad_insertar_h(h,1,70);
	printf("bheapd\n");
	cola_prioridad_insertar_h(h,2,60);
	cola_prioridad_insertar_h(h,3,50);
	cola_prioridad_insertar_h(h,4,40);
	cola_prioridad_insertar_h(h,5,30);
	cola_prioridad_insertar_h(h,6,20);
	cola_prioridad_insertar_h(h,7,10);
	printf("imprimo el minimo %d\n",cola_prioridad_obtener_minimo_h(h));
	printf("\tdato|prioridad\n");
	bheapd_imprimir(h);
	puts("");
	cola_prioridad_insertar_h(h,12,100);
	bheapd_imprimir(h);
	puts("");
	cola_prioridad_eliminar_minimo_h(h);
	bheapd_imprimir(h);
	puts("");
	cola_prioridad_insertar_h(h,42,55);
	bheapd_imprimir(h);
	puts("");

	free(h->datos);
	free(h);*/

	int arr[10]={6,28,7,3,98,12,73,92,0,10}, arr2[5]={12,16,62,72,76};
	heapify(arr, 10);

	BHeapdin h1=malloc(sizeof(struct _BHeapdin));
	h1->nelems=10;
	h1->memoria=10;
	h1->datos=malloc(sizeof(int)*h1->memoria);
	h1->datos=arr;

	//for(int j=0;j<h1->nelems;j++){//prineto lo que tengo en el arreglo nomas
	//	printf("%d ",h1->datos[j]);
	//}
	//puts("");

	BHeapdin h2=malloc(sizeof(struct _BHeapdin));
	h2->nelems=5;
	h2->memoria=5;
	h2->datos=malloc(sizeof(int)*h2->memoria);
	h2->datos=arr2;

	//for(int j=0;j<h2->nelems;j++){//prineto lo que tengo en el arreglo nomas
	//	printf("%d ",h2->datos[j]);
	//}
	//puts("");

	BHeapdin h=bheapd_merge(h1,h2);

	int i=0;
	int n=0;
	for(;i<h->nelems;i++){
		printf("%d ",h->datos[i]);
		if(i+1==aux(2,n)){
			printf("\n");
			n++;
		}
	}

	free(h1->datos); //se rompe aca, probablemente en algun lugar me fui fuera del arreglo
	free(h1);
	free(h2->datos);
	free(h2);
	free(h);
	free(h->datos);

	return 0;
}
