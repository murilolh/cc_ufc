//**************************************************************
//                                                             *
// Implementação de Métodos de Integração Numérica             *
// Métodos Numéricos II 2009.1                                 *
// Murilo Lima de Holanda                       Mat:0286740    *
//                                                             *
// Regra do Trapézio Fechada Simples                           *
// Regra do Trapézio Fechada Estendida                         *
// Regra do Trapézio Aberta Simples                            *
// Regra do Trapézio Aberta Estendida                          *
//					                       *
//**************************************************************

#include "polinomio.h"  //Arquivo com funções usadas para lidar com polinômios
#include "trapezio.h" //Arquivo com funções que calculam integrais através da Regra do Trapézio
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
  float a, b, f1, f2, TraFS, TraFE, TraAS, TraAE;
 
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
  //Recebe o número de divisões da função no intervalo
  system("clear");
  printf("Digite o numero de divisoes: (min=1)\n");
  scanf("%d",&n);  
  
  float xe[n-1], fxe[n-1];//Vetores que guardam os pontos de divisão da regra Fechada Estendida
  float xa[2],fxa[2];//Vetores que guardam os pontos de divisão da regra Aberta simples
  float xae[(n*3)-1], fxae[(n*3)-1];//Vetores que guardam os pontos de divisão da regra aberta estendida
  Divisao(a,b,n,xe);//Calcula os pontos de divisão do polinômio para a Regra Fechada Estendida
  Divisao(a,b,3,xa);//Calcula os 2 pontos de divisão do polinômio para a Regra Aberta Simples
  Divisao(a,b,n*3,xae);//Calcula os pontos de divisão do polinômio para a Regra Aberta Estendida
  //Calcula todas as imagens usadas na integração
  f1=getfx(a, P);
  f2=getfx(b, P);
  fxa[0]=getfx(xa[0], P);
  fxa[1]=getfx(xa[1], P);
  for(i=0;i<n-1;i++)
     fxe[i]=getfx(xe[i], P);
  for(i=0;i<(3*n)-1;i++)
     fxae[i]=getfx(xae[i], P);
  //Calcula a integral pelos métodos
  TraFS=TraFechadaSimples(a,b,f1,f2);
  TraFE=TraFechadaEstendida(a,b,n,f1,f2,fxe);
  TraAS=TraAbertaSimples(a,b,fxa);  
  TraAE=TraAbertaEstendida(a,b,n,xae,fxae);
  //Imprime os resultados   
  system("clear");
  printf("Grau do Polinomio: %d\n",g);
  printf("Termos do Polinomio: ");
  ImprimeLista(P);
  printf("\n\na= %0.2f        f(a)= %0.2f",a,f1);
  printf("\nb= %0.2f        f(b)= %0.2f\n",b,f2);
  printf("\n\nIntegral por:\n\n");
  printf("Trapezio Fechada Simples:     %0.2f\n\n",TraFS);
  printf("Trapezio Fechada Estendida:   %0.2f\n\n",TraFE);
  printf("Trapezio Aberta Simples:      %0.2f\n\n",TraAS);
  printf("Trapezio Aberta Estendida:    %0.2f\n\n",TraAE);
  printf("----------------------------------------------------");

  free(P);
  menu();
}

