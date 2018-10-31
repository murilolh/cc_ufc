#include "Matriz.h"
#include "Vetor.h"
#include <math.h>
#include <iostream>

using std :: cout;



Vetor :: Vetor(float x, float y, float z){
	int i;	
	m = 3; n = 1;
	A =(double **) calloc(m, sizeof (double *));
	for(i = 0; i < m; i++)
		A[i] = (double *) calloc(1, (sizeof(double)));
		A[0][0] = x;
		A[1][0] = y;		
		A[2][0] = z;
}

void Vetor :: setVetor(float x, float y, float z){
	A[0][0] = x;
	A[1][0] = y;		
	A[2][0] = z;
}

Vetor :: Vetor(int c){
	int i;

	m = c; n = 1;
	A =(double **) calloc(c, sizeof (double *));
	for(i = 0; i < c; i++)
		A[i] = (double *) calloc(1, (sizeof(double)));
	for(i = 0; i < c; i++)
		A[i][0] = 0;
}

Vetor :: Vetor(){
	A = NULL;
}

void Vetor :: getCol(Matriz M, int i){
	int k;

	m = M.get_m(); n = 1;
	if(A != NULL){
  		for(k = 0; k < m; k++)
			free(A[k]);
		free(A);
	}
	A =(double **) calloc(m, sizeof (double *));
	for(k = 0; k < m; k++)
		A[k] = (double *) calloc(n, (sizeof(double)));
	for(k = 0; k < m; k++)
		setElem(k,0,M.getElem(k,i));
}

double Vetor :: modulo(){
	int i;
	double mod = 0;

	for(i = 0; i < get_m(); i++)
		mod += getElem(i,0)*getElem(i,0);
	mod = sqrt(mod);
	return mod;
}

Vetor Vetor :: unitario(){
	int i;
	Vetor e;

	e = Vetor(get_m());
	for(i = 0; i < get_m(); i++)
		e.setElem(i,0,getElem(i,0)/(double)modulo());
	return e;
}

Vetor operator* (double x, Vetor B){
	int i,j;
	Vetor *C;

	C = new Vetor(B.get_m());
	for(i = 0; i < B.get_m(); i++)
		C->setElem(i, 0, x*B.getElem(i,0));
	return *C;
}

Vetor operator* (Matriz A, Vetor B){
	int i,j,k;
	Vetor *C;

	if(A.get_n() != B.get_m()){
		B.getCol(A,0);
		return B;
	}
	C = new Vetor(A.get_m());
	for(i = 0; i < A.get_m(); i++)
		for(j = 0; j < B.get_n(); j++)
			for(k = 0; k < B.get_m(); k++)
				C->setElem(i, j,C->getElem(i,j) + A.getElem(i,k) * B.getElem(k,j));
	return *C;
}

Vetor operator* (Vetor A, Vetor B){
	double x,y,z;
	Vetor *C;
	
	if(((A.get_m() == 3) && (A.get_n() == 1))&&((B.get_m() == 3) && (B.get_n() == 1))){
		C = new Vetor(3);
		x = A.getElem(1,0)*B.getElem(2,0) - A.getElem(2,0)*B.getElem(1,0);
		y = A.getElem(2,0)*B.getElem(0,0) - A.getElem(0,0)*B.getElem(2,0);
		z = A.getElem(0,0)*B.getElem(1,0) - A.getElem(1,0)*B.getElem(0,0);
		C->setElem(0,0,x);
		C->setElem(1,0,y);
		C->setElem(2,0,z);
		return *C;
	}
}

Vetor operator+ (Vetor A, Vetor B){
	double x,y,z;
	Vetor *C;
	
	if(A.get_m() == B.get_m()){
		C = new Vetor(3);
		x = A.getElem(0,0) + B.getElem(0,0);
		y = A.getElem(1,0) + B.getElem(1,0);
		z = A.getElem(2,0) + B.getElem(2,0);
		C->setElem(0,0,x);
		C->setElem(1,0,y);
		C->setElem(2,0,z);
		return *C;
	}
}
