#include<stdio.h>
#include<stdlib.h>
#include<cmath>

void cria_vetor_X(float A[64][64], float solucao[64], float solucao[64]);

void cria_matriz_C(float A[64][64], float C[64][64]);

void cria_vetor_G(float A[64][64], float solucao[64], float v_G[64]);

void mult_MV(float M[64][64], float V[64], float aux[64]);

void cria_vetor_de_iteracoes(float A[64][64], float v_G[64], float solucao[64], float aux[64]);

void troca_V(float vet1[64], float vet2[64]);

float retorna_maior(float V[10]);

float calculo_do_delta(float solucao[64], float vet_1[64], float vet_aux[64]);

void gauss_jacobi(float A[64][64], float solucao[64], float resultado[64]);
