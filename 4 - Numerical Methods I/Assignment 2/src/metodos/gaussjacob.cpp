#include "gaussjacob.h"
#include <iomanip>
#include <iostream>
#include <cmath>

using namespace std;

#define MAX 30

/* método construtor de gauss-jacob */
gaussjacob::gaussjacob(double (*M)[MAX], double* T, int N, double E): metodo(M, T, N, E){};

int gaussjacob::inversa(){
	
	if (criteriodaslinhas() == 1)
	{
		cout << "Criterio das linhas satisfeito!" <<endl;
		getchar();
		getchar();
	}
	else
	{
		cout << "Criterio das linhas nao satisfeito!" << endl;
		getchar();
		getchar();
	}
		
	double D[MAX];
	double X[3] = {1,1,1};
	double X1[MAX];
	double Teste1, Teste2;
	double inversa[MAX][MAX];
	int B[MAX];
	int iteracoes[MAX];
	int k=0;
	
	int I[MAX][MAX]; //matriz identidade
			
	//inicializa a matriz identidade		
	for (int i=0; i<N; i++)
	{
		for (int j=0; j<N; j++)
		{
			if (i==j) I[i][j] = 1;
			else I[i][j] = 0;
		}
	}

	
	for (int c=0; c<N; c++)  // para cada coluna da matriz de coeficientes A
	{
		for (int j=0; j<N; j++)  // atribui ao vetor B os elementos de cada coluna da matriz identidade
			B[j] = I[j][c];
			
		while(true)
		{
			for (int i=0;i<N;i++)
				X1[i] = ((B[i] + somatorio(X,i))/M[i][i]);  //calcula os valores da coluna usando o metodo
		
			cout << "P/ K=" << k << endl;
			
			for(int i=0;i<N;i++)
				cout << "x" << i << " = " << X1[i] << " ";
			cout << endl;
				
			k++; //incrementa o numero de iterações por coluna da matriz inversa
			
			Teste1 = fabs(max(diferenca(X,X1)));  //teste da diferença dos coeficientes absoluta
			Teste2 = fabs(max(diferenca(X,X1)))/fabs(max(X1));	//teste da diferença dos coeficientes relativa
			
			if ((Teste1 < E) || (Teste2 < E)) break;  //a iteração para quando um dos testes for satisfeito
													
			for(int i=0;i<N;i++)   //atualiza os valores do vetor resultado a cada iteração
				X[i]=X1[i];   			
		}
		
		iteracoes[c] = k; //atribui o valor das iterações por cada coluna num vetor de iteraçoes
		
		k = 0;
		
		for (int j=0;j<N; j++)
		{
			inversa[j][c] = X1[j];    // atribui os valores de X1 na coluna c da matriz inversa
			X[j] = X1[j] = 1;            //reinicializa os vetores utilizados no método
		}				
	}

	for (int i=0; i<N ; i++)
		for (int j=0; j<N ; j++)
			D[i] += inversa[i][j]*T[j];
		
	system("clear");	
	cout << "--------------------------------------------------------------------------------\n"
	     << "|                       SOLUÇÃO PELO MÉTODO DE GAUSS-JACOB                     |\n"
	     << "--------------------------------------------------------------------------------\n"
		 << "| Termos da matriz inversa de A												|\n"
		 << "--------------------------------------------------------------------------------\n";
	 	 	 
	 	for (int i=0; i<N ; i++)
		{
			cout << "\n";
			for (int j=0; j<N ; j++)	
	 			cout << setw(8) << setprecision(6) << inversa[i][j] << " ";
	 		cout << "\n";
    	}	
    	
	cout << "\n--------------------------------------------------------------------------------\n"
	     << "| Deslocamentos das particulas													|\n"
		 << "--------------------------------------------------------------------------------\n"
		 << endl;
		 
		for (int i=0; i<N ; i++)
		{
			cout << "    D[" << i+1 << "]: " << setw(8) << setprecision(6) << D[i] << endl;
			cout << "\n";
		}
	cout << "--------------------------------------------------------------------------------\n";
	cout << "\nPressione ENTER para voltar ao menu anterior..." << endl;
	getchar();

	return 0;
}

