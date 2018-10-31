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

int metodo::criteriodesassenfeld(){
	double max=0.0;
	double soma1[MAX],soma2[MAX];
	double soma=0.0;
	double beta[MAX];
	for(int i=1;i<=N;i++) //inicialização dos beta's
	    beta[i]=1.0;
	int i=1;
	for(int j=1;j<N;j++) //calculo do beta1
	{
		  if(i!=j) soma+=M[i][j];
		  beta[1]=soma/M[i][i];
		  max=beta[1];
	}
		 
    for(int i=2;i<=N;i++) //para os outros beta's
       for(int j=1;j<=N;j++)
          for(int k=j;k<=i-1;k++)
              soma1[i]+=fabs(M[i][j])*beta[j]; //primeiro termo para  calculo do beta[i]
    for(int i=2;i<=N;i++)
    {
       for(int j=1;j<=N;j++)
       {
          for(int k=i+1;k<=N;k++)
              soma2[i]+=fabs(M[i][j]); //segundo termo para calculo do beta[i]
          beta[i]=(soma1[i]+soma2[i])/M[i][i]; //valor de beta[i]
       }
       if(max<beta[i]) max=beta[i]; //achar o maior
    }
    
    if(max<1)
       return 1; //converge
    else
       return 0; //nao converge

}    
    
             
               
		  
    
		  
       
		  


