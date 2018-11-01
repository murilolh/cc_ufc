//**************************************************************
//                                                             *
// Implementação de Métodos de Integração Numérica             *
// Métodos Numéricos II 2009.1                                 *
// Murilo Lima de Holanda                       Mat:0286740    *
//                                                             *
// Legendre com 2 ou 3 pontos                                  *
//					                       *
//**************************************************************

#include "legendre.h" //Arquivo com funções que calculam integrais através de Legendre
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

void menu();
int escolha();
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

int escolha()
{
  system("clear");
  int n;
  printf("Digite o numero de pontos de Legendre desejado: (2 ou 3)\n");
  scanf("%d",&n);
  if (n==2) return 2;
  else if (n==3) return 3;
  else return escolha();
}

int main()
{
  TipoLista *P;//Lista usada para guardar o Polinômio
  int g,i,t,n;
  float a, b, INT;
  float R2[2], P2[2];
  float R3[3], P3[3];
 
  system("clear");
  printf("Digite o grau do polinomio a ser integrado:\n");
  scanf("%d",&g);
  P=crialista();
  
  system("clear");
  for(i=0;i<=g;i++)//Obtém a lista de termos do polinômio
  {
     printf("Digite o termo %d do polinomio:\n",i);
     scanf("%d",&t);
     Inserir(t, P);
  }
  //Recebe o intervalo de integração
  system("clear");
  printf("Digite o inicio do intervalo:\n");
  scanf("%f",&a);
  printf("Digite o fim do intervalo:\n");
  scanf("%f",&b);

  //Recebe o número de pontos de Legendre
  n= escolha();

  //Tabela de Valores
  R2[0]= -1/sqrt(3);
  R2[1]= 1/sqrt(3);
  P2[0]=P2[1]=1;
  R3[0]= -0.77456669;
  R3[1]= 0;
  R3[2]= 0.77456669;
  P3[0]= 0.55555556;
  P3[1]= 0.88888889;
  P3[2]= 0.55555556;

  //Calcula a integral
  if (n==2) 
      INT = Legendre(a,b,2,R2,P2,P);
  else
      INT = Legendre(a,b,3,R3,P3,P);
    
  //Imprime o resultado   
  system("clear");
  printf("Grau do Polinomio: %d\n",g);
  printf("Termos do Polinomio: ");
  ImprimeLista(P);
  printf("\n\na= %0.2f",a);
  printf("\nb= %0.2f \n",b);
  printf("\n\nIntegral por %d pontos de Legendre:\n\n",n);
  printf("   %0.2f\n\n",INT);
  printf("----------------------------------------------------");

  free(P);
  menu();
}

