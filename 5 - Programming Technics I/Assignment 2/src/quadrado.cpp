/*
quadrado.cpp
Métodos de manipulação de quadrados*/
#include "quadrado.h"
#include <iostream>
#include <math.h>
using namespace std;

//Construtor
quadrado::quadrado(float lado)
{
     this->lado=lado;
}

//Retorna a area do quadrado
float quadrado::getArea()
{
      return (lado*lado);
}

//Imprime os atributos do quadrado
void quadrado::imprimir()
{
     mostraFigura();//Imprime os atributos gerais
     cout << "Lado: " << lado << endl;//Imprime o atributo especifico 'lado'
}

