#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <cmath>

#include "metodos/contexto.h"
#include "metodos/metodo.h"
#include "metodos/gaussjacob.h"
#include "metodos/gaussseidel.h"

/*	Equipe:
 * 	Rafael de Lima
 * 	Paulo Sérgio V. Alves
 * 	Cicero Antonio         
 * 	Leandro Monteiro
 * 	Murilo de Holanda
 */ 
 
using namespace std;

#define MAX 30

int main()
{
	int n; //numero de particulas 
	int flag = 1; //usado para garantir o retorno ao menu inicial ou sair do programa
	double e; //precisão
	
		
	do 
	{
		system("clear");
		cout << "--------------------------------------------------------------------------------\n"
        	 << "|                        TRABALHO II DE MÉTODOS NUMÉRICOS                      |\n"
 	 	 	 << "--------------------------------------------------------------------------------\n"
	 	 	 << endl;
	
    	cout<< "\n Digite o número de partículas: ";
    	cin>>n;
    	cout<< "\n Digite a precisão: ";
    	cin>>e;
		
		system("clear");
    	cout << "--------------------------------------------------------------------------------\n"
         	 << "|                        TRABALHO II DE MÉTODOS NUMÉRICOS                      |\n"
 	 	 	 << "--------------------------------------------------------------------------------\n"
	 	 	 << "\n\n Número de partículas: " << n << "       Precisão: " << e << "\n";
    	

    	double (*A)[MAX] = new double[n][MAX];
		double B[MAX];
		
		cout << "\n Digite os termos da matriz dos coeficientes: ";
		cout << "\n\n";
		
    	for (int i=0; i<n ; i++)
			for (int j=0; j<n ; j++)
			{
				cout << " A[" << i+1 << "][" << j+1 << "]: ";
				cin >> A[i][j];
			}
			
		cout << "\n Digite o vetor de termos independentes: ";
		cout << "\n\n";
		
		for (int i=0; i<n; i++)
			{
				cout << " B[" << i+1 << "]: ";
		    	cin >> B[i];
			}
			
		
	    
	    //criaçao do menu
	    
	    unsigned int escolha; //opçao digitada pelo usuario
	    
		do 
		{
			system("clear");
			cout << "--------------------------------------------------------------------------------\n"
        		 << "|                        TRABALHO II DE MÉTODOS NUMÉRICOS                      |\n"
 	 		 	 << "--------------------------------------------------------------------------------\n"
	 		 	 << "\n\n Número de partículas: " << n << "       Precisão: " << e << "\n"	 	  
				 << "\n\n Escolha uma dentre as alternativas abaixo: \n"  
				 << "\n 1- Obter a inversa de A e os deslocamentos pelo metodo de Gauss-Jacob\n"
				 << " 2- Obter a inversa de A e os deslocamentos pelo metodo de Gauss-Seidel\n"
				 << " 3- Reiniciar o programa\n"
				 << " 0- Sair\n"
				 << "\n Sua escolha: ";
		
			 cin >> escolha;
		
			 switch (escolha) {
				case 1:
					system("clear");
					
					gaussjacob *jacob; // define um objeto dinâmico da classe problema
														 	
					jacob = new gaussjacob(A, B, n, e); //instancia o atributo o (construtor do N-R original)
        			
        			contexto *contexto1;
        			
        			contexto1 = new contexto(jacob);
							
					contexto1->executar();
					
					break;
				case 2: 
					system("clear");
					
					gaussseidel *seidel; // define um objeto dinâmico da classe problema
					
					seidel = new gaussseidel(A, B, n, e); //instancia o atributo o (construtor do N-R original)
					
					contexto *contexto2;
					
					contexto2 = new contexto(seidel);
					
				    contexto2->executar();
				
					break;
				case 3: 
					flag = 1;
					break;
				case 0: 
					cout << "\n Fim do programa\n" << std::endl;
					flag = 0;
					break;
		 		default:
		 		break;
	 		}
	 		 
	 	}while (escolha != 0 && escolha != 3); 
	 	
	 	delete A;
	 	
	}while (flag != 0);		
    return 0;	
}
	
