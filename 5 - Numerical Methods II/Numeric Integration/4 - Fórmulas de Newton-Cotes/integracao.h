/*
integracao.h
Funções que calculam integrais através das fórmulas de Newton-Cotes*/

//Estruturas usadas nas Listas Encadeadas
typedef struct cel  
{
    int termo;
    struct cel *prox;
}celula;

typedef struct     
{
    celula *primeiro,*ultimo;
}TipoLista;

//Cria a lista de termos do Polinômio
TipoLista* crialista();

//Insere termos no Polinômio     
void Inserir(int x,TipoLista *Lista);

//Imprime a lista de termos
void ImprimeLista(TipoLista *Lista);

//Calcula f(x) ataves de um x dado
float getfx(float x, TipoLista *Polinomio);

//Função que recebe o intervalo, o número de divisões dele e retorna um vetor com os pontos de divisão
void Divisao(float a, float b, int n, float x[]);

//Calcula a integral pela regra do Trapézio Fechada com tolerância
float TraFechada(float a, float b, TipoLista *P);

//Calcula a integral pela regra do Trapézio Aberta 
float TraAberta(float a, float b, TipoLista *P);

//Calcula a integral pela regra de Simpson 1/3 Fechada 
float Simp13Fechada(float a, float b, TipoLista *P);

//Calcula a integral pela regra de Simpson 1/3 Aberta 
float Simp13Aberta(float a, float b, TipoLista *P);

//Calcula a integral pela regra de Simpson 3/8 Fechada
float Simp38Fechada(float a, float b, TipoLista *P);

//Calcula a integral pela regra de Simpson 1/3 Aberta
float Simp38Aberta(float a, float b, TipoLista *P);

//Calcula a integral pela fórmula de Newton-Cotes de 4º grau Fechada
float NewtonCotes4F(float a, float b, TipoLista *P);

//Calcula a integral pela fórmula de Newton-Cotes de 4º grau Aberta
float NewtonCotes4A(float a, float b, TipoLista *P);
