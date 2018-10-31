/*Alunos: Cícero Cavalcante de Araújo
          Murilo Lima de Holanda            */
//     LISTA DINÂMICA ORDENADA
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
int c=0;  //Variável incrementada quando a lista é criada
typedef int TipoT;  //Definindo o tipo de conteúdo da lista dinâmica
typedef struct cel  //Definindo a estrutura célula, que formará a lista
{
    TipoT conteudo;
    struct cel *prox;
}celula;

typedef struct     //Definindo a estrutura da Lista Dinâmica
{
    celula *primeiro,*ultimo;
}TipoLista;

TipoLista* crialista() //Cria a lista
{
    TipoLista* Lista = (TipoLista*) malloc(sizeof(TipoLista));
    Lista->primeiro=(celula*) malloc(sizeof(celula));
    Lista->ultimo=(celula*) malloc(sizeof(celula));
    Lista->ultimo->prox=NULL; //Anula a célula seguinte à célula do último elemento
    Lista->primeiro=Lista->ultimo;
    return(Lista);
}
     
int vazia(TipoLista *Lista) //Verifica se a lista está vazia
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
       Lista->ultimo=Lista->ultimo->prox;//Abrindo um espaço vazio na lista
       Lista->ultimo->prox=NULL;
       int z; //Variável que guarda o elemento da posição que receberá o elemento dado
       celula *aux;
       aux=Lista->primeiro->prox;
       /*Agora o programa colocará o elemento na posição correta, guardando o
         o elemento que estava nesta posição e colocando no seguinte, até
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

void Remover(int x, TipoLista *Lista)//Remove da lista todos os elementos iguais ao conteúdo dado
{
    int vf=0;//Variável incrementada quando algum elemento for removido
    int p=0; //Variável que receberá o número de elementos da lista
    celula *aux,*ax,*ant,*pos;//Células auxiliares no processo de remoção
    aux=Lista->primeiro->prox;
    while (aux!=NULL) //Contador para o número de elementos da célula
    {
       p++;  
       aux=aux->prox; 
    }
    /*O número de vezes que será feito o processo será igual ao número de elementos
      na lista, garantindo assim com que todos elementos de conteúdo igual ao 
      conteúdo que deseja-se remover sejam removidos        */
    for (int i=0;i<=p;i++)
    {
       aux=Lista->primeiro;
       while (aux->prox!=NULL)//Fará a verificação do início ao fim da lista 
       {
          //Começa quando encontra um elemento igual ao que deseja-se retirar
          if (aux->prox->conteudo==x)
          {
             /*Se o elemento que deseja-se retirar estiver na última posição da 
               lista faz a célula anterior à que guarda o elemento apontar
               para a célula que finaliza a lista */
             if (aux->prox->prox==NULL)
             {
                /*Zera a lista caso o elemento que deseja-se retirar seja o único
                  elemento da lista */
                if (aux->prox==Lista->primeiro->prox) 
                    Lista->primeiro=Lista->ultimo;
                else
                /*Se o elemento que deseja-se retirar for o último, mas não o
                  único elemento da lista, remove o mesmo     */
                    while (aux->prox->conteudo==x)
                    {
                        aux->prox->conteudo=aux->conteudo;
                        ax=Lista->primeiro;
                        while (ax->prox->conteudo < aux->conteudo)     
                            ax=ax->prox;     
                        ax->prox=aux->prox;
                    }
             }
             /*Se o elemento que deseja-se retirar não estiver na última posição 
               da lista, faz a célula anterior à que guarda o elemento apontar
               para a próxima   */
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
    //Avisa se o conteúdo pedido não existir na lista
    if (vf==0)
         printf("\nO elemento %d nao esta na lista!",x);
    else
         printf("\nO elemento %d foi removido da lista!",x);
}

int VerifElemento(int x, TipoLista *Lista)//Verifica se o elemento está na lista
{
    int pos=0;//Variável para a posição do elemento
    int vf=0; //Variável incrementada se o elemento estiver na lista
    celula *aux;
    aux=Lista->primeiro->prox;
    //Percorre toda a lista em busca do elemento
    while (aux!=NULL) 
    {    
       if (aux->conteudo==x)//Se o elemento for encontrado, dá sua posição
       {
         printf("\nO numero %d esta na posicao %d da lista.",x,pos);
         vf++;
       } 
       pos++;
       aux=aux->prox;
    }       
    if (vf==0)//Se o elemento não for encontrado, avisa que ele não está na lista
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
  int n;//Variável para a opção do menu
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
          c++;//Incrementando a variável que desbloqueia as outras funções
          printf("Lista criada!");
     break;
     case 2:
          if (c==0)
            printf("A lista nao foi criada!");
          else if (vazia(Lista))//Verificando se a lista está vazia
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
            Inserir(x,Lista);//Inserindo o número digitado na lista 
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
            VerifElemento(x,Lista);//Verificando se o elemento digitado está na lista
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
