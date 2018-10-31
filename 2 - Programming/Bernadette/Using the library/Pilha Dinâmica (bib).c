/*Alunos: Cícero Cavalcante de Araújo
          Murilo Lima de Holanda            */
//     PILHA DINÂMICA
#include "estru.h"
#include <stdio.h> 
#include <conio.h> 
#include <stdlib.h>
int c=0; //Variável que indica se a pilha foi criada ou não

int menu(Plhd *P) //Menu principal
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
          exit(1); //Saindo do menu
     break;
     case 1: 
          P=plhd_cria(); //Criando uma nova pilha
          c++;
          printf("Pilha criada!");
     break;
     case 2: 
          if (c==0)
             printf("A pilha nao foi criada!");
          else if (plhd_vaz(P))//Verificando se a pilha está vazia
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
             printf("Digite numero a ser adicionado\n");
             scanf("%d",&x);
             plhd_ins(x,P); //Inserindo um elemento na pilha
             printf("\nO numero %d foi adicionado na pilha!",x);
          }
     break;
     case 4: 
          if (c==0)
             printf("A pilha nao foi criada!");
          else
          {
             plhd_rem(P); //Removendo o último elemento da pilha
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
             plhd_busc(x,P); //Buscando um elemento na pilha
          }
     break;
     case 6: 
          if (c==0)
              printf("A pilha nao foi criada!");
          else if (plhd_vaz(P))
              printf("A pilha esta vazia!");
          else
          {
              printf("A pilha e:\n\n");
              plhd_print(P); //Imprimindo a pilha
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
   Plhd *p;//Definindo a pilha usada no programa
   menu(p); //Chamando o menu
}
