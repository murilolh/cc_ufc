/*
figura.cpp
Métodos de manipulação das figuras*/
#include "figura.h"
#include <iostream>

using namespace std;

//Retorna o proximo elemento na lista
figura *figura::getProx()
{
    return prox;
}
 
//Seta o proximo elemento de uma figura na lista       
void figura::setProx(figura *proximo)
{
    prox=proximo;
}

//Retorna o nome da figura
char *figura::getNome()
{
    return nome;
}

//Retorna o tipo da figura
int figura::getTipo()
{
    return tipo;
}

//Imprime os atributos gerais da figura
void figura::mostraFigura()
{
    cout << "Nome: " << nome << "; ";
    cout << "Cor: " << cor << "; ";
    cout << "Area: " << area << "; ";
}

//Seta os atributos da figura       
void figura::setAtrib(char nome[30],char cor[20],float area, int tipo)
{
    this->tipo=tipo;
    strcpy(this->nome,nome);
    strcpy(this->cor,cor);
    this->area=area;
    this->prox=NULL;
}
