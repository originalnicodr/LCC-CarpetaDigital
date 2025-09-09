#include <stdio.h>

int main(int argc, char *argv[]){
  for(int i = 0; i<argc; printf("%s\n", argv[i]),i++);
}
