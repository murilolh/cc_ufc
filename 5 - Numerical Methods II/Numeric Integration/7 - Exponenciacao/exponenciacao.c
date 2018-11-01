/*
exponenciacao.c
Funções que calculam integrais através de Exponenciacao simples e dupla*/
#include "exponenciacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

#define E 2.71828183

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

//Calcula cosh(x) ataves de um x dado
float coshiper(float x)
{
   return((0.5)*(pow(E,x)+pow(E,-x)));
}

//Calcula senh(x) ataves de um x dado
float senhiper(float x)
{
   return((0.5)*(pow(E,x)-pow(E,-x)));
}

//Calcula tgh(x) ataves de um x dado
float tghiper(float x)
{
   return((senhiper(x))/(coshiper(x)));
}

//Obtém todos os alphas da parametrização
void getalpha(int n, float alpha[])
{
   float delta, a;
   int i;
   delta= 2/(float)n;
   a=-1;
   for(i=0;i<=n;i++)
   {
      alpha[i] = a;
      a = a + delta;
   }
}

//Calcula x(alpha) de todos os alphas dados
void getxalpha(int n, float alpha[], float xalpha[], float xc)
{
   int i;
   for(i=0;i<=n;i++)
      xalpha[i] = xc*tghiper(alpha[i]);      
}

//Calcula f(xalpha) de todos os x(alpha) dados
void getfxalpha(int n, float xalpha[], float fxalpha[], TipoLista *P)
{
   int i;
   for(i=0;i<=n;i++)
      fxalpha[i] = getfx(xalpha[i],P); 
}

//Calcula a integral pelo método da Exponencial simples
float ExpSimples(int n, float xc, float alpha[], TipoLista *P)
{
   int i;
   float INT;
   float xalpha[n+1];
   float fxalpha[n+1];
   INT  = 0;  
   getxalpha(n,alpha,xalpha,xc);
   getfxalpha(n,xalpha,fxalpha,P);
   for(i=0;i<=n;i++)
      INT  = INT + ((fxalpha[i])/pow(coshiper(alpha[i]),2));
   INT = INT * ((2*xc)/(float)n);
   return INT;     
} 

//Calcula a integral pelo método da Exponencial dupla
float ExpDupla(int n, float xc, float alpha[], TipoLista *P)
{
   float INT;
   INT  = 0;  
   return INT;    
} 
