#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int n;
int fib[100];

int fibonacci(int x)
{
    fib[0]=0;
    fib[1]=1;
    if(x==1) printf(" %d ",fib[0]);
    else{
      for(int i=0;i<2;i++)
          printf(" %d ",fib[i]);
      for(int j=2;j<x;j++){
          fib[j]=fib[j-1]+fib[j-2];
          printf(" %d ",fib[j]);
      }
    }
    printf("\n\n");
}

int main()
{
    pid_t pid;

    pid=fork();

	 
    if(pid<0){
              fprintf(stderr,"Fork Failed");
              return(-1);
    }
   
    else if (pid==0){
         printf("\nDigite o valor de n: \n");
         scanf("%d",&n);
         if(n<0){
            printf("\nVoce precisa digitar um numero maior que zero\n");
            }
         else if (n==0){
            printf("\nNenhum termo na sequencia de Fibonacci para n igual a %d\n\n",n);
            }
         else{
            printf("\nOs %d termos da sequencia de Fibonacci sao: \n",n); 
            fibonacci(n);
            }
    }
    else{
         wait(NULL);
         return(0);
    }
}
             
