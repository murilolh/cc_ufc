#include "Listest.h"
#include "Listdin.h"
#include <stdio.h> 
#include <conio.h> 
#include <stdlib.h>

int c,j,t;

int menu(List_est l ,List_din L)
{
    int o;
    printf("**** MENU PRINCIPAL ***\n\n");
    printf("Digite a opcao desejada:\n");
    printf("1 - Utilizar lista estatica\n");
    printf("2 - Utilizar lista dinamica \n");
    printf("0 - Sair\n");
    scanf("%d",&o);
    system("cls");
    switch(o)
    {
        case 0:
             exit(1);
        break;
        case 1:
             menu_est(l);
        break;
        case 2:
             menu_din(L);
        break;
        default:
               system("cls");
               menu(l,L);
    }
    getch();
    system("cls");
    menu(l,L);          
}

int menu_est(List_est l, List_din L)
{    
     int q,n;
     printf("**** LISTA ESTATICA ***\n\n");
     printf("Digite a opcao desejada:\n");
     printf("1 - Criar uma nova lista\n");
     printf("2 - Verificar se a lista esta vazia\n");
     printf("3 - Inserir novo elemento\n");
     printf("4 - Imprimir a cabeca\n");
     printf("5 - Imprimir a cauda\n");
     printf("0 - Voltar para o Menu Principal\n");
     scanf("%d",&n);
     system("cls");
     switch(n)
     {
          case 0:
               l=Empty_est();
               c=j=0;
               menu(l,L);
          break;
          case 1:
               l=Empty_est();
               j=t=0;
               c++;
               printf("Lista criada");
          break;
          case 2:
          if (c==0)
             printf("A lista nao foi criada!");
          else if (isEmpty_est(l))
             printf("A lista esta vazia!");
          else 
             printf("A lista nao esta vazia!");
          break;
          case 3:
               if (c==0)
                  printf("A lista nao foi criada!");  
               else
               {             
                 printf("Digite o numero a ser adicionado:\n");
                 scanf("%d",&q);
                 l= cons_est((int*)q,l);
                 j++;
                 t++;
                 printf("\nO numero %d foi adicionado na lista!",q);
               }
          break;
          case 4:
               if (c==0)
                   printf("A lista nao foi criada!");
               else if (j==0)
                   printf("Nao existem elementos na cabeca!"); 
               else
               {
                   printf("A cabeca e:\n\n");
                   printf("%d",head_est(l));
               }
          break;
          case 5:
               if (c==0)
                   printf("A lista nao foi criada!");
               else if (j<=1)
                   printf("Nao existem elementos na cauda!"); 
               else
               {
                   printf("A cauda e:\n\n");
                   List_est Lis;
                   Lis=tail_est(l);
                   int i; 
                   for(i=0;i<=(t-2);i++)
                   {
                      printf("%d ",head_est(Lis));
                      Lis = tail_est(Lis);                      
                   }             
               }
          break;
          default:
               system("cls");
               menu_est(l,L); 
     }
     getch();
     system("cls");
     menu_est(l,L);
}

int menu_din(List_est l, List_din L)
{    
     int q,n;
     printf("**** LISTA DINAMICA ***\n\n");
     printf("Digite a opcao desejada:\n");
     printf("1 - Criar uma nova lista\n");
     printf("2 - Verificar se a lista esta vazia\n");
     printf("3 - Inserir novo elemento\n");
     printf("4 - Imprimir a cabeca\n");
     printf("5 - Imprimir a cauda\n");
     printf("0 - Voltar para o Menu Principal\n");
     scanf("%d",&n);
     system("cls");
     switch(n)
     {
          case 0:
               L=Empty_din();
               c=j=t=0;
               menu(l,L);
          break;
          case 1:
               L=Empty_din();
               j=t=0;
               c++;
               printf("Lista criada");
          break;
          case 2:
          if (c==0)
             printf("A lista nao foi criada!");
          else if (isEmpty_din(L))
             printf("A lista esta vazia!");
          else 
             printf("A lista nao esta vazia!");
          break;
          case 3:
               if (c==0)
                  printf("A lista nao foi criada!");  
               else
               {             
                 printf("Digite o numero a ser adicionado:\n");
                 scanf("%d",&q);
                 L= cons_din((int*)q,L);
                 j++;
                 t++;
                 printf("\nO numero %d foi adicionado na lista!",q);
               }
          break;
          case 4:
               if (c==0)
                   printf("A lista nao foi criada!");
               else if (j==0)
                   printf("Nao existem elementos na cabeca!"); 
               else
               {
                   printf("A cabeca e:\n\n");
                   printf("%d",head_din(L));
               }
          break;
          case 5:
               if (c==0)
                   printf("A lista nao foi criada!");
               else if (j<=1)
                   printf("Nao existem elementos na cauda!"); 
                else
               {
                   printf("A cauda e:\n\n");
                   List_din Lis;
                   Lis = tail_din(L);
                   int i;
                   for(i=0;i<=(t-2);i++)
                   {
                      printf("%d ",head_din(Lis));
                      Lis = tail_din(Lis);                      
                   }                  
               }
          break;
          default:
               system("cls");
               menu_din(l,L); 
     }
     getch();
     system("cls");
     menu_din(l,L);
}

int main()
{
    List_est l;
    List_din L;
    menu(l,L);
}
