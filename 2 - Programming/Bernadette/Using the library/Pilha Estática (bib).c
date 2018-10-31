/*Alunos: Cícero Cavalcante de Araújo
          Murilo Lima de Holanda            */
//     PILHA ESTÀTICA
#include "estru.h"
#include <stdio.h> 
#include <conio.h> 
#include <stdlib.h>
#define MaxTam 100
int c=0; //Variável que indica se a pilha foi criada

int menu(Plhe *P) //Menu principal do programa
{
  int n;
  printf("Digite a opcao desejada:\n");
  printf("1- Criar uma nova pilha\n");
  printf("2- Verificar se a pilha esta vazia\n");
  printf("3- Inserir elemento na pilha\n");
  printf("4- Remover elemento da pilha\n");
  printf("5- Dar a posicao de um elemento na pilha\n");
  printf("6- Imprimir a pilha\n");
  printf("0- Sair\n");
  scanf("%d",&n);
  system("cls");
  switch(n)
  {
     case 0:
          exit(1); //Sai do menu
     break;
     case 1: 
          P=plhe_cria(); //Criando a pilha
          c++;
          printf("Pilha criada!");
     break;
     case 2: 
          if (c==0)
            printf("A pilha nao foi criada!");
          else if (plhe_vaz(P)) //Verificando se a pilha está vazia
            printf("A pilha esta vazia!");
          else 
            printf("A pilha nao esta vazia!");
     break;
     case 3: 
          if (c==0)
            printf("A pilha nao foi criada!");
          else
          {
             int x;
             printf("Digite numero a ser adicionado na pilha\n");
             scanf("%d",&x);
             plhe_ins(P,x); //Inserindo um elemento na pilha
             printf("\nO numero %d foi adicionado na pilha!",x);
          }
     break;
     case 4: 
          if (c==0)
             printf("A pilha nao foi criada!");
          else
          {
             plhe_rem(P); //Removendo o último elemento da pilha
             printf("O elemento do topo da pilha foi removido!\n");            
          }
     break;
     case 5: 
          if (c==0) 
             printf("A pilha nao foi criada!");
          else
          {
             int x; 
             printf("Digite o numero a ser buscado:\n");
             scanf("%d",&x);
             plhe_busc(x,P); //Buscando um elemento na pilha
          }
     break;
     case 6: 
          if (c==0)
             printf("A pilha nao foi criada!");
          else if (plhe_vaz(P))
             printf("A pilha esta vazia!");
          else
          {
             printf("A pilha e:\n\n");
             plhe_print(P); //Imprimindo os elementos da pilha
          }
     break;
     default: 
          system("cls");
          menu(P);   
  }
  getch();
  system("cls");
  menu(P);
}        
int main() 
{
   Plhe *p; //Definindo a pilha usada no programa
   menu(p); //Chamando o menu
}
