#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

//Ej3

//No tengo que modificar nada, ya que al codificar denuevo nos devolvera la palabra original, decodificando.
//Esto se debe a las propiedades del xor.
//No se gana nada codificando más de una vez ya que es lo mismo que codificar con un sólo codigo (codigo=codigo1^codigo2)

/* Entrada estandar */

void Codificador(int codigo){
	int i=0;
	char a;
	char* palabra=malloc(sizeof(char)*30);
	printf("Introdusca el texto: ");
	while((a=getchar())!='\n'){
	   palabra[i]=a^codigo;
	   putchar(palabra[i]);
	   i++;
   }
   puts("");
   //printf("%s\n",palabra);
}

int main(int argc, char **argv){
  puts("\nEjercicio 3");
	Codificador((int)*argv[1]);
  return 0;
}
