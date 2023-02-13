#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

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

//Ej 2

void rotarXOR(int *a, int *b, int *c){
  *a = (*a)^(*b);
  *b = (*b)^(*a);//a  *b=b^(a^b)=a
  *a = (*b)^(*a);//   *a=a^(a^b)=b
  *a = (*a)^(*c);//   *a=b^c
  *c = (*c)^(*a);//b  *c=c^a^(b^c)=a^b // *c=c^a=c^(b^c)=b
  *a = (*c)^(*a);//c  (b^c)^a^(a^b)=c  // *a=c^a=b^b^c=c
}

//Ej3

//No tengo que modificar nada, ya que al codificar denuevo nos devolvera la palabra original, decodificando. Esto se debe a las propiedades del xor.

/* Entrada estandar */
void codificarPalabra(char *pal, int codigo){
  char a;
  int i=0;
  while((a=getchar())!='\n'){
	  
	  pal[i]=a^codigo;
  }	  
  printf("%s\n",pal);
}

void Codificador(int codigo){
	int i=0;
	char a;
	char* palabra=malloc(sizeof(char)*30);
	printf("Introdusca el texto: ");
	while((a=getchar())!='\n'){
	   palabra[i]=a^codigo;
	   i++;
   }
   printf("%s\n",palabra);
	//codificarPalabra(palabra,codigo);
}


//Ej4

unsigned mult(unsigned a, unsigned b){
  int r = 0;
  while (b > 0) {//si no entra retorna 0
     if (b & 1) r = r + a;
     a = a << 1;
     b = b >> 1;
 }
  return r;
}

//Ej5

#define NROCONS 16
typedef struct {
  unsigned short n[NROCONS];
} nro;

void bP(unsigned short valor){//Impresion de bits
  for(int i=15; i>=0; i--){
	if(valor&(1<<i)) printf("1");
	else printf("0");
	}
}

void printB(nro num){//Imprimir numeros de la estructura nro
  for(int i=NROCONS-1; i>=0; i--){
    bP(num.n[i]);
    printf(" ");
  }
}

void print(nro n)
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


nro nro_and(nro a, nro b){
  nro r;
  int i;
  for(i=0; i<NROCONS;i++){
      r.n[i]=(a.n[i])&(b.n[i]);
    }
  return r;
}

nro nro_or(nro a, nro b){
  nro r;
  int i;  
  for(i=0; i<NROCONS;i++){
      r.n[i]= (a.n[i])|(b.n[i]);
    }
  return r;
}

unsigned nro_equal0(nro a){
  int i;
	for(i=0; i<NROCONS; i++){
		if(a.n[i] != 0b0){
			return 0;
		}
	}
	return 1;
}

unsigned nro_equal1(nro a){
  int i;
  if (a.n[0]!= 0b1) return 0;//ya es diferente a 1 el resultado
	for(i=1; i<NROCONS; i++){
		if(a.n[i] != 0b0){
			return 0;
		}
	}
	return 1;
}

void nro_espar(nro n){
  if (n.n[0]&&0b0000000000000001) printf("El numero es impar\n");
  else printf("El numero es par\n");
}

nro nro_suma(nro a, nro b){
  nro r;
  // Inicializacion en 0
  for(int i=0; i<NROCONS; r.n[i]=0, i++);
  for(int i=0; i<NROCONS; i++){//iteracion en la estructura
    r.n[i] = r.n[i] + a.n[i] + b.n[i];
    if ((r.n[i]<a.n[i])||(r.n[i]<b.n[i])){
	    if (i==NROCONS-1) printf("El resultado es erroneo, ocurrio un overflow respecto al tamanio de la estructura \n");
      else  r.n[i+1]++;
    }
  }
  return r;
}

nro nro_izq(nro a, unsigned c){//c es cantidad de lugares que se mueve
  int mascara = 0b1000000000000000;
  int actual ,anterior;
  for(int j=0; j<c; j++){
	  for(int i=NROCONS-1;i>0;i--){
		  if(i==NROCONS-1&&(a.n[i]&mascara!=0)){
			  printf("El resultado es erroneo, ocurrio un overflow respecto al tamanio de la estructura \n");
			  return a;//Ver algun valor para marcar error
		  }
		  anterior=(((a.n[i-1]&mascara) != 0)? 0b1 : 0b0);
		  a.n[i] = a.n[i]<<1;
          a.n[i] = a.n[i]+anterior;	
		}
		a.n[0]=a.n[0]<<1;
	}
  return a;
}

nro nro_der(nro a, unsigned c){//c es cantidad de lugares que se mueve
  int mascara = 0b0000000000000001;
  short int siguiente;
  short int actual,anterior;
  for(int j=0; j<c; j++){
    for(int i=0; i<NROCONS-1; i++){//Por qué no recorrer del ultimo al primero?
      if(i==0&&(a.n[i]&mascara!= 0)){
        printf("El resultado es erroneo, ocurrio un overflow respecto al tamanio de la estructura \n");
        return a;//Ver algun valor apra marcar error 
	    }
      siguiente = (((a.n[i+1]&mascara) != 0)? 0b1000000000000000 : 0b0);//cambiar esto a if
      a.n[i] = a.n[i]>>1;
      a.n[i] = a.n[i] + siguiente;
    }
    a.n[15] = a.n[15]>>1;
  }
  return a;
}
		  
    for(int i=0; i<NROCONS-1; i++){//Por qué no recorrer del ultimo al primero?
      if(i==0&&(a.n[i]&mascara!= 0)){
        printf("El resultado es erroneo, ocurrio un overflow respecto al tamanio de la estructura \n");
        return a;//Ver algun valor apra marcar error 
	}
      siguiente = (((a.n[i+1]&mascara) != 0)? 0b1000000000000000 : 0b0);//cambiar esto a if
      a.n[i] = a.n[i]>>1;
      a.n[i] = a.n[i] + siguiente;
      }
      a.n[15] = a.n[15]>>1;
    }
  return a;
}rn a;
}

//Ej6

nro multRuso(nro a, nro b){
  nro r;
  for(int i=0; i<NROCONS; r.n[i]=0b0,i++);
  while (!nro_equal0(b)) {
     if (b.n[0] & 1)  r = nro_suma(r,a);
     a = nro_izq(a,1);
     b = nro_der(b,1);
 }
  return r;
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
  for(int i=0;i<NROCONS; a.n[i]=0b1111111111111111,i++);
  printf("RES = %d\n", compara_cero(a));
  return 1;
  */

  //Ej6
  /*
  nro a; 	//5
  for(int i=1;i<NROCONS; a.n[i]=0b0,i++);
  a.n[0] = 0b101;
  nro b; //2
  for(int i=1;i<NROCONS; b.n[i]=0b0,i++);
  b.n[0] = 0b10;
  print(multRuso(a,b));
  return 1;
  */

}

int main(int argc, char **argv)
{	
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
  */


	//Codificador((int)*argv[1]);
	/*unsigned a=mult(2,2);
	unsigned b=mult(2,3);
	printf("%d\n %d\n",a,b);
	*/
	nro a,b;
	for(int i=0;i<NROCONS; a.n[i]=0b1111111111111111,i++);
	for(int i=0;i<NROCONS; b.n[i]=0b1111111111111111,i++);
	b.n[0]=0b000000000000000;
	//a.n[0]=0b1111111111111110;
	nro c=multRuso(a,b);
	printf("a=\n");
	printB(a);
	//printf("\nb=\n");
	//printB(b);
	printf("\nc=\n");
	printB(c);
	
	
	return 0;
}