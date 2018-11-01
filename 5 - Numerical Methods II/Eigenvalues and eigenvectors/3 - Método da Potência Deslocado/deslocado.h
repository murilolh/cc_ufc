/*
deslocado.h
Funções de leitura e escrita no arquivo, de manipulacao de vetores e matrizes necessarias para o metodo da potencia deslocado*/

#include <stdio.h>
#include <stdlib.h>
#include <cmath>

#define MAX 60

void ler_dados(FILE *fd, float dados[MAX]);//Le a dimensao da matriz, a tolerancia e o chute inicial a partir de um arquivo passado como parametro
void ler_matriz(FILE *fd, int d, float M[MAX][MAX]);//Le a matriz a partir do arquivo
float tolerancia(int t);//Recebe a tolerancia em casas decimais e retorna um real
float modulo(float c[], int d);//Calcula o modulo de um vetor
void normaliza(float c[], int d, float r[]);//O vetor r recebe o vetor c normalizado
void igualar_vetores(float V1[], float V2[], int d);//Iguala dois vetores
void mult_MV(float M[MAX][MAX], float V[], int d, float RS[]);//Mutiplica uma matriz por um vetor
float escalar(float V1[], float V2[], int d);//Faz o produto escalar de 2 vetores de dimensao d
void sub_MM(float M1[MAX][MAX], float M2[MAX][MAX], float RS[MAX][MAX], int d);//Subtrair uma matriz de outra
void result_inicio(int d, int t, float mu, float E, float M[MAX][MAX], float chute[], float lambda);//Gera os resultados iniciais em um arquivo
void result_iter(int k, int d, float y0[], float y1[], float x[], float lambda[2], float e, float E);//Gera o resultado de uma iteracao em um arquivo
void result_final(int k, int d, float y1[], float lambda);//Gera o resultado final em um arquivo
