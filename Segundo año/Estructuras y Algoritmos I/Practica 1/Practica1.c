#include <stdio.h>
#include <malloc.h>
//Ejercicio 1
void bubble_sort(float arreglo[], int longitud) {
	int iter, i;
    for (iter = 0 ; iter < longitud - 1 ; iter++) {
		for (i = 0 ; i < longitud - iter - 1; i++) {
			if (arreglo[i] > arreglo[i + 1]) {
				float aux = arreglo[i];
				arreglo[i] = arreglo[i + 1];
				arreglo[i + 1] = aux;
			}
		}
	}
}

float mediana(float *arreglo, int longitud){
	float mediana;
	float arreglocopy[longitud];

	//malloc?
	//arreglocopy=malloc(sizeof(floa
    int i;
	for(i=0;i<longitud;i++){
		arreglocopy[i]=arreglo[i];
	}

	bubble_sort(arreglocopy, longitud);

	if(longitud%2==0){
		mediana= (arreglocopy[longitud/2] + arreglocopy[(longitud/2)-1])/2;
	}
	else{
		mediana=arreglocopy[(int)(longitud/2)]; //(longitud-1)/2)
	}
	return mediana;
}

/*int main(){
  float arreglo1[5]={5.5, 7, 2, 7, 2}, arreglo2[8]={4.7,2,3,3,10,5,7,5}, mediana1, mediana2;
  mediana1=mediana(arreglo1,5);
  mediana2=mediana(arreglo2,8);
  printf("Mediana de arreglo1: %f\nMediana de arreglo2: %f",mediana1, mediana2);
}*/

//Ejercicio 2

int stringlen(char* str){ //no cuenta \0
	int cont=0;
	for(;str[cont]!='\0';cont++);
	return cont;
}

void stringreverse(char* str){
	int cant=stringlen(str);
	//printf("cant=%d",cant);
	char copy[cant+1];
    int i;
	for(i=cant-1;i>=0;i--){
		copy[cant-1-i]=str[i];
	}
	copy[cant]='\0';
	//printf("copy=%s\n",copy);
	for(i=0;i<cant;i++){
			str[i]=copy[i];
	}
}

int stringconcat(char* str1, char* str2, int max){//suponemos que str1[max]
	int cant1=0, cant2=0;
	cant1=stringlen(str1);
	cant2=stringlen(str2);

	int cont=0;
    int i;
	if(cant1+cant2<=max){
		for(i=cant1;i<cant1+cant2;i++){//cant1+cant2+1 el +1 por el '\0' pero si lo ponemos aca lo cuenta como caracter contado
			str1[i]=str2[i-cant1];
			printf("Copia? %c\n", str1[i]);
			cont++;
		}
		str1[cant1+cant2]='\0'; //al p2
		printf("str1 = %s\n",str1);
	}
	else{
		for(i=cant1;i<max;i++){ //max es la cantidad de caracteres maximos, no la ultima posicion
			str1[i]=str2[i-cant1];
			cont++;
		}
		str1[max]='\0';
		printf("str1 = %s\n",str1);
	}
	return cont;
}

int string_compare(char* str1, char* str2){
    int min=0;

    if (stringlen(str1)<stringlen(str2)) min=stringlen(str1);
    else min=stringlen(str2);

    int i;
    for (i=0;i<min;i++){
        if(str1[i]<str2[i]) return -1;
        if(str1[i]>str2[i]) return 1;
    }

    if (stringlen(str1)<stringlen(str2)) return -1;
    if (stringlen(str1)>stringlen(str2)) return 1;
    return 0;
}

int string_subcadena(char* str1, char* str2){
    int min=0;

    if (stringlen(str1)<stringlen(str2)) min=stringlen(str1);
    else min=stringlen(str2);

    int i;
    for (i=0;i<min;i++){
        if (str1[i]==str2[i]) return i;
    }

    return -1;
}

char* string_unir(char* arregloStrings[], int capacidad, char* sep){
    int longitud=0, i; // 1
    char* rest;
    for(i=0;i<capacidad;i++){
        longitud += stringlen(arregloStrings[i]); // 3 + stringlen

    }
    longitud+= stringlen(sep)*(capacidad-1);
    rest=malloc(sizeof(char)*longitud);
    //stringconcat(rest,arregloString[0],capacidad);
    for(i=0;i<capacidad;i++){
        if(i!=0){
            stringconcat(rest,sep,longitud);
        }
        stringconcat(rest,arregloStrings[i],longitud);
    }
    printf("Prueba rest: %s\n",rest);
    return rest;
}

//int main(){
	//printf("Hola?\n%d",stringlen("hola"));
	/*char str[5]="hola";
	printf("%s\n",str);
	stringreverse(str);
	printf("%s\n",str);*/

	/*char str1[8]="hola", str2[5]="qsyL",str3[]="Anita lava la tina";
	printf("Caracteres copiados: %d",stringconcat(str1,str3,7));*/

	/*char str[5]="hola";
	printf("strlen= %d",stringlen(str));*/

	/*printf("Hola = Hola? %d\n",string_compare("Hola","Hola"));
	printf("Bola = Hola? %d\n",string_compare("Bola","Hola"));
	printf("Hola = Holasss? %d\n",string_compare("Hola","Holasssss"));*/

	//printf("hola con esa= %d",string_subcadena("hola","esa"));
    /*char* arregloStrings[4];//={"Hola"."Soy","Un","Cacahuate"};
    arregloStrings[0]="Hola";
    arregloStrings[1]="Soy";
    arregloStrings[2]="Un";
    arregloStrings[3]="Cacahuate";
    string_unir(arregloStrings,4," homosexual ");*/

//}

typedef struct {
int* direccion;
int capacidad;
} ArregloEnteros;

ArregloEnteros* arreglo_enteros_crear(int capacidad){ //tengo que usar malloc si o si
    ArregloEnteros* arreglo=NULL;
    arreglo=malloc(sizeof(ArregloEnteros*));
    arreglo->direccion= malloc(sizeof(int)*capacidad);
    arreglo->capacidad= capacidad;
    return arreglo;
}

void arreglo_enteros_destruir(ArregloEnteros* arreglo){
    free(arreglo->direccion);
    free(arreglo);
}

int arreglo_enteros_leer(ArregloEnteros* arreglo, int pos){
    //if(0 <= pos <arreglo->cantidad)){
        //printf("%d\n",arreglo->direccion[pos]);
        return arreglo->direccion[pos];
    //}
    /*else{
        printf("fuera de rango");

    }*/
}
void arreglo_enteros_escribir(ArregloEnteros* arreglo, int pos, int dato){
    arreglo->direccion[pos]=dato;
}

int arreglo_enteros_capacidad(ArregloEnteros* arreglo){
    return arreglo->capacidad;
}

void arreglo_enteros_imprimir(ArregloEnteros* arreglo){
    int i;
    for(i=0;i<arreglo->capacidad;i++){
        printf("%dº: %d\n",i ,arreglo_enteros_leer(arreglo, i));
    }
}

void arreglo_enteros_ajustar(ArregloEnteros* arreglo, int capacidad){
    arreglo->direccion=realloc(arreglo->direccion,capacidad);
    arreglo->capacidad=capacidad;
}

void arreglo_enteros_insertar(ArregloEnteros* arreglo, int pos, int dato){
    arreglo_enteros_ajustar(arreglo, arreglo->capacidad+1);
    int i;
    for(i=arreglo->capacidad-1;i>pos;i--){
        arreglo->direccion[i]=arreglo->direccion[i-1];
    }
    arreglo_enteros_escribir(arreglo, pos, dato);
}

void arreglo_enteros_eliminar(ArregloEnteros* arreglo, int pos){
    int i;
    for(i=pos;i<arreglo->capacidad-1;i++){
        arreglo->direccion[i]=arreglo->direccion[i+1];
    }
    arreglo_enteros_ajustar(arreglo,arreglo->capacidad-1);
}


/*int main (){
    ArregloEnteros* cosa=arreglo_enteros_crear(5);
    int i;
    for(i=0;i<5;i++){
        cosa->direccion[i]=i;
    }
    i=arreglo_enteros_leer(cosa,2);
    //arreglo_enteros_destruir(cosa);
    arreglo_enteros_escribir(cosa,4,10);
    arreglo_enteros_insertar(cosa,2,20);
    arreglo_enteros_eliminar(cosa,3);

    //printf("%d %d %d %d %d",cosa->direccion[0], cosa->direccion[1], cosa->direccion[2], cosa->direccion[3], cosa->direccion[4]);
    arreglo_enteros_imprimir(cosa);
    printf("Capacidad= %d", arreglo_enteros_capacidad(cosa));
    return 0;
}*/

typedef struct {
	float* datos;
	int filas, columnas;
} MatrizUni;

typedef struct { //las coordenadas para acceder a un elemento arrancaran de [0][0]
	float** datos;
	int filas, columnas;
} MatrizBi;

MatrizUni* matriz_crear_uni(int f, int c)
{
	MatrizUni * nueva = malloc(sizeof(MatrizUni));
	nueva->datos = malloc(sizeof(float) * f * c);
	nueva->filas = f;
	nueva->columnas = c;
	return nueva;
}

MatrizBi* matriz_crear_bi(int f, int c)
{
	MatrizBi * nueva = malloc(sizeof(MatrizBi));
	nueva->datos = malloc(sizeof(float*) * f);
	for(int i = 0; i < f; i++)
	{
		nueva->datos[i] = malloc(sizeof(float) * c); //[fila][columna]
	}
	nueva->filas = f;
	nueva->columnas = c;
	return nueva;
}

void matriz_destruir_uni (MatrizUni* matriz){
    free(matriz);
}

void matriz_destruir_bi (MatrizUni* matriz){
    for (int i=0;i<matriz->filas;i++){
        //free(matriz->datos[i]); //me tira error
    }
}

float matriz_leer_uni (MatrizUni* matriz, int f, int c){ //el numero de columnas no lo alcanza en las filas. Osea tengo el lugar 4*0+3, y el siguiente es 4*1 + 0
    return matriz->datos[matriz->columnas*f+c];
}

float matriz_leer_bi (MatrizBi* matriz, int f, int c){
    return matriz->datos[f][c];
}

void matriz_escribir_uni (MatrizUni* matriz, int f, int c, float dato){
    matriz->datos[matriz->columnas*f+c]=dato;
}

void matriz_escribir_bi (MatrizBi* matriz, int f, int c, float dato){
    matriz->datos[f][c]=dato;
}

void matriz_imprimir_uni (MatrizUni* matriz){
    for(int i=0; i<matriz->filas;i++){
        for(int j=0;j<matriz->columnas;j++){
            printf("%f ",matriz->datos[matriz->columnas*i+j]);
        }
        printf("\n");
    }
}

void matriz_imprimir_bi (MatrizBi* matriz){
    for (int i=0; i<matriz->filas;i++){
        for (int j=0;j<matriz->columnas;j++){
            printf("%f ",matriz->datos[i][j]);
        }
        printf("\n");
    }

}
//No estaria funcionando?
void matriz_intercambiarfilas_uni(MatrizUni* matriz, int fila1, int fila2){ //arranco de 0
    float dato;
    for(int i=matriz->columnas*fila1;i<matriz->columnas*(fila1+1);i++){
        dato=matriz->datos[i];
        matriz->datos[i]=matriz->datos[i+matriz->columnas*(fila2-fila2)];
        matriz->datos[i+matriz->columnas*(fila2-fila2)]=dato; //i-matriz->columnas*fila1+matriz->columna*fila2
    }
}

void matriz_intercambiarfilas_bi(MatrizBi* matriz, int fila1, int fila2){
    float* dato=malloc(sizeof(float) * matriz->columnas);
    for(int i=0;i<matriz->columnas;i++){
        dato[i]=matriz->datos[fila1][i];
        matriz->datos[fila1][i]=matriz->datos[fila2][i];
        matriz->datos[fila2][i]=dato[i];
    }
    free(dato);
}

MatrizUni* matriz_sumar_uni(MatrizUni* matriz1, MatrizUni* matriz2){
    MatrizUni* nueva= matriz_crear_uni(matriz1->filas,matriz1->columnas);
    for(int i=0; i<matriz1->filas;i++){
        for(int j=0;j<matriz1->columnas;j++){
            matriz_escribir_uni(nueva,i,j,matriz1->datos[matriz1->columnas*i+j]+matriz2->datos[matriz2->columnas*i+j]);
        }
    }
    return nueva;
}

MatrizBi* matriz_sumar_bi(MatrizBi* matriz1, MatrizBi* matriz2){
    MatrizBi* nueva= matriz_crear_bi(matriz1->filas,matriz2->columnas);
    for (int i=0; i<matriz1->filas;i++){
        for (int j=0;j<matriz1->columnas;j++){
            nueva->datos[i][j]=matriz1->datos[i][j]+matriz2->datos[i][j];
        }
    }
    return nueva;
}

MatrizUni* matriz_multiplicar_uni(MatrizUni* matriz1,MatrizUni* matriz2){
    MatrizUni* nueva= matriz_crear_uni(matriz1->filas,matriz2->columnas);
    float temp=0;

    for(int k=0;k<matriz1->columnas;k++){
        for (int i=0;i<matriz2->columnas;i++){
            for (int j=0; j<matriz2->filas;j++){//matriz2->filas==matriz1->columnas
                temp+=matriz1->datos[matriz1->columnas*k+j]*matriz2->datos[matriz2->columnas*j+i];
            }
            nueva->datos[nueva->columnas*k+i]=temp;
            temp=0;
        }
    }

    return nueva;
}

MatrizBi* matriz_multiplicar_bi (MatrizBi* matriz1, MatrizBi* matriz2){
    MatrizBi* nueva= matriz_crear_bi(matriz1->filas,matriz2->columnas);
    float temp=0;

    for(int k=0;k<matriz1->columnas;k++){
        for (int i=0;i<matriz2->columnas;i++){
            for (int j=0; j<matriz2->filas;j++){//matriz2->filas==matriz1->columnas
                temp+=matriz1->datos[k][j]*matriz2->datos[j][i];
            }
            nueva->datos[k][i]=temp;
            temp=0;
        }
    }
    return nueva;
}

typedef struct {
	float* datos;
	int orden;
} MatrizTriangularInf;

MatrizTriangularInf* matriztrianginf_crear(int orden){
    MatrizTriangularInf* nueva;
    int capacidad=0;
    for(int i=1;i<=orden;i++) capacidad+=i; //sumatoria de orden, para saber cuantos espacios tengo que tener en la cadena
    nueva=malloc(sizeof(MatrizTriangularInf));
    nueva->datos=malloc(sizeof(float)*capacidad);
    nueva->orden=orden;
    return nueva;
}

MatrizTriangularInf* matriztrianginf_destruir(MatrizTriangularInf* matriz){
    free(matriz->datos); //no recuerdo si habia que hacerle free a los dos
    free(matriz);
}

float matriztrianginf_leer(MatrizTriangularInf* matriz, int f, int c){ // arranca de [0][0]
    if (f<c) return 0;
    return matriz->datos[f+c+1]; //no va a quedar [3][2]==[2][3] por que si f<c ya lo filtre antes
}

void matriztrianginf_escribir(MatrizTriangularInf* matriz, int f, int c, float dato){
    if (f<c) printf("No puede modificar los elementos en las posiciones donde la coordenada fila es menor a la coordenada columna\n");
    else matriz->datos[f+c+1]=dato;
}

void matriztrianginf_imprimir(MatrizTriangularInf* matriz){
    for(int i=0;i<matriz->orden;i++){
        for (int j=0;j<matriz->orden;j++){
            printf("%f ",matriztrianginf_leer(matriz,i,j));
        }
        printf("\n");
    }
}

int main(){
    /*MatrizUni* matriz1= matriz_crear_uni(2,2);
    matriz_escribir_uni(matriz1,0,0,1);
    matriz_escribir_uni(matriz1,0,1,2);
    matriz_escribir_uni(matriz1,1,0,3);
    matriz_escribir_uni(matriz1,1,1,4);
    matriz_imprimir_uni(matriz1);

    matriz_imprimir_uni(matriz_multiplicar_uni(matriz1,matriz1));*/

    //matriz_intercambiarfilas_uni(matriz1,0,1);

    //matriz1=matriz_sumar_uni(matriz1,matriz1);

    /*MatrizBi* matriz= matriz_crear_bi(2,2);
    matriz_escribir_bi(matriz,0,0,1);
    matriz_escribir_bi(matriz,0,1,2);
    matriz_escribir_bi(matriz,1,0,3);
    matriz_escribir_bi(matriz,1,1,4);
    matriz_imprimir_bi(matriz);

    matriz_imprimir_bi(matriz_multiplicar_bi(matriz,matriz));*/

    //matriz_intercambiarfilas_bi(matriz,0,1);
    //matriz=matriz_sumar_bi(matriz,matriz);

    MatrizTriangularInf* matriz = matriztrianginf_crear(2);
    matriztrianginf_escribir(matriz, 0, 0, 1);
    matriztrianginf_escribir(matriz, 1, 0, 1);
    matriztrianginf_escribir(matriz, 1, 1, 1);
    matriztrianginf_imprimir(matriz);
}

