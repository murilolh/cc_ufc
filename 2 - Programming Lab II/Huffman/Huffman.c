#include "heap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct arv
{
    char c[8];
    int f;
    struct arv* esq;
    struct arv* dir;
}Arv;

Arv Aux[256];
Arv Vet[256];
Arv *List[256];

int compare (const void * a, const void * b)
{
    Arv *c=(Arv*)a;
    Arv *d=(Arv*)b;
    return (c->f - d->f);
}

int main (int argc, char *argv[])
{
    if (argc<2)
    {
        printf("Voce deve digitar um argumento!");
        getch();
        exit(1);
    }
    FILE *fd;
    fd = fopen(argv[1], "r");
    int i;
    int k=0;
    for (i=0;i<=255;i++)
    {
        Aux[i].f=0;
        itoa(i,Aux[i].c,2);
    }
    while (!feof(fd))
        Aux[(getc(fd)) & 255].f++;
    for (i=0;i<=255;i++)
        if (Aux[i].f != 0)
        {
            Vet[k].f=Aux[i].f;
            strcpy(Vet[k].c,Aux[i].c);
            List[k] = &Vet[k];
            k++;
        }
    heapCria(*List,k,sizeof(Arv),compare);
    int h;
    for(h=0;h<k;h++)
        if (List[k-1]->f >= List[h]->f)
        {

        }
    for(h=0;h<k;h++)
        printf("\n%0.8s = %d" , List[h]->c , List[h]->f);
    fclose (fd);
}
