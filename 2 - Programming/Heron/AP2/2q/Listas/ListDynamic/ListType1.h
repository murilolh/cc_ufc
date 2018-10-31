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

//Definição da estrutura Nó da lista

typedef struct HeadNode
{
      struct Node_List *FirstNode;
}HeadNode;

// Definição da estrutura Nó-cabeça que representará a Lista

typedef struct HeadNode *List;
//Definição de T.A.D Lista 

#endif




