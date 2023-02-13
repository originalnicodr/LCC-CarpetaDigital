static void swap(int *p, int *q) {
  int t = *p;
  *p = *q;
  *q = t;
}

void bsort(int datos[], int tam) {
  int ordenado = 0, i;

  for(int j = 0; j<tam; j++) {
    for (i = 0; i < tam - 1; ++i)
      if (datos[i] > datos[i + 1]) {
        swap(&datos[i], &datos[i + 1]);
      }
  }
}

int es_permutacion(int *arr1, int *arr2, int tam){
	bsort(arr1,tam);
	bsort(arr2,tam);
	
	for(int i=0; i<tam; i++){
		if(arr1[i] != arr2[i]){
			return 0;
		}
	}
	return 1;
}
