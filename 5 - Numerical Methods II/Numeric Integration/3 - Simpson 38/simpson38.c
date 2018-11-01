/*
simpson38.c
Funções que calculam integrais através da Regra de Simpson 3/8   */
#include "simpson38.h"
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
