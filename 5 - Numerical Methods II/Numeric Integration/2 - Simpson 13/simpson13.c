/*
simpson13.c
Funções que calculam integrais através da Regra de Simpson 1/3   */
#include "simpson13.h"
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

//Função que recebe o intervalo, o número de divisões dele e retorna um vetor com os pontos de divisão
void Divisao(float a, float b, int n, float x[])
{
    float k;
    int i;
    k=((b-a)/(float)n);	 	 
    for(i=0;i<(n-1);i++)
      x[i]= a + (i+1)*k;	 
}

//Calcula a integral pela regra de Simpson 1/3 Fechada Simples
float SimpFechadaSimples(float delta, float f1, float f2, float f3)
{
    float R;
    R= (delta/3)*(f1 + 4*f2 + f3);
    return R;
}

//Calcula a integral pela regra de Simpson 1/3 Fechada Estendinda
float SimpFechadaEstendida(float a, float b, int n, float f1, float f3, float fx[])
{
    float H,R;
    int i;
    if (n<=1) return -1;//Existem no mínimo 2 divisões 
    H=(b-a)/(float)n;//Distância entre cada divisão
    R= f1 + f3; 
    R= R + 4*fx[0];
    for (i=1;i<n-1;i++)
    {
       if(i%2==0)
          R= R + 4*fx[i];
       else
          R= R + 2*fx[i];
    } 
    R= R*(H/3);
    return R;
}

//Calcula a integral pela regra de Simpson 1/3 Aberta Simples
float SimpAbertaSimples(float a, float b, float fx[])
{
    float H,R;
    H=(b-a)/4;
    R= ((4*H)/3)*(2*fx[0] - fx[1] + 2*fx[2]);
    return R; 
}

//Calcula a integral pela regra de Simpson 1/3 Aberta Estendida
float SimpAbertaEstendida(float a, float b, int n,float x[], float fx[])
{
    float H,R;
    int i,p;
    if (n<=1) return -1;//Existem no mínimo 2 divisões
    H=(b-a)/(float)n;//Distância entre cada divisão
    R= SimpAbertaSimples(a,a+H, &(fx[0],fx[1],fx[2]) );//Calcula a integral do 1º intervalo  
    p=3;
    for(i=0;i<n-2;i++)//Soma com as integrais do 2º até o penúltimo intervalo
    {
       R= R + SimpAbertaSimples(x[p],x[p+4],&(fx[p+1],fx[p+2],fx[p+3]));
       p=p+4;  
    }
    if (n>1) R=R + SimpAbertaSimples(x[p],b,&(fx[p+1],fx[p+2],fx[p+3]));//Soma com a integral do último intervalo   
    return R; 
}
