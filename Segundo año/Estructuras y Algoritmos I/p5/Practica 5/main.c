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

//Ver si se puede hacer btree_alturaux con recorrer

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

void cbtree_recorrer (CBTree arbol, FuncionVisitante visit){//Mal? como por profundidad
	int i=0;
	for(;i<arbol.nelems;i++) visit(arbol.nelems);
	return;
}

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
				for (;indice->left->left!=NULL;indice=indice->left) //me voy a parar en el anterior al ultimo elemento
				raiz->dato=indice->left->dato;
				free(indice->left);
				indice->left=NULL;
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

int bstree_es_balanceado(BSTree raiz){//devuelve 0 si las ramas NO estan balanceadas, 1 si lo estan
	if(fabs(bstree_altura(raiz->left)-bstree_altura(raiz->right))>1) return 0;//fabs=valor absoluto diferencia de 2 en adelante
	return 1;
}


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

//Cree la estructura NaccP en el main, sería conveniente hacer una función no recursiva que genere la estructura y corra esta función?
int bstree_acceder(BSTree arbol, int pos, NaccP Nodo){
    assert(pos>=0);
    if(arbol != NULL){
        bstree_acceder(arbol->left,pos,Nodo);
        if(Nodo->pos==pos){//Llego a la posición 
			Nodo->dato=arbol->dato;//guarda el dato de la posición
			Nodo->pos++;//suma 1 para que al terminar el llamado anterior no entre de nuevo
			return Nodo->dato;
		}
        Nodo->pos++;
        bstree_acceder(arbol->right,pos,Nodo);
    }
     return Nodo->dato;
}
    
//************************************************************************************************************************
//Estas funciones estan en el archivo AVL.c no lo necesitas, funciona como borrador porque se me complicaba pensar con tantas cosas escritas


//Devuelve 1 si el arbol es balanceado y todos sus subarboles tambien lo son, y 0 si alguno no lo es
int bstree_es_balanceadoT(BSTree raiz){
	if(!raiz){//raiz nulo
		return 1;//Retorno 1 por ser el neutro del producto y porque si no tiene hijos esta balanceado
	}
	//Me va a ir multiplicando segun sea balanceado o no cada subarbol, si uno no es balanceado todo se hace 0(Propiedad del producto)
	return bstree_es_balanceado(raiz)*(bstree_es_balanceadoT(raiz->left))*(bstree_es_balanceadoT(raiz->right));
}

BSTree rotacion_simple(BSTree raiz, BSTree hijo){
	//assert((hijo==raiz->left||hijo==raiz->right));
	//Me fijo cual es el hijo a rotar
	if(hijo == raiz->left){
		raiz->left=hijo->right;
		hijo->right=raiz;
		return hijo;
	}
	else{
		raiz->right=hijo->left;
		hijo->left=raiz;
		return hijo;
	}
}

BSTree rotacion_doble(BSTree padre, BSTree hijo){
	//assert((hijo==padre->left||hijo==padre->right));
	//Me fijo cual es el hijo
	if(hijo == padre->left){
		hijo=rotacion_simple(hijo,hijo->right);//Primera rotacion simple
		padre->left=hijo;//le modifico el puntero para que apunte al nuevo hijo
		padre=rotacion_simple(padre,hijo);//Segunda rotacion
		return padre;
	}
	else{//analogo
		hijo=rotacion_simple(hijo, hijo->left);
		padre->right = hijo;
		padre=rotacion_simple(padre, hijo);
		return padre;
	}
}



BSTree bstree_balancear(BSTree arbol){
	if(bstree_es_balanceadoT(arbol))return arbol;//Si esta balanceado no hago nada
	if(!bstree_es_balanceado(arbol)){//Veo si la raiz esta desbalanceada
		//Me fijo cual subarbol pesa mas
		if(bstree_altura(arbol->left)<bstree_altura(arbol->right)){
			//Reviso que tipo de desbalance tengo
			BSTree temp = arbol->right;
			if(bstree_altura(temp->left)<bstree_altura(temp->right)){//hacia afuera
				arbol=rotacion_simple(arbol,arbol->right);
				arbol=bstree_balancear(arbol);//una vez hecha la rotacion vuelvo a llamar por si sigue desbalanceado
			}
			else{//hacia adentro
				arbol=rotacion_doble(arbol,arbol->right);
				arbol=bstree_balancear(arbol);
			}
		}
		
		else{//analogo
			BSTree temp = arbol->left;
			if(bstree_altura(temp->right)<bstree_altura(temp->left)){
				arbol=rotacion_simple(arbol,arbol->left);
				arbol=bstree_balancear(arbol);
			}
			else{
				arbol=rotacion_doble(arbol,arbol->left);
				arbol=bstree_balancear(arbol);
			}
		}
	}
	//Deberia usar un else? creo que no ya que por la llamada recursiva dentro del if solo llega aca una vez balanceada la raiz
	//por lo menos parece funcionar
	//Una vez que balancie la raiz, reviso los subarboles
	arbol->left=bstree_balancear(arbol->left);
	arbol->right=bstree_balancear(arbol->right);
	
}


BSTree AVTree_insertar(BSTree raiz, int dato){
	raiz = bstree_insertar(raiz,dato);//Como el AVL es un ABB uso el mismo insertar
	if(!bstree_es_balanceadoT(raiz)) raiz=bstree_balancear(raiz);//Me fijo si conserva el balance, si no lo balanceo
	return raiz;
}


//************************************************************************************************************************    
    
    
    
    
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
  arbolito=AVTree_insertar(arbolito,5);
  arbolito=AVTree_insertar(arbolito,2);
  arbolito=AVTree_insertar(arbolito,50);
  arbolito=AVTree_insertar(arbolito,12);
  arbolito=AVTree_insertar(arbolito,7);
  arbolito=AVTree_insertar(arbolito,82);
  arbolito=AVTree_insertar(arbolito,100);
  arbolito=AVTree_insertar(arbolito,10);
  bstree_imprimir(arbolito);
  printf("cantidad de elementos %d\n Contiene a 12? %d\n Altura = %d\n Menor elemento= %d\n",bstree_nelementos(arbolito),bstree_contiene(arbolito,12),bstree_altura(arbolito),bstree_minimo(arbolito));
  //arbolito=bstree_eliminar(arbolito,50);
	puts("");
	/*NaccP Nodo=malloc(sizeof(Nacc));//creo una estructura para el accder
	Nodo->pos=0;//lo inicializo en la pos 0
	Nodo->dato=arbolito->dato;//el dato en que se inicializa no es importante ya que la función acceder se lo va a asignar
	printf("Elemento en la posicion 3: %d\n",bstree_acceder(arbolito,3,Nodo));
*/
  printf("Balanceado? %d \n",bstree_es_balanceadoT(arbolito));
  bstree_imprimir(arbolito);
  /*arbolito=bstree_balancear(arbolito);
  printf("Balanceado? %d \n",bstree_es_balanceadoT(arbolito));
  bstree_imprimir(arbolito);*/
  btree_destruir((BTree)arbolito);
 
  return 0;
}
