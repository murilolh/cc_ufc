#ifndef _LIST_H_
#define _LIST_H_

//List.h

#include "../ListDynamic/ListType1.h"

List Empty();
List Cons(void *Info, List l);
void *Head(List l);
List Tail(List l);
int IsEmpty(List l);

#endif
