/*
gauss.c
Funções que calculam integrais através de Gauss-Hermite, Laguerre e Chebyshev*/
#include "gauss.h"
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

//Cria a lista de termos do Polinômio
TipoLista* crialista() 
{
    TipoLista* Lista = (TipoLista*) malloc(sizeof(TipoLista));
    Lista->primeiro = (celula*) malloc(sizeof(celula));
    Lista->ultimo   = (celula*) malloc(sizeof(celula));
    Lista->ultimo->prox = NULL; 
    Lista->primeiro = Lista->ultimo;
    return(Lista);
}

//Insere termos no Polinômio     
void Inserir(int x,TipoLista *Lista) 
{
    Lista->ultimo->prox = (celula*) malloc(sizeof(celula));
    Lista->ultimo->prox->termo = x;
    Lista->ultimo = Lista->ultimo->prox;
    Lista->ultimo->prox = NULL;    
}

//Imprime a lista de termos
void ImprimeLista(TipoLista *Lista)
{
    celula *aux;
    aux=Lista->primeiro->prox;
    while (aux!=NULL) 
    {     
        printf("%d ",aux->termo);
        aux=aux->prox;
    }
}

//Calcula f(x) ataves de um x dado
float getfx(float x, TipoLista *Polinomio)
{
    float f;
    int i;
    celula *aux;
    aux=Polinomio->primeiro->prox;
    i=0;
    f=0;
    while (aux!=NULL) 
    {
        f=f + (aux->termo)*(pow(x,i));
        i++;
        aux=aux->prox;
    }
    return f;   
}

//Calcula a integral por Hermite, Laguerre ou Chebyshev
float metodo(int n, float R[], float W[], TipoLista *P)
{
    float INT;
    int i;
    float fx[n];
    float t;
    for (i=0;i<n;i++)
       fx[i] = getfx(R[i],P);
    INT=0;
    for (i=0;i<n;i++)
       INT = INT + fx[i]*W[i];    
    return INT; 
}
