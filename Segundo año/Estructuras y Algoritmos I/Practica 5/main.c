#include <stdio.h>
#include <stdlib.h>
#include "btree.h"
#include <math.h>
#include <assert.h>
//#include "slist.h"

//falta 4 iterativo, 5 b altura?, 6 revisar, 11 dante, 13 fer

//me daba paja separarlo en header
//-----------------------------------------------------------------------------------------------------------------------

static void imprimir_entero(int data) {
  printf("%d ", data);
}

Colas colas_crear(){
	Colas c=malloc(sizeof(struct _Colas));
	c->primero=NULL;
	c->ultimo=NULL;
	return c;
}

int colas_es_vacia(Colas c){
	return (c->primero==NULL)&&(c->ultimo==NULL);
}

BTree colas_primero(Colas c){
	return c->primero->dato;
}

void colas_encolar(Colas c, BTree dato){
	SNodo *nuevoUltimo=malloc(sizeof(SNodo));
	nuevoUltimo->sig=NULL;
	nuevoUltimo->dato=dato;

	if(colas_es_vacia(c)){
		c->primero=malloc(sizeof(SNodo));
		c->ultimo=malloc(sizeof(SNodo));//es necesario hacer dos malloc?
		c->primero=nuevoUltimo;
		c->ultimo=nuevoUltimo;
	}

	else{
		c->ultimo->sig=nuevoUltimo;
		c->ultimo=nuevoUltimo;
	}
}

void colas_desencolar(Colas c){
	if(colas_es_vacia(c)){
		printf("La cola es vacia. \n");
		return;
	}
	if(c->primero==c->ultimo){
		c->primero=NULL;
		c->ultimo=NULL;
	}
	else{
		SNodo *temp = malloc(sizeof(SNodo));
		temp = c->primero;
		c->primero=c->primero->sig;
		//free(temp);
	}
}
void colas_imprimir(Colas c){
	if(!(colas_es_vacia(c))){
		SNodo *temp=malloc(sizeof(SNodo));
		temp=c->primero;

		for(;temp!=NULL; temp=temp->sig){
			printf("%d ",temp->dato->dato);
		}
		printf("\n");
	}
	else printf("La cadena esta vacia\n");
}


/*void colas_imprimir(Colas c){
	slist_recorrer(c->primero, imprimir_entero);
	return;
}*/

/*void colas_destruir(Colas c){
	slist_destruir(c->primero);
	//slist_destruir(c->ultimo);
	free(c);
	return;
}*/

//-----------------------------------------------------------------------------------------------------------------------

int btree_suma_elems(BTree raiz){
	if(!raiz) return 0;
	int cont=raiz->dato;
	if(!raiz->left&&!raiz->right) return raiz->dato;
	if(raiz->left!=NULL) cont+=btree_suma_elems(raiz->left);
	if(raiz->right!=NULL) cont+=btree_suma_elems(raiz->right);
	return cont;
}

int btree_nelems(BTree raiz){
	if(!raiz) return 0;
	int cont=1;
	if(!raiz->left&&!raiz->right) return 1;
	if(raiz->left!=NULL) cont+=btree_nelems(raiz->left);
	if(raiz->right!=NULL) cont+= btree_nelems(raiz->right);
	return cont;
}

int btree_alturaux(BTree raiz, int alturamax){
	if(!raiz) return -1;//caso arbol vacio
	if(!raiz->left&&!raiz->right) return alturamax;
	if((raiz->left!=NULL)&&(raiz->right!=NULL)){
		if(btree_alturaux(raiz->left,alturamax++)>btree_alturaux(raiz->right,alturamax++)) return btree_alturaux(raiz->left,alturamax++);
		else return btree_alturaux(raiz->right,alturamax++);
	}
	if(raiz->left!=NULL) return btree_alturaux(raiz->left,alturamax++);
	else return btree_alturaux(raiz->right,alturamax++);
}

//Hacer el btree recorrer con pilas?

int btree_altura(BTree raiz){
	return btree_alturaux(raiz,0);
}

void btree_recorrer_it (BTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitante visit){//implementar pila
	int cant=btree_nelems(arbol);
	int *arr=malloc(sizeof(int)*cant);
	int cont=0;
	switch (orden){
		case BTREE_RECORRIDO_IN:
			btree_recorrer(arbol->left, orden, visit);
			/*arr[cont]=arbol->dato;
			cont++;*/
			btree_recorrer(arbol->right, orden, visit);
			break;
		 case BTREE_RECORRIDO_POST:
			btree_recorrer(arbol->left, orden, visit);
			btree_recorrer(arbol->right, orden, visit);
			arr[cont]=arbol->dato;
			cont++;
			break;
		 case BTREE_RECORRIDO_PRE:
			arr[cont]=arbol->dato;
			cont++;
			btree_recorrer(arbol->left, orden, visit);
			btree_recorrer(arbol->right, orden, visit);
			break;
		}
	//Llamar funcion visitante de forma iterativa en la pila
}



void imprimir_int(int dato){
  printf("%d ",dato);
}

void visit_suma (int dato, void *contador){
	*(int*)contador+=dato;
}

int btree_sumaextra_elems(BTree raiz){
	int contador=0;
	btree_recorrer_extra(raiz,BTREE_RECORRIDO_PRE,visit_suma, &contador);
	return contador;
}

void visit_contar (int dato, void *contador){
	*(int*)contador=*(int*)contador+1;
}

int btree_nelemsextra(BTree raiz){
	int contador=0;
	btree_recorrer_extra(raiz,BTREE_RECORRIDO_PRE,visit_contar, &contador);
	return contador;
}

/*void btree_recorrer_bfs_aux (BTree arbol, Colas cola){
	if(arbol!=NULL){
		if(colas_es_vacia(cola)) colas_encolar(cola, 1);//primer caso de raiz
		
		if(arbol->left!=NULL)colas_encolar(cola, 1);
		else colas_encolar(cola, 0);
		if(arbol->right!=NULL)colas_encolar(cola, 1);
		else colas_encolar(cola, 0);
		
		
	}
}


void btree_recorrer_bfs (BTree arbol){
	Colas cola=colas_crear();
	
}*/

//btree_recorrer_bfs y colas_encolar_alt por fede

void btree_recorrer_bfs (BTree arbol, FuncionVisitante visit){
	Colas c=colas_crear();
	colas_encolar(c,arbol);

	while (!colas_es_vacia(c)){
		BTree temp=btree_crear();
		temp=(BTree) colas_primero(c);
		colas_desencolar(c);
		visit(temp->dato);
		if(temp->left!=NULL){
			colas_encolar(c, temp->left);
		}
		if(temp->right !=NULL){
			colas_encolar(c, temp->right);
		}
	}
}
//------------------------------------------------------------------

void mirror(BTree arbol){
  if(arbol != NULL){
        mirror(arbol->left);
        mirror(arbol->right);
		BTree temp=arbol->left;
		arbol->left=arbol->right;
		arbol->right=temp;
    }
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

CBTree cbtree_crear (int niveles){
	CBTree arbol;
	arbol.dato=malloc(sizeof(int)*aux(2,niveles));
	arbol.nelems=0;
	return arbol;
}

void cbtree_destruir (CBTree arbol){
	free(arbol.dato);
}

void cbtree_insertar (CBTree arbol, int dato){
	if(arbol.nelems==sizeof(arbol.dato)/sizeof(int)){//revisar
		printf("El arbol esta lleno\n");
		return;
	}
	arbol.dato[arbol.nelems]=dato;
	arbol.nelems++;
	return;
}

int cbtree_nelementos (CBTree arbol){
    return arbol.nelems;
}

//Recorrido en profundidad de dante
//---------------------------------------------------------------------------------------
void imprimir_arbol_pre(int datos[], int nelems, int posRaiz, FuncionVisitante visit)
{
    visit(datos[posRaiz]);
    int posSubIzq = posRaiz * 2 + 1;
    int posSubDer = posRaiz * 2 + 2;
    if(posSubIzq < nelems){
      imprimir_arbol_pre(datos, nelems, posSubIzq, visit);//subarbol izq
      if(posSubDer < nelems) imprimir_arbol_pre(datos, nelems, posSubDer, visit);//subarbol der
    }
}

void imprimir_arbol_in(int datos[], int nelems, int posRaiz, FuncionVisitante visit)
{
    int posSubIzq = posRaiz * 2 + 1;
    int posSubDer = posRaiz * 2 + 2;
    if(posSubIzq < nelems) imprimir_arbol_in(datos, nelems, posSubIzq, visit);//subarbol izq
    visit(datos[posRaiz]);
    if(posSubDer < nelems) imprimir_arbol_in(datos, nelems, posSubDer, visit);//subarbol der
}

void cbtree_recorrer(CBTree arbol, FuncionVisitante visit){//cb arbol era el del arreglo del arbol completo
  if(arbol.nelems == 1) visit(arbol.dato[0]);
  imprimir_arbol_in(arbol.dato, arbol.nelems, 0, visit);
}
//----------------------------------------------------------------------------------

void cbtree_recorrer_bfs (CBTree arbol, FuncionVisitante visit){
    int i=0;
    for(;i<arbol.nelems;i++) visit(arbol.nelems);
	return;
}
//No, no es necesario por que recorriendo un array de principio a fin se recorre por extension




BSTree bstree_insertar(BSTree raiz, int dato){
    if(raiz==NULL){
        raiz=malloc(sizeof(BSTree));
        raiz->dato=dato;
        raiz->left=NULL;
        raiz->right=NULL;
        //return raiz; //por el ultimo NULL no es necesario
    }
    else{
        if(dato<raiz->dato) raiz->left=bstree_insertar(raiz->left,dato);
        else if (dato>raiz->dato) raiz->right=bstree_insertar(raiz->right,dato);
    }
    return raiz;
}

int bstree_contiene (BSTree arbol,int dato){
    if(arbol==NULL) return 0;
    if(arbol->dato==dato) return 1;
    if(dato<arbol->dato) return bstree_contiene(arbol->left,dato);
    return bstree_contiene(arbol->right,dato);
}

BSTree bstree_eliminar(BSTree raiz, int dato){//se ejecuta una vez, luego usa la auxiliar para la recursividad
	if (raiz==NULL) return raiz;
	if(raiz->dato==dato){//encontro el dato
		if(raiz->left!=NULL&&raiz->right!=NULL){//tiene dos hijos
            //separar en funciones? fijate de que capaz no sea necesario usar el padre por que en el return ya redireccionas la memoria
			BSTree indice=raiz->right;

			if (indice->left==NULL){//funca bien
				raiz->dato=indice->dato;
				raiz->right=indice->right;
				free(indice);
				//raiz->right=NULL;
			}
			else{
				for (;indice->left->left!=NULL;indice=indice->left); //me voy a parar en el anterior al ultimo elemento
				raiz->dato=indice->left->dato;

				BSTree temp=indice->left;
				indice->left=indice->left->right;

				free(temp);
				indice->left=NULL;
				//------------------------------------ MAL que pasa si el indice->left->right no es null? osea el ultimo hijo de la izquierda tiene hijos a la derecha?

			}
			
		}
		else if(raiz->left==NULL&&raiz->right==NULL){//caso sin hijos
			free(raiz);
			raiz=NULL;
		}
		else{
			if(raiz->left!=NULL){//tiene 1 hijo en left
				raiz->dato=raiz->left->dato;
				BTNodo *temp=raiz->left;
				raiz->right=raiz->left->right;//cannot acces memory? WTF, solucionalo! hacer primero el hijo opuesto(right si tiene 1 hijo en left)
				raiz->left=raiz->left->left;
				free(temp);
			}
			else{//tiene 1 hijo en right
				raiz->dato=raiz->right->dato;
				BTNodo *temp=raiz->right;
				raiz->left=raiz->right->left;
				raiz->right=raiz->right->right;
				free(temp);
			}
		}
		return raiz;
	}
	if(dato<raiz->dato) raiz->left=bstree_eliminar(raiz->left, dato);
    else raiz->right=bstree_eliminar(raiz->right, dato);
	return raiz;//hace falta esto?
}

//----------------------------ATENCION-------------------------------
//Estas funciones estan casteando a un arbol normal, si cambio la estructura del original del arbol me cambian estas funciones que uso en arbol binario,
//mejor hacer copy paste

int bstree_nelementos(BSTree arbol){//revisar esta, probablemente no te tome la funcion interna
    return btree_nelemsextra((BTree)arbol);
}

int bstree_altura(BSTree arbol){//revisar esta, probablemente no te tome la funcion interna
    return btree_alturaux((BTree)arbol,0);
}

void bstree_recorrer(BSTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitante visit){
    btree_recorrer((BTree)arbol,orden,visit);
}
//---------------------------------------------------------------------

//La condición necesaría para que un ABB tenga forma de lista luego de agregar varios elementos
//es que el elemento que se agregue sea siempre menor (o mayor) al anterior.

//Recorrerá la cantidad de nodos que sean menores (o mayores) al elemento a buscar, al igual que en una lista ordenada

//Si comparamos cuantos nodos recorre en una lista hasta encontrar el elemento con un ABB, recorreran la misma cantidad de nodos
 
void bstree_imprimir (BSTree arbol){
    bstree_recorrer(arbol, BTREE_RECORRIDO_IN,imprimir_entero);
}

//Balanceo de dante
//----------------------------------------------------------------------------------
static int dif(int a, int b){
    if(a - b < 0) return 0;
    return a - b;
}

int estado_balance_aux (BSTree arbol, int cont){
	//if((arbol->left==NULL&&arbol->right==NULL)||(arbol->left==NULL&&(arbol->right->left==NULL&&arbol->right->right==NULL))||(arbol->right==NULL&&(arbol->left->left==NULL&&arbol->left->right==NULL)))return 0;//o no tiene hijos, o la diferencia es de un solo nivel
	
}

//0 si no esta balanceado, 1 si lo esta
static int estado_balance(BSTree arbol){//el balance se puede interpretar por la cantidad de nodos o la altura, depenediendo el criterio
	if(arbol==NULL) return 1;
    int nelemsIzq = bstree_nelementos(arbol->left);
    int nelemsDer = bstree_nelementos(arbol->right);
    if(dif(nelemsIzq,nelemsDer) + dif(nelemsDer,nelemsIzq) <= 1){
		return estado_balance(arbol->left)*estado_balance(arbol->right);
	}
    return 0;
}


//por el cambio de estado_balance, no se usa esta funcion de balancear
/*BSTree bstree_balancear(BSTree arbol){
    if(arbol == NULL) return NULL;
    int estado = estado_balance(arbol);
    if(estado == 1) return arbol;
    if(estado == 0){
        BSTree nuevaRaiz = arbol->right;
        arbol->right = NULL;
        BSTree menorNodo = nuevaRaiz;
        for(; menorNodo->left != NULL; menorNodo = menorNodo->left);
        menorNodo->left = arbol;
        nuevaRaiz = bstree_balancear(nuevaRaiz);
    }
    if(estado == -1){
        BSTree nuevaRaiz = arbol->left;
        arbol->left = NULL;
        BSTree menorNodo = nuevaRaiz;
        for(; menorNodo->right != NULL; menorNodo = menorNodo->right);
        menorNodo->right = arbol;
        nuevaRaiz = bstree_balancear(nuevaRaiz);
    }
}*/

//-----------------------------------------------------------------------------

/*BTree bstree_balancear(BTree raiz){
	if(raiz==NULL) return raiz;
	if(!bstree_es_balanceado(raiz)){
		if(!bstree_es_balanceado(raiz))
	}
}*/

int bstree_minimo(BSTree arbol){
	if(arbol->left == NULL) return arbol->dato;
	return bstree_minimo(arbol->left);
}

/*void guardar_arreglo(int dato, void *arr){
	int i=0;
	for(;((int**)arr)[i]==NULL;i++);
	//*(((int**)arr)[i])=dato;
	((int**)arr)[i]=&dato;
}

int bstree_acceder(BSTree arbol, int pos){//accede al elemento de la posicion dada con respecto al recorrido inorder
	int **arr;
	int nelems=bstree_nelementos(arbol);
	arr=malloc(sizeof(int*)*nelems);//arreglo de punteros de int, para identificar los lugares vacios

	int i=0;
	for(;i<nelems;i++){
		arr[i]=malloc(sizeof(int));
		arr[i]=NULL;//inicializo todo en NULL
	}
	btree_recorrer_extra((BTree)arbol, BTREE_RECORRIDO_IN, guardar_arreglo, arr, nelems);
	int dato= *(arr[pos]);//me tira null esto

	i=0;
	for(;i<nelems;i++) free(arr[i]);
	free(arr);

	return dato;

}*/

//Dante
void bstree_acceder_aux(int indice, int dato, int* ptrres){//recorre todo el arbol hasta encontrar el indice, pero sigue recorriendo aunque lo haya encontrado
  static int cont = 0;
  if(indice == cont) *ptrres = dato;
  else cont++;
}

void bstree_acceder_aux2(BSTree arbol, int indice, int* ptrres){
  if(arbol != NULL){
    bstree_acceder_aux2(arbol->left, indice, ptrres);
    bstree_acceder_aux(indice, arbol->dato, ptrres);
    bstree_acceder_aux2(arbol->right, indice, ptrres);
  }
}

int bstree_acceder(BSTree arbol, int indice){
  int res, *ptrres = &res;
  bstree_acceder_aux2(arbol, indice, ptrres);
  return res;
}

//Cree la estructura NaccP en el main, sería conveniente hacer una función no recursiva que genere la estructura y corra esta función?
int bstree_acceder2(BSTree arbol, int pos, NaccP Nodo){
    assert(pos>=0);
    if(arbol != NULL){
        bstree_acceder2(arbol->left,pos,Nodo);
        if(Nodo->pos==pos){//Llego a la posición 
			Nodo->dato=arbol->dato;//guarda el dato de la posición
			Nodo->pos++;//suma 1 para que al terminar el llamado anterior no entre de nuevo
			return Nodo->dato;
		}
        Nodo->pos++;
        bstree_acceder2(arbol->right,pos,Nodo);
    }
     return Nodo->dato;
}
    
int main() {
  /*BTree ll = btree_unir(1, btree_crear(), btree_crear());
  BTree l = btree_unir(2, ll, btree_crear());
  BTree r = btree_unir(3, btree_crear(), btree_crear());
  BTree raiz = btree_unir(4, l, r);*/
  
  /*BTree ll = btree_unir(1, btree_crear(), btree_crear());
  
  BTree test2= btree_unir(24, btree_crear(), btree_crear());
  BTree test= btree_unir(24, test2, btree_crear());
  
  BTree l = btree_unir(2, ll, test);
  BTree r = btree_unir(3, btree_crear(), btree_crear());
  BTree raiz = btree_unir(4, l, r);
  
  //printf("Test de suma de elementos= %d",btree_suma_elems(raiz));
  //printf("Test de cantidad de elementos= %d",btree_nelems(raiz));
  printf("Test de altura de arbol= %d",btree_altura(raiz));

  //btree_recorrer(raiz, BTREE_RECORRIDO_POST, imprimir_entero);
  puts("");
  btree_destruir(raiz);*/

  /*BTree ll = btree_unir(1, btree_crear(), btree_crear());
  BTree l = btree_unir(2, ll, btree_crear());
  BTree r = btree_unir(3, btree_crear(), btree_crear());
  BTree raiz = btree_unir(4, l, r);

  btree_recorrer(raiz,BTREE_RECORRIDO_PRE,imprimir_int);*/

  //printf("Suma de los elementos: %d",btree_sumaextra_elems(raiz));
  //puts("");
  //printf("Cantidad de elementos: %d",btree_nelemsextra(raiz));

  /*btree_recorrer(raiz,BTREE_RECORRIDO_PRE,imprimir_int);
  puts("");
  //mirror(raiz);
  //btree_recorrer(raiz,BTREE_RECORRIDO_PRE,visit_contar);
  printf("nelemsextra¡?¡? %d/n",btree_nelemsextra(raiz));
  btree_destruir(raiz);*/
  
  BSTree arbolito=NULL;
  arbolito=bstree_insertar(arbolito,5);
  arbolito=bstree_insertar(arbolito,50);
  arbolito=bstree_insertar(arbolito,12);
  arbolito=bstree_insertar(arbolito,82);
  arbolito=bstree_insertar(arbolito,2);
  arbolito=bstree_insertar(arbolito,7);
  bstree_imprimir(arbolito);
  printf("cantidad de elementos %d\n Contiene a 12? %d\n Altura = %d\n Menor elemento= %d\n",bstree_nelementos(arbolito),bstree_contiene(arbolito,12),bstree_altura(arbolito),bstree_minimo(arbolito));
  //arbolito=bstree_eliminar(arbolito,50);
	puts("");
	NaccP Nodo=malloc(sizeof(Nacc));//creo una estructura para el accder
	Nodo->pos=0;//lo inicializo en la pos 0
	Nodo->dato=arbolito->dato;//el dato en que se inicializa no es importante ya que la función acceder se lo va a asignar
	printf("Elemento en la posicion 3: %d\n",bstree_acceder2(arbolito,3,Nodo));

  bstree_imprimir(arbolito);
  puts("");
  puts("");
  printf("Arbolito balanceador? %d",estado_balance(arbolito));
  puts("");

  BSTree arbolbalanceado=NULL;
  arbolbalanceado=bstree_insertar(arbolbalanceado,5);
  arbolbalanceado=bstree_insertar(arbolbalanceado,4);
  arbolbalanceado=bstree_insertar(arbolbalanceado,6);
  arbolbalanceado=bstree_insertar(arbolbalanceado,3);
  arbolbalanceado=bstree_insertar(arbolbalanceado,2);

  printf("Arbol balanceador? %d",estado_balance(arbolbalanceado));
  
  btree_destruir((BTree)arbolito);
  btree_destruir((BTree)arbolbalanceado);
 
  return 0;
}
