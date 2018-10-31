//Aluno: Murilo Lima de Holanda  Mat: 0286740
/*  O jogo da Torre de Han�i consiste em passar todos os discos colocados em
    ordem decrescente de tamanho em um pino de origem para um outro pino, o pino
    de destino, utilizando um terceiro pino, o pino trabalho. Um disco de cada
    vez � deslocado de um pino a outro, sendo que nunca um disco de tamanho
    maior ficar� sobre um disco de tamanho menor. */
/*  Este programa mostra o disco que tem que ser movido, os pinos de origem e
    destino deste disco no movimento e testa se o movimento � v�lido, ou seja,
    se o disco movido est� indo para cima de um disco de tamanho maior. */
#include <stdio.h>
#include <stdlib.h>
#define N 50       //N�mero m�ximo de discos nos pinos
int cont = 0;      //Contador para o n�mero de movimentos
struct pilha       //Estrutura pilha que usaremos para armazenar os discos
{
    int x;
    char nome;
    int vet[N];
};

typedef struct pilha Pilha;

//Fun��o que cria uma pilha. Neste programa criaremos 3 pilhas.
Pilha* pilha_cria(char m)
{
    Pilha* p = (Pilha*) malloc(sizeof(Pilha));
    p->x = 0;
    p->nome = m;
    return(p);
}

/* Fun��o que coloca um elemento na pilha. Este elemento vem de outra pilha
   atrav�s da fun��o pilha_pop. */
void pilha_push (Pilha *p, int v)
{
     if (p->x == N)
     {
              printf("Capacidade da pilha estourou.\n");
              exit(1);
      }
p->vet[p->x] = v;
p->x++;
}

//Fun��o usada para verificar se a pilha est� vazia.
int pilha_vazia (Pilha* p)
{
    return (p->x == 0);
}

/* Fun��o que tira um elemento da pilha. Este elemento vai para outra pilha
   atrav�s da fun��o pilha_push. */
int pilha_pop (Pilha* p)
{                        //
      int v;
      if (pilha_vazia(p))
      {
                         printf("Pilha vazia.\n");
                         exit(1);
                         }
v = p->vet[p->x-1];
p->x--;
return v;
      }

/* Fun��o que dir� a sequ�ncia de movimentos e os discos movidos
   e testar� se o movimento � v�lido.   */
void hanoi(int n, Pilha *pa, Pilha *pb, Pilha *pc)
{
  if (n>0)
  {
     hanoi(n-1, pa, pc, pb);
     if (!pilha_vazia(pb)) //Se o pino de destino n�o estiver vazio ele testa a
     {                     //validade do movimento.
        if (pb->vet[pb->x-1]<pa->vet[pa->x-1])
        printf("\nMOVIMENTO INVALIDO\n");
        }
     pilha_push(pb, pilha_pop(pa)); //Tira o disco de uma pilha e coloca em outra.
     printf("Move o disco %d de %c para %c\n",pb->vet[pb->x-1],pa->nome,pb->nome);
     cont++; //Contagem de movimentos.
     hanoi(n-1, pc, pb, pa);
  }
}

int main()
{
   int n,i;
   Pilha *pa,*pb,*pc;
   pa = pilha_cria ('A');//Cria uma pilha vazia e atribui a ela um nome.
   pb = pilha_cria ('B');
   pc = pilha_cria ('C');
   printf("Digite a quantidade de discos: ");
   scanf("%d",&n);
   printf("\n");
   for (i=n;i>=1;i--)
   {
       pilha_push(pa,i); //Adicionando o total de discos ao pino de origem.
   }
   hanoi(n, pa, pb, pc); //Acionando a fun��o hanoi.
   printf("\nA quantidade de movimentos e:\n%d\n",cont);
}
