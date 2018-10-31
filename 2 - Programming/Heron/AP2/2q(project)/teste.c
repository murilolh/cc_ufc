#include <stdio.h> 
#include <conio.h> 
#include <stdlib.h>

typedef struct Node_List
{
        void *info;
        struct Node_List *Next;
        int count;
}NodeList;

typedef struct 
{
       NodeList *FirstNode;
}HeadNode;

typedef HeadNode List;

List Empty()
{
     HeadNode l;
     l.FirstNode=NULL;
     return (l);
}

int isEmpty(List l)
{
     return(l.FirstNode==NULL);
}

List cons(void *info, List l)
{
     NodeList *Aux = (NodeList*)malloc(sizeof(NodeList));
     HeadNode li;
     li.FirstNode->count=0;
     Aux->info = info;
     Aux->Next = l.FirstNode;
     li.FirstNode = Aux;
     return(li);              
}

void *head(List l)
{
     return(l.FirstNode->info);
}

List tail(List l)
{
     List Lis;
     Lis=Empty();
     NodeList *Aux = (NodeList*)malloc(sizeof(NodeList));
     Aux = l.FirstNode->Next;
     Lis.FirstNode = Aux;
     return(Lis);     
}

List remover(int k, List l)
{
     
}

int c,j,t;

int menu(List L)
{    
     int q,n;
     printf("**** LISTA DINAMICA ***\n\n");
     printf("Digite a opcao desejada:\n");
     printf("1 - Criar uma nova lista\n");
     printf("2 - Verificar se a lista esta vazia\n");
     printf("3 - Inserir novo elemento\n");
     printf("4 - Imprimir a cabeca\n");
     printf("5 - Imprimir a cauda\n");
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
                 L= cons((int*)q,L);
                 L.FirstNode->Next++;
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
                   printf("%d",head(L));
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
