/*
integracao.h
Funções que calculam integrais através das fórmulas de Newton-Cotes*/

//Função que recebe o intervalo, o número de divisões dele e retorna um vetor com os pontos de divisão
void Divisao(float a, float b, int n, float x[]);

//Calcula a integral pela regra do Trapézio Fechada 
float TraFechada(float a, float b, float f1, float f3);

//Calcula a integral pela regra do Trapézio Aberta 
float TraAberta(float a, float b, float fx[]);

//Calcula a integral pela regra de Simpson 1/3 Fechada 
float Simp13Fechada(float delta, float f1, float f2, float f3);

//Calcula a integral pela regra de Simpson 1/3 Aberta 
float Simp13Aberta(float a, float b, float fx[]);

//Calcula a integral pela regra de Simpson 3/8 Fechada
float Simp38Fechada(float a, float b, float f1, float f4, float fx[]);

//Calcula a integral pela regra de Simpson 1/3 Aberta
float Simp38Aberta(float a, float b, float fx[]);

//Calcula a integral pela fórmula de Newton-Cotes de 4º grau Fechada
float NewtonCotes4F(float a, float b, float f1, float f5, float fx[]);

//Calcula a integral pela fórmula de Newton-Cotes de 4º grau Aberta
float NewtonCotes4A(float a, float b, float fx[]);
