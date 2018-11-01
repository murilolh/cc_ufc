/*
lista.h
Classe da lista de figuras*/
#ifndef LISTA_H
#define LISTA_H
#include "circulo.h"
#include "quadrado.h"
#include "triangulo.h"
#include "trapezio.h"
#include "figura.h"
#include <cstring>

using namespace std;

class lista
{
    private:
        figura *inic,*fim;
    public:
        lista();//Contrutor                          
        ~lista();//Destrutor                                   
        void inserir(figura *);//Insere uma figura na lista 
        void remover(char *);//Remove uma figura da lista de acordo com seu nome
        void listar();//Lista os elementos
        void areaTotal();//Imprime a area total da lista     
        void quick(int inicio, int final, figura *vet_fig[], int flag);//Algoritmo Quick-Sort para ordenacao   
        void ordena(int flag);//Ordena os elementos de acordo com o criterio escolhido 
        void listartipo(int flag, int tipo);//Ordena e Lista os elementos de um tipo determinado   
};

#endif
