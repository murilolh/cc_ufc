//**************************************************************
//                                                             *
// Implementação de Métodos de Integração Numérica             *
// Métodos Numéricos II 2009.1                                 *
// Murilo Lima de Holanda                       Mat:0286740    *
//                                                             *
// Regra de Simpson 1/3 Fechada Simples                        * 
// Regra de Simpson 1/3 Fechada Estendida                      *
// Regra de Simpson 1/3 Aberta Simples                         *
// Regra de Simpson 1/3 Aberta Estendida                       *
//							       *
//**************************************************************

#include "polinomio.h"  //Arquivo com funções usadas para lidar com polinômios
#include "simpson13.h" //Arquivo com funções que calculam integrais através da regra de Simpson 1/3
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
  float a, b, delta, f1, f2, f3, SimpFS, SimpFE, SimpAS, SimpAE;
 
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
  printf("Digite o numero de divisoes: (min=2)\n");
  scanf("%d",&n);  
  
  delta=(b-a)/2;//Calcula o delta usado na integração
  float xe[n-1], fxe[n-1];//Vetores que guardam os pontos de divisão da regra Fechada Estendida
  float xa[3],fxa[3];//Vetores que guardam os ponto de divisão da regra Aberta simples
  float xae[(n*4)-1], fxae[(n*4)-1];//Vetores que guardam os pontos de divisão da regra aberta estendida
  Divisao(a,b,n,xe);//Calcula os pontos de divisão do polinômio para a Regra Fechada Estendida
  Divisao(a,b,4,xa);//Calcula os 3 pontos de divisão do polinômio para a Regra Aberta Simples
  Divisao(a,b,n*4,xae);//Calcula os pontos de divisão do polinômio para a Regra Aberta Estendida
  //Calcula todas as imagens usadas na integração
  f1=getfx(a, P);
  f2=getfx((b+a)/2, P);
  f3=getfx(b, P);
  fxa[0]=getfx(xa[0], P);
  fxa[1]=getfx(xa[1], P);
  fxa[2]=getfx(xa[2], P); 
  for(i=0;i<n-1;i++)
     fxe[i]=getfx(xe[i], P);
  for(i=0;i<(4*n)-1;i++)
     fxae[i]=getfx(xae[i], P);
  //Calcula a integral pelos métodos
  SimpFS=SimpFechadaSimples(delta,f1,f2,f3);
  SimpFE=SimpFechadaEstendida(a,b,n,f1,f3,fxe);
  SimpAS=SimpAbertaSimples(a,b,fxa);
  SimpAE=SimpAbertaEstendida(a,b,n,xae,fxae);
  //Imprime os resultados   
  system("clear");
  printf("Grau do Polinomio: %d\n",g);
  printf("Termos do Polinomio: ");
  ImprimeLista(P);
  printf("\n\na= %0.2f        f(a)= %0.2f",a,f1);
  printf("\n(b+a)/2= %0.2f    f((b+a)/2)= %0.2f ",delta,f2);
  printf("\nb= %0.2f        f(b)= %0.2f\n",b,f3);  
  printf("\n\nIntegral por:\n\n");
  printf("Simpson 1/3 Fechada Simples:         %0.2f\n\n",SimpFS);
  printf("Simpson 1/3 Fechada Estendida:       %0.2f\n\n",SimpFE);
  printf("Simpson 1/3 Aberta Simples:          %0.2f\n\n",SimpAS);
  printf("Simpson 1/3 Aberta Estendida:        %0.2f\n\n",SimpAE);
  printf("----------------------------------------------------");

  free(P);
  menu();
}

