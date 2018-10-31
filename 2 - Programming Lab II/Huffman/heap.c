#include "heap.h"
#define FESQ(i) ((2*i)+1)
#define FDIR(i) ((2*i)+2)
#define PAI(j) ((j-1)/2)

void descer(void *h, int n,int j, size_t size, int (*compare)(const void *, const void *))
{ 
     void* aux = malloc(size);
     int i,c;
     for(i=j;i<((n/2)+1);i++)
     {
         if ((compare(h+FESQ(i)*size, h+FDIR(i)*size)) <= 0)
         {
             memcpy(aux, h+FDIR(i)*size, size);
             c=0;
         }
         else
         {
             memcpy(aux, h+FESQ(i)*size, size);
             c=1;
         }
         if (compare(aux, h+i*size) > 0)
         {
             if(c==0)
                memcpy(h+FDIR(i)*size, h+(i)*size, size);
             else
                memcpy(h+FESQ(i)*size, h+(i)*size, size);
             memcpy(h+i*size,aux,size);
         }
     }
}

void heapCria(void *h, int n, size_t size, int (*compare)(const void *, const void *))
{
     int l;
     for(l=(n/2)-1; l>=0;l--)
        descer(h,n,l,size,compare);   
}

void subir(void* h, int n, size_t size, int (*compare)(const void *, const void *))
{
     int i,j;
     void* Aux = malloc(size);
     j=n;
     for(i=0;i<((n/2)-1);i++)
     {
          if((compare(h+PAI(j)*size, h+j*size))<0)
          {
               memcpy(Aux,h+j*size,size);
               memcpy(h+j*size,h+PAI(j)*size,size);
               memcpy(h+PAI(j)*size,Aux,size);
               j=PAI(j);
          }
     }
}

void Inserir( void *h, void* x, int n, size_t size, int (*compare)(const void *, const void *) )
{
     memcpy(h+n*size,&x,size);
     subir(h,n,size,compare);
}

void Remover( void *h, int n, size_t size, int (*compare)(const void *, const void *))
{
     memcpy(h, ((char*)h)+(n-1)*size, size);
     descer((int*)h,n-1,0,sizeof(size),compare);
}
