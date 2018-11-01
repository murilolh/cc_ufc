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

#include "integracao.h" //Arquivo com as fórmulas de Newton-Cotes
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

#define MAX 100

void menu();
float escolha(float a, float b, float to, TipoLista *P);
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

//Menu de escolha e cálculo da integral por um dos métodos
float escolha(float a, float b, float to, TipoLista *P)
{
  int o,d,i;
  float R1,R2;
  float x[MAX];
  R1=0;
  d=1;
  system("clear");
  printf("Digite a regra de integracao desejada:\n");
  printf("1- Regra do Trapezio Fechada\n");
  printf("2- Regra do Trapezio Aberta\n");
  printf("3- Simpson 1/3 Fechada\n");
  printf("4- Simpson 1/3 Aberta\n");
  printf("5- Simpson 3/8 Fechada\n");
  printf("6- Simpson 3/8 Aberta\n");
  printf("7- Newton-Cotes de grau 4 Fechada\n");
  printf("8- Newton-Cotes de grau 4 Aberta\n");
  scanf("%d",&o);
  system("clear");
  switch(o)
  {
     case 1:
         R2 = TraFechada(a,b,P);
         while(fabs(R1-R2)>to)
         {
            d++; 
            R1=R2;
            Divisao(a,b,d,x);
            R2= TraFechada(a,x[0],P);
            for(i=0;i<d-2;i++)
              R2= R2 + TraFechada(x[i],x[i+1],P);
            R2= R2 + TraFechada(x[d-1],b,P);            
         }
         return R2;                    
     break;
     case 2:
         R2 = TraAberta(a,b,P);
         while(fabs(R1-R2)>to)
         { 
            d++; 
            R1=R2;
            Divisao(a,b,d,x);
            R2= TraAberta(a,x[0],P);
            for(i=0;i<d-2;i++)
              R2= R2 + TraAberta(x[i],x[i+1],P);
            R2= R2 + TraAberta(x[d-1],b,P);            
         }
         return R2;
     break;
     case 3:
         R2 = Simp13Fechada(a,b,P);
         while(fabs(R1-R2)>to)
         { 
            d++; 
            R1=R2;
            Divisao(a,b,d,x);
            R2= Simp13Fechada(a,x[0],P);
            for(i=0;i<d-2;i++)
              R2= R2 + Simp13Fechada(x[i],x[i+1],P);
            R2= R2 + Simp13Fechada(x[d-1],b,P);            
         }
         return R2;
     break;
     case 4:
	 R2 = Simp13Aberta(a,b,P);
         while(fabs(R1-R2)>to)
         { 
            d++; 
            R1=R2;
            Divisao(a,b,d,x);
            R2= Simp13Aberta(a,x[0],P);
            for(i=0;i<d-2;i++)
              R2= R2 + Simp13Aberta(x[i],x[i+1],P);
            R2= R2 + Simp13Aberta(x[d-1],b,P);            
         }
         return R2;
     break;
     case 5:
         R2 = Simp38Fechada(a,b,P);
         while(fabs(R1-R2)>to)
         { 
            d++; 
            R1=R2;
            Divisao(a,b,d,x);
            R2= Simp38Fechada(a,x[0],P);
            for(i=0;i<d-2;i++)
              R2= R2 + Simp38Fechada(x[i],x[i+1],P);
            R2= R2 + Simp38Fechada(x[d-1],b,P);            
         }
         return R2;
     break;
     case 6:
	 R2 = Simp38Aberta(a,b,P);
         while(fabs(R1-R2)>to)
         { 
            d++; 
            R1=R2;
            Divisao(a,b,d,x);
            R2= Simp38Aberta(a,x[0],P);
            for(i=0;i<d-2;i++)
              R2= R2 + Simp38Aberta(x[i],x[i+1],P);
            R2= R2 + Simp38Aberta(x[d-1],b,P);            
         }
         return R2;
     break;
     case 7:
         R2 = NewtonCotes4F(a,b,P);
         while(fabs(R1-R2)>to)
         { 
            d++; 
            R1=R2;
            Divisao(a,b,d,x);
            R2= NewtonCotes4F(a,x[0],P);
            for(i=0;i<d-2;i++)
              R2= R2 + NewtonCotes4F(x[i],x[i+1],P);
            R2= R2 + NewtonCotes4F(x[d-1],b,P);            
         }
         return R2;
     break;
     case 8:
         R2 = NewtonCotes4A(a,b,P);
         while(fabs(R1-R2)>to)
         { 
            d++; 
            R1=R2;
            Divisao(a,b,d,x);
            R2= NewtonCotes4A(a,x[0],P);
            for(i=0;i<d-2;i++)
              R2= R2 + NewtonCotes4A(x[i],x[i+1],P);
            R2= R2 + NewtonCotes4A(x[d-1],b,P);            
         }
         return R2;
     break;          
     default:
          system("clear");
          escolha(a,b,to,P);   
  }
}

int main()
{
  TipoLista *P;//Lista usada para guardar o Polinômio
  int g,i,t,c;
  float a, b, to, INT;
  
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

  //Recebe a tolerância
  system("clear");
  printf("Digite quantas casas decimais de precisao:\n");
  scanf("%d",&c);

  //A tolerância é um float na forma 10^(-c)
  to=1;
  for(i=0;i<c;i++)
     to=to/10;   

  INT = escolha(a,b,to,P);
  
  //Imprime os resultados   
  system("clear");
  printf("Grau do Polinomio: %d\n",g);
  printf("Termos do Polinomio: ");
  ImprimeLista(P);
  printf("\n\na= %0.2f",a);
  printf("\nb= %0.2f",b);
  printf("\n\nIntegral pelo metodo escolhido:\n\n%f\n\n",INT);
  printf("----------------------------------------------------");

  free(P);
  menu();
}
