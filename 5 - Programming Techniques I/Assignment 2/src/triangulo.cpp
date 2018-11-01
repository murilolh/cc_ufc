/*
triangulo.cpp
Métodos de manipulação de triangulos*/
#include "triangulo.h"
#include <iostream>
#include <math.h>
using namespace std;

//Construtor
triangulo::triangulo(float base,float altura)
{
     this->base=base;
     this->altura=altura;
}

//Retorna a area do triangulo
float triangulo::getArea()
{
      return (base*altura)/2;
}

//Imprime os atributos do triangulo
void triangulo::imprimir()
{
     mostraFigura();//Imprime os atributos gerais  
     cout << "Base: " << base << "; ";//Imprime os atributo especifico 'base'
     cout << "Altura: " << altura << endl;//Imprime os atributo especifico 'altura'
}


