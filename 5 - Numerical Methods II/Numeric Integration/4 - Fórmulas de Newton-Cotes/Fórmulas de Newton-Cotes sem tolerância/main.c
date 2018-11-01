//**************************************************************
//                                                             *
// Implementação de Métodos de Integração Numérica             *
// Métodos Numéricos II 2009.1                                 *
// Murilo Lima de Holanda                       Mat:0286740    *
//           				                       *
// Regra do Trapézio Fechada                                   *
// Regra do Trapézio Aberta                                    *
// Regra de Simpson 1/3 Fechada                                *
// Regra de Simpson 1/3 Aberta                                 *
// Regra de Simpson 3/8 Fechada                                *
// Regra de Simpson 3/8 Aberta                                 *
// Fórmula de Newton-Cotes  - 4º grau Fechada                  *
// Fórmula de Newton-Cotes  - 4º grau Aberta                   *
//					                       *
//**************************************************************

#include "polinomio.h"  //Arquivo com funções usadas para lidar com polinômios
#include "integracao.h" //Arquivo com as fórmulas de Newton-Cotes
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
  float a, b, delta, fa, fb, fc, TraF, TraA, Simp13F, Simp13A, Simp38F, Simp38A, NC4F, NC4A;
  float x2[2], fx2[2];//Vetores que guardam os pontos de divisão para 3 divisões
  float x3[3], fx3[3];//Vetores que guardam os pontos de divisão para 4 divisões
  float x4[4], fx4[4];//Vetores que guardam os pontos de divisão para 5 divisões
  float x5[5], fx5[5];//Vetores que guardam os pontos de divisão para 6 divisões
 
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

  delta = (b-a)/2;
  Divisao(a,b,3,x2);//Calcula 2 pontos de divisão 
  Divisao(a,b,4,x3);//Calcula 3 pontos de divisão
  Divisao(a,b,5,x4);//Calcula 4 pontos de divisão
  Divisao(a,b,6,x5);//Calcula 5 pontos de divisão 
  //Calcula todas as imagens usadas na integração
  fa=getfx(a, P);
  fc=getfx((b+a)/2, P);
  fb=getfx(b, P);
  for(i=0;i<2;i++)
     fx2[i]=getfx(x2[i], P);
  for(i=0;i<3;i++)
     fx3[i]=getfx(x3[i], P);
  for(i=0;i<4;i++)
     fx4[i]=getfx(x4[i], P);
  for(i=0;i<5;i++)
     fx5[i]=getfx(x5[i], P);
  //Calcula a integral pelos métodos
  TraF=     TraFechada(a, b, fa, fb);
  TraA=     TraAberta(a, b, fx2);
  Simp13F=  Simp13Fechada(delta, fa, fc, fb);
  Simp13A=  Simp13Aberta(a, b, fx3);
  Simp38F=  Simp38Fechada(a, b, fa, fb, fx2);
  Simp38A=  Simp38Aberta(a, b, fx4);
  NC4F=     NewtonCotes4F(a, b, fa, fb, fx3);
  NC4A=     NewtonCotes4A(a, b, fx5);
  //Imprime os resultados   
  system("clear");
  printf("Grau do Polinomio: %d\n",g);
  printf("Termos do Polinomio: ");
  ImprimeLista(P);
  printf("\n\na= %0.2f        f(a)= %0.2f",a,fa);
  printf("\nb= %0.2f        f(b)= %0.2f\n",b,fb);
  printf("\n\nIntegral por:\n\n");
  printf("Trapezio Fechada:                     %0.2f\n",TraF);
  printf("Trapezio Aberta:                      %0.2f\n",TraA);
  printf("Simpson 1/3 Fechada:                  %0.2f\n",Simp13F);
  printf("Simpson 1/3 Aberta:                	%0.2f\n",Simp13A);
  printf("Simpson 3/8 Fechada:      	         %0.2f\n",Simp38F);
  printf("Simpson 3/8 Aberta:                	%0.2f\n",Simp38A);
  printf("Newton-Cotes 4º Grau Fechada:      	%0.2f\n",NC4F);
  printf("Newton-Cotes 4º Grau Aberta:       	%0.2f\n",NC4A);
  printf("----------------------------------------------------");

  free(P);
  menu();
}

