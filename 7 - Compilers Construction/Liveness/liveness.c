#include <stdio.h>

#define MAXVAR 100		//Máximo números de Variáveis
#define MAXNOH 1000		//Máximo números de Nós

int i, j, k;			//Usadas em loops	
int nIter;			//Iteração do loop
int nCom;			//Número de Comandos
int nVar;			//Número de variáveis	
int succ[MAXNOH][MAXNOH];	//Matriz que define a sucessão de nós
int def[MAXNOH][MAXVAR];	//Matriz de definição entre nós e variáveis
int use[MAXNOH][MAXVAR];	//Matriz de uso entre nós e variáveis
int in[MAXNOH][MAXVAR];		//Variáveis live-in do nó
int out[MAXNOH][MAXVAR];	//Variáveis live-out do nó
int inLinha[MAXNOH][MAXVAR];	//Vetor auxiliar
int outLinha[MAXNOH][MAXVAR];	//Vetor auxiliar

void leArquivo(FILE* entrada)
{
	fscanf(entrada, "%d  %d", &nCom, &nVar);
	
	for(i = 0; i < nCom; i++)
		fscanf(entrada, "%d %d %d", &use[i][0],  &use[i][1],  &use[i][2]);

	for(i = 0; i < nCom; i++)
		fscanf(entrada, "%d %d %d", &def[i][0],  &def[i][1],  &def[i][2]);
	
	for(i = 0; i < nCom; i++)
		for(j = 0; j < nCom; j++)
			fscanf(entrada, "%d", &succ[i][j]);   
}

void impResult(FILE* saida)
{
	fprintf(saida, "\n--- %dª Iteração --- \n\nIN: \n        ", nIter);

	for(i = 0; i < nVar; i++)
		fprintf(saida, "Var%d ", i); 

	fprintf(saida, "\n");

	for(i = 0; i < nCom; i++)
		fprintf(saida, " Com%d |  %d    %d    %d\n", i + 1, in[i][0],  in[i][1],  in[i][2]);

	fprintf(saida, "\nOUT: \n        ");
		
	for(i = 0; i < nVar; i++)
		fprintf(saida, "Var%d ", i); 

	fprintf(saida, "\n");
	
	for(i = 0; i < nCom; i++)
		fprintf(saida, " Com%d |  %d    %d    %d\n", i + 1, out[i][0],  out[i][1],  out[i][2]);

}

int comparar()
{
	for(i = 0; i < nCom; i++)
		for(j = 0; j < nVar; j++)
			if(inLinha[i][j] != in[i][j])
				return 0;
	
	for(i = 0; i < nCom; i++)
		for(j = 0; j < nVar; j++)
			if(outLinha[i][j] != out[i][j])
				return 0;

	 return 1;
}

int main()
{
	FILE *entrada = fopen("entrada.txt", "r");
	FILE *saida = fopen("saida.txt", "w");
	nIter = 0;

	leArquivo(entrada);
	
	fprintf(saida, "Número de Comandos: %d \nNumero de Variáveis: %d \n", nCom, nVar);

	do
	{
		for (i = 0; i < nCom; i++)
		{
			for(j = 0; j < nVar; j++)
			{ 
				inLinha[i][j] = in[i][j];
				outLinha[i][j] = out[i][j];

				int aux = out[i][j] - def[i][j];
				if (aux < 0)
					aux = 0;
				in[i][j] = use[i][j] || aux;       
			}	
	
			for (j = 0; j < nVar; j++)
					out[i][j] = 0; 			  

			for (j = 0; j < nCom; j++)
				if(succ[i][j] == 1)
					for(k = 0; k < nVar; k++)
						out[i][k] = out[i][k] || in[j][k];
		}
		nIter++;	
		
		impResult(saida);
	
	}
	while (!comparar());
}
