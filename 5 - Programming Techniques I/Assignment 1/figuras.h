/*
figuras.h
Definição das estruruas e funções de manipulação das estruturas de dados usadas e das figuras*/

//Estrutura de um Círculo
typedef struct cir  
{   
    char nome[10];
    char cor[10];
    float area;
    float raio;
    struct cir *prox;//Ponteiro que aponta para outro círculo
}Circulo;

//Estrutura de um Quadrado
typedef struct quad  
{ 
    char nome[10];
    char cor[10];
    float area;
    float lado;
    struct quad *prox;//Ponteiro que aponta para outro quadrado
}Quadrado;

//Estrutura de um Triângulo
typedef struct tri  
{ 
    char nome[10];
    char cor[10];
    float area;
    float base;
    float altura;
    struct tri *prox;//Ponteiro que aponta para outro triângulo
}Triangulo;

//Estrutura de uma Lista de Círculos
typedef struct     
{
    Circulo *primeiro;
    float Area_total;//Área de todos os círculos existentes na lista
}ListaCir;

//Estrutura de uma Lista de Quadrados
typedef struct     
{
    Quadrado *primeiro;
    float Area_total;//Área de todos os quadrados existentes na lista
}ListaQuad;

//Estrutura de uma Lista de Triângulos
typedef struct     
{
    Triangulo *primeiro;
    float Area_total;//Área de todos os triângulos existentes na lista
}ListaTri;

//Estrutura que guarda uma lista de cada tipo de figura
typedef struct
{
    ListaCir *circ;
    ListaQuad *quad;
    ListaTri *tri;
}Figura;

//Estrutura de um termo genérico
typedef struct cel  
{
    char nome[10];
    char cor[10];
    float area;
    int tipo;
    struct cel *prox;
}celula;

//Estrutura da lista encadeada de termos genéricos usada na ordenação
typedef struct     
{
    celula *primeiro,*ultimo;
}TipoLista;

//Cria uma lista vazia de termos genéricos
TipoLista* crialistatermos();

//Insere ordenadamente termos na lista de acordo com o critério de ordenação
void Inserir_ord(int f,char nome[10], char cor[10], float area, int tipo, TipoLista *Lista);

//Cria uma lista vazia de Círculos
ListaCir* criaCir();

//Cria uma lista vazia de Quadrados
ListaQuad* criaQuad();

//Cria uma lista vazia de Triângulos
ListaTri* criaTri();

//Cria uma estrutura com uma lista vazia de cada tipo de figura
Figura* crialista();

//Retorna o tipo de figura escolhido
int escolha_tipo();

//Insere um círculo
void inserir_cir(Figura *fig, char nome[10], char cor[10], float raio);

//Insere um quadrado
void inserir_quad(Figura *fig, char nome[10], char cor[10], float lado);

//Insere um triângulo
void inserir_tri(Figura *fig, char nome[10], char cor[10], float base, float altura);

//Remove uma figura qualquer de acordo com o seu nome
int remover(Figura *fig, char nome[10]);

//Lista todas as figuras
void listar(Figura *fig);

//Ordena todos as figuras de acordo com o critério de ordenação em uma lista encadeada
TipoLista* listatermos(int f,Figura *fig);

//Imprime a lista de termos genéricos
void imprime_lista(TipoLista *Lista);

//Ordena as figuras de acordo com o critério de ordenação
void ordenar(int f,Figura *fig);

//Retorna a área total das figuras
float area_total(Figura *fig);

