#include "Listdin.h"

List_din Empty_din()
{
     HeadNode l;
     l.FirstNode=NULL;
     return (l);
}

int isEmpty_din(List_din l)
{
     return(l.FirstNode==NULL);
}

List_din cons_din(void *Info, List_din l)
{
     NodeList *Aux = (NodeList*)malloc(sizeof(NodeList));
     HeadNode li;
     Aux->Info = Info;
     Aux->Next = l.FirstNode;
     li.FirstNode = Aux;
     return(li);              
}

void *head_din(List_din l)
{
     return(l.FirstNode->Info);
}

List_din tail_din(List_din l)
{
     List_din Lis;
     Lis=Empty_din();
     NodeList *Aux = (NodeList*)malloc(sizeof(NodeList));
     Aux = l.FirstNode->Next;
     Lis.FirstNode = Aux;
     return(Lis);
}
