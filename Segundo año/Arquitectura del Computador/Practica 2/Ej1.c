#include <stdio.h>
#include <ieee754.h>
#include <assert.h>

//Ejercicio 1

unsigned int Fexp(float f){//Extrae exponente de flotante
   int *a=(int*)&f;
  return (*a>>23)&0b11111111;//aplico un corrimiento del numero y uso & con una mascara para sacar el exponente
}

unsigned int Fmant(float f){//extrae mantisa de flotante
  int *a=(int*)&f;
  return(*a&0b11111111111111111111111);//0b11111111111111111111111
}

int main(){
  float ff=15;
  union ieee754_float a;
  a.f=ff;
  assert(a.ieee.exponent==Fexp(ff));
  assert(a.ieee.mantissa==Fmant(ff));
  return 0;
}
