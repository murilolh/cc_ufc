/*
trapezio.c
Funções que calculam integrais através da Regra do Trapézio*/
#include "trapezio.h"
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

//Calcula a integral pela regra do Trapézio Fechada Simples
float TraFechadaSimples(float a, float b, float f1, float f3)
{
    float R;
    R= (b-a)*((f1+f3)/2);
    return R; 
}

//Calcula a integral pela regra do Trapézio Fechada Estendinda
float TraFechadaEstendida(float a, float b, int n, float f1, float f3, float fx[])
{
    float H,R;
    int i;
    if (n<=0) return -1;//Existe no mínimo 1 divisão
    H=(b-a)/(float)n;//Distância entre cada divisão
    R= f1 + f3;
    for (i=0;i<n-1;i++)
       R= R + 2*fx[i];
    R= R*(H/2);
    return R;
}

//Calcula a integral pela regra do Trapézio Aberta Simples
float TraAbertaSimples(float a, float b, float fx[])
{
    float H,R;
    H=(b-a)/3;
    R= ((3*H)/2)*(fx[0]+fx[1]);
    return R; 
}

//Calcula a integral pela regra do Trapézio Aberta Estendida
float TraAbertaEstendida(float a, float b, int n,float x[], float fx[])
{
    float H,R;
    int i,p;
    if (n<=0) return -1;//Existe no mínimo 1 divisão
    H=(b-a)/(float)n;//Distância entre cada divisão
    R= TraAbertaSimples(a,a+H, &(fx[0],fx[1]) );  //Calcula a integral do 1º intervalo  
    p=2;
    for(i=0;i<n-2;i++)//Soma com as integrais do 2º até o penúltimo intervalo
    {
       R= R + TraAbertaSimples(x[p],x[p+3],&(fx[p+1],fx[p+2]));
       p=p+3;  
    }
    if (n>1) R=R + TraAbertaSimples(x[p],b,&(fx[p+1],fx[p+2]));//Soma com a integral do último intervalo
    return R; 
}
