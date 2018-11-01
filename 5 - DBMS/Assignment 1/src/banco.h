/*
banco.h
Funções de leitura dos arquivos, fazendo a iteracao entre banco e a aplicacao 
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "lista.h"

//Seleciona rids de um indice atraves de uma clausula dada
TipoLista* selecao(char tabela[12], char* atributo, int n_atributo, int operacao, void* valor);

//Faz a intersecao de dois conjuntos de rids
TipoLista* intersecao(TipoLista *A, TipoLista *B);

//A partir de um conjnto de rids, busca e mostra o resultado
TipoLista* resultado(TipoLista *R, char tabela[12]);
