#include <stdio.h>
#include <conio.h>


/*int main(){

	int Edad;

	printf("Ingrese su edad\n");
	scanf("%d", &Edad);

	if(Edad > 64){
		printf("Seguridad Social");
		return 0;
	}
	if (Edad < 18) {
		printf("Exento");
		return 0;
	}
	printf("Imposible");
	return 0;
}*/

//Ejercicio 9
/*int main (){
	int i=1;
	while (i<=100){
		printf("%d\n",i);
		i++;
		}
}*/

//Ejercicio 10

/*int main (){
	int i=1;
	while (i<=100){
		printf("%d\n",i);
		i = 2 + i;
		}
}*/

//Ejercicio 11
/*int main(){
	int a, b;
	printf("Ingrese los extremos del intervalo\n");
	scanf("%d %d" ,&a ,&b);
	while (a>=b){
		printf("Ingrese los valores correctamente\n");
		scanf("%d %d" ,&a ,&b);
	}
	while(a<=b){
		printf("%d\n",a);
		a++;
	}
	return 0;
}*/

//Ejercicio 12: hecho!

//EJERCICIO 13

/*int main(){

	int numero;
	double a=1;

	printf("Ingrese un número\n");
	scanf("%d", &numero);
	while(numero > 0){
		a = numero * a;
		numero--;
		}
	printf("factorial: %2.lf", a);
	return 0;
	}*/

// EJERCICIO 14
/*
int main(){
	int cant, cont1=0, cont2=0,cont3=0, edad, edad1=0, edad2=0, edad3=0;
	float indice, prom1, prom2, prom3;
	printf("Ingrese la cantidad de pacientes\n");
	scanf("%d" ,&cant);
	while (cant>0){
		printf("Ingrese el indice del paciente\n");
		scanf("%f",&indice);
		printf("Ingrese la edad del paciente\n");
		scanf("%d",&edad);
		if(indice>0.9){
			cont2++;
			edad2=edad2+edad;
		}
		else if (indice>0.6){
			cont1++;
			edad1=edad1+edad;
		}
		edad3=edad3+edad;
		cont3++;
		cant--;
	}
	//printf("%d %d %d",cont1, cont2, cant);
	if(cont3!=0){
		prom3=edad3/cont3;
	}
	else prom3=0;
	if(cont1!=0){
		prom1=edad1/cont1;
	}
	else prom1=0;
	if(cont2!=0){
		prom2=edad2/cont2;
	}
	else prom2=0;
	printf("La edad promedio de los pacientes analizados es %f, la de los pacientes ingresados es %f y la de los operados es %f", prom1, prom2, prom3);
	return 0;
}
*/
//EJERCICIO 15

/*int maximo(int a, int b){
	if (a < b){
		return b;
		}
	return a;
	}

int main(){
	float a, b, c, d, max=0;
	printf("Ingrese 4 números\n");
	scanf("%f", &a);
	scanf("%f", &b);
	scanf("%f", &c);
	scanf("%f", &d);
	max = maximo(maximo(a, b), maximo(c, d));
	printf("El número más grande ingresado fue: %f\n", max);
	return 0;
	}
*/

//EJERCICIO 16

int ladosTriangulo (int a, int b, int c){
	if((a>0)&&(b>0)&&(c>0)&&(((a>b)&&(a>c)&&(b+c>a))||((b>a)&&(b>c)&&(a+c>b))||((c>a)&&(c>b)&&(a+b>c)))){
		return 1;
	}
	return 0;
}

//EJERCICIO 17

int esRectangulo (int a, int b, int c){
	if(ladosTriangulo(a,b,c)==1){
	     if((2*(max3(a,b,c))*(max3(a,b,c)))==(a*a+b*b+c*c)){
             return 1;
         }
         return 0;
	}
}

int max3(int a, int b, int c){
	if((a>=b)&&(a>=c)){
		return a;
	}
	if((b>=a)&&(b>=c)){
		return b;
	}
	return c;
}

int main (){
	printf("%d\n",esRectangulo(3,5,4));
	printf("%d\n",esRectangulo(5,13,12));
	printf("%d\n",esRectangulo(7,3,5));
}

//EJRCICIO 18

/*int pascua(int ano){ //no me gusta como lo define el ejercicio
	int A, B, C, D, E, F;
	A=ano;
	B=ano;
	C=ano;
	D=(19*A+24);
	E=(2*B+4*C+6*D+5);
	N=(22+D+E);
	return N;
}

int main(){
	int ano;
	printf("Ingrese el año a analizar\n")
	scanf("%d",&ano)
	if(pascua(ano)>31){
		printf("La fecha de pascua para el año dado sera el %d de abril",pascua(ano)-31);
		return 0;
	}
	printf("La fecha de pascua para el año dado sera el %d de marzo",pascua(ano));
	return 0;
}*/

//EJERCICIO 19

/*int fibonacci(int n){
	if (n==0){
		return 0;
	}
	if (n==1){
		return 1;
	}
	if (n>=2){
		return (fibonacci(n-1)+fibonacci(n-2));
	}
}

int main(){
	int n;
	scanf("%d",&n);
	printf("%d" ,fibonacci(n))
	return 0;
}*/
