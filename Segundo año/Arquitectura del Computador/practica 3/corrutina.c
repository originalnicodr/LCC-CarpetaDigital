#include <stdio.h>
#include "guindows.h"

task t1, t2, t3 ,taskmain;

void ft1(){
	double d;
	int a;
	printf("Direccion de a=%p\n",&a);
	for(d=-1;;d+=0.001) {
		printf("d=%f\n", d);
		TRANSFER(t1,t2);
	}
}

void ft2(){
	int i,b;
	printf("Direccion de b=%p\n",&b);
	for(i=0;i<10000;i++) {
		printf("i=%d\n", i);
		TRANSFER(t2,t3);
	}
	//TRANSFER(t2, taskmain);
}

void ft3(void){
    int i,c;
	printf("Direccion de c=%p\n",&c);
    for (i = 0; i < 5000; i++) {
        printf("t3: i=%d\n", i);
        TRANSFER(t3, t1);
    }
    TRANSFER(t3, taskmain);
}

int main(){
	stack(t1,ft1);
	stack(t2,ft2);
    stack(t3,ft3);
	TRANSFER(taskmain,t1);
	return 0;
}