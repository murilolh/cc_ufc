/*Alunos: Cícero Cavalcante de Araújo
          Murilo Lima de Holanda            */
//     1ª AP - QUESTÂO 01

#include "1q.h"//Arquivo de cabeçalho que contém as funções da estrutura

char str[50];//String usada no programa
Lstd *L1,*L2,*L3,*ax;//Listas dinâmicas usadas no programa
int c=0,pos,p;//Variáveis inteiras usadas no programa

//Função que converte a string(str) em uma lista(L1)
char strconvertlist(char s[50])
{
    L1=lstd_cria();//Cria a lista L1
    int i;
    for (i=0;s[i];i++)
       lstd_ins(s[i],L1);
}

//Função que converte uma lista em uma string
char listconvertstr(Lstd *l,char s[50])
{
    celula *aux;
    aux=l->primeiro->prox;
    int i=0;
    while (aux!=NULL)
    {
        s[i]=aux->conteudo;
        i++;
        aux=aux->prox;
    }
    s[i]='\0';//Fim da string
}

//Função que informa a localização da primeira ocorrênicia de uma string em outra
char strpos(Lstd *l, Lstd *i)
{
    celula *aux,*ax;
    aux=l->primeiro->prox;
    ax=i->primeiro->prox;
    pos=0;//Posição inicial de L1
    p=-1;//'p' é inicializada com o valor -1, que é o valor retornado caso L2 não esteja em L1
    int t=0;//Variável icrementada quando um caracterre de L2 é encontrado em L1
    while (aux!=NULL)
    {
       if (aux->conteudo==ax->conteudo) //Caso o caracter de L1 seja igual ao de L2
       {
          p=pos;//'p' recebe a posição desse caracter em L1
          t++;//A variável 't' é incrementada
          ax=ax->prox;//Salta-se para o próximo caracter de L2
          if (ax==NULL)//Se o próximo for NULL significa que a string L2 foi achada em L1
            break;
       }
       else //Caso o caracter de L1 não seja igual ao de L2
       {
          t=0;//'t' é zerado
          ax=i->primeiro->prox;//Volta-se para o primeiro caracter de L2
       }
       pos++;//Incrementa-se a posição em L1
       aux=aux->prox;//Salta-se para o próximo caracter de L1
    }
    p=p-(t-1);//'p' recebe a posição de início da primeira ocorrência de L2 em L1
    if(ax!=NULL)//Se L2 não for achada em L1
       p=-1;
    return(p);
}

//Função que imprime uma substring obtida a partir da posição 'i1' de L1 com tamanho 'i2'
char substr(Lstd *l, int i1, int i2)
{
    celula *aux;
    aux=l->primeiro->prox;
    pos=0;//Variável para a posição em L1
    p=0;//Variável para o número de caracteres impressos
    while (aux!=NULL)
    {
        if (pos==i1)//Se a posição em L1 for a posição pedida
        {
           while (p!=i2)//Vai imprimir os 'i2' elementos de L1 a partir da posição i1
           {
             printf("%c",aux->conteudo);
             aux=aux->prox;
             p++;
             pos++;
             if (aux==NULL)//Pára quando chega no fim de L1
               break;
           }
        }
        if (aux==NULL)//Pára quando chega no fim de L1
          break;
        aux=aux->prox;//Salta-se para o próximo caracter de L1
        pos++;
    }
    if (p==0)//Se 'p' permanecer como '0', significa que a posição 'i2' não foi encontrada em L1
    {
       system("clear");
       printf("Posicao invalida!");
    }
}

//Função que compara duas strings representadas por listas
char strcomp(Lstd *l, Lstd *i)
{
    celula *aux,*ax;
    aux=l->primeiro->prox;
    ax=i->primeiro->prox;
    p=0;//'p' é iniciada com '0'
    while (aux!=NULL) //Percorre L1
    {
       //Se L1 for maior que L2 ou o conteudo de L1 for diferente de L2
       if ((ax==NULL) || (aux->conteudo!=ax->conteudo))
       {
          p=1;//As strings são diferentes
          break;
       }
       else if (p==1)//Se elas forem diferentes não é nesessário continuar
          break;
       aux=aux->prox;
       ax=ax->prox;
    }
    if ((ax!=NULL)) //Se L2 for maior que L1, elas são diferentes
       p=1;
    return(p);
}

//Concatena duas listas em uma única lista L3
char strconcat(Lstd *l, Lstd *i)
{
    celula *aux,*ax;
    aux=l->primeiro->prox;
    ax=i->primeiro->prox;
    L3=lstd_cria();//Cria a lista L3
    while (aux!=NULL)
    {
        lstd_ins(aux->conteudo,L3);//Coloca os elementos de L1 em L3
        aux=aux->prox;
    }
    while (ax!=NULL)
    {
        lstd_ins(ax->conteudo,L3);//Coloca os elementos de L2 em L3
        ax=ax->prox;
    }
}

//Função que recebe uma lista e retorna a mesma invertida
char strinvert(Lstd *l)
{
    char aux[50];
    p=strlen(str);//Tamanho da string
    int x=p;
    int j=0;
    while (j!=x)//Coloca os elementos de 'str' em aux de forma invertida
    {
        aux[j]=str[p-1];
        p--;
        j++;
    }
    aux[j]='\0';//Fim da string
    strcpy(str,aux);//Copia a string 'aux' em 'str'
    strconvertlist(str);//Converte a string em uma lista
}

//Função que recebe uma lista e retorna a mesma ordenada pelo método da bolha
char strord(Lstd *l)
{
    int x;
    x=strlen(str);//Tamanho da string
    int lsup,bol,k;
    char aux;
    lsup=x-1;//'lsup' recebe a última posição da string
    while (lsup > 0)
    {
      bol=0;
      for (k=0;k<=lsup-1;k++)
      {
         if  (str[k]>str[k+1])
         {
            aux=str[k];
            str[k]=str[k+1];
            str[k+1]=aux;
            bol=k;
         }
      }
      lsup=bol;
    }
    str[x]='\0';//Fim da string
    strconvertlist(str);//Converte a string em uma lista
}

//Função que coloca numa nova lista os caracteres em comum entre L1 e L2
char strinters(Lstd *l, Lstd *i)
{
    celula *aux,*ax;
    aux=l->primeiro->prox;
    ax=i->primeiro->prox;
    L3=lstd_cria();//Cria a lista L3
    while (aux!=NULL)//Percorre L1
    {
       ax=i->primeiro->prox;
       while (ax!=NULL)//Percorre L2
       {
          if (aux->conteudo==ax->conteudo)//Verifica se os caracteres sao iguais
            if ((lstd_busc(aux->conteudo, L3))==0)//Nao coloca caracteres repetidos
              lstd_ins(aux->conteudo,L3);
          ax=ax->prox;
       }
       aux=aux->prox;
    }
}

int menu()//Função para o menu principal do programa
{
  int o;
  printf("Digite a rotina desejada:\n\n");
  printf("1- strconvertlist\n");
  printf("2- listconvertstr\n");
  printf("3- strpos\n");
  printf("4- substr\n");
  printf("5- strcomp\n");
  printf("6- strconcat\n");
  printf("7- strinvert\n");
  printf("8- strord\n");
  printf("9- strinters\n");
  printf("\n0- Sair\n\n");
  scanf("%d",&o);
  system("clear");
  switch(o)
  {
     case 0:
          exit(1);//Sai do programa
     break;
     case 1:
          printf("Digite a string a ser convertida em uma lista:\n");
          scanf("%s",str);
          strconvertlist(str);//Converte str em uma lista
          c++;//Somente depois que esta lista é criada que as outras rotinas podem ser feitas
          printf("\n\nA string foi convertida em uma lista!\n\n");
          printf("A lista e:\n");
          lstd_print(L1);//Imprime a lista
     break;
     case 2:
          if (c==0)
             printf("Nao existem elementos na lista!");
          else
          {
             listconvertstr(L1,str);//Converte a lista em uma string
             printf("A lista foi convertida em uma string!\n\n");
             printf("A string e:\n%s\n",str);//Imprime a string
          }
     break;
     case 3:
          if (c==0)
             printf("Nenhuma string criada!");
          else
          {
             printf("Digite a string L2 a ser comparada com L1:\n");
             scanf("%s",str);
             L2=L1;//L1 e L2 no momento são iguais
             strconvertlist(str);//Converte a string em L1
             ax=L1;//Troca-se L1 por L2
             L1=L2;
             L2=ax;
             listconvertstr(L1,str);
             printf("\n\nL1: %s",str);//Imprime a string L1
             if (strpos(L1,L2)==-1)//Caso L2 não ocorra em L1
                printf("\n\nA string L2 nao ocorre na string L1!");
             else
                printf("\n\n\nA primeira ocorrencia de L2 em L1 ocorre a partir da posicao %d!",p);
          }
     break;
     case 4:
          if (c==0)
             printf("Nenhuma string criada!");
          else
          {
             int P,T;
             printf("A partir de qual posicao deseja retirar uma substring de L1?\n");
             scanf("%d",&P);//Pede a posição
             printf("\nQual tamanho da substring?\n");
             scanf("%d",&T);//Pede o tamanho da substring
             listconvertstr(L1,str);
             printf("\n\nL1: %s",str);
             printf("\n\n\nA substring e:\n\n");
             substr(L1,P,T);//Imprime a substring
          }
     break;
     case 5:
          if (c==0)
             printf("Nenhuma string criada!");
          else
          {
             printf("Digite a string L2 a ser comparada com L1:\n");
             scanf("%s",str);
             L2=L1;
             strconvertlist(str);
             ax=L1;
             L1=L2;
             L2=ax;
             listconvertstr(L1,str);
             printf("\n\nL1: %s",str);
             if ((strcomp(L1,L2))==0)//Compara as duas listas
                printf("\n\n\nA duas strings sao iguais!");
             else
                printf("\n\n\nA duas strings sao diferentes!");
          }
     break;
     case 6:
          if (c==0)
             printf("Nenhuma string criada!");
          else
          {
             printf("Digite a string L2 a ser concatenada com L1:\n");
             scanf("%s",str);
             L2=L1;
             strconvertlist(str);
             ax=L1;
             L1=L2;
             L2=ax;
             strconcat(L1,L2);//Concatena L1 e L2 em uma nova lista L3
             listconvertstr(L1,str);
             printf("\n\nL1: %s",str);
             listconvertstr(L3,str);//Converte L3 em uma string
             printf("\n\nA nova string e:\n");
             printf("%s\n",str);//Imprime a string
          }
     break;
     case 7:
          if (c==0)
             printf("Nenhuma string criada!");
          else
          {
             listconvertstr(L1,str);
             printf("L1: %s",str);
             strinvert(L1);//Inverte a lista
             listconvertstr(L1,str);//Converte a lista em string
             printf("\n\n\n\nA string foi invertida!\n\n");
             printf("\nA string invertida e:\n%s",str);//Imprime a string
          }
     break;
     case 8:
          if (c==0)
             printf("Nenhuma string criada!");
          else
          {
             listconvertstr(L1,str);
             printf("L1: %s",str);
             strord(L1);//Ordena a lista
             listconvertstr(L1,str);//Converte a lista em string
             printf("\n\n\n\nA string foi ordenada!\n\n");
             printf("\nA string ordenada e:\n%s",str);//Imprime a string

          }
     break;
     case 9:
          if (c==0)
             printf("Nenhuma string criada!");
          else
          {
             printf("Digite a string L2:\n");
             scanf("%s",str);
             L2=L1;
             strconvertlist(str);
             ax=L1;
             L1=L2;
             L2=ax;
             listconvertstr(L1,str);
             printf("\n\nL1: %s",str);
             strinters(L1,L2);//Verifica caracteres iguais em L1 e L2
             if (lstd_vaz(L3))
                printf("\n\nNenhum caractere pertence a L1 e a L2!");
             else
             {
                printf("\n\nOs caracteres que estao em L1 e em L2 sao:\n");
                lstd_print(L3);//Imprime a lista que contem os caracteres em comum à L1 e à L2
             }
           }
     break;
     default:
          system("clear");
          menu();
  }
  system("clear");
  menu();
}

int main()
{
  menu();//Chama o menu
}
