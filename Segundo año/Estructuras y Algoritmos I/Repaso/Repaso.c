#include <stdio.h>
#include <conio.h>
#include <malloc.h>

  typedef struct cartaDeBarajaEspanola  {
      int numero, palo; //1= oro, 2 =copa, 3=espada, 4=basto
  } carta;

  typedef struct Contacto{
    char* nombre, telefono;
    unsigned int edad;
  } contacto;

  typedef struct Punto{
      int x,y;
  } punto;

  typedef struct Agenda{
    contacto* contactos;
    int cantcontactos;
  } agenda;

  contacto crearcontacto(void){
    contacto nuevocontacto;
    char nombre[40], telefono[40]; //habia que darles un maximo
    unsigned int edad;

    printf("Ingrese el nombre del contacto\n");
    gets(nombre);
    printf("Ingrese el telefono del contacto\n");
    gets(telefono);
    printf("Ingrese la edad del contacto\n");
    scanf("%u", edad); //%u para unsigned int
    nuevocontacto.nombre=malloc(sizeof(char)*strlen(nombre));
    nuevocontacto.nombre= nombre;
    nuevocontacto.telefono=malloc(sizeof(char)*strlen(telefono));
    nuevocontacto.telefono= telefono;
    nuevocontacto.edad= edad;
}

punto medio(punto a, punto b){
    punto c;
    c.x=(a.x+b.x)/2;
    c.y=(a.y+b.y)/2;
    return c;
}

void funcion1(){
    char testc[5]="Test";
    int testi=5;
    float testf=5.0;

    printf("Espacio de memoria de int: %p \n Espacio de memoria de float: %p\n Espacio de memoria de cadena: %p\n%p\n%p\n%p\n%",testi, testf, testc[0], testc[1], testc[2], testc[3], testc[4]);
}

struct cartaDeBarajaEspanola carta_azar(carta mazo[], int longmazo){ //no me estaria andando
    return mazo[rand() % (longmazo) + 1];//rand() % (max_number + 1 - minimum_number) + minimum_number
}

void funcion2(){
    carta mazo [49]; //deje uno mas para el \0
    int palo=1;
    int numero=1;
    for (int i=1;i<=48;i++){
        mazo[i].numero=numero;
        mazo[i].palo=palo;
        numero++;
        if (numero > 12){
            palo++;
            numero=1;
        }
        //printf("Numero: %d - Palo: %d\n", mazo[i].numero, mazo[i].palo);
    }
    carta azar= carta_azar(mazo,48);
    printf("Carta azar: %d de %d", azar);
}

void setzerozero(int kk[]){
    kk[0]=0;
    if (kk!=0) printf("No se ha seteado el primer elemento a 0\n");
    else return;
}

void setin(int* puntero){
    if(*puntero!=0) *puntero=1;
    else *puntero=0;
}

void actualizaredad(contacto* nuevocontacto) {
    unsigned int edad;
    printf("Reingrese la edad del contacto\n");
    scanf("%u",edad);
    nuevocontacto->edad=edad;
}

int prom(contacto* nuevocontacto, int cantcontactos){ //la diferencia esta en que si tomas un puntero no necesitas saber de antemano la cantidad de contactos?
    int promedio=0;
    for (int i=0;i<cantcontactos;i++){
        promedio+=nuevocontacto->edad;
    }
    promedio=promedio/cantcontactos;
    return promedio;
}

agenda eliminar_contacto (agenda agendac, int n){
    //posicion del contacto a eliminar
    for(int i=n;i<agendac.cantcontactos;i++){
        agendac.contactos[n]=agendac.contactos[n];
    }
    n-=1;
    return agendac;
}

agenda editar_edad (agenda agendac, int n, int edad){
    agendac.contactos[n].edad= edad;
    return agendac;
}

agenda mostrar_datos (agenda agendac){
    for (int i=0;i<agendac.cantcontactos;i++) printf("Nombre: %s - Telefono: %s - Edad: %d",agendac.contactos[i].nombre,agendac.contactos[i].telefono,agendac.contactos[i].edad);
}



/*Otra signatura válida para main es int main(int argc, char *argv[]). El argumento argc cuenta
la cantidad de argumentos pasados, y argv es un arreglo de cadenas que representan cada uno de los
argumentos pasados al programa.
Escriba un programa que imprime en pantalla la cantidad de argumentos que recibió, y el contenido de
los mismos.*/

int main() {
    //funcion1();
    //funcion2();

    //ej5) Null
    //crearcontacto();

    /*int* puntero;
    *puntero=6; //me tira error, wtf
    setin(puntero);
    printf("%d",*puntero);*/

    char* c;
    c=malloc(sizeof(char));
    free(c);
    free(c); //crashea?

}
