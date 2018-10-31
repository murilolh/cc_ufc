#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <cmath>

#include "metodos/problema.h"
#include "metodos/newtonraphson.h"
#include "metodos/modificado.h"
#include "metodos/original.h"

/*	Equipe:
 * 	Rafael de Lima
 * 	Paulo Sérgio V. Alves
 * 	Cicero Antonio         
 * 	Leandro Monteiro
 * 	Murilo de Holanda
 */ 
 
using namespace std;

int main()
{
	int n; //numero de particulas 
	int flag = 1; //usado para garantir o retorno ao menu inicial ou sair do programa
	double e; //precisão
	problema *p; // define um objeto dinâmico da classe problema
		
	do 
	{
		system("clear");
		cout << "--------------------------------------------------------------------------------\n"
        	 << "|                        TRABALHO I DE MÉTODOS NUMÉRICOS                       |\n"
 	 	 	 << "--------------------------------------------------------------------------------\n"
	 	 	 << endl;
	
    	cout<< "\n Digite o número de partículas: ";
    	cin>>n;
    	cout<< "\n Digite a precisão: ";
    	cin>>e;
	
    	p = new problema(n, e); //instancia o objeto
	
		flag = p->simulacao(); // simula o problema
	
		delete p;
	
	}while (flag != 0);
			
    return 0;	
}
	
