#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>



//Ej5

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

//Operaciones avisando overflow//

nro nro_suma_flag(nro a, nro b){
  nro r;
  // Inicializacion en 0
  int i;
  for(i=0; i<NROCONS; r.n[i]=0, i++);
  for(i=0; i<NROCONS; i++){//iteracion en la estructura
    r.n[i] = r.n[i] + a.n[i] + b.n[i];
    if ((r.n[i]<a.n[i])||(r.n[i]<b.n[i])){
	    if (i!=NROCONS-1){
			printf("El resultado de la suma es erroneo, ocurrio un overflow respecto al tamanio de la estructura \n");
			return r;
		}
        r.n[i+1]++;
    }
  }
  return r;
}

nro nro_izq_flag(nro a, unsigned c){//c es cantidad de lugares que se mueve
  int mascara = 0b1000000000000000;
  int actual ,anterior;
  int j,i;
  for(j=0; j<c; j++){
	  for(i=NROCONS-1;i>0;i--){
		  if(i==NROCONS-1&&(a.n[i]&mascara!=0)){
			  printf("El resultado del corrimiento es erroneo, ocurrio un overflow respecto al tamanio de la estructura \n");
			  return a;
		  }
		  anterior=(((a.n[i-1]&mascara) != 0)? 0b1 : 0b0);
		  a.n[i] = a.n[i]<<1;
          a.n[i] = a.n[i]+anterior;
		}
		a.n[0]=a.n[0]<<1;
	}
  return a;
}

nro nro_der_flag(nro a, unsigned c){//c es cantidad de lugares que se mueve
  int mascara = 0b0000000000000001;
  short int siguiente;
  short int actual,anterior;
  int i,j;
  for(j=0; j<c; j++){
    for(i=0; i<NROCONS-1; i++){//Por qué no recorrer del ultimo al primero?
      if(i==0&&(a.n[i]&mascara!= 0)){
        printf("El resultado del corrimiento es erroneo, ocurrio un overflow respecto al tamanio de la estructura \n");
        return a;
       }
      siguiente = (((a.n[i+1]&mascara) != 0)? 0b1000000000000000 : 0b0);//cambiar esto a if
      a.n[i] = a.n[i]>>1;
      a.n[i] = a.n[i] + siguiente;
    }
    a.n[15] = a.n[15]>>1;
  }
  return a;
}

//Operaciones ignorando overflow//

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

int main(){
  //Ej 5
  	puts("\nEjercicio 5 a");
  	nro f,g;
    int i;
  	for(i=0;i<NROCONS; f.n[i]=0b1111111111111111,i++);
  	for(i=0;i<NROCONS; g.n[i]=0b0000000000000000,i++);
  	g.n[0]=0b000000000000001;
  	nro_equal0(f)==1 ? printf("El numero es cero\n") : printf("El numero es distinto a cero\n");
  	nro_equal1(g)==1 ? printf("El numero es uno\n") : printf("El numero es distinto a uno\n");
  	nro_espar(f);

  	puts("\nPulse enter para continuar");
      while(getchar()!='\n');

  	puts("\nEjercicio 5 b");
  	puts("Avisando cuando ocurre overflow");
  	nro h;
  	puts("\ng>>3 =");
  	h=nro_der_flag(g,3);
  	puts("\n");
  	printB(h);
  	puts("\nf<<3 =");
  	h=nro_izq_flag(f,3);
  	puts("\n");
  	printB(h);

    puts("\nPulse enter para continuar");
      while(getchar()!='\n');

    puts("\nEjercicio 5 c");
  	puts("Avisando cuando ocurre algun overflow");
  	puts("\nf+g =");
  	h=nro_suma_flag(f,g);
  	puts("\n");
  	printB(h);
    puts("");
    return 0;
}
