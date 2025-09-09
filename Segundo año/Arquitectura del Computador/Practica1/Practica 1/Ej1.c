#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int main(){
  //Ej1
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
  //printf("%d\n", menouno);
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
  return 0;
}
