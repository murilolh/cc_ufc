/*
exponenciacao.h
Funções que calculam integrais através de Exponenciacao simples e dupla*/

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

//Obtém todos os alphas e os fx(alpha) da parametrização
void getalpha(int n, float alpha[]);

//Calcula cosh(x) ataves de um x dado
float coshiper(float x);

//Calcula senh(x) ataves de um x dado
float senhiper(float x);

//Calcula tgh(x) ataves de um x dado
float tghiper(float x);

//Obtém todos os alphas  da parametrização
void getalpha(int n, float alpha[]);

//Calcula x(alpha) de todos os alphas dados
void getxalpha(int n, float alpha[], float xalpha[], float xc);

//Calcula f(xalpha) de todos os xalphas dados
void getfxalpha(int n, float xalpha[], float fxalpha[], TipoLista *P);

//Calcula a integral pelo método da Exponencial simples
float ExpSimples(int n, float xc, float alpha[], TipoLista *P);

//Calcula a integral pelo método da Exponencial dupla
float ExpDupla(int n, float xc, float alpha[], TipoLista *P);

