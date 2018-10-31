#include <iostream>
#include "Matriz.h"

using std :: cout;

int Matriz :: get_m(){
	return m;
}

int Matriz :: get_n(){
	return n;
}

double Matriz :: getElem(int i, int j){
	return A[i][j];
}

void Matriz :: trocaLinha(int i, int j){
	double * aux;

	if(!((0 <= i)&&(i < get_m())&&(0 <= j)&&(j < get_m())))
		return;
	aux = A[i];
	A[i] = A[j];
	A[j] = aux;
}

void Matriz :: trocaColuna(int i, int j){
	double aux;
	int k;

	if(!((0 <= i)&&(i < get_n())&&(0 <= j)&&(j < get_n())))
		return;
	for(k = 0; k < get_m(); k++){
		aux = A[k][i];
		A[k][i] = A[k][j];
		A[k][j] = aux;
	}
}

void Matriz :: somaLinha(int i, int j, double coef){
	int k;

	for(k = 0; k < get_n(); k++)
		A[i][k] = A[i][k] + coef*A[j][k];
}

Matriz operator* (Matriz A, Matriz B){
	int i,j,k;
	Matriz *C;

	if(A.get_n() != B.get_m())
		return A;
	C = new Matriz(A.get_m(), B.get_n());
	for(i = 0; i < A.get_m(); i++)
		for(j = 0; j < B.get_n(); j++)
			for(k = 0; k < B.get_m(); k++)
				C->setElem(i, j,C->getElem(i,j) + A.getElem(i,k) * B.getElem(k,j));
	return *C;
}

Matriz operator* (double x, Matriz B){
	int i,j;
	Matriz *C;

	C = new Matriz(B.get_m(), B.get_n());
	for(i = 0; i < B.get_m(); i++)
		for(j = 0; j < B.get_n(); j++)
			C->setElem(i, j, x*B.getElem(i,j));
	return *C;
}

Matriz operator+ (Matriz A, Matriz B){
	int i,j;
	Matriz *C;

	if((A.get_m() != B.get_m()) && (A.get_n() != B.get_n()))
		return A;
	C = new Matriz(A.get_m(), B.get_n());
	for(i = 0; i < A.get_m(); i++)
		for(j = 0; j < B.get_n(); j++)
			C->setElem(i, j,C->getElem(i,j) + A.getElem(i,j) + B.getElem(i,j));
	return *C;
}

Matriz Matriz :: transpor(){
	Matriz *transposta;
	int i,j;

	transposta = new Matriz(n, m);
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			transposta->setElem(i, j, A[j][i]);
	return *transposta;
}


void Matriz :: setElem(int l, int c, double elem){
	A[l][c] = elem;
}

Matriz :: Matriz(int l, int c){
	int i,j;

	m = l; n = c;
	A =(double **) calloc(m, sizeof (double *));
	for(i = 0; i < m; i++)
		A[i] = (double *) calloc(n, (sizeof(double)));
	for(i = 0; i < m; i++)
		for(j = 0; j < n; j++)
			A[i][j] = 0;
}

Matriz :: Matriz(){}

/*Matriz :: Matriz(Matriz B){
	int i,j;

	m = B.get_m(); n = B.get_n();
	A =(double **) calloc(m, sizeof (double *));
	for(i = 0; i < m; i++)
		A[i] = (double *) calloc(n, (sizeof(double)));
	for(i = 0; i < m; i++)
		for(j = 0; j < n; j++)
			A[i][j] = B.getElem(i,j);
}*/
			
void Matriz :: mostra(){
	int i, j;

	for(i = 0; i < m; i++){
		for(j = 0; j < n; j++)
			cout << "|\t " << A[i][j];
		cout << "\t|\n";
	}
}

Matriz Matriz :: identidade(){
	int i;
	Matriz *I;

	I = new Matriz(m, m);
	for(i = 0; i < m; i++)
		I->setElem(i,i,1);
	return *I;
}

/*
void Matriz :: inserirCol(int j, Vetor b){
	int i;

	for(i = 0; i < get_m(); i++){
		A[i][j] = b.getElem(i,0);
	}
}*/
