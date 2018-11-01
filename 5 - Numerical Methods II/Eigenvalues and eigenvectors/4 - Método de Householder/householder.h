/*
householder.h
Funções de leitura e escrita no arquivo, de manipulacao de vetores e matrizes necessarias para o metodo de Householder*/

#include <stdio.h>
#include <stdlib.h>
#include <cmath>

#define MAX 60

void ler_dados(FILE *fd, float dados[2]);//Le a dimensao da matriz e a tolerancia a partir de um arquivo passado como parametro
void ler_matriz(FILE *fd, int d, float M[MAX][MAX]);//Le a matriz a partir do arquivo
float tolerancia(int t);//Recebe a tolerancia em casas decimais e retorna um real
float modulo(float c[], int d);//Calcula o modulo de um vetor
void normaliza(float c[], int d, float r[]);//O vetor r recebe o vetor c normalizado
void igualar_vetores(float V1[], float V2[], int d);//Iguala dois vetores
void mult_MV(float M[MAX][MAX], float V[], int d, float RS[]);//Mutiplica uma matriz por um vetor
float escalar(float V1[], float V2[], int d);//Faz o produto escalar de 2 vetores de dimensao d
void sub_VV(float V1[], float V2[], float RS[], int d);//Subtrair um vetor de outro
void div_VE(float V[], float E, float R[],int d);//Divide um vetor por um escalar
void mult_V(float V[], float M[MAX][MAX],int t);//Multiplica um vetor por seu transposto
void mult_VE(float M[MAX][MAX],int E,int d);//Multiplica uma matriz por um escalar
void sub_MM(float M1[MAX][MAX], float M2[MAX][MAX], float RS[MAX][MAX], int d);//Subtrair uma matriz de outra
void mult_MM(float M1[MAX][MAX], float M2[MAX][MAX], float RS[MAX][MAX], int d);//Multiplica uma matriz por outra
float max_elem_MT(float M[MAX][MAX], int d);//Obtem o maior elemento fora da tridiagonal de uma matriz
void igualar_MM(float M1[MAX][MAX] ,float M2[MAX][MAX], float d);//Iguala uma matriz a outra
void trasp_M(float A[MAX][MAX], float At[MAX][MAX], int d);//Traspoe a matriz A em At
void householder(int d, float E, float T[MAX][MAX], float H[MAX][MAX]);//Usa Householder para alterar a matriz T e gerar a matriz de Householder(H)
void result_inicio(int d, int t, float E, float M[MAX][MAX]);//Gera os resultados iniciais em um arquivo
void result_final(int d, float H[MAX][MAX], float T[MAX][MAX]);//Gera o resultado final em um arquivo
