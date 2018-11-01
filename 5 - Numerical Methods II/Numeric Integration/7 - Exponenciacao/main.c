//**************************************************************
//                                                             *
// Implementação de Métodos de Integração Numérica             *
// Métodos Numéricos II 2009.1                                 *
// Murilo Lima de Holanda                          Mat:0286740 *
//                                                             *
// Exponenciação simples e dupla                               *
//	                                                       *
//**************************************************************

#include "exponenciacao.h" //Arquivo com funções que calculam integrais através de Gauss-Hermite, Laguerre e Chebyshev
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

void menu();
void metodo(int n, int xc, int g, float to, float alpha[],TipoLista *P);
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

//Função de escolha do método
void metodo(int n, float xc, int g, float to, float alpha[], TipoLista *P)
{  
  int m;
  float INT1, INT2;
  system("clear");
  printf("Digite o metodo de integracao desejado:\n");
  printf("1- Exponenciacao simples\n");
  printf("2- Exponenciacao dupla\n");
  scanf("%d",&m);
  if ((m>0) && (m<3)) 
  {
     system("clear");
     printf("Grau da Funcao: %d\n",g);
     printf("Termos da Funcao: ");
     ImprimeLista(P);
     switch(m)
     {
        case 1:
            INT2=ExpSimples(n,xc,alpha,P);             
            do
            {
               INT1=INT2;
               xc = xc + 0.5;
               INT2=ExpSimples(n,xc,alpha,P);
            }
            while(fabs(INT2-INT1)>to);            
  	    printf("\n\nIntervalo:   -%0.1f    a    +%0.1f\n",xc,xc); 
            printf("\nIntegral por Exponenciacao simples com %d cortes:\n\n",n);
        break;
        case 2:
            INT2=ExpDupla(n,xc,alpha,P);             
            do
            {
               INT1=INT2;
               xc = xc + 0.5;
               INT2=ExpDupla(n,xc,alpha,P);
            }
            while(fabs(INT2-INT1)>to);
            printf("\n\nIntervalo:   -%0.1f    a    +%0.1f\n",xc,xc); 
            printf("\nIntegral por Exponenciacao dupla com %d cortes:\n\n",n);
        break;       
     }
     printf("   %0.2f\n\n",INT2);
     printf("----------------------------------------------------");
  }
  else
     metodo(n,xc,g,to,alpha,P);  
}

int main()
{
  TipoLista *P;//Lista usada para guardar o Polinômio
  int g,i,t,n,m,c;
  float to,xc;  
  
  system("clear");
  printf("Digite o grau da funcao a ser integrada:\n");
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
  system("clear");
  printf("Digite o numero de particoes:\n");
  scanf("%d",&n);
  
  //Valor padrão inicial do ponto de corte
  xc = 5;
  
  //Recebe a tolerância
  system("clear");
  printf("Digite quantas casas decimais de precisao:\n");
  scanf("%d",&c);

  //A tolerância é um float na forma 10^(-c)
  to=1;
  for(i=0;i<c;i++)
     to=to/10;  
  
  //Calcula todos os n+1 alphas da parametrização
  float alpha[n+1];  
  getalpha(n,alpha);
        
  //Calcula e imprime os resultados
  metodo(n,xc,g,to,alpha,P);      
  
  free(P);
  menu();
}

