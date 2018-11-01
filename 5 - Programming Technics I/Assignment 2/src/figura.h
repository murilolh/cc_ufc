/*
figura.h
Classe base das figuras*/
#ifndef FIGURA_H
#define FIGURA_H
#include <cstring>

using namespace std;

class figura
{
    protected:
        int tipo;
        char nome[30],cor[20];
        float area;                            
        figura *prox;
    public:
        int getTipo();//Retorna o tipo da figura
        figura *getProx();//Retorna o proximo elemento na lista
        void setProx(figura *);//Seta o proximo elemento de uma figura na lista 
        char *getNome();//Retorna o nome da figura               
        void mostraFigura();//Imprime os atributos gerais da figura
        void setAtrib(char *,char*,float,int);//Seta os atributos da figura
        virtual void imprimir()=0;//Imprime os atributos gerais da figura
        virtual float getArea()=0;//Imprime a area da figura        
};

#endif
