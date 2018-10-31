/*Alunos: C�cero Cavalcante de Ara�jo
          Murilo Lima de Holanda            */
//     LISTA EST�TICA
#include "estru.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define max 100
int c=0;
int vf;

int menu(Lste L)//Menu inicial do programa
{
  int n;
  printf("Digite a opcao desejada:\n");
  printf("1- Criar uma nova lista\n");
  printf("2- Verificar se a lista esta vazia\n");
  printf("3- Inserir elemento no final da lista\n");
  printf("4- Inserir elemento na ordem\n");
  printf("5- Inserir em uma dada posicao da lista\n");
  printf("6- Remover o ultimo elemento da lista\n");
  printf("7- Remover o elemento de uma posicao da lista\n");
  printf("8- Imprimir a lista\n");
  printf("9- Dar a posicao de um elemento na lista\n");
  printf("0- Sair\n");
  scanf("%d",&n);
  system("cls");
  switch(n)
  {
     case 0:
          exit(1);//Sai do programa
     break;
     case 1:
          lste_cria(&L); //Criando a lista
          c++;
          printf("Lista criada!");
     break;
     case 2:
          if (c==0)
             printf("A lista nao foi criada!");
          else if (lste_vaz(&L))
             printf("A lista esta vazia!");
          else 
             printf("A lista nao esta vazia!");
     break;
     case 3:
          if (c==0)
              printf("A lista nao foi criada!");
          else
          {
              int x;
              printf("Digite o ultimo numero a ser adicionado\n");
              scanf("%d",&x);
              lste_insul(x ,&L);//Inserindo o n�mero digitado no fim da lista
              printf("\nO numero %d foi adicionado!",x);
          }
     break;
     case 4:
          if (c==0)
             printf("A lista nao foi criada!");
          else
          {
              int h;
              printf("Digite o numero a ser adicionado\n");
              scanf("%d",&h);
              lste_insul(h ,&L);//Adicionando o elemento � lista
              lste_ord(&L);//Ordenando a lista j� com o elemento adicionado
              printf("\nO numero %d foi adicionado na lista ordenada.",h); 
          }
     break;
     case 5:
          if (c==0)
              printf("A lista nao foi criada!");
          else
          {
              int num,po;
              printf("Digite a posicao do numero:\n");
              scanf("%d",&po);
              if (L.ultimo>po)//S� pede o n�mero se a posi��o j� estiver criada na lista
              {
                 printf("\nDigite o numero a ser adicionado na posicao:\n");
                 scanf("%d",&num);
                 lste_inpos(num,po,&L);//Inserindo o elemento na posi��o desejada
                 printf("\nO numero %d foi adicionado na posicao %d!",num,po);
              }
              else
                 printf("\nPosicao invalida!");
          }
     break;
     case 6:
          if (c==0)
             printf("A lista nao foi criada!");
          else if (L.ultimo>0)
          {
             printf("O ultimo elemento da lista foi removido!");
             lste_remul(&L);//Removendo o �ltimo elemento da lista, desde que ela n�o esteja vazia
          }
          else 
             printf("A lista esta vazia!");          
     break;
     case 7:
          if (c==0)
             printf("A lista nao foi criada!");
          else
          {
             int ps;
             printf("Digite a posicao do numero a ser removido:\n");
             scanf("%d",&ps);
             if (L.ultimo>ps)
             {
                lste_rempos(ps,&L);//Removendo o elemento da posi��o, desde que esta seja v�lida
                printf("\nO elemento que estava na posicao %d foi removido!",ps);
             }
             else
                printf("\nPosicao invalida!");
          }
     break;     
     case 8:
          if (c==0)
             printf("A lista nao foi criada!");
          else if (lste_vaz(&L))//N�o imprime a lista se ela n�o tiver elementos
             printf("A lista esta vazia!");
          else
          {
             printf("A lista e:\n\n");
             lste_print(&L);//Imprimindo a lista
          }
     break;
     case 9:
          if (c==0)
             printf("A lista nao foi criada!");
          {
             int z;
             printf("Digite o numero a ser verificado:\n");
             scanf("%d",&z);
             lste_busc(z, &L);//Buscando o elemento   
          }
     break;
     default:
          system("cls");
          menu(L);   
  }
  getch();
  system("cls");
  menu(L);
}

int main()
{
  Lste L;//Definindo a lista usada no programa
  menu(L);
}

