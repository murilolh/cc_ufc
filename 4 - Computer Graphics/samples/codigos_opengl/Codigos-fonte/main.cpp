//*****************************************************
//
// main.cpp 
// Classe que cria um objeto ExemploCpp.
//
// Marcelo Cohen e Isabel H. Manssour
// Este c�digo acompanha o livro 
// "OpenGL - Uma Abordagem Pr�tica e Objetiva"
// 
//*****************************************************

#include "ExemploCpp.h"

int main()
{ 
	ExemploCpp *exemplo = new ExemploCpp();
	exemplo->inicializaLoopGlut();
	return 0;
}
