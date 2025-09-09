#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
3) Escribir un programa que tome la entrada estándard, la codifique e imprima
   el resultado en salida estándard. La codificación deberá ser hecha caracter
   a caracter utilizando XOR y un código que se pasa como parámetro. ¿Qué
   modificaciones le tengo que hacer al programa para que decodifique? ¿Gano
   algo codificando más de una vez?. Probarlo codificando el fuente del programa
   y utilizando como código -98.
*/

//No tengo que modificar nada, ya que al codificar denuevo nos devolvera la palabra original

/* Impresion binaria */
void binaryPrint(int valor){
  for(int i=31; i>=0; i--){
    if((i+1)%8 == 0){
      printf(" ");
      }
      (valor&(1<<i)) ? printf("1"):printf("0");
    }
  printf(" =  %d\n", valor);

}
/* Entrada estandar */
void codificarPalabra(char *pal, int codigo){
  for(int i=0; i<strlen(pal); i++){
    pal[i] = pal[i]^codigo;
  }
  printf("%s\n",pal);
}

int main(int argc, char *argv[]){
  int codigo;
  printf("CODIGO: ");
  scanf("%d",&codigo);
  char *temp = malloc(sizeof(char) * 100);
  char *pal;
  printf("PALABRA: ");
  scanf("%s ",temp);
  gets();
  //for(int i=0; i<strlen(pal);binaryPrint(pal[i]), i++);
  pal = malloc(sizeof(char) * strlen(temp)+1);
  strcpy(pal,temp);
  codificarPalabra(pal,codigo);
  //for(int i=0; i<strlen(pal);binaryPrint(pal[i]), i++);
}
