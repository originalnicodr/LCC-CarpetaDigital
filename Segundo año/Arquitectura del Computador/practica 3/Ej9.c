#include <stdio.h>

f(char a, int b, char c, long d,
  char e, short f, int g, int h) {
	printf("a: %p\n", &a);
	printf("b: %p\n", &b);
	printf("c: %p\n", &c);
	printf("d: %p\n", &d);
	printf("e: %p\n", &e);
	printf("f: %p\n", &f);
	printf("g: %p\n", &g);
	printf("h: %p\n", &h);
	return 0;
}

void main() {
	return f('1',2,'3',4,'5',6,7,8);
}

/*	Se guardaran en la pila los argumentos h y g que superan la cantidad de argumentos que se pueden guardar en los registros antes de inicializar f.

	Cuando llamamos a f se inserta en el tope de la pila su direccion de retorno y el rbp antes de llamar a f.
	Luego se envian las direcciones de memoria correspondientes a la pila que haran de argumentos de la funcion.

	Algunos argumentos son menores a 8 bytes (los char tienen 1 byte y los short tienen 4 bytes), y para mantener la estructura de la pila estos se extienden a 8 bytes (4 en el caso de que sea menor a 4 bytes).

	Si hay dos datos de 4 bytes los junta (para no desperdiciar memoria) y se completa con un entero '1' al f.

		Pila:
	
	|r.a. main		|
	|h = 8			|
	|g = 7			|
	|r.a f			|
	|rbp(main)		|
	|a = 31 | b = 2	|
	|c = 33 | e = 35|
	|d = 4			|
	|f = 6	| f' = 1|
*/