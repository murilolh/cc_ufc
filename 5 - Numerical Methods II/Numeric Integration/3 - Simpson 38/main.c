//**************************************************************
//                                                             *
// Implementação de Métodos de Integração Numérica             *
// Métodos Numéricos II 2009.1                                 *
// Murilo Lima de Holanda                       Mat:0286740    *
//           						       *
// Regra de Simpson 3/8 Fechada Simples             	       * 
// Regra de Simpson 3/8 Aberta Simples                         *
//                                                             *
//**************************************************************

#include "polinomio.h"  //Arquivo com funções usadas para lidar com polinômios
#include "simpson38.h" //Arquivo com funções que calculam integrais através da regra de Simpson 1/3
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

void menu();
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

int main()
{
  TipoLista *P;//Lista usada para guardar o Polinômio
  int g,i,t,n;
  float a, b, f1, f4, Simp38F, Simp38A;
 
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
  
  float xf[2], fxf[2];//Vetores que guardam os pontos de divisão da regra Fechada 
  float xa[4],fxa[4];//Vetores que guardam os ponto de divisão da regra Aberta
  Divisao(a,b,3,xf);//Calcula os 2 pontos de divisão do polinômio para a Regra Fechada
  Divisao(a,b,5,xa);//Calcula os 4 pontos de divisão do polinômio para a Regra Aberta 
  //Calcula todas as imagens usadas na integração
  f1=getfx(a, P);
  f4=getfx(b, P);
  for(i=0;i<2;i++)
     fxf[i]=getfx(xf[i], P);
  for(i=0;i<4;i++)
     fxa[i]=getfx(xa[i], P);
  //Calcula a integral pelos métodos
  Simp38F=Simp38Fechada(a,b,f1,f4,fxf);
  Simp38A=Simp38Aberta(a,b,fxa);
  //Imprime os resultados   
  system("clear");
  printf("Grau do Polinomio: %d\n",g);
  printf("Termos do Polinomio: ");
  ImprimeLista(P);
  printf("\n\na= %0.2f        f(a)= %0.2f",a,f1);
  printf("\nb= %0.2f        f(b)= %0.2f\n",b,f4);  
  printf("\n\nIntegral por:\n\n");
  printf("Simpson 3/8 Fechada:         %0.2f\n\n",Simp38F);
  printf("Simpson 3/8 Aberta:          %0.2f\n\n",Simp38A);
  printf("----------------------------------------------------");
  
  free(P);
  menu();
}

