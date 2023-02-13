#include <stdio.h>

unsigned int Fexp(float f){//Extrae exponente de flotante
   int *a=(int*)&f;
  return (*a>>23)&0b11111111;//aplico un corrimiento del numero y uso & con una mascara para sacar el exponente
}

unsigned int Fmant(float f){//extrae mantisa de flotante
  int *a=(int*)&f;
  return(*a&0b11111111111111111111111);//0b11111111111111111111111
}

//Ejercicio 2

int myisnan(float f){
  return ((Fexp(f)==0b11111111)&&(Fmant(f)!=0));
}

int myisnan2(float f){//Un numero Nan tiene la propiedad que es diferente a si mismo
  return(!(f==f));
}

int main(){
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
  return 0;
}
