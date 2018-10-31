#include <stdio.h> 
#include <conio.h> 
#include <stdlib.h>

typedef struct Node_List
{
        void *Info;
        struct Node_List *Next;
}NodeList;

typedef struct 
{
       NodeList *FirstNode;
}HeadNode;

typedef HeadNode List_din;

List_din Empty_din();
List_din cons_din(void *Info, List_din l);
void *head_din(List_din l);
List_din tail_din(List_din l);
int isEmpty_din(List_din l);


