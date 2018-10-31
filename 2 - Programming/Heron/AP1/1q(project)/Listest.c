#include "Listest.h"

List_est Empty_est()
{
     List_est l;
     l.t=0;
     return (l);
}

List_est cons_est(void* inf, List_est l)
{
     int i;
     List_est lis;
     lis=Empty_est();
     for(i=l.t;i>=0;i--)
         lis.vet[i+1]=l.vet[i];
     lis.vet[0]=inf;
     lis.t=(l.t)+1;
     return(lis);
}

void* head_est(List_est l)
{
     return(l.vet[0]);
}

List_est tail_est(List_est l)
{
     int j;
     List_est lis;
     for(j=0;j<MAX;j++)
         lis.vet[j]=l.vet[j+1];
     lis.t=(l.t)-1;
     return(lis);
}

int isEmpty_est(List_est l)
{
     return((l.t)==0);
}

