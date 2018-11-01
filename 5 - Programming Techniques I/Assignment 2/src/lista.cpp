/*
lista.cpp
Métodos de manipulação da lista de figuras*/
#include "lista.h"
#include <stdio.h>
#include <iostream>

using namespace std;

//Contrutor
lista::lista()
{
    inic=NULL;
    fim=NULL;
}

//Destrutor
lista::~lista()
{
    figura *aux;
    while(inic!=NULL)
    {
        aux=inic;
        inic=inic->getProx();
        delete aux;
    }
}

//Insere uma figura na lista 
void lista::inserir(figura *i)
{
    if (!fim)               //primeira figura da lista
    {
        inic=i;
        fim=i;
    }
    else
        fim->setProx(i);   //A insercao e feita no fim da lista
    i->setProx(NULL);
    fim=i;   
}

//Remove uma figura da lista de acordo com seu nome
void lista::remover(char nome[30])
{
    figura *i,*ant,*aux;
    ant=NULL;
    aux=NULL;
    i=inic;
    while (i)//Busca a figura
    {
        if (!strcmp(nome,i->getNome()))
        {
            aux=i;
            i=NULL;
        }
        else
        {
            ant=i;
            i=i->getProx();
        }
    }
    if (!aux)//Caso a figura nao exista
    {
        cout <<"\nA figura " << nome << " nao existe!\n" << endl;
        return;
    }
    else
    {
        if (ant)
            ant->setProx(aux->getProx());
        else
        {
            if (aux!=fim)
                inic=aux->getProx();  
            else
            {
                inic=aux->getProx(); 
                fim=inic;
            }
        }
        if (aux==fim && ant)
             fim=ant;
        cout <<"\nA figura " << nome << " foi removida com sucesso!\n" << endl;
        delete(aux);
    }
}

//Lista os elementos
void lista::listar()
{
    if (!inic)//Verifica se a lista esta vazia
        cout << "\nNao exitem figuras na lista!\n" << endl;
    else
    {
        figura *aux;
        aux=inic;
        while (aux)//Imprime cada elemento da lista
        {
            aux->imprimir();
            aux=aux->getProx();
        }
    }
}

//Imprime a area total da lista     
void lista::areaTotal()
{
    float area=0;
    if (!inic)//Verifica se a lista esta vazia
        cout << "\nNao exitem figuras na lista!\n" << endl;
    else
    {
        figura *aux;
        aux=inic;
        while (aux)//Soma a area de cada figura da lista
        {
            area=area+aux->getArea();
            aux=aux->getProx();
        }
    }
    cout << "\nArea Total:" << area << "\n" << endl;
}

//Algoritmo Quick-Sort para ordenacao
void lista::quick(int inicio, int final, figura *vet_fig[], int flag)
{
    if(final - inicio > 0)
    {
    	figura *aux;
	    float pivot1 = vet_fig[inicio]->getArea();
	    string pivot2 = vet_fig[inicio]->getNome();
	    int esq = inicio + 1;
	    int dir = final;
	    while(esq < dir)
        {
	        if((flag==1 && (vet_fig[esq]->getArea() <= pivot1)) || (flag==2 && (vet_fig[esq]->getNome() <= pivot2)))
                esq++;
            else
            {
	            aux = vet_fig[esq];
	            vet_fig[esq] = vet_fig[dir];
                vet_fig[dir] = aux;
	            dir--;
            }
        }
	    if((flag==1 && (vet_fig[esq]->getArea() > pivot1)) || (flag==2 && (vet_fig[esq]->getNome() > pivot2)))
            esq--;
        aux = vet_fig[inicio];
	    vet_fig[inicio] = vet_fig[esq];
	    vet_fig[esq] = aux;
        quick(inicio, esq-1, vet_fig, flag);
        quick(dir, final, vet_fig, flag);
    }
}

//Ordena os elementos de acordo com o criterio escolhido 
void lista::ordena(int flag)
{
    int num_figuras = 0;
    int i = 0;
    figura *fig = inic;
    while(fig != NULL)//Conta o numero de elementos
    {
        num_figuras++;
        fig = fig->getProx();
    }
    
    if(num_figuras > 0)
    {
        figura *vet_fig[num_figuras];//Vetor auxiliar
        
        i=0;
        fig = inic;
        while(fig != NULL)//Coloca todos os elementos da lista no vetor
        {
            vet_fig[i] = fig;
            i++;
            fig = fig->getProx();
        }
        quick(0, num_figuras-1, vet_fig, flag);//Ordena o vetor
        //Coloca os elementos ordenados do vetor de volta na lista
        for(i=0;i<num_figuras-1;i++)
            vet_fig[i]->setProx(vet_fig[i+1]);
        vet_fig[num_figuras-1]->setProx(NULL);

        inic = vet_fig[0];
        fim = vet_fig[num_figuras-1];        
    }
}

//Ordena e Lista os elementos de um tipo determinado
void lista::listartipo(int flag, int tipo)
{
    if(flag==1)
        ordena(1);
    if(flag==2)
        ordena(2);
    figura *aux=inic;
    if(aux==NULL)
        cout << "\nNao exitem figuras na lista!\n" << endl;
    while(aux!=NULL)
    {
        if(aux->getTipo()==tipo)
            aux->imprimir();
        aux=aux->getProx();
    }
}
