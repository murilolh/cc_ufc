/*
trapezio.cpp
Métodos de manipulação de trapezios*/
#include "trapezio.h"
#include <iostream>
#include <math.h>
using namespace std;

//Construtor
trapezio::trapezio(float bas1,float bas2,float altura)
{
     this->bas1=bas1;
     this->bas2=bas2;
     this->altura=altura;
}

//Retorna a area do trapezio
float trapezio::getArea()
{
      return (((bas1+bas2)*altura)/2);
}

//Imprime os atributos do trapezio
void trapezio::imprimir()
{
     mostraFigura();//Imprime os atributos gerais
     cout << "Base Maior: " << bas1    << "; ";//Imprime o atributo especifico 'base maior'
     cout << "Base Menor: " << bas2    << "; ";//Imprime o atributo especifico 'base menor'
     cout << "Altura: "     << altura  << endl;//Imprime o atributo especifico 'altura'
}


