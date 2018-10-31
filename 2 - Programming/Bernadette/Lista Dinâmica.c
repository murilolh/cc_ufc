/*Alunos: C�cero Cavalcante de Ara�jo
          Murilo Lima de Holanda            */
//     LISTA DIN�MICA ORDENADA
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
int c=0;  //Vari�vel incrementada quando a lista � criada
typedef int TipoT;  //Definindo o tipo de conte�do da lista din�mica
typedef struct cel  //Definindo a estrutura c�lula, que formar� a lista
{
    TipoT conteudo;
    struct cel *prox;
}celula;

typedef struct     //Definindo a estrutura da Lista Din�mica
{
    celula *primeiro,*ultimo;
}TipoLista;

TipoLista* crialista() //Cria a lista
{
    TipoLista* Lista = (TipoLista*) malloc(sizeof(TipoLista));
    Lista->primeiro=(celula*) malloc(sizeof(celula));
    Lista->ultimo=(celula*) malloc(sizeof(celula));
    Lista->ultimo->prox=NULL; //Anula a c�lula seguinte � c�lula do �ltimo elemento
    Lista->primeiro=Lista->ultimo;
    return(Lista);
}
     
int vazia(TipoLista *Lista) //Verifica se a lista est� vazia
{  
    return(Lista->primeiro==Lista->ultimo);
}

void Inserir(TipoT x,TipoLista *Lista) //Insere um elemento ordenadamente na lista
{
    Lista->ultimo->prox=(celula*) malloc(sizeof(celula));
    if (vazia(Lista))//Se a lista estiver vazia, insere o primeiro normalmente
    {
       Lista->ultimo=Lista->ultimo->prox;
       Lista->primeiro->prox->conteudo=x;
       Lista->primeiro->prox->prox=NULL;
    }
    else//A partir do primeiro elemento colocado o programa ordena os elementos seguintes
    {
       Lista->ultimo=Lista->ultimo->prox;//Abrindo um espa�o vazio na lista
       Lista->ultimo->prox=NULL;
       int z; //Vari�vel que guarda o elemento da posi��o que receber� o elemento dado
       celula *aux;
       aux=Lista->primeiro->prox;
       /*Agora o programa colocar� o elemento na posi��o correta, guardando o
         o elemento que estava nesta posi��o e colocando no seguinte, at�
         que se chegue ao fim da lista */
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

void Remover(int x, TipoLista *Lista)//Remove da lista todos os elementos iguais ao conte�do dado
{
    int vf=0;//Vari�vel incrementada quando algum elemento for removido
    int p=0; //Vari�vel que receber� o n�mero de elementos da lista
    celula *aux,*ax,*ant,*pos;//C�lulas auxiliares no processo de remo��o
    aux=Lista->primeiro->prox;
    while (aux!=NULL) //Contador para o n�mero de elementos da c�lula
    {
       p++;  
       aux=aux->prox; 
    }
    /*O n�mero de vezes que ser� feito o processo ser� igual ao n�mero de elementos
      na lista, garantindo assim com que todos elementos de conte�do igual ao 
      conte�do que deseja-se remover sejam removidos        */
    for (int i=0;i<=p;i++)
    {
       aux=Lista->primeiro;
       while (aux->prox!=NULL)//Far� a verifica��o do in�cio ao fim da lista 
       {
          //Come�a quando encontra um elemento igual ao que deseja-se retirar
          if (aux->prox->conteudo==x)
          {
             /*Se o elemento que deseja-se retirar estiver na �ltima posi��o da 
               lista faz a c�lula anterior � que guarda o elemento apontar
               para a c�lula que finaliza a lista */
             if (aux->prox->prox==NULL)
             {
                /*Zera a lista caso o elemento que deseja-se retirar seja o �nico
                  elemento da lista */
                if (aux->prox==Lista->primeiro->prox) 
                    Lista->primeiro=Lista->ultimo;
                else
                /*Se o elemento que deseja-se retirar for o �ltimo, mas n�o o
                  �nico elemento da lista, remove o mesmo     */
                    while (aux->prox->conteudo==x)
                    {
                        aux->prox->conteudo=aux->conteudo;
                        ax=Lista->primeiro;
                        while (ax->prox->conteudo < aux->conteudo)     
                            ax=ax->prox;     
                        ax->prox=aux->prox;
                    }
             }
             /*Se o elemento que deseja-se retirar n�o estiver na �ltima posi��o 
               da lista, faz a c�lula anterior � que guarda o elemento apontar
               para a pr�xima   */
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
    //Avisa se o conte�do pedido n�o existir na lista
    if (vf==0)
         printf("\nO elemento %d nao esta na lista!",x);
    else
         printf("\nO elemento %d foi removido da lista!",x);
}

int VerifElemento(int x, TipoLista *Lista)//Verifica se o elemento est� na lista
{
    int pos=0;//Vari�vel para a posi��o do elemento
    int vf=0; //Vari�vel incrementada se o elemento estiver na lista
    celula *aux;
    aux=Lista->primeiro->prox;
    //Percorre toda a lista em busca do elemento
    while (aux!=NULL) 
    {    
       if (aux->conteudo==x)//Se o elemento for encontrado, d� sua posi��o
       {
         printf("\nO numero %d esta na posicao %d da lista.",x,pos);
         vf++;
       } 
       pos++;
       aux=aux->prox;
    }       
    if (vf==0)//Se o elemento n�o for encontrado, avisa que ele n�o est� na lista
         printf("\nO elemento %d nao esta na lista!",x);
}    

void ImprimeLista(TipoLista *Lista)//Imprime os elementos da lista
{
    celula *aux;
    aux=Lista->primeiro->prox;
    while (aux!=NULL) 
    {     
        printf("%d ",aux->conteudo);
        aux=aux->prox;
    }
}

int menu(TipoLista *Lista)//Menu inicial do programa
{
  int n;//Vari�vel para a op��o do menu
  printf("Digite a opcao desejada:\n");
  printf("1- Criar uma nova lista\n");
  printf("2- Verificar se a lista esta vazia\n");
  printf("3- Inserir elemento\n");
  printf("4- Remover elemento especifico da lista\n");
  printf("5- Dar a posicao de um elemento na lista\n");
  printf("6- Imprimir a lista\n");
  printf("0- Sair\n");
  scanf("%d",&n);
  system("cls");
  switch(n)
  {
     case 0:
          exit(1);//Sai do programa
     break;
     case 1:
          Lista=crialista();//Criando a lista
          c++;//Incrementando a vari�vel que desbloqueia as outras fun��es
          printf("Lista criada!");
     break;
     case 2:
          if (c==0)
            printf("A lista nao foi criada!");
          else if (vazia(Lista))//Verificando se a lista est� vazia
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
            printf("Digite numero a ser adicionado\n");
            scanf("%d",&x);
            Inserir(x,Lista);//Inserindo o n�mero digitado na lista 
            printf("\nO numero %d foi adicionado na lista!",x);
          }
     break;
     case 4:
          if (c==0)
            printf("A lista nao foi criada!");
          else
          {
            int x;
            printf("Digite o conteudo a ser removido da lista\n");
            scanf("%d",&x);
            Remover(x,Lista);//Removendo elemento digitado na lista
          }
     break;
     case 5:
          if (c==0)
             printf("A lista nao foi criada!");
          else
            {
            int x;
            printf("Digite o numero a ser verificado:\n");
            scanf("%d",&x);
            VerifElemento(x,Lista);//Verificando se o elemento digitado est� na lista
            }
     break;
     case 6:
          if (c==0)
             printf("A lista nao foi criada!");
          else if (vazia(Lista))
              printf("A lista esta vazia!");
          else
          {
          printf("A lista e:\n\n");
          ImprimeLista(Lista);//Imprimindo a lista
          }
     break;
     default:
          system("cls");
          menu(Lista);   
  }
  getch();
  system("cls");
  menu(Lista);
}

int main()
{
   TipoLista *L;//Definindo a lista usada no programa
   menu(L); //Chamando o menu principal
}
