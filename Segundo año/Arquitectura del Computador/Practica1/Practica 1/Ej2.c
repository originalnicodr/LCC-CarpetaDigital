#include <stdio.h>
#include <assert.h>

#include <stdlib.h>

//Ej 2

void rotarXOR(int *a, int *b, int *c){
  *a = (*a)^(*b);
  *b = (*b)^(*a);//a  *b=b^(a^b)=a
  *a = (*b)^(*a);//   *a=a^(a^b)=b
  *a = (*a)^(*c);//   *a=b^c
  *c = (*c)^(*a);//b  *c=c^a^(b^c)=a^b // *c=c^a=c^(b^c)=b
  *a = (*c)^(*a);//c  (b^c)^a^(a^b)=c  // *a=c^a=b^b^c=c
}
int main(){
  puts("\nEjercicio 2");
  char enter;
  int a=1,b=3,c=5;
  printf("A=%d B=%d C=%d\n",a,b,c);
  rotarXOR(&a,&b,&c);
  printf("A=%d B=%d C=%d\n",a,b,c);
  return 0;
}
