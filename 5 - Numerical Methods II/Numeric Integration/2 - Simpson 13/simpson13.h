/*
simpson13.h
Funções que calculam integrais através da Regra de Simpson 1/3   */

//Função que recebe o intervalo, o número de divisões dele e retorna um vetor com os pontos de divisão
void Divisao(float a, float b, int n, float x[]);

//Calcula a integral pela regra de Simpson 1/3 Fechada Simples
float SimpFechadaSimples(float delta, float f1, float f2, float f3);

//Calcula a integral pela regra de Simpson 1/3 Fechada Estendinda
float SimpFechadaEstendida(float a, float b, int n, float f1, float f3, float fx[]);

//Calcula a integral pela regra de Simpson 1/3 Aberta Simples
float SimpAbertaSimples(float a, float b, float fx[]);

//Calcula a integral pela regra de Simpson 1/3 Aberta Estendida
float SimpAbertaEstendida(float a, float b, int n,float x[], float fx[]);
