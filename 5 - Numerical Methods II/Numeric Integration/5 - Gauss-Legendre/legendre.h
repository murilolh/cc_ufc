/*
legendre.h
Funções que calculam integrais através de Gauss-Legendre*/

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

//Calcula o x de theta
float getxtheta(float a, float b, float theta);

//Calcula a integral por Legendre
float Legendre(float a, float b, int n, float R[], float W[], TipoLista *P);
