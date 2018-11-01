/*
integracao.c
Funções que calculam integrais através das Formulas de Newton-Cotes */
#include "integracao.h"
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

//Calcula a integral pela regra do Trapézio Fechada 
float TraFechada(float a, float b, float f1, float f3)
{
    float R;
    R= (b-a)*((f1+f3)/2);
    return R; 
}

//Calcula a integral pela regra do Trapézio Aberta 
float TraAberta(float a, float b, float fx[])
{
    float H,R;
    H=(b-a)/3;
    R= ((3*H)/2)*(fx[0]+fx[1]);
    return R; 
}

//Calcula a integral pela regra de Simpson 1/3 Fechada 
float Simp13Fechada(float delta, float f1, float f2, float f3)
{
    float R;
    R= (delta/3)*(f1 + 4*f2 + f3);
    return R;
}

//Calcula a integral pela regra de Simpson 1/3 Aberta 
float Simp13Aberta(float a, float b, float fx[])
{
    float H,R;
    H=(b-a)/4;
    R= ((4*H)/3)*(2*fx[0] - fx[1] + 2*fx[2]);
    return R; 
}

//Calcula a integral pela regra de Simpson 3/8 Fechada
float Simp38Fechada(float a, float b, float f1, float f4, float fx[])
{
    float R,H;
    H= (b-a)/3;
    R= (3*H/8)*(f1 + 3*fx[0] + 3*fx[1] + f4);
    return R;
}

//Calcula a integral pela regra de Simpson 3/8 Aberta
float Simp38Aberta(float a, float b, float fx[])
{
    float R,H;
    H= (b-a)/5;
    R= (5*H/24)*(11*fx[0] + fx[1] + fx[2] + 11*fx[3]);
    return R;
}

//Calcula a integral pela fórmula de Newton-Cotes de 4º grau Fechada
float NewtonCotes4F(float a, float b, float f1, float f5, float fx[])
{
    float R,H;
    H= (b-a)/4;
    R= (2*H/45)*(7*f1 + 32*fx[0] + 12*fx[1] + 32*fx[2] + 7*f5);
    return R;
}

//Calcula a integral pela fórmula de Newton-Cotes de 4º grau Aberta
float NewtonCotes4A(float a, float b, float fx[])
{
    float R,H;
    H= (b-a)/6;
    R= (6*H/20)*(11*fx[0] - 14*fx[1] + 26*fx[2] - 14*fx[3] + 11*fx[4]);
    return R;
}

