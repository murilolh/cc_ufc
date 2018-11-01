/*
jacobi.c
Funções de leitura e escrita no arquivo, de manipulacao de vetores e matrizes necessarias para o metodo de Jacobi*/
#include "jacobi.h" 

//Le a dimensao da matriz e a tolerancia a partir de um arquivo passado como parametro
void ler_dados(FILE *fd, float dados[])
{
    int i,j,k;
    char va[30];
    int count=0;
    while (count<30)  
    {                
        va[count]=getc(fd);
        count++;
    }
    dados[0]=atoi(&va[0]);    //Armazena a dimensao da matriz.
    count=0;
    while(va[count]!=' ')  
        count++;           
    dados[1]=atoi(&va[count+1]);  //Armazena a toleracia.
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

//Mutiplica uma matriz de dimensao d por um vetor de tamanho d
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

//Faz o produto escalar de 2 vetores de tamanho t
float escalar(float V1[], float V2[], int t)
{
   int i;
   float RS = 0;
   for(i=1;i<=t;i++)
      RS = RS + V1[i]*V2[i];
   return RS;  
}
//Subtrair um vetor de outro
void sub_VV(float V1[], float V2[], float RS[], int t)
{
   int i;
   for(i=1;i<=t;i++)
      RS[i] = V1[i]-V2[i];   
}

//Divide um vetor por um escalar
void div_VE(float V[], float E, float R[],int t)
{
   int i;
   for(i=1;i<=t;i++)
       R[i]=V[i]/E;
}

//Multiplica um vetor por seu transposto
void mult_V(float V[], float M[MAX][MAX],int t)
{
   int i,j;
   for(i=1;i<=t;i++)
      for(j=1;j<=t;j++)
         M[i][j]=V[i]*V[j];
}

//Multiplica uma matriz por um escalar
void mult_VE(float M[MAX][MAX],int E,int d)
{
   int i,j;
   for(i=1;i<=d;i++)
      for(j=1;j<=d;j++)
         M[i][j] = M[i][j] * E;
}

//Subtrair uma matriz de outra
void sub_MM(float M1[MAX][MAX], float M2[MAX][MAX], float RS[MAX][MAX], int d)
{
   int i,j;
   for(i=1;i<=d;i++)
      for(j=1;j<=d;j++)
         RS[i][j] = M1[i][j] - M2[i][j] ;   
}

//Multiplica uma matriz por outra
void mult_MM(float M1[MAX][MAX], float M2[MAX][MAX], float RS[MAX][MAX], int d)
{
   int i,j,k;
   for(i=1;i<=d;i++)
      for(j=1;j<=d;j++)
      {
         RS[i][j] = 0;
         for(k=1;k<=d;k++)
            RS[i][j] = RS[i][j] + M1[i][k] * M2[k][j];
      }
}

//Obtem o maior elemento fora da tridiagonal de uma matriz
float max_elem_MT(float M[MAX][MAX], int d)
{
   int i,j;
   float max;
   max = 0;
   for(i=1;i<=d;i++)
      for(j=1;j<=d;j++)
         if( ((i>j+1) || (j>i+1)) && (fabs(M[i][j]) > max) )
             max = fabs(M[i][j]); 
   return max;
}

//Obtem o maior elemento fora da diagonal de uma matriz
float max_elem_MD(float M[MAX][MAX], int d)
{
   int i,j;
   float max;
   max = 0;
   for(i=1;i<=d;i++)
      for(j=1;j<=d;j++)
         if((i!=j) && (fabs(M[i][j]) > max))
             max = fabs(M[i][j]); 
   return max;
}

//Iguala uma matriz a outra
void igualar_MM(float M1[MAX][MAX] ,float M2[MAX][MAX], float d)
{ 
   int i,j;
   for(i=1;i<=d;i++)
      for(j=1;j<=d;j++)
         M1[i][j] = M2[i][j];
}

//Traspoe a matriz A em At
void trasp_M(float A[MAX][MAX], float At[MAX][MAX], int d)
{
   int i,j;
   for(i=1;i<=d;i++)
      for(j=1;j<=d;j++)
         At[j][i] = A[i][j];
}

//Acha os autovalores de M gerando a matriz R com os autovetores correspondentes
void jacobi(int d, float E, float M[MAX][MAX], float R[MAX][MAX])
{
    int i,j,k,lin,col;
    float max,theta, costheta, sentheta;
    float I[MAX][MAX];
    float r[MAX][MAX];
    float rt[MAX][MAX];
    float aux[MAX][MAX];
    
    //Inicializar matriz identidade e a matriz de Autovetores(matrizes de rotacao acumuladas)
     for(i=1;i<=d;i++)
       for(j=1;j<=d;j++)
       {
          if(i==j)
          {
            I[i][j] = 1;
            R[i][j] = 1;
          }
          else
          {
            I[i][j] = 0;
            R[i][j] = 0;
          }
       }   
    
    k=0;
    do
    {
        max=1;
        for (j=1;j<=d;j++)
        {
            for(i=1;i<=d;i++)
            {
               if(i>j)
               {
                  igualar_MM(r,I,d);//A matriz r inicia como uma identidade
                  theta = 0.5*atan((2*M[i][j])/(M[i][i]-M[j][j]));
                  costheta = cos(theta);
                  sentheta = sin(theta);
                  r[j][j] = costheta;
                  r[i][i] = costheta;
                  r[j][i] = -sentheta;
                  r[i][j] = sentheta;
                  trasp_M(r,rt,d);//Matriz rt é a transposta de r
                    
                  mult_MM(r,M,aux,d);//Acha aux = r*M
                  igualar_MM(M,aux,d);//M = aux
                  mult_MM(M,rt,aux,d); //Acha aux = M*rt
                  igualar_MM(M,aux,d);//M = aux 
                                   
                  mult_MM(R,r,aux,d);//Acha aux = R*r
                  igualar_MM(R,aux,d);//R = aux
               }
            }
        }
        max = max_elem_MD(M,d);//Acha o elemento maximo fora da diagonal
        k++;//Incrementa o numero de iteracoes        
    }while((max >= E) && (k<MAX));
}

//Gera os resultados iniciais em um arquivo
void result_inicio(int d, int t, float E, float M[MAX][MAX])
{
    int i,j;
    FILE *saida;
    saida  = fopen("output.txt","w");
    fprintf(saida,"\n\n*********************** METODO DE JACOBI ***********************************\n");
    fprintf(saida,"Dimensao da matriz: %d\nTolerancia: %d casas decimais(%f)\n",d,t,E);
    fprintf(saida,"\nMatriz M:");          
    for(i=1;i<=d;i++)
    {
       fprintf(saida,"\n");
       for(j=1;j<=d;j++)
          fprintf(saida,"%12.8f ",M[i][j]);
    }   
    fclose(saida);
}

//Gera o resultado final em um arquivo
void result_final(int d, float M[MAX][MAX], float R[MAX][MAX])
{
    int i,j;
    FILE *saida;
    saida  = fopen("output.txt","a");
    fprintf(saida,"\n\nLista de Autovalores:\n");          
    for(i=1;i<=d;i++)
       for(j=1;j<=d;j++)
          if(i==j)
            fprintf(saida,"%12.8f ",M[i][j]);
    fprintf(saida,"\n\nMatriz de Autovetores:");          
    for(i=1;i<=d;i++)
    {
       fprintf(saida,"\n");
       for(j=1;j<=d;j++)
          fprintf(saida,"%12.8f ",R[i][j]);
    }
    fprintf(saida,"\n\n*********************** FIM DO PROGRAMA ************************************");
    fclose(saida);
}

