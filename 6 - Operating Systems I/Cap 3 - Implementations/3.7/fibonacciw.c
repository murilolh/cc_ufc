#include <stdio.h>

int n;
int fib[100];

int fibonacci(int x)
{
    int i,j;
    fib[0]=0;
    fib[1]=1;
    if(x==1) printf(" %d ",fib[0]);
    else{
      for(i=0;i<2;i++)
          printf(" %d ",fib[i]);
      for(j=2;j<x;j++){
          fib[j]=fib[j-1]+fib[j-2];
          printf(" %d ",fib[j]);
      }
    }
    printf("\n\n");
}

int main()
{
   
   printf("\nDigite o valor de n: \n");
   scanf("%d",&n);
   if(n<=0)
     printf("\nVoce precisa digitar um numero maior que zero\n");
   else
   {
     printf("\nOs %d termos da sequencia de Fibonacci sao: \n",n); 
     fibonacci(n);
     getch();
   }
}
             
