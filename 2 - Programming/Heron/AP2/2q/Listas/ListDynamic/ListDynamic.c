//ListDynamic.c

#include "ListType1.h"

struct GetKey
{
 int key;
};

List Empty()
{
 HeadNode *l = (HeadNode*)malloc(sizeof(HeadNode));
 l->FirstNode = NULL;
 return(l);
}

//Construtora -> Cria Lista Vazia

int IsEmpty(List l)
{
 return(l->FirstNode==NULL);
}

// Observadora -> Verifica se est� vazia

List Cons(void *Info, List l)
{
  HeadNode *Lis = (HeadNode*)malloc(sizeof(HeadNode));
  NodeList *Aux = (NodeList*)malloc(sizeof(NodeList));
  Aux->Info = Info;
  Aux->Count = 1;
  Aux->Next = l->FirstNode; 
  Lis->FirstNode = Aux;
  printf("\nSucess: Key inserted!");
  printf("\n");
  //Controle interno dos contadores e chaves da lista
  NodeList *Print;
  Print = (NodeList*)malloc(sizeof(NodeList));
  Print = Lis->FirstNode;
  printf("\nMemory Management: ");
  while(Print!=NULL)
  {
         printf("%d ", Print->Count);     
         Print = Print->Next;        //Imprime a situa��o dos contadores da lista       
  }                                //depois da inser�ao de um n�
  printf("\n");
  Print = Lis->FirstNode;
  printf("\nList Keys: ");
  while(Print!=NULL)
  {
         struct GetKey *k =(struct GetKey*)Print->Info;
         int NodeKey = k->key;
         printf("%d ", NodeKey);     
         Print = Print->Next;        //Imprime a situa��o das chaves da lista       
  }                                //depois da inser��o de um n�
  printf("\n");
  return(Lis);
}

//Construtora -> Insere um n� na Lista

void *Head(List l)
{
      if(IsEmpty(l))
     {
         printf("\nError: List Empty\n");
         getch();
         l = Empty(l);
         return(l);
     }  
     return(l->FirstNode->Info);
}

//Observadora -> Retorna o conte�do do n�-cabe�a da Lista

List Tail(List l)
{
     if(IsEmpty(l))
     {
         printf("\nError: List Empty\n");
         getch();
         l = Empty(l);
         return(l);
     }
     HeadNode *Lis = (HeadNode*)malloc(sizeof(HeadNode));  
     if(l->FirstNode->Next == NULL)
     {
        Lis = Empty();
        return(Lis);
     }
     Lis->FirstNode = l->FirstNode->Next;
     l->FirstNode->Next->Count++;
     return(Lis);
}

//Observadora -> Retorna o conteudo da Lista sem o n�-cabeca

