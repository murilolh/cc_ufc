/*
circulo.h
Classe circulo derivada da classe figura*/
#ifndef CIRCULO_H
#define CIRCULO_H
#include "figura.h"
#include <cstring>
using namespace std;

class circulo: public figura
{
      private:
              float raio;//Raio do circulo
      public:
              circulo(float); //Construtor     
              ~circulo();     //Destrutor
              float getArea();//Retorna a area do circulo     
              void imprimir();//Imprime os atributos do circulo              
};
#endif
