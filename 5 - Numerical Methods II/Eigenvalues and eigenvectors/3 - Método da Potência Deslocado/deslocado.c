/*
deslocado.c
Funções de leitura e escrita no arquivo, de manipulacao de vetores e matrizes necessarias para o metodo da potencia deslocado*/
#include "deslocado.h" 

//Le a dimensao da matriz, a tolerancia e o chute inicial a partir de um arquivo passado como parametro
void ler_dados(FILE *fd, float dados[MAX])
{
    int i,j,k;
    char va[30];
    int count=0;
    while (count<30)  
    {                
        va[count]=getc(fd);
        count++;
    }
    count=0;
    dados[1]=atoi(&va[count]);    //Armazena a dimensao da matriz.
    k=1;
    for(i=1;i<=dados[1];i++)
    {
        while(va[count]!=' ')   
            count++;
        dados[i+1]=atof(&va[count]);  //Armazena o chute inicial.
        count++;
        k++;
    }
    count++;
    while(va[count]!=' ')  
        count++;           
    dados[k+1]=atoi(&va[count+1]);  //Armazena o mu.
    count++;
    while(va[count]!=' ')  
        count++;           
    dados[k+2]=atoi(&va[count+1]);  //Armazena a toleracia.
}

//Le a matriz a partir do arquivo
void ler_matriz(FILE *fd, int d, float M[MAX][MAX])
{
    int i,j;
    char aux[d*360];
    int count=0; 
    while (!feof(fd))  //Guarda os caracteres do arquivo em 'aux'.
    {
        aux[count]=getc(fd);
        count++;
    }
    count=0;    
    for(i=1;i<=d;i++)
    {
        while (aux[count]!='\n')  
            count++;
        count++;
        for(j=1;j<=d;j++)
        {
          M[i][j] = atof(&aux[count]); 
          while(aux[count]!=' ')    
            count++;          
          count++;
        }  
        count = count - 2*d;     
    }
}

//Recebe a tolerancia em casas decimais e retorna um real
float tolerancia(int t)
{
    float E = 1;
    int i;
    for(i=0;i<t;i++)
      E = E * 0.1;
    return E;
}

//Calcula o modulo de um vetor
float modulo(float c[], int d)
{
   int i;
   float mod = 0;
   for(i=1;i<=d;i++)
       mod = mod + c[i]*c[i];     
   mod = sqrt(mod);
   return mod;            
}

//O vetor r recebe o vetor c normalizado
void normaliza(float c[], int d, float r[])
{
   int i;
   float mod = 0;
   mod = modulo(c,d);        
   for(i=1;i<=d;i++)
   {
       r[i] = c[i];
       r[i]=r[i]/(float)mod;
   }   
}

//Iguala dois vetores
void igualar_vetores(float V1[], float V2[], int d)
{
   int i;
   for(i=1;i<=d;i++)
      V1[i]=V2[i];	
}

//Mutiplica uma matriz por um vetor
void mult_MV(float M[MAX][MAX], float V[], int d, float RS[])
{
   int i,j; 
   for(i=1;i<=d;i++)
   {
      RS[i]=0;
      for(j=1;j<=d;j++)
         RS[i] = RS[i] + M[i][j]*V[j];
   }    
}

//Faz o produto escalar de 2 vetores de dimensao d
float escalar(float V1[], float V2[], int d)
{
   int i;
   float RS = 0;
   for(i=1;i<=d;i++)
      RS = RS + V1[i]*V2[i];
   return RS;  
}

//Subtrair uma matriz de outra
void sub_MM(float M1[MAX][MAX], float M2[MAX][MAX], float RS[MAX][MAX], int d)
{
   int i,j;
   for(i=1;i<=d;i++)
      for(j=1;j<=d;j++)
         RS[i][j] = M1[i][j] - M2[i][j] ;   
}

//Gera os resultados iniciais em um arquivo
void result_inicio(int d, int t, float mu, float E, float M[MAX][MAX], float chute[], float lambda)
{
    int i,j;
    FILE *saida;
    saida  = fopen("output.txt","w");
    fprintf(saida,"\n********************** METODO DA POTENCIA DESLOCADO **********************\n\n");
    fprintf(saida,"Dimensao da matriz: %d\nTolerancia: %d casas decimais(%f)\nMU = %5.3f\n",d,t,E,mu);
    fprintf(saida,"Vetor de chute inicial: ");
    for(i=1;i<=d;i++)
       fprintf(saida,"%9.6f ",chute[i]);
    fprintf(saida,"\nAutovalor inicial: %9.6f",lambda);
    fprintf(saida,"\nMatriz M:");          
    for(i=1;i<=d;i++)
    {
       fprintf(saida,"\n");
       for(j=1;j<=d;j++)
          fprintf(saida,"%9.6f ",M[i][j]);
    }
    fprintf(saida,"\n---------------------------------------------------------------------------");
    fclose(saida);
}

//Gera o resultado de uma iteracao em um arquivo
void result_iter(int k, int d, float y0[], float y1[], float x[], float lambda[2], float e, float E)
{
    int i,j;
    FILE *saida;
    saida  = fopen("output.txt","a");
    fprintf(saida,"\nK = %d\n\nLambda[%d] = %9.6f\nAutovetor inicial: y[%d]=  ",k,k,lambda[0],k);
    for(i=1;i<=d;i++)
       fprintf(saida,"%9.6f ",y0[i]); 
    fprintf(saida,"\nAutovetor inicial normalizado: x[%d]= ",k);
    for(i=1;i<=d;i++)
       fprintf(saida,"%9.6f ",x[i]);
    fprintf(saida,"\nAutovetor final: y[%d]=  ",k+1);
    for(i=1;i<=d;i++)
       fprintf(saida,"%9.6f ",y1[i]);
    fprintf(saida, "\nLambda[%d] = %9.6f",k+1,lambda[1]);
    fprintf(saida, "\ne = %12.8f     E = %12.8f",e,E);
    fprintf(saida,"\n---------------------------------------------------------------------------");
    fclose(saida);
}

//Gera o resultado final em um arquivo
void result_final(int k, int d, float y1[], float lambda)
{
    int i,j;
    FILE *saida;
    saida  = fopen("output.txt","a");
    fprintf(saida,"\n\nNumero de Iteracoes necessarias =  %d",k);
    fprintf(saida,"\nAutovetor encontrado: = ");
    for(i=1;i<=d;i++)
       fprintf(saida,"%9.6f ",y1[i]);
    fprintf(saida, "\nAutovalor encontrado = %9.6f",lambda);
    fprintf(saida,"\n\n*********************** FIM DO PROGRAMA ************************************");
    fclose(saida);
}

