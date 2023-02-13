static void swap(int *p, int *q) {
  int t = *p;
  *p = *q;
  *q = t;
}

void bsort(int datos[], int tam) {//ordena de menor a mayor
  int ordenado = 0, i;

  while (!ordenado) {
    ordenado = 1;
    for (i = 0; i < tam - 1; ++i)
      if (datos[i] > datos[i + 1]) {
        ordenado = 0;//si hago un cambiazo, tengo que verificar que ese elemento no tenga que seguir "subiendolo"
        swap(&datos[i], &datos[i + 1]);
      }
  }
}