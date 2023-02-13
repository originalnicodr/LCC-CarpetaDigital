#ifndef __BSORT_H__
#define __BSORT_H__

typedef int (*CmpFunc)(void *, void *);

void bsort(int datos[], int tam);

#endif /* __BSORT_H__ */
