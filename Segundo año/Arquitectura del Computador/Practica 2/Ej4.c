#include <stdio.h>
#include <ieee754.h>
#include <assert.h>
#include <math.h>

//Impresion binaria

void binaryPrint(int valor){
  int i;
  for(i=31; i>=0; i--){
    if((i+1)%8 == 0){
      printf(" ");
      }
      (valor&(1<<i)) ? printf("1"):printf("0");
    }
  printf(" =  %d\n", valor);
}

void BinaryPrintF(float f){
  int *a=(int*)&f;
  int i;
  for(i=31; i>=0; i--){
    if(i==30||i==22) printf(" ");
    (*a&(1<<i)) ? printf("1"):printf("0");
    }
    printf(" =  %f\n", f);
}

void binaryPrint4(unsigned long long valor){//imprime 36 bits de un long long
  int i;
  for(i=35; i>=0; i--){
    if((i+1)%8 == 0){
      printf(" ");
      }
      (valor&(1ll<<i)) ? printf("1"):printf("0");
    }
  printf(" =  %lli\n", valor);
  printf(" =  %llx\n", valor);
}

//Ejercicio 4
struct _numero{
  unsigned int signo:1;
  unsigned int f:18;
  unsigned int e:16;
};

//b=2, q=30000
//A continuacion calcularemos el mayor numero representable
//Como tenemos 16 bits en el exponente, el mayor numero representable en este
//sera 2^16-1=65535
//Restando el sesgo tendremos e-q=65535-30000=35535
//Luego, la mantisa mas grande representable sera 2^(-1)+2^(-2)+...+2^(-17)+2^(-18)=0,999996185
//Por ultimo, tomamos un signo=0 y calculamos el numero:
//Nmax=(-1)^0*0,999996185*2^35535=0,999996185*2^35535

//El menor numero representable sera interpretado como el numero cuyo valor absoluto sea menor igual
//al resto de los numeros representables, sin incluir el cero

//Tomaremos la mantisa mas chica posible, la cual es 2^(-18)
//Luego, tomaremos el menor numero representable en el exponente, el cual es 0
//Al aplicar el sesgo tendremos e-q=0-30000=-30000
//Tomaremos el signo=0 y calculamos el numero:
//Nmin=(-1)^0*2^(-18)*2^(-30000)=2^(-18)*2^(-30000

void numero_print(struct _numero n){
  printf("%d | ",n.signo);
  int i;
  for(i=15; i>=0; i--){//imprimimos exponente
    /*if((i+1)%8 == 0){
      printf(" ");
    }*/
      (n.e&(1<<i)) ? printf("1"):printf("0");
    }
  printf(" | ");
  for(i=17; i>=0; i--){//imprimimos mantisa
    /*if((i+1)%8 == 0){
      printf(" ");
    }*/
      (n.f&(1<<i)) ? printf("1"):printf("0");
    }
}

struct _numero suma_numero(struct _numero a, struct _numero b){
  struct _numero res;
  if (a.e!=b.e){//aumento el mas chico, puedo perder bits a la derecha (pero son menos significativos)
    //podria verse si conviene bajar en lugar de subir con el tema de los bits
    while (b.e<a.e) {
      b.e++;
      b.f=b.f>>1;
    }
    while (a.e<b.e) {
      a.e++;
      a.f=a.f>>1;
    }
  }
  //tengo los exponentes iguales
  res.e=a.e;//cualquiera de los dos
  if (a.signo==b.signo){//Si tienen el mismo signo
    res.f=a.f+b.f;
    if((res.f<a.f)||(res.f<b.f)){//hubo un overflow?
      res.f=res.f>>1;
      res.f=res.f|0b100000000000000000;
      res.e++;
    }
  }
  else if ((a.signo==1)&&(b.signo==0)){//a negativo y b positivo
    if (a.f<b.f){
      res.signo=0;
      res.f=b.f-a.f;
    }
    else{
      res.signo=1;
      res.f=a.f-b.f;
    }
  }
  else{//b negativo y a positivo
    if (b.f<a.f){
      res.signo=0;
      res.f=a.f-b.f;
    }
    else{
      res.signo=1;
      res.f=b.f-a.f;
    }
  }
  if (res.f==0) res.e=0;//en nuestro estandar tomamos que el cero se representa con el exponente igual a 0 (como en IEE 754)
  return res;
}

struct _numero producto_numero(struct _numero a, struct _numero b){
  //desplazamiento de temp para llegar al primer 1, luego cuando se encuentra
  //empezar a contar hasta llegar a 18 bits, eso es la cantidad de bits que se van
  //a poder salvar del resultado, lo mas cercano. Luego truncar guardando el
  //resultado en res y modificando el exponente
  struct _numero res;
  //devolver 0 si alguna de las mantisas es 0, ahorra pasar portodo el producto
  if ((a.f==0)||(b.f==0)){
    res.f=0;
    res.e=0;
    res.signo=0;
    return res;
  }
  //define el signo final del resultado
  if (a.signo==b.signo) res.signo=0;
  else res.signo=1;
  //sumo los exponentes
  res.e=a.e+b.e;
  //producto de mantisas
  unsigned long long temp=((unsigned long long)(a.f))*b.f;
  //corrimiento de las mantisas para que "entren" en 18 bits
  int i=0;
  for(i=35;(temp&(1ll<<i))==0;i--);
  //si se genera un overflow en el exponenete entonces devolvemos 0
  if (res.e<a.e||res.e<b.e){
    puts("ERROR, overflow en exponente");
    res.e=0;
    res.f=0;
    res.signo=0;
    return res;
  }
  if (i>17){
    temp=temp>>(i-17);//si el primer 1 encontrado esta en el final de los 36 bits, se deja como esta
    res.e=res.e+(i-17);
  }
  res.f=temp;

  return res;
}
 int main(){
   //Ejercicio 4

   struct _numero n1,n2;
   n1.f=0b010000000000000010;
   n2.f=0b001000000000000110;
   n1.e=0b0000000000000001;
   n2.e=0b0000000000000001;
   n1.signo=0;
   n2.signo=0;
   puts("n1+n2=");
   numero_print(suma_numero(n1,n2));
   puts("\nn1*n2=");
   numero_print(producto_numero(n1,n2));
   puts("");
 }
