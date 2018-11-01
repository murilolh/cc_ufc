/*
triangulo.h
Classe circulo derivada da classe figura*/
#ifndef TRIANGULO_H
#define TRIANGULO_H
#include "figura.h"
#include <cstring>
using namespace std;

class triangulo: public figura{
      private:
              float base;  //Base do triangulo
              float altura;//Altura do triangulo
      public:
              triangulo(float,float);  //Construtor   
              ~triangulo();            //Destrutor
              float getArea();         //Retorna a area do triangulo
              void imprimir();         //Imprime os atributos do triangulo              
};
#endif
