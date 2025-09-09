#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define NROCONS 16
typedef struct {
  unsigned short n[NROCONS];
} nro;

void bP(unsigned short valor){//Impresion de bits
  int i;
  for(i=15; i>=0; i--){
	if(valor&(1<<i)) printf("1");
	else printf("0");
	}
}

void printB(nro num){//Imprimir numeros de la estructura nro
  int i;
  for(i=NROCONS-1; i>=0; i--){
    bP(num.n[i]);
    printf(" ");
  }
}

nro nro_suma(nro a, nro b){
  nro r;
  // Inicializacion en 0
  int i;
  for(i=0; i<NROCONS; r.n[i]=0, i++);
  for(i=0; i<NROCONS; i++){//iteracion en la estructura
    r.n[i] = r.n[i] + a.n[i] + b.n[i];
    if ((r.n[i]<a.n[i])||(r.n[i]<b.n[i])){
	    if (i!=NROCONS-1) r.n[i+1]++;
    }
  }
  return r;
}

nro nro_izq(nro a, unsigned c){//c es cantidad de lugares que se mueve
  int mascara = 0b1000000000000000;
  int actual ,anterior;
  int j,i;
  for(j=0; j<c; j++){
	  for(i=NROCONS-1;i>0;i--){
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
  int j,i;
  for(j=0; j<c; j++){
    for(i=0; i<NROCONS-1; i++){
      siguiente = (((a.n[i+1]&mascara) != 0)? 0b1000000000000000 : 0b0);
      a.n[i] = a.n[i]>>1;
      a.n[i] = a.n[i] + siguiente;
    }
    a.n[15] = a.n[15]>>1;
  }
  return a;
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


//Ej6

nro multRuso(nro a, nro b){
  nro r;
  int i;
  for(i=0; i<NROCONS; r.n[i]=0b0,i++);
  while (!nro_equal0(b)) {
     if (b.n[0] & 1)  r = nro_suma(r,a);
     a = nro_izq(a,1);
     b = nro_der(b,1);
 }
  return r;
}

int main(){
  puts("\nEjercicio 6 ");
  puts("Ignoramos cuando ocurre algun overflow");
  nro k,j,h;
  int i;
  for(i=1;i<NROCONS; j.n[i]=0b0,i++);
  j.n[0] = 0b101;
  for(i=1;i<NROCONS; k.n[i]=0b0,i++);
  k.n[0] = 0b10;
  printf("j x k =\n");
  h=multRuso(j,k);
  puts("\n");
  printB(h);
  return 0;
}
