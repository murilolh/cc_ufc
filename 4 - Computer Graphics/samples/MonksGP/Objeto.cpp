#include "Objeto.h"
#include <iostream>

void Objeto :: setPosicao(float x, float y, float z){
	this->x = x;
	this->y = y;
	this->z = z;
}

void Objeto :: setRotacao(float rx, float ry, float rz){
	this->rx = rx;
	this->ry = ry;
	this->rz = rz;
}

float* Objeto :: getPosicao(){
	float* posicao;
	posicao = (float*) calloc(3, sizeof(float));
	posicao[0] = this->x;
	posicao[1] = this->y;
	posicao[2] = this->z;
	return posicao;
} 
