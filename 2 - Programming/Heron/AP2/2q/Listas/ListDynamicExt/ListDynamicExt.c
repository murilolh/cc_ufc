//ListDynamicExt.c

#include "../List/List1.h"

struct GetKey
{
 int key;
};

List Rem(int Key, List l)
{
     //Controle interno dos contadores e chaves da lista
  NodeList *Print;
  Print = (NodeList*)malloc(sizeof(NodeList));
  Print = l->FirstNode;
  printf("\nMemory Management: ");
  while(Print!=NULL)
  {
         printf("%d ", Print->Count);     
         Print = Print->Next;        //Imprime a situação dos contadores da lista       
  }                                //depois da inserçao de um nó
  printf("\n");
  Print = l->FirstNode;
  printf("\nList Keys: ");
  while(Print!=NULL)
  {
         struct GetKey *k =(struct GetKey*)Print->Info;
         int NodeKey = k->key;
         printf("%d ", NodeKey);     
         Print = Print->Next;        //Imprime a situação das chaves da lista       
  }                                //depois da inserção de um nó
  printf("\n");
     if(IsEmpty(l))
     {
         printf("\nError: List Empty");
         getch();
         l = Empty(l);
         return(l);
     }     
     NodeList *Aux, *Ant;
     Aux = l->FirstNode->Next;
     Ant = l->FirstNode;
     struct GetKey *k =(struct GetKey*)l->FirstNode->Info;
     int NodeKey = k->key;  
     if (NodeKey == Key)
     {
          l->FirstNode->Count--;
          printf("\nSucess: HeadNode Key removed!\n");
          if(l->FirstNode->Count==0)
          {
              printf("\nFree HeadNode!\n");
              free(l->FirstNode);
          } 
          l->FirstNode = l->FirstNode->Next;
          return(l);
     }
     else
     {      
            while(Aux != NULL)
            {
               k =(struct GetKey*)Aux->Info;
               NodeKey = k->key;    
               if (NodeKey == Key)
               { 
                  Ant->Next = Aux->Next;
                  Aux->Count--;
                  printf("\nSucess: Tail Key removed!\n");
                  getch();
                  if(Aux->Count==0)
                  { 
                     printf("\nFree Tail Node!\n");
                     free(Aux);
                  }
                  return(l);
               }
               Aux = Aux->Next;
               Ant = Ant->Next;            
            }
            printf("\nError: Key don't finded\n");
            getch();
            return(l);   
     }    
}
