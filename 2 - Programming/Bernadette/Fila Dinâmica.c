/*Alunos: Cícero Cavalcante de Araújo
          Murilo Lima de Holanda            */
//     FILA DINÂMICA
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
int c=0; //Variável que indica se a fila já foi criada ou não 
typedef int TipoT; //Definindo o tipo de conteúdo da fila dinâmica  
typedef struct cel //Definindo a estrutura célula, que formará a fila
{
    TipoT conteudo;
    struct cel *prox;
}celula;

typedef struct //Definindo a estrutura fila    
{
    celula *primeiro,*ultimo;
}TipoFila;

TipoFila* criafila() //Cria uma nova fila
{
    TipoFila* Fila = (TipoFila*) malloc(sizeof(TipoFila));
    Fila->primeiro=(celula*) malloc(sizeof(celula));
    Fila->ultimo=(celula*) malloc(sizeof(celula));
    Fila->ultimo->prox=NULL; 
    Fila->primeiro=Fila->ultimo;
    return(Fila);
}
     
int vazia(TipoFila *Fila) //Verifica se a fila está vazia
{  
    return(Fila->primeiro==Fila->ultimo);
}

void Inserir(TipoT x,TipoFila *Fila) //Insere um elemento na fila
{
    Fila->ultimo->prox=(celula*) malloc(sizeof(celula));
    Fila->ultimo=Fila->ultimo->prox;
    Fila->ultimo->conteudo=x;
    Fila->ultimo->prox=NULL;    
}

void Remover(TipoFila *Fila) //Remove um elemento da fila
{
    celula *aux;
    aux=Fila->primeiro;
    Fila->primeiro=aux->prox;
    free(aux); //Libera o espaço de memória
}

int Verifica(int x, TipoFila *Fila) //Verifica se um elemento está na fila
{
    int pos=0;
    int vf=0; 
    celula *aux;
    aux=Fila->primeiro->prox;
    while (aux!=NULL) //Percorrendo os elementos da fila
    {    
      if (aux->conteudo==x) //Caso o elemento esteja na fila
      {
        printf("\nO numero %d esta na posicao %d da fila.",x,pos);
        vf++;
      } 
      pos++;
      aux=aux->prox;
    }       
    if (vf==0) //Caso o elemento não esteja na fila
      printf("\nO elemento %d nao esta na fila!",x);
}    

void Imprime(TipoFila *Fila) //Imprime a fila
{
    celula *aux;
    aux=Fila->primeiro->prox;
    while (aux!=NULL) 
    {     
      printf("%d ",aux->conteudo);
      aux=aux->prox;
    }
}

int menu(TipoFila *Fila) //Menu principal
{
  int n;
  printf("Digite a opcao desejada:\n");
  printf("1- Criar uma nova fila\n");
  printf("2- Verificar se a fila esta vazia\n");
  printf("3- Inserir elemento no final da fila\n");
  printf("4- Remover o primeiro elemento da fila\n");
  printf("5- Buscar um elemento na lista\n");
  printf("6- Imprimir a fila\n");
  printf("0- Sair\n");
  scanf("%d",&n);
  system("cls");
  switch(n)
  {
     case 0:
          exit(1); //Saindo do programa
     break;
     case 1:
          Fila=criafila(); //Criando uma nova fila
          c++;
          printf("Fila criada!");
     break;
     case 2:
          if (c==0)
            printf("A fila nao foi criada!");
          else if (vazia(Fila)) //Verificando se a fila está vazia
            printf("A fila esta vazia!");
          else 
            printf("A fila nao esta vazia!");
          break;
     case 3:
          if (c==0)
            printf("A fila nao foi criada!");
          else
          {
            int x;
            printf("Digite numero a ser adicionado\n");
            scanf("%d",&x);
            Inserir(x,Fila); //Inserindo um elemento na fila
            printf("\nO numero %d foi adicionado na fila!",x);
          }
     break;
     case 4:
          if (c==0)
            printf("A fila nao foi criada!");
          else
          {
            printf("O primeiro elemento da fila foi removido!\n");
            Remover(Fila); //Removendo o primeiro elemento da fila
          }
     break;
     case 5:
          if (c==0)
             printf("A fila nao foi criada!");
          else
            {
            int x;
            printf("Digite o numero a ser buscado:\n");
            scanf("%d",&x);
            Verifica(x,Fila); //Buscando um elemento na fila
            }
     break;
     case 6:
          if (c==0)
             printf("A fila nao foi criada!");
          else if (vazia(Fila))
             printf("A fila esta vazia!");
          else
          {
             printf("A fila e:\n\n");
             Imprime(Fila);//Imprimindo a fila
          }
     break;
     default:
          system("cls");
          menu(Fila);   
  }
  getch();
  system("cls");
  menu(Fila);
}

int main()
{
   TipoFila *F;//Definindo a fila usada no programa
   menu(F);  //Chamando o menu
}
