#include "List.h"

int c,j,t;

typedef struct {
          
          int key;                                                                                                                                                                                                                     
          void* info;
}Info;

int menu(List L)
{    
     int n,ch;
     int k=0;
     Info* q;
     printf("**** LISTA DINAMICA ***\n\n");
     printf("Digite a opcao desejada:\n");
     printf("1 - Criar uma nova lista\n");
     printf("2 - Verificar se a lista esta vazia\n");
     printf("3 - Inserir novo elemento\n");
     printf("4 - Remover um elemento\n");
     printf("5 - Imprimir a cabeca\n");
     printf("6 - Imprimir a cauda\n");
     printf("0 - Sair\n");
     scanf("%d",&n);
     system("cls");
     switch(n)
     {
          case 0:
               exit(1);
          break;
          case 1:
               L=Empty();
               j=t=0;
               c++;
               printf("Lista criada");
          break;
          case 2:
          if (c==0)
             printf("A lista nao foi criada!");
          else if (isEmpty(L))
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
                 k++;
                 q->key=k;
                 L= cons((Info*)q,L);
                 j++;
                 t++;                 
                 printf("\nO numero %d foi adicionado na lista!",q);
               }
          break;
          case 4:
               if (c==0)
                  printf("A lista nao foi criada!"); 
               else if (isEmpty(L))
                  printf("A lista esta vazia!"); 
               else
               {   
                  printf("Digite a chave do elemento a ser removido:\n");
                  scanf("%d",ch);
                  if (ch>k)
                     printf("\nNão existe um elemento na lista com a chave %d!",ch);
                  else
                     Remover(ch,L);                                                                                                             
               }
          break;
          case 5:
               if (c==0)
                   printf("A lista nao foi criada!");
               else if (j==0)
                   printf("Nao existem elementos na cabeca!"); 
               else
               {
                   printf("A cabeca e:\n\n");
                   printf("%d",head(L));
               }
          break;
          case 6:
               if (c==0)
                   printf("A lista nao foi criada!");
               else if (j<=1)
                   printf("Nao existem elementos na cauda!"); 
                else
               {
                   printf("A cauda e:\n\n");
                   List Lis;
                   Lis = tail(L);
                   int i;
                   for(i=0;i<=(t-2);i++)
                   {
                      printf("%d ",head(Lis));
                      Lis = tail(Lis);                      
                   }                  
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
    List L;
    menu(L);
}
