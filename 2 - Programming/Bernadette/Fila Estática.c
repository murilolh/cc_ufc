/*Alunos: Cícero Cavalcante de Araújo
          Murilo Lima de Holanda            */
//     FILA ESTÀTICA
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define max 100
int c=0; //Variável que indica se a fila já foi criada ou não
int t; //Variável que conta o número de elementos da fila
typedef int TipoT; //Definindo o tipo de elementos da fila
typedef struct     //Definindo a estrutura fila
{
    TipoT item[max]; 
    int primeiro,ultimo; 
}TipoFila;

void Criafila(TipoFila *Fila) //Cria uma nova fila
{
    (Fila->ultimo)=(Fila->primeiro)=0;
}
     
int Vazia(TipoFila *Fila) //Verifica se a fila está vazia
{
    return ((Fila->ultimo)==(Fila->primeiro));
}

void Inserir(TipoT x,TipoFila *Fila) //Insere um elemento na fila
{
    if ((Fila->ultimo)>=max) //Caso a capacidade da fila seja igual à máxima
       printf("\n\nLista cheia!\n");
    else //Caso contrário,o elemento é adicionado na última posição da fila
    {
       Fila->item[Fila->ultimo]=x;
       Fila->ultimo++; //Incrementa o último elemento da fila
    }
}

void Remover(TipoFila *Fila) //Remove um elemento da fila
{
    if (Vazia(Fila)) //Se a fila estiver vazia, o programa indica e não faz nada até a fila ser criada
       printf("A lista esta vazia!");
    else
    {
        int i;
        for (i=0;i<=Fila->ultimo;i++)
           Fila->item[i]=Fila->item[i+1];
        Fila->ultimo--;
    }
}
  
int Verifica (int x , TipoFila *Fila) //Verifica se um elemento está na fila
{
    int vf=0;
    int pos=0;
    int i;
    for (i=0;i<=t-1;i++) //Percorrendo os elementos da fila
    {
      if (Fila->item[i] == x) //Caso o elemento esteja na fila
      {
         printf("\nO numero %d esta na posicao %d da fila.",x,pos);
         vf++;
      } 
      pos++;
    }
    if (vf==0) //Caso o elemento não esteja na fila
      printf("\nO elemento %d nao esta na fila!",x);
}
    
int Imprime(TipoFila *Fila) //Imprime a fila
{
    int i;
    for (i=(Fila->primeiro);i<(Fila->ultimo);i++)
       printf("%d ",Fila->item[i]);
}
    
int menu(TipoFila F) //Menu principal
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
          exit(1);//Saindo do programa
     break;
     case 1: 
          Criafila(&F); //Criando uma nova fila
          c++;
          t=0;
          printf("Fila criada!");
     break;
     case 2: 
          if (c==0)
            printf("A fila nao foi criada!");
          else if (Vazia(&F)) //Verificando se a fila está vazia
            printf("A fila esta vazia!");
          else 
            printf("A fila nao esta vazia!");
     break;
     case 3: 
          if (c==0)
            printf("A lista nao foi criada!");
          else
          {
            int x;
            printf("Digite o ultimo numero a ser adicionado\n");
            scanf("%d",&x);
            Inserir(x ,&F);//Inserindo um elemento na fila
            t++;
            printf("\nO numero %d foi adicionado!",x);
          }
     break;
     case 4: 
          if (c==0)
            printf("A fila nao foi criada!");
          else
          {
            Remover(&F);//Removendo o primeiro elemento da fila
            t--;
            printf("O primeiro elemento da fila foi removido!\n");            
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
            Verifica(x,&F);//Buscando um elemento na fila
          }
     break;
     case 6: 
          if (c==0)
            printf("A fila nao foi criada!");
          else if (Vazia(&F))
            printf("A fila esta vazia!");
          else
          {
             printf("A fila e:\n\n");
             Imprime(&F); //Imprimindo a fila
          }         
     break;
     default:
          system("cls");
          menu(F);   
  }
  getch();
  system("cls");
  menu(F);
}

int main() 
{
  TipoFila F; //Definindo a fila usada no programa
  menu(F); //Chamando o menu
}
