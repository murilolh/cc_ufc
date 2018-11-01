/*
lista.c
Usa listas encadeadas para guardar os rids selecionados*/

#include <stdio.h>
#include <stdlib.h>

//Estruturas usadas nas Listas Encadeadas
typedef struct cel  
{
    int rid;
    struct cel *prox;
}celula;

typedef struct     
{
    celula *primeiro,*ultimo;
}TipoLista;

//Cria a lista
TipoLista* crialista();

//Insere rids na lista     
void Inserir(int x,TipoLista *Lista);

//Insere rids ordenadamente na lista
void Inserir_ord(int x, TipoLista *Lista);//Vamo inserir ordenadamente nos conjuntos A e B

//Remove um rid da lista
void Remover(int x, TipoLista *Lista);

//Busca por um rid na lista
int Buscar(int x, TipoLista *Lista);

//Imprime a lista no arquivo
void ImprimeLista(TipoLista *Lista);
