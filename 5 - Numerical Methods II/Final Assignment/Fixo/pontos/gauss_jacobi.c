#include "gauss_jacobi.h"

// cria o vetor X de solução inicial
void cria_vetor_X(float A[64][64], float resultado[64], float vet[64])
{
    int j;
    for(j=1;j<=63;j++)
	 vet[j] = resultado[j]/A[j][j];
}

// cria a matriz C a partir da matriz inicial
// matriz C utilizada na relação x = Cx' + g 
void cria_matriz_C(float A[64][64], float C[64][64])
{
    int i,j;
    for(i=1;i<=63;i++)
       for(j=1;j<=63;j++)
	  if(i==j)
	      C[i][j] = 0;
          else
	      C[i][j] = -1 * (A[i][j]/A[i][i]);		
}

// cria o vetor g da relação x = Cx' + g
void cria_vetor_G(float A[64][64], float resultado[64], float v_G[64])
{
    int i;
    for(i=1;i<=63;i++)
	v_G[i] = resultado[i]/ A[i][i];
}

// função q realiza a multiplicação entre uma matriz e um vetor
void mult_MV(float M[64][64], float V[64], float aux[64])
{
    int i,j;
    float coef;
    for(i=1;i<=63;i++)
    {
       coef=0;
       for(j=1;j<=63; j++)	
          coef = coef + M[i][j] * V[j];		
       aux[i] = coef;
    }
}

// cria um vetor para uma iteraçao
void cria_vetor_de_iteracoes(float A[64][64], float v_G[64], float resultado[64], float aux[64])
{
    int i;
    mult_MV(A,resultado,aux);
    for(i=1;i<=63;i++)
	aux[i] = aux[i] + v_G[i];		
}

// faz a troca de elementos entre dois vetores
void troca_V(float vet1[64], float vet2[64])
{
    int i;
    for(i=1;i<=63;i++)
	vet1[i] = vet2[i];
}

// retorna o maior valor de um vetor
// valor em modulo
float retorna_maior(float V[64])
{
    int i;
    float maior = fabs(V[0]); 
    for(i=2;i<=63;i++)
	 if(maior < fabs(V[i]))
           maior = fabs(V[i]);
    return maior;
}

float calculo_do_delta(float vet_x[64], float vet_1[64], float vet_aux[64])
{
    int i,j;
    float aux_erro = 0;
    for(i=1;i<=63;i++)
	vet_aux[i] = fabs(vet_1[i]);
    for(j=1;j<63;j++)
	vet_aux[j] = vet_aux[j] - vet_x[j];

    aux_erro = retorna_maior(vet_aux)/retorna_maior(vet_1);
    return aux_erro;
}

void gauss_jacobi(float A[64][64], float solucao[64], float resultado[64])
{
    float vetor_x[64];
    float matrizC[64][64];
    float vetorG[64];
    float vet2[64];

    float erro = 0.00001;
    int iteracoes = 1000;
	
    // criação do vetor inicial x, da Matriz C e do vetor G
    cria_vetor_X(A, resultado, vetor_x);
    cria_matriz_C(A, matrizC);
    cria_vetor_G(A, resultado, vetorG);
    cria_vetor_de_iteracoes(matrizC, vetorG, vetor_x, solucao);
    float aux = 9999;
    while(iteracoes >= 0 && aux > erro)
    {
	aux = calculo_do_delta(vetor_x, solucao, vet2);
	if(aux > erro)
        {
	   iteracoes--;
	   troca_V(vetor_x, solucao);		
	   cria_vetor_de_iteracoes(matrizC, vetorG, vetor_x, solucao);
	}
    }    	
}
