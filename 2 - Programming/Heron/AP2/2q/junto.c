#include <stdio.h> 
#include <conio.h> 
#include <stdlib.h>

int c,j,t,k;

typedef struct Node_List
{
        void *info;
        int count;
        struct Node_List *Next;
}NodeList;

typedef struct HeadNode
{
      struct Node_List *FirstNode;
}HeadNode;

typedef struct HeadNode *List;

typedef struct 
{
     int key;                                                                                                                                                                                                                     
     void* info;
}Info;

List Empty()
{
     HeadNode *l = (HeadNode*)malloc(sizeof(HeadNode));
     l->FirstNode = NULL;
     return(l);
}

int isEmpty(List l)
{
     return(l->FirstNode==NULL);
}

List cons(void *info, List l)
{
     NodeList *Aux = (NodeList*)malloc(sizeof(NodeList));
     Aux->count=1;
     HeadNode *li = (HeadNode*)malloc(sizeof(HeadNode));
     Aux->info = info;
     Aux->Next = l->FirstNode;
     li->FirstNode = Aux;
     return(li);              
}

void *head(List l)
{
     return(l->FirstNode->info);
}

List tail(List l)
{
     List Lis;
     Lis=Empty();
     NodeList *Aux = (NodeList*)malloc(sizeof(NodeList));
     Aux = l->FirstNode->Next;
     Lis->FirstNode = Aux;
     if(l->FirstNode->Next != NULL)
         l->FirstNode->Next->count++;
     return(Lis);     
}

List remover(int key, List l)
{
     List Lis;
     Lis = l;
     int v=0;
     NodeList *Aux = (NodeList*)malloc(sizeof(NodeList));
     NodeList *Ant = (NodeList*)malloc(sizeof(NodeList));
     Info* q = (Info*)malloc(sizeof(Info));
     q = head(Lis);
     if (q->key == key)
     {
         v++;       
         l->FirstNode->count--;
         if(l->FirstNode->count==0)
             free(l->FirstNode);
         l->FirstNode = l->FirstNode->Next;    
         printf("\n\nO elemento %d foi excluido da lista!",q->info);      
     }          
     else
     {
         Aux = Lis->FirstNode->Next;
         Ant = Lis->FirstNode;   
         while(Aux!=NULL)
         {
            Info* q = (Info*)malloc(sizeof(Info));
            q = Aux->info;
            if(q->key == key)
            {
               v++;
               Ant->Next = Aux->Next;
               Aux->count--;
               if(Aux->count==0)
                  free(Aux);
               printf("\n\nO elemento %d foi excluido da lista!",q->info);            
            }                 
            Aux=Aux->Next;
            Ant=Ant->Next;          
         }
     }
     if (v==0)
         printf("\n\nNao existe elemento com a chave %d na lista",key);  
     return(Lis);    
}

int menu(List L)
{    
     int n;
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
               j=t=k=0;
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
                  int inf; 
                  Info* q = (Info*)malloc(sizeof(Info));           
                  printf("Digite o numero a ser adicionado:\n");
                  scanf("%d",&inf);
                  q->info=(int*)inf;
                  q->key=k;
                  k++;                 
                  L= cons(q,L);
                  j++;
                  t++;                 
                  printf("\nO numero %d foi adicionado na lista!",q->info);                  
               }
          break;
          case 4:
               if (c==0)
                  printf("A lista nao foi criada!"); 
               else if (isEmpty(L))
                  printf("A lista esta vazia!"); 
               else
               {  
                  int ch; 
                  printf("Digite a chave do elemento a ser removido:\n");
                  scanf("%d",&ch);
                  L= remover(ch,L);
                  j--;
                  t--;                                                                                                                                 
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
                   Info* q = (Info*)malloc(sizeof(Info));
                   q = head(L);
                   printf("%d",q->info);
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
                      Info* q = (Info*)malloc(sizeof(Info));
                      q = head(Lis); 
                      printf("%d ",q->info);
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

