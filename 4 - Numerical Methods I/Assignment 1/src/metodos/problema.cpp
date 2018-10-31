#include "problema.h"
#include <iostream>
#include <iomanip>
#include <cmath>


using namespace std;

#define MAX 30

problema::problema(int n, double e) //atribui numero de particulas a N e precisao a E
{
	N = n;
	E = e;	
}

int problema:: simulacao()
{
	int flag = 1;
	Matriz = new double[MAX][MAX]; //definição da matriz onde ficam guardadas as respostas
	unsigned int escolha; //opçao digitada pelo usuario
	
	interface(); 
	
	//criaçao do menu
	do {
		
		system("clear");
		cout << "--------------------------------------------------------------------------------\n"
        	 << "|                        TRABALHO I DE MÉTODOS NUMÉRICOS                       |\n"
 	 	 	 << "--------------------------------------------------------------------------------\n"
	 	 	 << "\n\n Número de partículas: " << N << "       Precisão: " << E << "\n"	 	  
			 << "\n\n Escolha uma dentre as alternativas abaixo: \n"  
			 << "\n 1-Imprimir Quadro Comparativo\n"
			 << " 2-Imprimir Quadro Resposta\n"
			 << " 3-Reiniciar o programa\n"
			 << " 0-Sair\n"
			 << "\n Sua escolha: ";
		 cin >> escolha;
		
		switch (escolha) {
			case 1: 
				comparativo();
				system("clear");
				break;
			case 2: 
				resposta();
				system("clear");
				break;
			case 3: 
				delete Matriz;
				return 1;
				break;
			case 0: 
				cout << "\n Fim do programa\n" << std::endl;
				delete Matriz;
				return 0;
		 		break;
			default:
		 		break;
	 		}
	 		 
	 }while (escolha != 0 && escolha != 3);
	
}
	

void problema:: interface()
{  
 	double Po; //instanciação das variáveis e matrizes que serão utilizadas
    double* QuadComp = new double[4];
    double* QuadComp2 = new double[4];
    double* Intervalo = new double [2];
    
    system("clear");
    cout << "--------------------------------------------------------------------------------\n"
         << "|                        TRABALHO I DE MÉTODOS NUMÉRICOS                       |\n"
 	 	 << "--------------------------------------------------------------------------------\n"
	 	 << "\n\n Número de partículas: " << N << "       Precisão: " << E << "\n";

	 	 
	 	 
    for(int i=0; i<N ; i++) //Guardar deslocamentos iniciais
    {
	    cout<< "\n Digite o deslocamento inicial da partícula P" << i << ": ";
	    cin>>Po;	
           
        o = new original(Po, E); //instancia o atributo o (construtor do N-R original)
        m = new modificado(Po, E); //instancia o atributo m (construtor do N-R modificado)
		
	    Intervalo = o->isolamento();
	    QuadComp = o->newton(); //recebe a matriz com os dados para o quadro do N-R original
        QuadComp2 = m->newton();//recebe a matriz com os dados para o quadro do N-R modificado

        //definiçao dos elementos da matriz que serao apresentados nos quadros
        Matriz[i][0] = i;
        Matriz[i][1] = Po;
        Matriz[i][2] = Intervalo[0];
        Matriz[i][3] = Intervalo[1];
	    
	    for (int k=0; k<5; k++)
	    {
			Matriz[i][k+4] = QuadComp[k];
			Matriz[i][k+9] = QuadComp2[k];
	    }
	    
	    delete o; //apos utilizados,os atributos sao deletados
	    delete m;      	         
    }
    
    system("clear");
    
    delete Intervalo;  //apos utilizadas,as matrizes sao apagadas
    delete QuadComp;
    delete QuadComp2; 
}

//Imprime o quadro comparativo
void problema:: comparativo()
{
    system("clear"); 
    cout << "--------------------------------------------------------------------------------\n"
	     << "|                             QUADRO COMPARATIVO                               |\n"
         << "--------------------------------------------------------------------------------\n"
	     << "|                        Método Newton-Raphson ORIGINAL                        |\n"
         << "--------------------------------------------------------------------------------\n"     
	     << "|n   |P0     |[a, b]  |x0o   |do          |Ko  |fxo            | |xk - x(k-1)| |\n" 
	     << "--------------------------------------------------------------------------------\n";
	
	 //imprime valores do N-R original				
    for(int i=0, j=0 ; i<N; i++)
    {		
	 	cout <<  left << "|" << setw(4) <<  Matriz[i][j] <<"|"<< setw(7) <<  setprecision(4) 
	 	<< Matriz[i][j+1] << "|" << "[" << setw(2) << Matriz[i][j+2]<< ", "<< setw(2) 
	 	<< Matriz[i][j+3] << "]" << "|"	<< setw(6) << Matriz[i][j+4] << "|" << setw(12) 
	 	<< setprecision(8) << Matriz[i][j+5]<< "|" << setw(4) << Matriz[i][j+6] << "|" 
	 	<< setw(15) << setprecision(11) << fixed << Matriz[i][j+7] << "|" << setw(15) 
	 	<< setprecision(11) << Matriz[i][j+8] << "|";
	 	cout.unsetf(ios_base::fixed);
    }
     
    cout << "--------------------------------------------------------------------------------\n"
	 	 << "|                       Método Newton-Raphson MODIFICADO                       |\n"
     	 << "--------------------------------------------------------------------------------\n"     
	 	 << "|n   |P0     |[a, b]  |x0m   |dm          |Km  |fxm            | |xk - x(k-1)| |\n" 
	 	 << "--------------------------------------------------------------------------------\n"; 			
	
	//imprime valores do N-R modificado
	for(int i=0, j=0 ; i<N; i++)	
	{
		cout <<  left << "|" << setw(4) <<  Matriz[i][j] <<"|"<< setw(7) << setprecision(4) 
		<< Matriz[i][j+1] << "|" << "[" << setw(2) << Matriz[i][j+2]<< ", "<< setw(2) 
		<< Matriz[i][j+3] << "]" << "|" << setw(6) << Matriz[i][j+9] << "|" << setw(12) 
		<< setprecision(8) << Matriz[i][j+10]<< "|" << setw(4) << Matriz[i][j+11] << "|" 
		<< setw(15) << setprecision(11) << fixed << Matriz[i][j+12] << "|" << setw(15) 
		<< setprecision(11) << Matriz[i][j+13] << "|";
	 	cout.unsetf(ios_base::fixed);
	
    }	
    //setw() = numero de caracteres entre as "|" 
    //setprecision() = numero de casas decimais 
    //fixed = colocar o float em forma decimal
    //cout.unsetf(ios_base::fixed); = cancelar fixed
    cout << "--------------------------------------------------------------------------------\n" 		
         << "\nPressione ENTER para voltar ao menu anterior..." << endl;
    getchar();
    getchar();
}

//Imprime quadro resposta 
void problema:: resposta()
{
	system("clear");
	
	cout << "--------------------------------------------------------------------------------\n"
	     << "|                             QUADRO RESPOSTA                                  |\n"
	     << "--------------------------------------------------------------------------------\n"
         << "|n     |P0         |do                |dm                | |(do-dm)|           |\n"
	     << "--------------------------------------------------------------------------------\n";
				
    for(int i=0, j=0 ; i<N; i++)
    {		
	 cout <<  left << "|" << setw(6) <<  Matriz[i][j] <<"|"<< setw(11) << setprecision(4) 
	 << Matriz[i][j+1] << fixed << "|" << setw(18)<< setprecision(14) << Matriz[i][j+5]<< "|" 
	 << setw(18) << setprecision(14) << Matriz[i][j+10]<<"|" << setw(21)<< setprecision(17) 
	 << fabs((Matriz[i][j+5])-(Matriz[i][j+10]))<<"|\n"
     << "--------------------------------------------------------------------------------\n";
	 cout.unsetf(ios_base::fixed);        	 		
    }
      		
    cout << "\nPressione ENTER para voltar ao menu anterior..." << endl;
    getchar();
    getchar();
    
}


