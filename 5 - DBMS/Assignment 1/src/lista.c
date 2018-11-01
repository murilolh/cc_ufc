/*
lista.c
Usa listas encadeadas para guardar os rids selecionados*/

#include "lista.h"

//Cria a lista
TipoLista* crialista() 
{
    TipoLista* Lista = (TipoLista*) malloc(sizeof(TipoLista));
    Lista->primeiro = (celula*) malloc(sizeof(celula));
    Lista->ultimo   = (celula*) malloc(sizeof(celula));
    Lista->ultimo->prox = NULL; 
    Lista->primeiro = Lista->ultimo;
    return(Lista);
}

//Insere rids na lista     
void Inserir(int x,TipoLista *Lista) 
{
    Lista->ultimo->prox = (celula*) malloc(sizeof(celula));
    Lista->ultimo->prox->rid = x;
    Lista->ultimo = Lista->ultimo->prox;
    Lista->ultimo->prox = NULL;    
}

//Insere rids ordenadamente na lista
void Inserir_ord(int x, TipoLista *Lista)
{
    celula *aux;
    celula *novo_noh;
    novo_noh = (celula*) malloc(sizeof(celula));
    novo_noh->rid = x;
    novo_noh->prox=NULL;
    aux=Lista->primeiro;       
    if(aux->prox==NULL)
        Lista->primeiro->prox=novo_noh;
    else
    {
        while (aux->prox!=NULL) 
        {     
            if (aux->prox->rid >  novo_noh->rid)
            {
                novo_noh->prox=aux->prox;
                aux->prox = novo_noh;      
                return;                             
            }
            aux=aux->prox;
        }
        aux->prox=novo_noh;
    }                
}

//Remove um rid da lista
void Remover(int x, TipoLista *Lista)
{
    celula *aux,*ant;
    aux=Lista->primeiro->prox;
    ant=Lista->primeiro;
    if(aux->rid == x)
    {
        ant->prox = aux->prox;
        free(aux);
    }
    else
    {
        while (aux!=NULL) 
        {     
            if (aux->rid ==  x)
            {
                ant->prox=aux->prox;
                if(aux == Lista->ultimo)
                  Lista->ultimo = ant;
                free(aux);
                return;                             
            }
            aux=aux->prox;
            ant=ant->prox;
        }        
    }    
}

//Busca por um rid na lista
int Buscar(int x, TipoLista *Lista)
{
    celula *aux;
    aux=Lista->primeiro->prox;
    while (aux!=NULL) 
    {     
        if (aux->rid == x) 
           return 1;
        aux=aux->prox;
    }
    return 0;
}

//Imprime a lista no arquivo
void ImprimeLista(TipoLista *Lista)
{
    FILE *saida; 
    saida = fopen("saida.txt","a");
    celula *aux;
    aux=Lista->primeiro->prox;
    while (aux!=NULL) 
    {     
        fprintf(saida,"%d ",aux->rid);
        aux=aux->prox;
    }
    fclose(saida);
}
