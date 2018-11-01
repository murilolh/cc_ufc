#include "gauss_jacobi.h"

// cria o vetor X de solução inicial
void cria_vetor_X(int d, float A[200][200], float* resultado, float* vet)
{
    int j;
    for(j=1;j<=d;j++)
	 vet[j] = resultado[j]/A[j][j];
}

// cria a matriz C a partir da matriz inicial
// matriz C utilizada na relação x = Cx' + g 
void cria_matriz_C(int d, float A[200][200], float C[200][200])
{
    int i,j;
    for(i=1;i<=d;i++)
       for(j=1;j<=d;j++)
	  if(i==j)
	      C[i][j] = 0;
          else
	      C[i][j] = -1 * (A[i][j]/A[i][i]);		
}

// cria o vetor g da relação x = Cx' + g
void cria_vetor_G(int d,float A[200][200], float* resultado, float* v_G)
{
    int i;
    for(i=1;i<=d;i++)
	v_G[i] = resultado[i]/ A[i][i];
}

// função q realiza a multiplicação entre uma matriz e um vetor
void mult_MV(int d, float M[200][200], float* V, float* aux)
{
    int i,j;
    float coef;
    for(i=1;i<=d;i++)
    {
       coef=0;
       for(j=1;j<=d; j++)	
          coef = coef + M[i][j] * V[j];		
       aux[i] = coef;
    }
}

// cria um vetor para uma iteraçao
void cria_vetor_de_iteracoes(int d, float A[200][200], float* v_G, float* resultado, float* aux)
{
    int i;
    mult_MV(d,A,resultado,aux);
    for(i=1;i<=d;i++)
	aux[i] = aux[i] + v_G[i];		
}

// faz a troca de elementos entre dois vetores
void troca_V(int d, float* vet1, float* vet2)
{
    int i;
    for(i=1;i<=d;i++)
	vet1[i] = vet2[i];
}

// retorna o maior valor de um vetor
// valor em modulo
float retorna_maior(int d, float* V)
{
    int i;
    float maior = fabs(V[0]); 
    for(i=2;i<=d;i++)
	 if(maior < fabs(V[i]))
           maior = fabs(V[i]);
    return maior;
}

float calculo_do_delta(int d, float* vet_x, float* vet_1, float* vet_aux)
{
    int i,j;
    float aux_erro = 0;
    for(i=1;i<=d;i++)
	vet_aux[i] = fabs(vet_1[i]);
    for(j=1;j<d;j++)
	vet_aux[j] = vet_aux[j] - vet_x[j];

    aux_erro = retorna_maior(d,vet_aux)/retorna_maior(d,vet_1);
    return aux_erro;
}

void gauss_jacobi(int d, float A[200][200], float* solucao, float* resultado)
{
    float vetor_x[d+1];
    float matrizC[200][200];
    float vetorG[d+1];
    float vet2[d+1];

    float erro = 0.00001;
    int iteracoes = 1000;
	
    // criação do vetor inicial x, da Matriz C e do vetor G
    cria_vetor_X(d, A, resultado, vetor_x);
    cria_matriz_C(d, A, matrizC);
    cria_vetor_G(d, A, resultado, vetorG);
    cria_vetor_de_iteracoes(d, matrizC, vetorG, vetor_x, solucao);
    float aux = 9999;
    while(iteracoes >= 0 && aux > erro)
    {
	aux = calculo_do_delta(d, vetor_x, solucao, vet2);
	if(aux > erro)
        {
	   iteracoes--;
	   troca_V(d, vetor_x, solucao);		
	   cria_vetor_de_iteracoes(d, matrizC, vetorG, vetor_x, solucao);
	}
    }    	
}
