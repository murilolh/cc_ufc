#ifndef _LISTTYPE_H_
#define _LISTTYPE_H_

//ListType.h

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

typedef struct Node_List
{
        int Count;
        void *Info;
        struct Node_List *Next;
}NodeList;

//Defini��o da estrutura N� da lista

typedef struct HeadNode
{
      struct Node_List *FirstNode;
}HeadNode;

// Defini��o da estrutura N�-cabe�a que representar� a Lista

typedef struct HeadNode *List;
//Defini��o de T.A.D Lista 

#endif




