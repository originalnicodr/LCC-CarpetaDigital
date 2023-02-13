++++++++++++++++++++++++++++++++++++++++++++++++//Ej1
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <gmp.h>


//Funcion para imprimir en binario
void binaryPrint(int valor){
  for(int i=31; i>=0; i--){
    if((i+1)%8 == 0){
      printf(" ");
      }
      (valor&(1<<i)) ? printf("1"):printf("0");
    }
  printf(" =  %d\n", valor);
}


/**
a) 10000000 00000000 00000000 00000000 ==  00000000 00000000 00000000 00000001  << 31
b) 10000000 00000000 10000000 00000000 == (1 << ...) | (1 << ...)
c) 11111111 11111111 11111111 00000000 == -1 & .....
d) 10101010 00000000 00000000 10101010 == 0xaa ..... (0xaa << .......)
e) 00000000 00000000 00000101 00000000 == ( 5 ..... 8)
f) 11111111 11111111 11111110 11111111 == -1 & (.... (1 << 8))
*/



//Ej 2

/* ROTAR VARIABLES USANDO XOR*/

void rotarXOR(int *a, int *b){//se trabaja con punteros por que tiene que "devolver" dos valores
  *a = (*a)^(*b);
  *b = (*b)^(*a);
  *a = (*b)^(*a);
}

//Ej3

//No tengo que modificar nada, ya que al codificar denuevo nos devolvera la palabra original

/* Entrada estandar */
void codificarPalabra(char *pal, int codigo){
  for(int i=0; i<strlen(pal); i++){
    pal[i] = pal[i]^codigo;
  }
  printf("%s\n",pal);
}


//Ej4

unsigned mult(unsigned a, unsigned b){
  int res = 0;

  while (b > 0) {

     if (b & 1)
         res = res + a;
     a = a << 1;
     b = b >> 1;
 }
  printf("Llegue aqui.\n");
  return res;
}

//Ej5

#define CANTSUBGRUPOS 16
typedef struct { unsigned short n[CANTSUBGRUPOS]; } nro;

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

//Ej6

nro multRuso(nro a, nro b){
  nro res;
  for(int i=0; i<CANTSUBGRUPOS; res.n[i]=0b0,i++);

  while (!compara_cero(b)) {

     if (b.n[0] & 1)
         res = sumaN(res,a);


     a = desplazar_izq(a,1);
     b = desplazar_der(b,1);
 }
  printf("Llegue aqui.\n");
  return res;
}


int main(){
  //Ej1

  /*
  //a)
  int a =      0b10000000000000000000000000000000;
  int aPrima = 0b00000000000000000000000000000001;
  assert(a == (aPrima<<31));

  //b)
  int b = 0b10000000000000001000000000000000;
  assert(b == ((1<<31)|(1<<15)));

  //c)
  int c =       0b11111111111111111111111100000000;
  int menouno = 0b11111111111111111111111111111111;
  printf("%d\n", menouno);
  assert(c == (menouno & c));

  //d)
  int d = 0b10101010000000000000000010101010;
  assert(d == 0xaa | (0xaa << 24));

  //e)

  int e = 0b00000000000000000000010100000000;
  assert( e == (5<<8));

  //f)
  int f = 0b11111111111111111111111011111111;
  assert(-1 & (~(1<<8)));

  int l = 18;
  int g = -18;
  int j = 1;
  binaryPrint(l);
  binaryPrint(f);
  binaryPrint(menouno);
  binaryPrint(j);
  */

  //Ej2
  /*
  int a=2,b=5;
  printf("El valor de a: %d y de b: %d\n",a,b);
  rotarXOR(&a,&b);
  printf("El valor de a: %d y de b: %d\n",a,b);
  */

  //Ej3
  /*
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
  */

  //Ej4
  //printf("Resultado: %d\n", mult(120,5));

  //Ej5
  /*
  nro a;
  for(int i=0;i<CANTSUBGRUPOS; a.n[i]=0b1111111111111111,i++);
  printf("RES = %d\n", compara_cero(a));
  return 1;
  */

  //Ej6
  /*
  nro a; 	//5
  for(int i=1;i<CANTSUBGRUPOS; a.n[i]=0b0,i++);
  a.n[0] = 0b101;
  nro b; //2
  for(int i=1;i<CANTSUBGRUPOS; b.n[i]=0b0,i++);
  b.n[0] = 0b10;
  print(multRuso(a,b));
  return 1;
  */

}
