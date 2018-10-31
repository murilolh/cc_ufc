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

// Observadora -> Verifica se está vazia

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
         Print = Print->Next;        //Imprime a situação dos contadores da lista       
  }                                //depois da inserçao de um nó
  printf("\n");
  Print = Lis->FirstNode;
  printf("\nList Keys: ");
  while(Print!=NULL)
  {
         struct GetKey *k =(struct GetKey*)Print->Info;
         int NodeKey = k->key;
         printf("%d ", NodeKey);     
         Print = Print->Next;        //Imprime a situação das chaves da lista       
  }                                //depois da inserção de um nó
  printf("\n");
  return(Lis);
}

//Construtora -> Insere um nó na Lista

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

//Observadora -> Retorna o conteúdo do nó-cabeça da Lista

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

//Observadora -> Retorna o conteudo da Lista sem o nó-cabeca

