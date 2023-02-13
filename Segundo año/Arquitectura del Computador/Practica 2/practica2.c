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

//Ejerciocio 1

unsigned int Fexp(float f){//Extrae exponente de flotante
   int *a=(int*)&f;
  return (*a>>23)&0b11111111;//aplico un corrimiento del numero y uso & con una mascara para sacar el exponente
}

unsigned int Fmant(float f){//extrae mantisa de flotante
  int *a=(int*)&f;
  return(*a&0b11111111111111111111111);//0b11111111111111111111111
}

int myisnan(float f){
  return ((Fexp(f)==0b11111111)&&(Fmant(f)!=0));
}

int myisnan2(float f){//Un numero Nan tiene la propiedad que es diferente a si mismo
  return(!(f==f));
}

//Ejercicio 3
//Numero de abogadro: 6,0225x10^23
//log_bx=n <=>x=b^n
//log_2(10^23)=n <=> (10^23)=2^n
//log_2(10^23)=(log_10(10^23))/(log_10(2))=23/(log_10(2))=76,40434618
//6,0225x10^23=6,0225x2^(76,40434618)=6,0225x2^(76)x2^(0,40434618)

//2^(0,40434618)=1,323488978

//6,0225x2^(76)x2^(0,40434618)=6,0225x2^(76)x1,323488978=6,0225x2^(76)x1,323488978=
//=6,0225x1,323488978x2^(76)=7,970738839x2^(76)

//Multiplicamos y dividimos por 2^2 para modificar la mantisa y aumentar el exponente en 2

//7,970738839x2^(76)*1=7,970738839x2^(76)*(2^2/2^2)=(7,970738839/2^2)x2^(76)*(2^2)=1,99268471*2^(78)

//Tenemos el 1, implicito de la estandarizacion IEEE 754, por lo que pasaremos la parte
//fraccionaria del numero a binario. Para hacerlo utilizaremos la funcion sacarbinario.

//sacarbinario(0.99268471);

//Se calcula el el numero del exponente para flotante y doble aplicando el sesgo en cada caso:
//78 + 127 = 205 para flotante
//78 + 1023 = 1101 para doble

//Luego se calcula cada exponente en binario

//Por lo tanto, concluimos que el numero 6,0225x10^23 en binario es:
//(1,1111111000100000100101011100110010110000011100100100)_2 * 2^(78)
//double
//0 | 00011001101 | 1111111000100000100101011100110010110000011100100100
//float
//0 | 11001101 | 11111110001000001001010

//La mantisa se le truncan los bits menos significativos para que la mantisa sea de 23 bits
//en flotante.

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

//Para representar el numero mas chico 

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
  printf("a= ");
  numero_print(a);
  puts("");
  printf("b= ");
  numero_print(b);
  puts("");
  //tengo los exponentes iguales
  res.e=a.e;//cualquiera de los dos
  if (a.signo==b.signo){//(((a.signo==0)&&(b.signo==0)||((a.signo==1)&&(b.signo==1))){//caso ambos positivos o ambos negativos
    res.f=a.f+b.f;
    if((res.f<a.f)||(res.f<b.f)){//hubo un overflow?
      res.f=res.f>>1;
      res.f=res.f|0b100000000000000000;//res.f=res.f+0b100000000000000000;//revisar esto
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
  //desplazamiento de temp para llegar al primer 1, luego cuando se encuentra
  //empezar a contar hasta llegar a 18 bits, eso es la cantidad de bits que se van
  //a poder salvar del resultado, lo mas cercano. Luego truncar guardando el
  //resultado en res y modificando el exponente
  return res;
}

void sacarbinario(double x){//le doy parte fraccionaria y la pasa a binario
  double a=x*2;
  printf("Binario: ");
  int i=0;
  for(;i<52;i++){
    if(a>1){
      printf("1");
      a=(a-1)*2;
    }
    else{
      printf("0");
      a=a*2;
    }
  }

}


int main(){
  float ff=15;
  union ieee754_float a;
  a.f=ff;
  assert(a.ieee.exponent==Fexp(ff));
  assert(a.ieee.mantissa==Fmant(ff));
  /*BinaryPrintF(f);
  binaryPrint(Fexp(f));
  binaryPrint(Fmant(f));
  printf("exp: %d\n mant: %d\n",a.ieee.exponent,a.ieee.mantissa );
  */
  float g = 0.0;
  float f = 0.0 / g;
  printf("f: %f\n", f);
  // ADVERTENCIA: ‘NAN’ es una extension de GCC.
  if (myisnan(f)) printf("myisnan dice que si\n");
  if (myisnan2(f)) printf("myisnan2 dice que si\n");
  if (isnan(f)) printf("isNaN dice que sı\n");
  float h=1/g;
  printf("%f\n",h );
  if (h==h) puts("infinito");//No ocurre lo mismo, la comparacion de inf==inf da true
  printf("%f\n", h+3 );//La suma de infinito positivo mas un numero da positivo

  //Ejercicio 4

  struct _numero n1,n2;
  n1.f=0b010000000000000010;
  n2.f=0b001000000000000110;
  n1.e=0b0000000000000001;
  n2.e=0b0000000000000001;
  n1.signo=0;
  n2.signo=0;
  numero_print(producto_numero(n1,n2));
  puts("");
  binaryPrint(205);
  //numero_print(suma_numero(n1,n2));
/*  printf("n1= ");
  numero_print(n1);
  puts("");
  printf("n2= ");
  numero_print(n2);
  puts("");
  numero_print(producto_numero(n1,n2));

  sacarbinario(0.602252);
*/
  sacarbinario(0.99268471);
  return 0;
}
