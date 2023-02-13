typedef enum {
  BTREE_RECORRIDO_IN,
  BTREE_RECORRIDO_PRE,
  BTREE_RECORRIDO_POST
} BTreeOrdenDeRecorrido;

typedef void (*FuncionVisitante) (int dato);
typedef void (*FuncionVisitanteExtra) (int dato, void *extra);

void btree_destruir(BTree nodo) {
  if (nodo != NULL) {
    btree_destruir(nodo->left);
    btree_destruir(nodo->right);
    free(nodo);
  }
}

int btree_suma_elems(BTree raiz){
	if(!raiz) return 0;
	int cont=raiz->dato;
	if(!raiz->left&&!raiz->right) return raiz->dato;
	if(raiz->left!=NULL) cont+=btree_suma_elems(raiz->left);
	if(raiz->right!=NULL) cont+=btree_suma_elems(raiz->right);
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

int btree_altura(BTree raiz){
	return btree_alturaux(raiz,0);
}

if(arbol.nelems==sizeof(arbol.dato)/sizeof(int)) //para revisar que esta lleno (arbol.dato es un arreglo)

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

        //no lo testie a esto
        
        BSTree temp=indice->left;
				indice->left=indice->left->right;

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

static int estado_balance(BSTree arbol){//el balance se puede interpretar por la cantidad de nodos o la altura, depenediendo el criterio
	if(arbol==NULL) return 1;
    int nelemsIzq = bstree_nelementos(arbol->left);
    int nelemsDer = bstree_nelementos(arbol->right);
    if(dif(nelemsIzq,nelemsDer) + dif(nelemsDer,nelemsIzq) <= 1){
		return estado_balance(arbol->left)*estado_balance(arbol->right);
	}
    return 0;
}

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



/**
 * Casillas en la que almacenaremos los datos de la tabla hash.
 */
typedef struct _CasillaHash{
  void* clave;
  void* dato;
  unsigned eliminado;//eliminado ==1, no eliminado ==0
} CasillaHash;

/**
 * Estructura principal que representa la tabla hash.
 */
typedef struct {
  CasillaHash* tabla;
  unsigned numElems;
  unsigned capacidad;
  FuncionHash hash;
  FuncionIgualdad comparador;
} TablaHash;

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
 * Casillas en la que almacenaremos los datos de la tabla hash.
 */
typedef struct _CasillaHash{
  void* clave;
  void* dato;
  struct _CasillaHash *sig;
} *CasillaHash;

/**
 * Estructura principal que representa la tabla hash.
 */
typedef struct {
  CasillaHash* tabla;//doble puntero
  unsigned numElems;
  unsigned capacidad;
  FuncionHash hash;
  FuncionIgualdad comparador;
  float factorDeCarga;
} TablaHash;

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