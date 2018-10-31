#include <stdlib.h>
#include <stdio.h>
#define max 50

typedef struct
{
    int topo;
    char vet[max];
}Plhe;

Plhe* plhe_cria()
{
    Plhe* p = (Plhe*) malloc(sizeof(Plhe));
    p->topo = 0;
    return(p);
}

int plhe_vaz (Plhe *Pilha)
{
    return (Pilha->topo == 0);
}

void plhe_ins (Plhe *Pilha, char x)
{
    if (Pilha->topo == max)
       printf("Capacidade da pilha estourou!\n");
    else
    {
       Pilha->vet[Pilha->topo] = x;
       Pilha->topo++;
    }
}

int plhe_rem (Plhe *Pilha)
{
     if (plhe_vaz(Pilha))
        printf("Pilha vazia!\n");
     else
     {
        char v;
        v = Pilha->vet[Pilha->topo-1];
        Pilha->topo--;
        return (v);
     }
}
