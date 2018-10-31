//ListStatic.c

#include "ListType1.h"

List Empty()
{
     List *l;
     l->FirstNode = 0;
     return(l);
}

//Construtora -> Cria Lista Vazia

int IsEmpty(List l)
{
     return((l->FirstNode)==0);
}

// Observadora -> Verifica se está vazia

List Cons(void* Info, List l)
{
     int i;
     HeadNode *aux = (HeadNode*)malloc(sizeof(HeadNode));
     aux = Empty();
     for(i=l->FirstNode;i>=0;i--)
         aux->NodeList[i+1]=l->NodeList[i];
     aux->NodeList[0]=Info;
     aux->FirstNode = (l->FirstNode)+1;
     return(aux);
}

// Observadora -> Verifica se está vazia

void* Head(List l)
{
     return(l->NodeList[0]);
}

//Observadora -> Retorna o conteúdo do nó-cabeça da Lista

List Tail(List l)
{
     int j;
     HeadNode *lis = (HeadNode*)malloc(sizeof(HeadNode));
     for(j=0;j<max;j++)
         lis->NodeList[j]=l->NodeList[j+1];
     lis->FirstNode=(l->FirstNode)+1;
     return(lis);
}

//Observadora -> Retorna o conteudo da Lista sem o nó-cabeca

/*List Print(List l)
{
     NodeList *Aux;
     Aux = (NodeList*)malloc(sizeof(NodeList));
     Aux = l->FirstNode;
     printf("\n");
     while(Aux!=NULL)
     {
        printf("%d ",*((int*)Aux->Info));
        Aux=Aux->Next;
     }
}

//Observadora -> Imprime a Lista Completa

*/


