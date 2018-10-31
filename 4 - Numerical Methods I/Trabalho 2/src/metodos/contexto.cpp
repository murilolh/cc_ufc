#include "contexto.h"
#include <iostream>


contexto::contexto(metodo *escolhido)
{
	abstrato = escolhido;
}

void contexto::executar()
{
	abstrato->inversa();
}
