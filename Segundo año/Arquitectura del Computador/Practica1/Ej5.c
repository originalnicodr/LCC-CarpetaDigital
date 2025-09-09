#include <stdio.h>
#include <gmp.h>
#define CANTSUBGRUPOS 16
typedef struct { unsigned short n[CANTSUBGRUPOS]; } nro;

/* Implementar:
    • Funciones que comparen con 0 y con 1 y determinen paridad para valores de este tipo.
    • Funciones que corran a izquierda y derecha los valores del tipo nro.
    • Funcion suma de valores del tipo nro.

    Nota: En el repositorio de la materia hay una funcion para imprimir valores de este tipo. Esta funcion
          utiliza la libreria GMP por lo cual debera compilar el codigo agregando la opcion -lgmp.
*/

/**
    Representacion de datos. La estructura es un arreglo de short ints.
    Es decir, cada 'casilla' del arreglo tiene un entero de 16 bits.

    Luego, el 'nro' queda representado de la forma:
    0           1           2            ... 15
    [01010.....][01010.....][01010.....] ... [01010.....]

    Donde el arreglo en 0, es decir el grupo de bits mas a la izquierda, en
    su representacion binaria total seria el grupo mas a la derecha.

    Por lo tanto, el bit MSB del arreglo en la posicion 15, la de mas peso,
    representa el bit de signo.

*/

void bP(unsigned short valor){
  for(int i=15; i>=0; i--){
	if(valor&(1<<i)) printf("1");
	else printf("0");
	}
}

void printB(nro num){
  for(int i=CANTSUBGRUPOS-1; i>=0; i--){
    bP(num.n[i]);
    printf(" ");
  }
}

void print(nro n)//?
{
	int i;
	char str[1024];
	short sign[16], num[16];
	mpz_t n1, n2;
	for (i=0; i<15; i++) {
		num[i] = n.n[i];
		sign[i] = 0;
	}
	num[15] = n.n[15] & 0x7FFF;
	sign[15] = n.n[15] & 0x8000;
	mpz_init(n1);
	mpz_init(n2);
	mpz_import(n1, 16, -1, 2, 0, 0, num);
	mpz_import(n2, 16, -1, 2, 0, 0, sign);
	mpz_neg(n2, n2);
	mpz_add(n2, n1, n2);
	mpz_get_str(str, 10, n2);
	printf("Número: %s\n", str);
	mpz_clear(n1);
	mpz_clear(n2);
}


nro andN(nro a, nro b){
  nro r;
  for(int i=0; i<CANTSUBGRUPOS;i++){
      r.n[i]=a.n[i]&b.n[i];
    }
  return r;
}

nro orN(nro a, nro b){
  nro r;
  for(int i=0; i<CANTSUBGRUPOS;i++){
      r.n[i]= (a.n[i])|(b.n[i]);
    }
  return r;
}

nro comp1N(nro a){//?
  for(int i=0; i<CANTSUBGRUPOS;i++){
    for(int j=0; j<CANTSUBGRUPOS;j++){
      a.n[i] = a.n[i]^1<<j;
    }
  }
  return a;
}

unsigned compara_cero(nro a){
	for(unsigned i=0; i<CANTSUBGRUPOS; i++){
		if(a.n[i] != 0b0){
			return 0;
		}
	}
	return 1;
}

nro sumaN(nro a, nro b){
  nro resultado;
  // Mascara para comparar con el MSB.
  int MSB = 0b1000000000000000;

  // Inicializamos en 0;
  for(int i=0; i<CANTSUBGRUPOS; resultado.n[i]=0, i++);

  for(int i=0; i<CANTSUBGRUPOS; i++){
    resultado.n[i] = resultado.n[i] + a.n[i] + b.n[i];
    if(((a.n[i]&MSB) != 0) && ((b.n[i]&MSB) != 0)){
      if(i>15) {printf("HUBO OVERFLOW CEBADO \n");}
      else{
        resultado.n[i+1]++;
        }
      }
    else  if(((a.n[i]&MSB) != 0) || ((b.n[i]&MSB) != 0)) {
      if((resultado.n[i]&MSB) == 0){
        if(i>15) printf("HUBO OVERFLOW CEBADO \n");
        else {
          resultado.n[i+1]++;
          }
      }
    }
  }
  return resultado;
}

nro desplazar_izq(nro a, unsigned cant){
  int MSB = 0b1000000000000000;
  int actual ,anterior;
  for(int j=0; j<cant; j++){
		anterior = 0b0;
    for(int i=0; i<CANTSUBGRUPOS; i++){
      actual = (((a.n[i]&MSB) != 0)? 0b1 : 0b0);
      a.n[i] = a.n[i]<<1;
      a.n[i] = a.n[i]+anterior;
      anterior = actual;
      }
    }
  return a;
  }

nro desplazar_der(nro a, unsigned cant){
  int LSB = 0b0000000000000001;
  short int siguiente;
  for(int j=0; j<cant; j++){
    for(int i=0; i<CANTSUBGRUPOS-1; i++){
      siguiente = (((a.n[i+1]&LSB) != 0)? 0b1000000000000000 : 0b0);
      a.n[i] = a.n[i]>>1;
      a.n[i] = a.n[i] + siguiente;
      }
      a.n[15] = a.n[15]>>1;
    }
  return a;
  }

int main(){
	
	nro a;
	for(int i=0;i<CANTSUBGRUPOS; a.n[i]=0b1111111111111111,i++);
	
	printf("RES = %d\n", compara_cero(a));
	
  return 1;
}
