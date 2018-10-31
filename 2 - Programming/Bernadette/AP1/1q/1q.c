#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define max 100

typedef char TipoT;

typedef struct cel
{
    TipoT conteudo;
    struct cel *prox;
}celula;

typedef struct
{
    celula *primeiro,*ultimo;
}Lstd;

Lstd* lstd_cria()
{
    Lstd* Lista = (Lstd*) malloc(sizeof(Lstd));
    Lista->primeiro=(celula*) malloc(sizeof(celula));
    Lista->ultimo=(celula*) malloc(sizeof(celula));
    Lista->ultimo->prox=NULL;
    Lista->primeiro=Lista->ultimo;
    return(Lista);
}

char lstd_vaz(Lstd *Lista)
{
    return(Lista->primeiro==Lista->ultimo);
}

void lstd_ins(TipoT x,Lstd *Lista)
{
    Lista->ultimo->prox=(celula*) malloc(sizeof(celula));
    Lista->ultimo=Lista->ultimo->prox;
    Lista->ultimo->conteudo=x;
    Lista->ultimo->prox=NULL;
}

char lstd_busc(char x, Lstd *Lista)
{
    int pos=0;
    int vf=0;
    celula *aux;
    aux=Lista->primeiro->prox;
    while (aux!=NULL)
    {
       if (aux->conteudo==x)
          vf++;
       pos++;
       aux=aux->prox;
    }
    return(vf);
}

void lstd_print(Lstd *Lista)
{
    celula *aux;
    aux=Lista->primeiro->prox;
    while (aux!=NULL)
    {
        printf("%c ",aux->conteudo);
        aux=aux->prox;
    }
}
