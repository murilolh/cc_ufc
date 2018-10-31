#include "..\List.h"
#include <stdio.h> 
#include <conio.h> 
#include <stdlib.h>

List Empty()
{
     List l;
     l.t=0;
     return (l);
}

List cons(void* inf, List l)
{
     int i;
     List lis;
     lis=Empty();
     for(i=l.t;i>=0;i--)
         lis.vet[i+1]=l.vet[i];
     lis.vet[0]=inf;
     lis.t=(l.t)+1;
     return(lis);
}

void* head(List l)
{
     return(l.vet[0]);
}

List tail(List l)
{
     int j;
     List lis;
     for(j=0;j<MAX;j++)
         lis.vet[j]=l.vet[j+1];
     lis.t=(l.t)-1;
     return(lis);
}

int isEmpty(List l)
{
     return((l.t)==0);
}

