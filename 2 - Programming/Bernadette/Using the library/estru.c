#include <stdlib.h>
#define max 100

typedef int tipodados;
typedef struct 
{
        tipodados item[max];
        int primeiro,ultimo;
        }Lste;
        
void lste_cria(Lste *Lista)
{
     (Lista->ultimo)=(Lista->primeiro)=0;
     }
     
int lste_vaz(Lste *Lista)
{
    return ((Lista->ultimo)==(Lista->primeiro));
    }

void lste_insul(int x,Lste *Lista)
{
     if ((Lista->ultimo)>=max)
         printf("\n\nLista cheia!\n");
     else
     {
         Lista->item[Lista->ultimo]=x;
         Lista->ultimo++;
     }
}

void lste_ord(Lste *Lista)
{
  int lsup,bol,k,aux;
  lsup=(Lista->ultimo)-1;
  while (lsup > 0)
  {
      bol=0;
      k=1;
      for (k=0;k<=lsup-1;k++)
      {
          if  (Lista->item[k]>Lista->item[k+1])
          {
             aux=Lista->item[k];
             Lista->item[k]=Lista->item[k+1];
             Lista->item[k+1]=aux;
             bol=k;
          }
      }
      lsup=bol;
  }
}

void lste_inpos(int x, int p, Lste *Lista)
{
     if ((Lista->ultimo)>=max)
        printf("\n\nLista cheia!\n");
     else
     Lista->item[p]=x;
}

void lste_remul(Lste *Lista)
{
    if (lste_vaz(Lista))
       printf("A lista esta vazia!");
    else
    {
    Lista->item[Lista->ultimo-1]=0;
    Lista->ultimo--;
    }
}

void lste_rempos(int p, Lste *Lista)
{
     int i;
     if (Lista->ultimo<p)
        printf("\nPosicao invalida!");
     for (i=p;i<=Lista->ultimo;i++)
        Lista->item[i]=Lista->item[i+1];
     Lista->ultimo--;
}

int lste_print(Lste *Lista)
{
    int i;
    for (i=(Lista->primeiro);i<(Lista->ultimo);i++)
       printf("%d ",Lista->item[i]);
}

int lste_busc(int x, Lste *Lista)
{
    int pos;
    int vf=0;
    int i;
    for (i=(Lista->primeiro);i<(Lista->ultimo);i++)
        if (Lista->item[i]==x)
        {
           pos=i;
           printf("\nO numero %d esta na posicao %d da lista.",x,pos); 
           vf++;                 
           }
     if (vf==0)
                printf("\nO elemento %d nao esta na lista!",x);       
}

typedef int TipoT;

typedef struct cel  
{
    TipoT conteudo;
    struct cel *prox;
}celula;

typedef struct     
{
    celula *primeiro,*ultimo;
}Lstd;

Lstd* lstd_cria() 
{
    Lstd* Lista = (Lstd*) malloc(sizeof(Lstd));
    Lista->primeiro=(celula*) malloc(sizeof(celula));
    Lista->ultimo=(celula*) malloc(sizeof(celula));
    Lista->ultimo->prox=NULL; 
    Lista->primeiro=Lista->ultimo;
    return(Lista);
}

int lstd_vaz(Lstd *Lista) 
{  
    return(Lista->primeiro==Lista->ultimo);
}

void lstd_ins(TipoT x,Lstd *Lista) 
{
    Lista->ultimo->prox=(celula*) malloc(sizeof(celula));
    if (lstd_vaz(Lista))
    {
       Lista->ultimo=Lista->ultimo->prox;
       Lista->primeiro->prox->conteudo=x;
       Lista->primeiro->prox->prox=NULL;
    }
    else
    {
       Lista->ultimo=Lista->ultimo->prox;
       Lista->ultimo->prox=NULL;
       int z; 
       celula *aux;
       aux=Lista->primeiro->prox;
       while (aux!=NULL) 
       {     
          if (aux->conteudo>x)
          {
            z=aux->conteudo;
            aux->conteudo=x;
            x=z;                          
          }
          aux=aux->prox;
       }   
    }
}

void lstd_remcom(int x, Lstd *Lista)
{
    int vf=0;
    int p=0; 
    int i;
    celula *aux,*ax,*ant,*pos;
    aux=Lista->primeiro->prox;
    while (aux!=NULL) 
    {
       p++;  
       aux=aux->prox; 
    }
    for (i=0;i<=p;i++)
    {
       aux=Lista->primeiro;
       while (aux->prox!=NULL)
       {
          if (aux->prox->conteudo==x)
          {
             if (aux->prox->prox==NULL)
             {
                if (aux->prox==Lista->primeiro->prox) 
                    Lista->primeiro=Lista->ultimo;
                else
                    while (aux->prox->conteudo==x)
                    {
                        aux->prox->conteudo=aux->conteudo;
                        ax=Lista->primeiro;
                        while (ax->prox->conteudo < aux->conteudo)     
                            ax=ax->prox;     
                        ax->prox=aux->prox;
                    }
             }
             else
             {
                ant=aux;
                pos=aux->prox->prox;
                ant->prox=pos;               
             }
             vf++;          
          }
          aux=aux->prox;
       }
    }
    if (vf==0)
         printf("\nO elemento %d nao esta na lista!",x);
    else
         printf("\nO elemento %d foi removido da lista!",x);
}

int lstd_busc(int x, Lstd *Lista)
{
    int pos=0;
    int vf=0; 
    celula *aux;
    aux=Lista->primeiro->prox;
    while (aux!=NULL) 
    {    
       if (aux->conteudo==x)
       {
         printf("\nO numero %d esta na posicao %d da lista.",x,pos);
         vf++;
       } 
       pos++;
       aux=aux->prox;
    }       
    if (vf==0)
         printf("\nO elemento %d nao esta na lista!",x);
} 

void lstd_print(Lstd *Lista)
{
    celula *aux;
    aux=Lista->primeiro->prox;
    while (aux!=NULL) 
    {     
        printf("%d ",aux->conteudo);
        aux=aux->prox;
    }
}

typedef struct     
{
    int topo; 
    int vet[max]; 
}Plhe;   

Plhe* plhe_cria() 
{
    Plhe* p = (Plhe*) malloc(sizeof(Plhe));
    p->topo = 0;
    return(p);
}

int plhe_vaz (Plhe *Pilha) 
{
    return (Pilha->topo == 0);
}

void plhe_ins (Plhe *Pilha, int x) 
{                                
    if (Pilha->topo == max)      
       printf("Capacidade da pilha estourou!\n");
    else
    {
       Pilha->vet[Pilha->topo] = x;
       Pilha->topo++;        
    }
}

int plhe_rem (Plhe *Pilha) 
{                        
    if (plhe_vaz(Pilha))
       printf("Pilha vazia!\n");
    else
       Pilha->topo--;       
}

int plhe_busc (int x , Plhe *Pilha) 
{
    int vf=0;
    int pos=0;
    int i;
    for (i=Pilha->topo-1;i>=0;i--)
    {
      if (Pilha->vet[i] == x)
      {
         printf("\nO numero %d esta na posicao %d da pilha.",x,pos);
         vf++;
      } 
      pos++;
    }
    if (vf==0)
      printf("\nO elemento %d nao esta na pilha!",x);
}

int plhe_print (Plhe *Pilha) 
{
    int i;
    for (i=Pilha->topo-1;i>=0;i--)
      printf("   %d\n\n",Pilha->vet[i]);
}

typedef struct 
{
    celula *fundo, *topo;
    int tamanho;
}Plhd;

Plhd* plhd_cria()
{
    Plhd* Pilha = (Plhd*) malloc(sizeof(Plhd));
    Pilha->topo=(celula*) malloc (sizeof(celula));
    Pilha->fundo=Pilha->topo; 
    Pilha->topo->prox=NULL; 
    Pilha->tamanho=0;
}

int plhd_vaz(Plhd *Pilha) 
{  
    return(Pilha->fundo==Pilha->topo);
}

void plhd_ins(TipoT x, Plhd *Pilha) 
{
    celula *aux;
    aux= (celula*) malloc (sizeof(celula));
    Pilha->topo->conteudo=x;
    aux->prox=Pilha->topo;
    Pilha->topo=aux;
    Pilha->tamanho++;
}

int plhd_rem (Plhd *Pilha) 
{         
    celula *aux;
    aux=Pilha->topo;
    Pilha->topo=aux->prox; 
    free(aux);        
    Pilha->tamanho--;
}

int plhd_busc(int x , Plhd *Pilha) 
{
    int vf=0;
    int pos=0;
    celula *aux;
    aux=Pilha->topo->prox;
    while (aux!=NULL) 
    {     
       if (aux->conteudo == x) 
       {
           printf("\nO numero %d esta na posicao %d da pilha.",x,pos);
           vf++;
       }
       pos++;
       aux=aux->prox;
    }
    if (vf==0) 
       printf("\nO elemento %d nao esta na pilha!",x);
}

void plhd_print(Plhd *Pilha) 
{
    celula *aux;
    aux=Pilha->topo->prox;
    while (aux!=NULL) 
    {     
       printf("  %d\n\n",aux->conteudo);
       aux=aux->prox;
    }
}

typedef struct     
{
    celula *primeiro,*ultimo;
}Fild;

Fild* fild_cria() 
{
    Fild* Fila = (Fild*) malloc(sizeof(Fild));
    Fila->primeiro=(celula*) malloc(sizeof(celula));
    Fila->ultimo=(celula*) malloc(sizeof(celula));
    Fila->ultimo->prox=NULL; 
    Fila->primeiro=Fila->ultimo;
    return(Fila);
}

int fild_vaz(Fild *Fila) 
{  
    return(Fila->primeiro==Fila->ultimo);
}

void fild_ins(TipoT x,Fild *Fila) 
{
    Fila->ultimo->prox=(celula*) malloc(sizeof(celula));
    Fila->ultimo=Fila->ultimo->prox;
    Fila->ultimo->conteudo=x;
    Fila->ultimo->prox=NULL;    
}

void fild_rem(Fild *Fila) 
{
    celula *aux;
    aux=Fila->primeiro;
    Fila->primeiro=aux->prox;
    free(aux); 
}

int fild_busc(int x, Fild *Fila) 
{
    int pos=0;
    int vf=0; 
    celula *aux;
    aux=Fila->primeiro->prox;
    while (aux!=NULL)
    {    
      if (aux->conteudo==x) 
      {
        printf("\nO numero %d esta na posicao %d da fila.",x,pos);
        vf++;
      } 
      pos++;
      aux=aux->prox;
    }       
    if (vf==0) 
      printf("\nO elemento %d nao esta na fila!",x);
} 

void fild_print(Fild *Fila) 
{
    celula *aux;
    aux=Fila->primeiro->prox;
    while (aux!=NULL) 
    {     
      printf("%d ",aux->conteudo);
      aux=aux->prox;
    }
}   



