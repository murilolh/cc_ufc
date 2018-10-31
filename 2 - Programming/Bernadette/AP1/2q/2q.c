/*Alunos: C�cero Cavalcante de Ara�jo
          Murilo Lima de Holanda            */
//     1� AP - QUEST�O 02
#include <stdio.h>
#include <stdlib.h>
#define MaxTam 10

typedef int Placa;
typedef int Movi;
typedef struct
{
   Placa placa[MaxTam];
   Movi mov[MaxTam];
   int frente, tras;
} Estac;

int u=0; //Vari�vel icrementada quando o estacionamento � criado
int pest; //Vari�vel para a posi��o dos carros no estacionamento
int pesp; //Vari�vel para a posi��o dos carros na espera
int tamest; //Vari�vel para o n�mero de carros no estacionamento
int tamesp=0; //Vari�vel para o n�mero de carros na espera
int Esp[10]; //Vetor para espera
int a=0; //�ndice para o vetor da espera

//Fun��o que cria o estacionamento
void CriaEst(Estac *Est)
{
   Est->frente=Est->tras=0;
   u=1;
   tamest=0;
}

//Fun��o que cria um estacionamento auxiliar
void CriaAux(Estac *Aux)
{
   Aux->frente=Aux->tras=0;
}

//Fun��o que coloca um carro no estacionamento
void car_estac(Placa x, Estac *Est)
{
   if(u==0)
      CriaEst(Est);
   if(u==1)
   {
      if(tamest==MaxTam)
      {
         Esp[a]=x;
         printf("\n\nO estacionamento esta cheio!");
         printf("\nO carro foi colocado na %da posicao da espera!", a+1);
         tamesp++;
         a++;
      }
      else
      {
         if(tamest==0)
         {
            Est->placa[Est->tras]=x;
            Est->mov[Est->tras]=0;
            tamest++;
            printf("\n\nO carro de placa %d foi estacionado!", x);
         }
         else
         {
            Est->tras++;
            Est->placa[Est->tras]=x;
            Est->mov[Est->tras]=0;
            tamest++;
            printf("\n\nO carro de placa %d foi estacionado!", x);
         }
      }
   }
}

//Fun��o que remove um carro do estacionamento
void car_rem(Placa x, Estac* Est, Estac *Aux)
{
   int j=pest+1;
   int i=0;
   int y;
   if(u==0)
      CriaEst(Est);
   if(u==1)
   {
      if(tamest==0)
         printf("\nEstacionamento vazio!\n");
      else
      {
         CriaAux(Aux);
         if(tamest==1)
           y=Est->mov[pest]+1;
         else
         {
           if(pest!=Est->tras)
           {
              for(i=0;i<Est->tras-pest;i++)
              {
                 Aux->placa[i]=Est->placa[j];
                 Aux->mov[i]=Est->mov[j];
                 y=Est->mov[pest]+1;
                 j++;
              }
              Aux->tras=Est->tras - pest - 1;
           }
           if(pest!=0)
           {
              j=0;
              for(i=Est->tras-pest;i<=Est->tras-1;i++)
              {
                 Aux->placa[i]=Est->placa[j];
                 Aux->mov[i]=Est->mov[j];
                 y=Est->mov[pest]+1;
                 j++;
              }
              Aux->tras=Est->tras-1;
           }
           for(i=0;i<=Aux->tras;i++)
           {
              Est->placa[i]=Aux->placa[i];
              Est->mov[i]=Aux->mov[i];
              Est->mov[i]=Est->mov[i]+1;
           }
           Est->tras=Aux->tras;
         }
         tamest--;
         printf("\nO carro de placa %d saiu. ", x);
         printf("Movimentos no estacionamento: %d\n", y);
         printf("\nTotal de vagas disponiveis: %d\n",MaxTam - tamest);
      }
      if(tamest == MaxTam-1)
      {
        if(tamesp>0)
        {
           Est->placa[Est->tras+1]=Esp[0];
           Est->mov[Est->tras+1]=0;
           Est->tras++;
           printf("\n\nO carro de placa %d, que estava na espera, foi estacionado!", Esp[0]);
           tamest++;
           a--;
           for(i=0;i<tamesp;i++)
              Esp[i]=Esp[i+1];
           tamesp--;
        }
      }
      free(Aux);
   }
}

//Fun��o que busca um carro no estacionamento
int est_busc(int x,Estac *Est)
{
   int i;
   if(tamest!=0)
     for(i=Est->frente;i<=Est->tras;i++)
       if(Est->placa[i]==x)
       {
          pest=i-Est->frente;
          return 1;
       }
   return (0);
}

//Fun��o que busca um carro na espera
int esp_busc(int x)
{
   int i;
   if(tamesp!=0)
     for(i=0;i<tamesp;i++)
       if(Esp[i]==x)
       {
         pesp=i;
         return 1;
       }
   return (0);
}

//Fun��o que retira um carro da espera
void esp_sai(int x)
{
   int i;
   for(i=pesp;i<tamesp;i++)
      Esp[i]=Esp[i+1];
   tamesp--;
   a--;
}

//Fun��o que imprime as listas de carros de estacionamento e da espera
void car_print(Estac *Est)
{
   int i;
   {
     if(tamest==0)//Se n�o houverem carros no estacionamento
       printf("Estacionamento vazio!");
     else
     {
       printf("CARROS NO ESTACIONAMENTO: %d \n\n", tamest);
       for(i=Est->frente;i<=Est->tras;i++)//Percorre o estacionamento imprimindo as informa��es
          printf("Placa: %d   Posicao: %do   Movimentos: %d\n\n",Est->placa[i], i+1, Est->mov[i]);
       printf("________________________________________________\n");
       printf("\nCARROS ESPERANDO POR VAGA: %d \n\n", tamesp);
       for(i=0;i<tamesp;i++)//Percorre a espera imprimindo as informa��es
          printf("Placa: %d   Posicao: %do   Movimentos: 0\n\n",Esp[i],i+1);
       printf("________________________________________________\n");
     }
   }
}

//Fun��o para o menu princinpal do programa
int menu(Estac estac, Estac aux)
{
  int o,b,q;
  printf("Digite a opcao desejada:\n");
  printf("\n1- Estacionar um carro\n");
  printf("2- Remover um carro\n");
  printf("3- Ver as listas de carros estacionados e em espera\n");
  printf("\n0- Sair\n");
  scanf("%d",&o);
  system("clear");
  switch(o)
  {
    case 0:
       exit(1);//Sai do programa
    break;
    case 1:
       printf("Digite a placa do carro a ser estacionado:\n");
       scanf("%d",&b);
       if((est_busc(b,&estac)))//Verifica se o carro esta no estacionamento
          printf("\nO carro de placa %d ja esta no estacionamento!",b);
       else if((esp_busc(b)))//Verifica se o carro esta na espera
          printf("\nO carro de placa %d ja esta na espera!",b);
       else
          car_estac(b,&estac);//Estaciona o carro
    break;
    case 2:
        printf("Digite a placa do carro a ser tirado do estacionamento:\n");
        scanf("%d",&q);
        if((est_busc(q,&estac)))//Verifica se o carro esta no estacionamento
           car_rem(q,&estac, &aux);
        else if((esp_busc(q)))//Verifica se o carro esta na espera
        {
           esp_sai(q);//Retira o carro da espera
           printf("\nO carro de placa %d saiu da espera!", q);
        }
        else//Caso o carro n�o esteja no estacionamento ou na espera
           printf("\nO Carro de placa %d esta no estacionamento!",q);
    break;
    case 3:
        car_print(&estac); //Imprime as listas dos carros estacionados e na espera
    break;
    default:
        system("clear");
        menu(estac, aux);
  }
  system("clear");
  menu(estac, aux);
}

int main()
{
  Estac estac, aux;
  menu(estac, aux);
}
