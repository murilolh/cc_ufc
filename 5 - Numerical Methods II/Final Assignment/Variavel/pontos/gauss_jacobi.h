#include<stdio.h>
#include<stdlib.h>
#include<cmath>

void cria_vetor_X(int d, float A[200][200], float* resultado, float* vet);
void cria_matriz_C(int d, float A[200][200], float C[200][200]);
void cria_vetor_G(int d, float A[200][200], float* resultado, float* v_G);
void mult_MV(int d, float M[200][200], float* V, float* aux);
void cria_vetor_de_iteracoes(int d, float A[200][200], float* v_G, float* vet_x, float* aux);
void troca_V(int d, float* vet1, float* vet2);
float retorna_maior(int d, float* V);
float calculo_do_delta(int d, float* vet_x, float* vet_1, float* vet_aux);
void gauss_jacobi(int d, float A[200][200], float* solucao, float* resultado);

