/*
trapezio.h
Funções que calculam integrais através da regra do trapézio*/

//Função que recebe o intervalo, o número de divisões dele e retorna um vetor com os pontos de divisão
void Divisao(float a, float b, int n, float x[]);

//Calcula a integral pela regra do Trapézio Simples
float TraFechadaSimples(float a, float b, float f1, float f3);

//Calcula a integral pela regra do Trapézio Estendinda
float TraFechadaEstendida(float a, float b, int n, float f1, float f3, float fx[]);

//Calcula a integral pela regra do Trapézio Aberta Simples
float TraAbertaSimples(float a, float b, float fx[]);

//Calcula a integral pela regra do Trapézio Aberta Estendida
float TraAbertaEstendida(float a, float b, int n,float x[], float fx[]);
