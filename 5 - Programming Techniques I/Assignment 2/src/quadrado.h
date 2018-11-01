/*
quadrado.h
Classe quadrado derivada da classe figura*/
#ifndef QUADRADO_H
#define QUADRADO_H
#include "figura.h"
#include <cstring>
using namespace std;

class quadrado: public figura
{
      private:
              float lado;//Lado do quadrado
      public:
              quadrado(float);//Construtor     
              ~quadrado();    //Destrutor
              float getArea();//Retorna a area do quadrado
              void imprimir();//Imprime os atributos do quadrado
};
#endif
