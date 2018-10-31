/*Alunos: Cícero Cavalcante de Araújo
          Murilo Lima de Holanda            */
//     LISTA DINÂMICA ORDENADA
#include "estru.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
int c=0;  //Variável incrementada quando a lista é criada

int menu(Lstd *Lista)//Menu inicial do programa
{
  int n;//Variável para a opção do menu
  printf("Digite a opcao desejada:\n");
  printf("1- Criar uma nova lista\n");
  printf("2- Verificar se a lista esta vazia\n");
  printf("3- Inserir elemento\n");
  printf("4- Remover elemento especifico da lista\n");
  printf("5- Dar a posicao de um elemento na lista\n");
  printf("6- Imprimir a lista\n");
  printf("0- Sair\n");
  scanf("%d",&n);
  system("cls");
  switch(n)
  {
     case 0:
          exit(1);//Sai do programa
     break;
     case 1:
          Lista=lstd_cria();//Criando a lista
          c++;//Incrementando a variável que desbloqueia as outras funções
          printf("Lista criada!");
     break;
     case 2:
          if (c==0)
            printf("A lista nao foi criada!");
          else if (lstd_vaz(Lista))//Verificando se a lista está vazia
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
            printf("Digite numero a ser adicionado\n");
            scanf("%d",&x);
            lstd_ins(x,Lista);//Inserindo o número digitado na lista 
            printf("\nO numero %d foi adicionado na lista!",x);
          }
     break;
     case 4:
          if (c==0)
            printf("A lista nao foi criada!");
          else
          {
            int x;
            printf("Digite o conteudo a ser removido da lista\n");
            scanf("%d",&x);
            lstd_remcom(x,Lista);//Removendo elemento digitado na lista
          }
     break;
     case 5:
          if (c==0)
             printf("A lista nao foi criada!");
          else
            {
            int x;
            printf("Digite o numero a ser verificado:\n");
            scanf("%d",&x);
            lstd_busc(x,Lista);//Verificando se o elemento digitado está na lista
            }
     break;
     case 6:
          if (c==0)
             printf("A lista nao foi criada!");
          else if (lstd_vaz(Lista))
              printf("A lista esta vazia!");
          else
          {
          printf("A lista e:\n\n");
          lstd_print(Lista);//Imprimindo a lista
          }
     break;
     default:
          system("cls");
          menu(Lista);   
  }
  getch();
  system("cls");
  menu(Lista);
}

int main()
{
   Lstd *L;//Definindo a lista usada no programa
   menu(L); //Chamando o menu principal
}
