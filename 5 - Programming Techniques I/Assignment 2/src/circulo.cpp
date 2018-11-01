/*
circulo.cpp
Métodos de manipulação de circulos*/
#include "circulo.h"
#include <iostream>
#include <math.h>
using namespace std;

//Construtor
circulo::circulo(float raio)
{
     this->raio=raio;
}

//Retorna a area do circulo
float circulo::getArea()
{
      return (M_PI*raio*raio);
}

//Imprime os atributos do circulo
void circulo::imprimir()
{
     mostraFigura();//Imprime os atributos gerais
     cout << "Raio: " << raio << endl;//Imprime os atributo especifico 'raio'
}
