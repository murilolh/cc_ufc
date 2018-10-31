/*Alunos: Cícero Cavalcante de Araújo
          Murilo Lima de Holanda            */
//     FILA DINÂMICA
#include "estru.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
int c=0; //Variável que indica se a fila já foi criada ou não 

int menu(Fild *Fila) //Menu principal
{
  int n;
  printf("Digite a opcao desejada:\n");
  printf("1- Criar uma nova fila\n");
  printf("2- Verificar se a fila esta vazia\n");
  printf("3- Inserir elemento no final da fila\n");
  printf("4- Remover o primeiro elemento da fila\n");
  printf("5- Buscar um elemento na lista\n");
  printf("6- Imprimir a fila\n");
  printf("0- Sair\n");
  scanf("%d",&n);
  system("cls");
  switch(n)
  {
     case 0:
          exit(1); //Saindo do programa
     break;
     case 1:
          Fila=fild_cria(); //Criando uma nova fila
          c++;
          printf("Fila criada!");
     break;
     case 2:
          if (c==0)
            printf("A fila nao foi criada!");
          else if (fild_vaz(Fila)) //Verificando se a fila está vazia
            printf("A fila esta vazia!");
          else 
            printf("A fila nao esta vazia!");
          break;
     case 3:
          if (c==0)
            printf("A fila nao foi criada!");
          else
          {
            int x;
            printf("Digite numero a ser adicionado\n");
            scanf("%d",&x);
            fild_ins(x,Fila); //Inserindo um elemento na fila
            printf("\nO numero %d foi adicionado na fila!",x);
          }
     break;
     case 4:
          if (c==0)
            printf("A fila nao foi criada!");
          else
          {
            printf("O primeiro elemento da fila foi removido!\n");
            fild_rem(Fila); //Removendo o primeiro elemento da fila
          }
     break;
     case 5:
          if (c==0)
             printf("A fila nao foi criada!");
          else
            {
            int x;
            printf("Digite o numero a ser buscado:\n");
            scanf("%d",&x);
            fild_busc(x,Fila); //Buscando um elemento na fila
            }
     break;
     case 6:
          if (c==0)
             printf("A fila nao foi criada!");
          else if (fild_vaz(Fila))
             printf("A fila esta vazia!");
          else
          {
             printf("A fila e:\n\n");
             fild_print(Fila);//Imprimindo a fila
          }
     break;
     default:
          system("cls");
          menu(Fila);   
  }
  getch();
  system("cls");
  menu(Fila);
}

int main()
{
   Fild *F;//Definindo a fila usada no programa
   menu(F);  //Chamando o menu
}
