/*
polinomio.h
Usa listas encadeadas para guardar os termos do polinômio e calcular f(x)*/

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

