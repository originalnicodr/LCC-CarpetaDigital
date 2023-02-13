
static void swap(int *p, int *q) {
  int t = *p;
  *p = *q;
  *q = t;
}

void bsortg(void *base, int tam, size_t size, CmpFunc cmp)
{
    int ordenado = 0, i;
    while(!ordenado)
    {
        ordenado = 1;
        for(i = 0; i < tam - 1; ++i)
            if(cmp(base + i * size, base + i * size + 1 * size))
            {
                ordenado = 0;
                swap((base + i * size), (base + i * size + 1 * size));
            }
    }
}
