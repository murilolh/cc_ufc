/*
simpson38.h
Funções que calculam integrais através da Regra de Simpson 3/8   */

//Função que recebe o intervalo, o número de divisões dele e retorna um vetor com os pontos de divisão
void Divisao(float a, float b, int n, float x[]);

//Calcula a integral pela regra de Simpson 3/8 Fechada
float Simp38Fechada(float a, float b, float f1, float f4, float fx[]);

//Calcula a integral pela regra de Simpson 3/8 Aberta
float Simp38Aberta(float a, float b, float fx[]);
