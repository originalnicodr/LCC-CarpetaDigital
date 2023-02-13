#include <stdio.h>
#include "bsort.h"

#define NELEMS(a) (sizeof((a))/sizeof(int))

int main(void) {
  int arr1[] = { 2, 4, 1, 3, 7, 8, 6, 9, 11, 0, 5, 10, 20 };
  int arr2[] = { 1, 3, 1, 3, 7, 8, 8, 9, 11, 0, 5, 10, 20 };
  int arr3[] = { 20, 10, 5, 0, 11, 9, 6, 8, 7, 3, 1, 4, 2 };

  bsort(arr1, NELEMS(arr1));

  for (i  = 0; i < NELEMS(arr1); ++i)
    printf("%d ", arr1[i]);
  puts("");

printf("RESULTADO INT ES PERMUTACION: %d\n", es_permutacion(arr1,arr2,NELEMS(arr1)));
printf("RESULTADO INT ES PERMUTACION: %d\n", es_permutacion(arr1,arr3,NELEMS(arr1)));

for (i  = 0; i < NELEMS(arr2); ++i)
    printf("%d ", arr2[i]);
  puts("");
  
  for (i  = 0; i < NELEMS(arr3); ++i)
    printf("%d ", arr3[i]);
  puts("");

  return 0;
}
