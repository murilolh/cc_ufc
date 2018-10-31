#include "metodo.h"
#include <iostream>
#include <cmath>

metodo::metodo (double (*A)[MAX], double B[], int n, double e){
	 //Instancia a Matriz de coeficientes M no método
    M = A;

    //Instancia o vetor de termos independentes T no método
    T = B;

    //Instancia o atributo precisao no método
    E = e;
    
    //Instancia o atributo numero de particulas no método
    N = n;
}
    
double metodo::somatorio (double *X,int lin){
	double total=0;
	for(int i=0;i<N;i++)
		if(i!=lin) total-=X[i]*M[lin][i];
	return total;
}


double* metodo::diferenca (double* X,double* Y){
	double* dif = new double[MAX];
	for(int i=0;i<N;i++)
		dif[i]=X[i]-Y[i];
	return dif;
}

double metodo::max(double* X){
	double max=X[0];
	for(int i=0;i<N;i++)
		if(X[i]>max) max=X[i];
	return max;
}

int metodo::criteriodaslinhas(){
  double max = 0.0;
  double soma;
  for (int i=0;i<N;i++)
  {
     soma = 0.0;
     for (int j=0;j<N;j++)
        if (i!=j) soma += M[i][j];
     
     soma = soma/M[i][i];
     if (max < soma) max = soma;
  }
  if (max < 1)
    return 1;
  else
    return 0;
}


