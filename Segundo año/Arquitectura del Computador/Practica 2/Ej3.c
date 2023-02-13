#include <stdio.h>

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

  sacarbinario(0.99268471);

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
  return 0;
}
