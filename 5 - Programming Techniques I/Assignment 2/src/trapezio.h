/*
trapezio.h
Classe trapezio derivada da classe figura*/
#ifndef TRAPEZIO_H
#define TRAPEZIO_H
#include "figura.h"
#include <cstring>
using namespace std;

class trapezio: public figura{
      private:
              float bas1;  //Base maior do trapezio
              float bas2;  //Base menor do trapezio
              float altura;//Altura do trapezio
      public:
              trapezio(float,float,float);//Construtor  
              ~trapezio();                //Destrutor
              float getArea();            //Retorna a area do trapezio
              void imprimir();            //Imprime os atributos do trapezio              
};
#endif
