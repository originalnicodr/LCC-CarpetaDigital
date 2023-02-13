SList slist_crear() {
  return NULL;
}|

void slist_destruir(SList lista) {
  SNodo *nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->sig;
    free(nodoAEliminar);
  }
}

int slist_vacia(SList lista) {
  return lista == NULL;
}

SList slist_agregar_final(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;

  if (lista == NULL)
    return nuevoNodo;

  SList nodo = lista;
  for (;nodo->sig != NULL;nodo = nodo->sig);
  /* ahora 'nodo' apunta al ultimo elemento en la lista */

  nodo->sig = nuevoNodo;
  return lista;
}

SList slist_agregar_inicio(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = lista;
  return nuevoNodo;
}

void slist_recorrer(SList lista, FuncionVisitante visit) {
  for (SNodo *nodo = lista; nodo != NULL; nodo = nodo->sig)
    visit(nodo->dato);
}

SList slist_intersecar(SList lista1, SList lista2){
    SList listar=slist_crear();
    if(lista1==NULL||lista2==NULL) return listar;
    SList inicio2=lista2;
    for(;lista1->sig!=NULL;lista1=lista1->sig){
        if((slist_contiene(lista2,lista1->dato)==1)&&(slist_contiene(listar,lista1->dato)==0)){
            listar = slist_agregar_final(listar,lista1->dato);
        }

        /*for(lista2=inicio2;lista2->sig!=NULL;lista2=lista2->sig){
            printf("%d == %d ?\n",lista1->dato,lista2->dato);
            if(lista1->dato==lista2->dato) listar=slist_agregar_final(listar, lista1->dato);
        }
        printf("%d == %d ?\n",lista1->dato,lista2->dato);
        if(lista1->dato==lista2->dato) listar=slist_agregar_final(listar, lista1->dato);*/
    }
    if((slist_contiene(lista2,lista1->dato)==1)&&(slist_contiene(listar,lista1->dato)==0)){
            listar = slist_agregar_final(listar,lista1->dato);
        }
    //printf("%d == %d ?\n",lista1->dato,lista2->dato);
    //if(lista1->dato==lista2->dato) listar=slist_agregar_final(listar, lista1->dato); //comparacion cuando llega al final
    return listar;
}

SList slist_reverso(SList lista) {
  SNodo* reversa = NULL;
  SNodo* it; //iteracion
  for (it = lista; it != NULL;) {
    SNodo* resto = it->sig;//resto va a ser temporal para guardar el it->sig
    it->sig = reversa; //el ultimo elemento apunta a null(en el primer caso) y despues el it, que es el nodo que te interesa ir poniendo va a apuntar al nodo que agregaste antes, con la linea de abajo se termina de ver
    reversa = it;//el ultimo elemento que agregue es el it, entonces ahora es el primer elemento de la lista de reverso, por lo que hago que apunte a el
    it = resto;
  }
  return reversa;
}

//buscar intercalar mas facil
//buscar slist_ordenar mas facil



//listas circulares doblemente enlazadas

void dlist_destruir(DList lista) {
  DNodo *nodoAEliminar;
  while (lista->sig != lista) {
    nodoAEliminar = lista;
    lista = lista->sig;
    lista->ant=lista->ant->ant;

    lista->ant->sig=lista; //enlazo el ultimo con el primero
    free(nodoAEliminar);
  }
  free(lista);
}

//colas

void cola_desencolar(Cola c){
	if(cola_es_vacia(c)) return;
	int pos=c->primero;
	c->primero=(c->primero+1)%MAX_COLA;
	if(c->primero==c->ultimo) c->primero=-1;
	return;
}

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

  }
  return
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
    menor->sig=ssortl(l);//creo que deberia poner menor->sig, si no es lo mismo
  }
  return menor;
}

void isort(int arr[], int tam){
  int i=0;//capaz que arranque en 1
  for(;i<tam;i++){//recorre toda la lista
    int j=0;
    for(;j<i;j++){//recorre lo ya ordenado
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

void bsort(int datos[], int tam) {//ordena de menor a mayor
  int ordenado = 0, i;

  while (!ordenado) {
    ordenado = 1;
    for (i = 0; i < tam - 1; ++i)
      if (datos[i] > datos[i + 1]) {
        ordenado = 0;//si hago un cambiazo, tengo que verificar que ese elemento no tenga que seguir "subiendolo"
        swap(&datos[i], &datos[i + 1]);
      }
  }
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