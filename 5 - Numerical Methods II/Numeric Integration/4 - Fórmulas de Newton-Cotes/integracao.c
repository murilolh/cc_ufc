/*
integracao.c
Funções que calculam integrais através das Formulas de Newton-Cotes */
#include "integracao.h"
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

//Função que recebe o intervalo, o número de divisões dele e retorna um vetor com os pontos de divisão
void Divisao(float a, float b, int n, float x[])
{
    float k;
    int i;
    k=((b-a)/(float)n);	 	 
    for(i=0;i<(n-1);i++)
      x[i]= a + (i+1)*k;	 
}

//Calcula a integral pela regra do Trapézio Fechada 
float TraFechada(float a, float b, TipoLista *P)
{
    float R,f1,f2;
    f1= getfx(a,P);
    f2= getfx(b,P);
    R= (b-a)*((f1+f2)/2);
    return R;
}

//Calcula a integral pela regra do Trapézio Aberta 
float TraAberta(float a, float b, TipoLista *P)
{
    int i;
    float H,R;
    float x[2], fx[2];
    Divisao(a,b,3,x);
    for(i=0;i<2;i++)
       fx[i]= getfx(x[i],P);
    H=(b-a)/3;
    R= ((3*H)/2)*(fx[0]+fx[1]);
    return R; 
}

//Calcula a integral pela regra de Simpson 1/3 Fechada 
float Simp13Fechada(float a, float b, TipoLista *P)
{
    float R,f1,f2,f3,delta;
    delta=(b-a)/2;
    f1= getfx(a,P);
    f2= getfx(((b+a)/2),P);
    f3= getfx(b,P);
    R= (delta/3)*(f1 + 4*f2 + f3);
    return R;
}

//Calcula a integral pela regra de Simpson 1/3 Aberta 
float Simp13Aberta(float a, float b, TipoLista *P)
{
    int i;
    float H,R;
    float x[3], fx[3];
    Divisao(a,b,4,x);
    for(i=0;i<3;i++)
       fx[i]= getfx(x[i],P);
    H=(b-a)/4;
    R= ((4*H)/3)*(2*fx[0] - fx[1] + 2*fx[2]);
    return R; 
}

//Calcula a integral pela regra de Simpson 3/8 Fechada
float Simp38Fechada(float a, float b, TipoLista *P)
{
    int i;
    float R,H,f1,f4;
    float x[2], fx[2];
    Divisao(a,b,3,x);
    for(i=0;i<2;i++)
       fx[i]= getfx(x[i],P);
    f1= getfx(a,P);
    f4= getfx(b,P);
    H= (b-a)/3;
    R= (3*H/8)*(f1 + 3*fx[0] + 3*fx[1] + f4);
    return R;
}

//Calcula a integral pela regra de Simpson 3/8 Aberta
float Simp38Aberta(float a, float b, TipoLista *P)
{
    int i;
    float R,H;
    float x[4], fx[4];
    Divisao(a,b,5,x);
    for(i=0;i<4;i++)
       fx[i]= getfx(x[i],P);
    H= (b-a)/5;
    R= (5*H/24)*(11*fx[0] + fx[1] + fx[2] + 11*fx[3]);
    return R;
}

//Calcula a integral pela fórmula de Newton-Cotes de 4º grau Fechada
float NewtonCotes4F(float a, float b, TipoLista *P)
{
    int i;
    float H,R,f1,f5;
    float x[3], fx[3];
    Divisao(a,b,4,x);
    for(i=0;i<3;i++)
       fx[i]= getfx(x[i],P);
    f1= getfx(a,P);
    f5= getfx(b,P);
    H= (b-a)/4;
    R= (2*H/45)*(7*f1 + 32*fx[0] + 12*fx[1] + 32*fx[2] + 7*f5);
    return R;
}

//Calcula a integral pela fórmula de Newton-Cotes de 4º grau Aberta
float NewtonCotes4A(float a, float b, TipoLista *P)
{
    int i;
    float R,H;
    float x[5], fx[5];
    Divisao(a,b,6,x);
    for(i=0;i<5;i++)
       fx[i]= getfx(x[i],P);
    H= (b-a)/6;
    R= (6*H/20)*(11*fx[0] - 14*fx[1] + 26*fx[2] - 14*fx[3] + 11*fx[4]);
    return R;
}

