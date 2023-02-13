#include <stdio.h>
#include <stdlib.h>
#include "glist.h"
#include <string.h>

int identificar(char* comando){
    
    int cont=0;

    char* c=NULL; //No puedo declararla despues y hacer c[cont] por que solo permite constantes

    
    for(;comando[cont]!=' ';cont++); //el contador va a estar en el lugar donde esta el espacio, pero como arranca de 0 son la cantidad de caracteres antes del espacio

    if(cont>14) return 0; //mas largo que cualquiera de los comandos

    c=malloc(sizeof(char)*cont);

    for(int i=0;i<cont;i++){
        c[i]=comando[i];
    }
    c[cont]='\0';//tengo que decirle hasta donde llega

    printf("\n\n Comando detectado: %s \n\n",c);

    if(strcmp(c,"crear")==0){
        free(c);
        return 1;
    }
    if(strcmp(c,"destruir")==0) {
        free(c);
        return 2;
    }
    if(strcmp(c,"imprimir")==0){
        free(c);
        return 3;
    }
    if(strcmp(c,"agregar_final")==0){
        free(c);
        return 4;
    }
    if(strcmp(c,"agregar_inicio")==0){
        free(c);
        return 5;
    }
    if(strcmp(c,"agregar_pos")==0){
        free(c);
        return 6;
    }
    if(strcmp(c,"longitud")==0){
        free(c);
        return 7;
    }
    if(strcmp(c,"concatenar")==0){
        free(c);
        return 8;
    }
    if(strcmp(c,"eliminar")==0){
        free(c);
        return 9;
    }
    if(strcmp(c,"contiene")==0){
        free(c);
        return 10;
    }
    if(strcmp(c,"indice")==0){
        free(c);
        return 11;
    }
    if(strcmp(c,"intersecar")==0){
        free(c);
        return 12;
    }
    if(strcmp(c,"ordenar")==0){
        free(c);
        return 13;
    }

    return 0; //si no encontro nigun comando
}

void imprimirlistam(void* lista){
    printf("\n%s\n",((AGList)lista)->nombre);
}

int main(int argc, char *argv[]) {
    char comando[256];
    GList listaM=glist_crear(); //AGList *listaM=NULL;
while (1){

    if(!glist_vacia(listaM)){
        glist_recorrer(listaM, imprimirlistam);
    }

    printf("Ingrese uno de los siguientes comandos:\n");
    printf("crear lista - Crea una Lista\n");
    printf("destruir lista - Destruye una lista\n");
    printf("imprimir lista - Imprime el contenido actual de la lista\n");
    printf("agregar_final lista elem - Agrega elem al final de la lista\n");
    printf("agregar_inicio lista elem - Agrega elem al principio de la lista\n");
    printf("agregar_pos lista elem pos - Agrega elem a la lista en la posicion pos\n");
    printf("longitud lista - Imprime la longitud de la lista longitud\n");
    printf("concatenar l1 l2 l3 -  Concatena l1 y l2 y crea l3 con el resultado\n");
    printf("eliminar lista pos - Elimina de lista el elemento en la posicion pos\n");
    printf("contiene lista elem - Imprime 'SI' si la lista contiene a elem, 'NO' sino\n");
    printf("indice lista elem - Imprime las posiciones en las que esta elem\n");
    printf("intersecar l1 l2 l3 - Crea l3 con la interseccion de l1 y l2");
    printf("ordenar lista - Ordena los elementos de la lista de menor a mayor\n");
    printf("s - salir\n");
    //printf("h - Imprime la lista de comandos\n");
    gets(comando);
    if(*(comando)=='s') return 0; //termino el programa

    printf("comando n: %d\n",identificar(comando));
    
    switch (identificar(comando)){
        case 1:{
            int cont=0;
            for(;comando[cont]!=' '; cont++); //tengo en cont el espacio donde esta el espacio

            //printf("forro\n\n");

            int comandol=strlen(comando);//longitud del comando para comparar el final
            int contn=comandol-cont; //contador que voy a usar para despues alojar la memoria con malloc del nombre //le resto -1?
            printf("\n\n%d=%d-%d-1\n\n",contn,comandol,cont);

            //printf("no alojo\n\n");

            char *nombre=malloc(sizeof(char)*contn);

            for(int i=cont+1;i<=comandol;i++){//cont+1 arranca del espacio que le sigue al espacio
                nombre[i-(cont+1)]=comando[i];
                //printf("%c",nombre[i]);
                printf("paso en el for\n");
            }
            //nombre[comandol]='\0';//por alguna razon sin esto me guarda basura en el final
            puts(" ");

            
            //Esto es para ver si ya existe una lista con el nombre dado
            if(!glist_vacia(listaM)){
                GList indice=listaM;
                for(;indice!=NULL&&strcmp(((AGNodo*)indice->dato)->nombre,nombre)!=0;indice=indice->sig);

                if(indice!=NULL){//si indice no es null entonces salio por la otra condicion, es decis encontro el mismo nombre
                    printf("Ya existe una lista con el nombre %s\n",nombre);
                    break;
                }
            }

            AGNodo *listaAGnueva= malloc(sizeof(AGNodo));
            GList listanueva=glist_crear();

            listaAGnueva->lista=listanueva; //tira error aca
            listaAGnueva->nombre=nombre;

            printf("nombre alojado: %s\n",listaAGnueva->nombre);

            listaM=glist_agregar_inicio(listaM,listaAGnueva); //uso agregar inicio por que no tiene que recorrer toda la lista;
            break;
            }
        case 2:{
            if(glist_vacia(listaM)){
                printf("Lista vacia, no se elimino ninguna lista\n");
                break;
            }
            int cont=0;
            for(;comando[cont]!=' '; cont++); //tengo en cont el espacio donde esta el espacio

            int comandol=strlen(comando);//longitud del comando para comparar el final
            int contn=comandol-cont; //contador que voy a usar para despues alojar la memoria con malloc del nombre //le resto -1?

            char *nombre=malloc(sizeof(char)*contn);

            for(int i=cont+1;i<=comandol;i++){//cont+1 arranca del espacio que le sigue al espacio
                nombre[i-(cont+1)]=comando[i];
            }
            GList indice=listaM;
            for(;indice!=NULL&&(strcmp(((AGNodo*)indice->sig->dato)->nombre,nombre)!=0);indice=indice->sig);//me fijo del siguiente por que tengo que cambiar el sig del anterior al que quiero eliminar

            printf("%s==%s?\n",((AGNodo*)indice->sig->dato)->nombre,nombre);

            if(indice!=NULL){//si indice no es null entonces salio por la otra condicion, es decis encontro el mismo nombre
                GNodo *nodo=indice->sig;
                indice->sig=indice->sig->sig;
                free(nodo);

                glist_destruir(((AGNodo*)indice->dato)->lista);
                free(((AGNodo*)indice->dato)->nombre);
                
                printf("elimino dale que se rompe todo wacho\n");
                break;
            }
            else {
                printf("No se ha encontrado la lista\n");
                break;
            }


        }
    }

  }
  return 0;
}
