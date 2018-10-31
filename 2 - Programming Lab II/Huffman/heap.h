#include <string.h>

void descer(void *h, int n,int j, size_t size, int (*compare)(const void *, const void *));
void heapCria(void *h, int n, size_t size, int (*compare)(const void *, const void *));
void subir(void* h, int n, size_t size, int (*compare)(const void *, const void *));
void Inserir( void *h, void* x, int n, size_t size, int (*compare)(const void *, const void *) );
void Remover( void *h, int n, size_t size, int (*compare)(const void *, const void *) );
