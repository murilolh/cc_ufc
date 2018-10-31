/*Alunos: Cícero Cavalcante de Araújo
          Murilo Lima de Holanda            */
//     LISTA ESTÁTICA
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define max 100
int c=0;
int vf;
typedef int tipodados; 
typedef struct //Definindo a estrutura lista
{
        tipodados item[max];
        int primeiro,ultimo;
        }TipoLista;

void crialista(TipoLista *Lista) //Cria a lista
{
     (Lista->ultimo)=(Lista->primeiro)=0;
     }
     
int vazia(TipoLista *Lista) //Verifica se a lista está vazia
{
    return ((Lista->ultimo)==(Lista->primeiro));
    }

void InserirUltimo(int x,TipoLista *Lista) //Insere um elemento na ultima posição da lista
{
     if ((Lista->ultimo)>=max)
         printf("\n\nLista cheia!\n");
     else
     {
         Lista->item[Lista->ultimo]=x;
         Lista->ultimo++;
     }
}

void OrdLista(TipoLista *Lista) //Ordena a lista(Utiliza o método da bolha)
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

void InserirPosicao(int x, int p, TipoLista *Lista)//Insere elemento na posição desejada
{
     if ((Lista->ultimo)>=max)
        printf("\n\nLista cheia!\n");
     else
     Lista->item[p]=x;
}

void RemoverUltimo(TipoLista *Lista)//Remove o último elemento da lista
{
    if (vazia(Lista))
       printf("A lista esta vazia!");
    else
    {
    Lista->item[Lista->ultimo-1]=0;
    Lista->ultimo--;
    }
}
 
void RemoverPosicao(int p, TipoLista *Lista)//Remove o elemento da posicao desejada
{
     int i;
     if (Lista->ultimo<p)
        printf("\nPosicao invalida!");
     for (i=p;i<=Lista->ultimo;i++)
        Lista->item[i]=Lista->item[i+1];
     Lista->ultimo--;
}
  
int ImprimeLista(TipoLista *Lista)//Imprime os elementos da lista
{
    int i;
    for (i=(Lista->primeiro);i<(Lista->ultimo);i++)
       printf("%d ",Lista->item[i]);
}
    
int VerifElemento(int x, TipoLista *Lista)//Imcrementa uma variável se o elemento estiver na lista
{
    vf=0;
    int i;
    for (i=(Lista->primeiro);i<(Lista->ultimo);i++)
       if (Lista->item[i]==x)
          vf++;  
}    

int VerifPosicao(int x, TipoLista *Lista)//Se o elemento estiver na lista, diz a posição do mesmo
{
    int pos;
    int i;
    for (i=(Lista->primeiro);i<(Lista->ultimo);i++)
        if (Lista->item[i]==x)
        {
           pos=i;
           printf("\nO numero %d esta na posicao %d da lista.",x,pos);                  
           }       
}
    
int menu(TipoLista L)//Menu inicial do programa
{
  int n;
  printf("Digite a opcao desejada:\n");
  printf("1- Criar uma nova lista\n");
  printf("2- Verificar se a lista esta vazia\n");
  printf("3- Inserir elemento no final da lista\n");
  printf("4- Inserir elemento na ordem\n");
  printf("5- Inserir em uma dada posicao da lista\n");
  printf("6- Remover o ultimo elemento da lista\n");
  printf("7- Remover o elemento de uma posicao da lista\n");
  printf("8- Imprimir a lista\n");
  printf("9- Verificar se um elemento esta na lista\n");
  printf("10- Dar a posicao de um elemento na lista\n");
  printf("0- Sair\n");
  scanf("%d",&n);
  system("cls");
  switch(n)
  {
     case 0:
          exit(1);//Sai do programa
     break;
     case 1:
          crialista(&L); //Criando a lista
          c++;
          printf("Lista criada!");
     break;
     case 2:
          if (c==0)
             printf("A lista nao foi criada!");
          else if (vazia(&L))
             printf("A lista esta vazia!");
          else 
             printf("A lista nao esta vazia!");
     break;
     case 3:
          if (c==0)
              printf("A lista nao foi criada!");
          else
          {
              int x;
              printf("Digite o ultimo numero a ser adicionado\n");
              scanf("%d",&x);
              InserirUltimo(x ,&L);//Inserindo o número digitado no fim da lista 
              printf("\nO numero %d foi adicionado!",x);
          }
     break;
     case 4:
          if (c==0)
             printf("A lista nao foi criada!");
          else
          {
              int h;
              printf("Digite o numero a ser adicionado\n");
              scanf("%d",&h);
              InserirUltimo(h ,&L);//Adicionando o elemento à lista
              OrdLista(&L);//Ordenando a lista já com o elemento adicionado
              printf("\nO numero %d foi adicionado na lista ordenada.",h); 
          }
     break;
     case 5:
          if (c==0)
              printf("A lista nao foi criada!");
          else
          {
              int num,po;
              printf("Digite a posicao do numero:\n");
              scanf("%d",&po);
              if (L.ultimo>po)//Só pede o número se a posição já estiver criada na lista
              {
                 printf("\nDigite o numero a ser adicionado na posicao:\n");
                 scanf("%d",&num);
                 InserirPosicao(num,po,&L);//Inserindo o elemento na posição desejada
                 printf("\nO numero %d foi adicionado na posicao %d!",num,po);
              }
              else
                 printf("\nPosicao invalida!");
          }
     break;
     case 6:
          if (c==0)
             printf("A lista nao foi criada!");
          else if (L.ultimo>0)
          {
             printf("O ultimo elemento da lista foi removido!");
             RemoverUltimo(&L);//Removendo o último elemento da lista, desde que ela não esteja vazia
          }
          else 
             printf("A lista esta vazia!");          
     break;
     case 7:
          if (c==0)
             printf("A lista nao foi criada!");
          else
          {
             int ps;
             printf("Digite a posicao do numero a ser removido:\n");
             scanf("%d",&ps);
             if (L.ultimo>ps)
             {
                RemoverPosicao(ps,&L);//Removendo o elemento da posição, desde que esta seja válida
                printf("\nO elemento que estava na posicao %d foi removido!",ps);
             }
             else
                printf("\nPosicao invalida!");
          }
     break;     
     case 8:
          if (c==0)
             printf("A lista nao foi criada!");
          else if (vazia(&L))//Não imprime a lista se ela não tiver elementos
             printf("A lista esta vazia!");
          else
          {
             printf("A lista e:\n\n");
             ImprimeLista(&L);//Imprimindo a lista
          }
     break;
     case 9:
          if (c==0)
             printf("A lista nao foi criada!");
          else
          {
              int y;
              printf("Digite o numero a ser verificado:\n");
              scanf("%d",&y);
              VerifElemento(y,&L);//Verificando se o elemento está na lista
              if (vf==0)//Se a variável tiver sido alterada, significa que o elemento está na lista
                 printf("\nO elemento %d nao esta na lista!",y);
              else 
                 printf("\nO elemento %d esta na lista!",y);
          }  
     break;
     case 10:
          if (c==0)
             printf("A lista nao foi criada!");
          {
             int z;
             printf("Digite o numero a ser verificado:\n");
             scanf("%d",&z);
             VerifElemento(z,&L);
             if (vf==0)
                printf("\nO elemento %d nao esta na lista!",z);
             else 
                VerifPosicao(z, &L);//Se o número estiver na lista, dá as possíveis posições deste número
          }
     break;
     default:
          system("cls");
          menu(L);   
  }
  getch();
  system("cls");
  menu(L);
}

int main()
{
  TipoLista L;//Definindo a lista usada no programa
  menu(L);
}
