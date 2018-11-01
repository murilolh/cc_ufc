//**************************************************************
//                                                             *
// Implementação de Métodos de Integração Numérica             *
// Métodos Numéricos II 2009.1                                 *
// Murilo Lima de Holanda                          Mat:0286740 *
//                                                             *
// Gauss- Hermite com 2 ou 3 pontos                            *
// Gauss- Laguerre com 2 ou 3 pontos                           *
// Gauss- Chebyshev com 2 ou 3 pontos                          *
//	                                                       *
//**************************************************************

#include "gauss.h" //Arquivo com funções que calculam integrais através de Gauss-Hermite, Laguerre e Chebyshev
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

#define PI 3.14159265

void menu();
int e_pontos();
int e_metodo();
int main();

//Menu mostrado quando um teste é feito e seus resultados são mostrados
void menu()
{
  int p;
  printf("\n1- Fazer novo teste \n");
  printf("0- Sair\n");
  scanf("%d",&p);
  if(p==1)  main();
  else if (p==0) exit(1);
  else menu();
}

//Função de escolha do número de pontos
int e_pontos()
{
  system("clear");
  int n;
  printf("Digite o numero de pontos de desejado: (2 ou 3)\n");
  scanf("%d",&n);
  if (n==2) return 2;
  else if (n==3) return 3;
  else return e_pontos();
}

//Função de escolha do método
int e_metodo()
{  
  int o;
  system("clear");
  printf("Digite o metodo de integracao desejado:\n");
  printf("1- Gauss-Hermite\n");
  printf("2- Gauss-Laguerre\n");
  printf("3- Gauss-Chebyshev\n");
  scanf("%d",&o);
  system("clear");
  if ((o>0) && (o<4))
     return o;
  else 
     return e_metodo();  
}

int main()
{
  TipoLista *P;//Lista usada para guardar o Polinômio
  int g,i,t,n,m;
  float INT;
  float H2[2], PH2[2];
  float L2[2], PL2[2];
  float C2[2], PC2[2];
  float H3[3], PH3[3];
  float L3[3], PL3[3];
  float C3[3], PC3[3];
  
  system("clear");
  printf("Digite o grau do polinomio resultante(f(xi)):\n");
  scanf("%d",&g);
  P=crialista();
  
  system("clear");
  for(i=0;i<=g;i++)//Obtém a lista de termos do polinômio
  {
     printf("Digite o termo %d do polinomio:\n",i);
     scanf("%d",&t);
     Inserir(t, P);
  }
  
  //Recebe o número de pontos
  n= e_pontos();  
  
  //Tabela de Valores 
  H2[0]= -0.707106781;    PH2[0]= 0.886226926;
  H2[1]= 0.707106781;     PH2[1]= 0.886226926;
  
  H3[0]= -1.224474487;    PH3[0]= 0.295408975;
  H3[1]= 0.0;             PH3[1]= 1.181635901; 
  H3[2]= 1.224474487;     PH3[2]= 0.295408975;
  
  L2[0]= 0.585786438;     PL2[0]= 0.853553391;
  L2[1]= 3.414213562;     PL2[1]= 0.146446609;

  L3[0]= 0.415774557;     PL3[0]= 0.71109301;
  L3[1]= 2.29428036;      PL3[1]= 0.278517734; 
  L3[2]= 6.289945083;     PL3[2]= 0.103892565;  
     
  C2[0]= 0.707106781;     PC2[0]= (PI/2);
  C2[1]= -0.707106781;    PC2[1]= (PI/2); 
   
  C3[0]= 0.866025403;     PC3[0]= (PI/3);
  C3[1]= 0.000000000;     PC3[1]= (PI/3);
  C3[2]= 0.866025403;     PC3[2]= (PI/3);      

  //Recebe o métono a ser usado
  m = e_metodo();

  //Calcula e imprime o resultado
  system("clear");
  printf("Grau do Polinomio f(xi): %d\n",g);
  printf("Termos do Polinomio f(xi): ");
  ImprimeLista(P);
  switch(m)
  {
     case 1:
         if (n==2) 
            INT=(metodo(2,H2,PH2,P));
  	 else
            INT=(metodo(3,H3,PH3,P));
         printf("\n\nf = e^(-x²)*f(xi)");
         printf("\n\nIntervalo:   -INF    a    +INF\n"); 
         printf("\nIntegral por Gauss-Hermite com %d pontos:\n\n",n);
     break;
     case 2:
         if (n==2) 
            INT=(metodo(2,L2,PL2,P));
         else
            INT=(metodo(3,L3,PL3,P));
         printf("\n\nf = e^(-x)*f(xi)");
         printf("\n\nIntervalo:   0    a    +INF\n"); 
         printf("\nIntegral por Gauss-Laguerre com %d pontos:\n\n",n);
     break;
     case 3:
         if (n==2) 
            INT=(metodo(2,C2,PC2,P));
         else
            INT=(metodo(3,C3,PC3,P));
         printf("\n\nf = (1/(sqrt(1-x²)))*f(xi)");
         printf("\n\nIntervalo:   -1    a    +1\n"); 
         printf("\nIntegral por Gauss-Chebyshev com %d pontos:\n\n",n);
     break;       
  }
  printf("   %0.2f\n\n",INT);
  printf("----------------------------------------------------");     
  
  free(P);
  menu();
}

