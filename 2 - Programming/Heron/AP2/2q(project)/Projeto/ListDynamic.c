#include "List.h"
#include <stdio.h> 
#include <conio.h> 
#include <stdlib.h>

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
