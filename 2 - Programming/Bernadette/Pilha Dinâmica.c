/*Alunos: Cícero Cavalcante de Araújo
          Murilo Lima de Holanda            */
//     PILHA DINÂMICA
#include <stdio.h> 
#include <conio.h> 
#include <stdlib.h>
int c=0; //Variável que indica se a pilha foi criada ou não
typedef int TipoT;  //Definindo o tipo de elementos da pilha
typedef struct cel  //Definindo a estrutura célula, que formará a pilha
{
    TipoT conteudo;
    struct cel *prox;
}celula;

typedef struct //Definindo a estrutura pilha
{
    celula *fundo, *topo;
    int tamanho;
}TipoPilha;

TipoPilha* PilhaCria()
{
    TipoPilha* Pilha = (TipoPilha*) malloc(sizeof(TipoPilha));
    Pilha->topo=(celula*) malloc (sizeof(celula));
    Pilha->fundo=Pilha->topo; 
    Pilha->topo->prox=NULL; //Valores iniciais das células e do tamanho
    Pilha->tamanho=0;
}

int Vazia(TipoPilha *Pilha) //Verifica se a pilha está vazia
{  
    return(Pilha->fundo==Pilha->topo);
}

void Empilhar(TipoT x, TipoPilha *Pilha) //Insere um elemento na pilha
{
    celula *aux;
    aux= (celula*) malloc (sizeof(celula));
    Pilha->topo->conteudo=x;
    aux->prox=Pilha->topo;
    Pilha->topo=aux;
    Pilha->tamanho++;//Incrementa o tamanho da pilha
}

int Remover (TipoPilha *Pilha) //Remove um elemento da pilha
{         
    celula *aux;
    aux=Pilha->topo;
    Pilha->topo=aux->prox; 
    free(aux); //Libera o espaço de memória         
    Pilha->tamanho--;
}

int Verifica (int x , TipoPilha *Pilha) //Busca um elemento na pilha
{
    int vf=0;
    int pos=0;
    celula *aux;
    aux=Pilha->topo->prox;
    while (aux!=NULL) 
    {     
       if (aux->conteudo == x) //Caso o elemento seja encontrado
       {
           printf("\nO numero %d esta na posicao %d da pilha.",x,pos);
           vf++;
       }
       pos++;
       aux=aux->prox;
    }
    if (vf==0) //Caso o elemento não seja encontrado
       printf("\nO elemento %d nao esta na pilha!",x);
}

void Imprime(TipoPilha *Pilha) //Imprime a pilha
{
    celula *aux;
    aux=Pilha->topo->prox;
    while (aux!=NULL) 
    {     
       printf("  %d\n\n",aux->conteudo);
       aux=aux->prox;
    }
}

int menu(TipoPilha *P) //Menu principal
{
  int n;
  printf("Digite a opcao desejada:\n");
  printf("1- Criar uma nova pilha\n");
  printf("2- Verificar se a pilha esta vazia\n");
  printf("3- Inserir elemento na pilha\n");
  printf("4- Remover elemento da pilha\n");
  printf("5- Dar a posicao de um elemento na pilha\n");
  printf("6- Imprimir a pilha\n");
  printf("0- Sair\n");
  scanf("%d",&n);
  system("cls");
  switch(n)
  {
     case 0: 
          exit(1); //Saindo do menu
     break;
     case 1: 
          P=PilhaCria(); //Criando uma nova pilha
          c++;
          printf("Pilha criada!");
     break;
     case 2: 
          if (c==0)
             printf("A pilha nao foi criada!");
          else if (Vazia(P))//Verificando se a pilha está vazia
             printf("A pilha esta vazia!");
          else 
             printf("A pilha nao esta vazia!");
     break;
     case 3: 
          if (c==0)
             printf("A pilha nao foi criada!");
          else
          {
             int x;
             printf("Digite numero a ser adicionado\n");
             scanf("%d",&x);
             Empilhar(x,P); //Inserindo um elemento na pilha
             printf("\nO numero %d foi adicionado na pilha!",x);
          }
     break;
     case 4: 
          if (c==0)
             printf("A pilha nao foi criada!");
          else
          {
             Remover(P); //Removendo o último elemento da pilha
             printf("O elemento do topo da pilha foi removido!\n");            
          }
     break;
     case 5: 
          if (c==0)
             printf("A pilha nao foi criada!");
          else
          {
             int x;
             printf("Digite o numero a ser buscado:\n");
             scanf("%d",&x);
             Verifica(x,P); //Buscando um elemento na pilha
          }
     break;
     case 6: 
          if (c==0)
              printf("A pilha nao foi criada!");
          else if (Vazia(P))
              printf("A pilha esta vazia!");
          else
          {
              printf("A pilha e:\n\n");
              Imprime(P); //Imprimindo a pilha
          }
     break;
     default: 
          system("cls");
          menu(P);   
  }
  getch();
  system("cls");
  menu(P);
}  
      
int main() 
{
   TipoPilha *p;//Definindo a pilha usada no programa
   menu(p); //Chamando o menu
}
