/*
qr.c
Funções de leitura e escrita no arquivo, de manipulacao de vetores e matrizes necessarias para o metodo QR*/
#include "qr.h" 

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

//Usa Householder para alterar a matriz T e gerar a matriz de Householder(H)
void householder(int d, float E, float T[MAX][MAX], float H[MAX][MAX])
{
    int i,j,k,c,it;
    float P[d+1];
    float Pl[d+1];
    float N[d+1];
    float mP,mN;
    float max;
    float h[MAX][MAX];
    float ht[MAX][MAX];
    float I[MAX][MAX];
    float aux[MAX][MAX];
   
    //Inicializar matriz identidade e a matriz de Householder
    for(i=1;i<=d;i++)
       for(j=1;j<=d;j++)
       {
          if(i==j)
          {
            I[i][j] = 1;
            H[i][j] = 1;
          }
          else
          {
            I[i][j] = 0;
            H[i][j] = 0;
          }
       }    

    it=0;
    do
    {
        c=1;
        max=1;
        for (k=1;k<=d-2;k++)
        {
            //Escolha de P
            for(i=1;i<=d;i++)
            {
               if(i>c)
                  P[i] = T[i][c];
               else
                  P[i] = 0;
            }          
            //Calculo de |P|
    	    mP = modulo(P,d);
    	    //Calculo de P'
            for(i=1;i<=d;i++)
            {
               if (i==c+1)
               {
                  if (P[i]>0)
                     Pl[i] = -mP;
                  else
                     Pl[i] = mP;
               }
               else
                  Pl[i]=0;
            }
    	    //Passo N = N = (P - P')/|P - P'|
    	    sub_VV(P,Pl,N,d);//Acha P - P'
            mN = modulo(N,d);//Acha |P - P'|
            div_VE(N,mN,N,d);//Acha N = (P - P')/|P - P'|
            //Passo h = I - 2*N*Nt
            mult_V(N,h,d);//Acha N*Nt
            mult_VE(h,2,d);//Acha 2*N*Nt
            sub_MM(I,h,h,d);//Acha I - 2*N*Nt
            //Passo T = h*T*h
            mult_MM(h,T,aux,d);//Acha aux = h*T
            igualar_MM(T,aux,d);//T = aux
            trasp_M(h,ht,d);//Matriz ht é a trasnposta de h
            mult_MM(T,ht,aux,d); //Acha aux=h*T*ht
            igualar_MM(T,aux,d);//T = aux
            //Passo H=H*h
            mult_MM(H,h,aux,d); //Acha aux = H*h
            igualar_MM(H,aux,d);//H = aux

            max = max_elem_MT(T,d);//Acha o elemento maximo fora da tridiagonal
            c++;//Incrementa o numero da coluna
            it++;//Incrementa o numero de iteracoes              
        }
    }while((max >= E) && (it<MAX));              
}

//Acha os autovalores de M gerando a matriz X com os autovetores correspondentes
void qr(int d, float E, float A[MAX][MAX], float X[MAX][MAX])
{
    int i,j,k;
    float max,theta, costheta, sentheta;
    float I[MAX][MAX];
    float Q[MAX][MAX];
    float Qt[MAX][MAX];
    float qt[MAX][MAX];
    float R[MAX][MAX];
    float aux[MAX][MAX];
    
    //Inicializar matriz identidade
    for(i=1;i<=d;i++)
       for(j=1;j<=d;j++)
       {
          if(i==j)
            I[i][j] = 1;
          else
            I[i][j] = 0;
       }    
    
    k=0;
    do
    {
        igualar_MM(Qt,I,d);//A matriz Qt inicia como uma identidade
        max=1;
        for (j=1;j<=d-1;j++)
        {
            for(i=1;i<=d;i++)
            {
               if(i>j)
               {
                  igualar_MM(qt,I,d);//A matriz qt inicia como uma identidade
                  if (A[j][j] != 0)
                     theta = atan(A[i][j]/A[j][j]);
                  else
                     theta = PI/2;
                  costheta = cos(theta);
                  sentheta = sin(theta);
                  qt[j][j] = costheta;
                  qt[i][i] = costheta;
                  qt[j][i] = sentheta;
                  qt[i][j] = -sentheta;
                  mult_MM(qt,A,aux,d);//Acha aux = qt*A
                  igualar_MM(A,aux,d);//A = aux
                  mult_MM(qt,Qt,aux,d);//Acha aux = qt*Qt
                  igualar_MM(Qt,aux,d);//Qt = aux
               }
            }
        }
        trasp_M(Qt,Q,d);//Matriz Q é a trasnposta de Qt
        igualar_MM(R,A,d);//Acha R =A, ja que a multiplicacao Qt*A ja foi feita usando os qt's
        mult_MM(R,Q,A,d);//Acha A = R*Q
        
        mult_MM(X,Q,aux,d); //Acha aux = X*Q
        igualar_MM(X,aux,d);//X = aux
        
        max = max_elem_MD(A,d);//Acha o elemento maximo fora da diagonal
        k++;//Incrementa o numero de iteracoes
    }while((max >= E) && (k<MAX));
}

//Gera os resultados iniciais em um arquivo
void result_inicio(int d, int t, float E, float M[MAX][MAX])
{
    int i,j;
    FILE *saida;
    saida  = fopen("output.txt","w");
    fprintf(saida,"\n\n*********************** METODO QR ******************************************\n");
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
void result_final(int d, float A[MAX][MAX], float X[MAX][MAX])
{
    int i,j;
    FILE *saida;
    saida  = fopen("output.txt","a");
    fprintf(saida,"\n\nLista de Autovalores:\n");          
    for(i=1;i<=d;i++)
       for(j=1;j<=d;j++)
          if(i==j)
            fprintf(saida,"%12.8f ",A[i][j]);
    fprintf(saida,"\n\nMatriz de Autovetores:");          
    for(i=1;i<=d;i++)
    {
       fprintf(saida,"\n");
       for(j=1;j<=d;j++)
          fprintf(saida,"%12.8f ",X[i][j]);
    }
    fprintf(saida,"\n\n*********************** FIM DO PROGRAMA ************************************");
    fclose(saida);
}

