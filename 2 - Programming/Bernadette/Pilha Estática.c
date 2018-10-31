/*Alunos: Cícero Cavalcante de Araújo
          Murilo Lima de Holanda            */
//     PILHA ESTÀTICA
#include <stdio.h> 
#include <conio.h> 
#include <stdlib.h>
#define MaxTam 100
int c=0; //Variável que indica se a pilha foi criada
struct pilha      //Definindo a estrutura pilha
{
    int topo; 
    int vet[MaxTam]; 
};

typedef struct pilha Pilha;

Pilha* PilhaCria() //Cria a pilha
{
    Pilha* p = (Pilha*) malloc(sizeof(Pilha));
    p->topo = 0;
    return(p);
}

int Vazia (Pilha *Pilha) //Verifica se a pilha está vazia
{
    return (Pilha->topo == 0);
}

void Inserir (Pilha *Pilha, int x) //Insere um elemento na pilha
{                                
    if (Pilha->topo == MaxTam)      //Compara o último elemento com o tamanhao máximo da pilha        
       printf("Capacidade da pilha estourou!\n");
    else
    {
       Pilha->vet[Pilha->topo] = x;
       Pilha->topo++; 
    }
}

int Remover (Pilha *Pilha) //Remove o último elemento da pilha
{                        
    if (Vazia(Pilha))
       printf("Pilha vazia!\n");
    else
       Pilha->topo--;
}

int Verifica (int x , Pilha *Pilha) //Verifica se um elemento está na pilha
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

int Imprime (Pilha *Pilha) //Imprime a pilha
{
    int i;
    for (i=Pilha->topo-1;i>=0;i--)
      printf("   %d\n\n",Pilha->vet[i]);
}

int menu(Pilha *P) //Menu principal do programa
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
          exit(1); //Sai do menu
     break;
     case 1: 
          P=PilhaCria(); //Criando a pilha
          c++;
          printf("Pilha criada!");
     break;
     case 2: 
          if (c==0)
            printf("A pilha nao foi criada!");
          else if (Vazia(P)) //Verificando se a pilha está vazia
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
             printf("Digite numero a ser adicionado na pilha\n");
             scanf("%d",&x);
             Inserir(P,x); //Inserindo um elemento na pilha
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
             Imprime(P); //Imprimindo os elementos da pilha
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
   Pilha *p; //Definindo a pilha usada no programa
   menu(p); //Chamando o menu
}
