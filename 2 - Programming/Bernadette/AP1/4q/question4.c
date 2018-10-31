/*Alunos: Cícero Cavalcante de Araújo
          Murilo Lima de Holanda            */
//     1ª AP - QUESTÂO 04
#include "4q.h" //Arquivo de cabeçalho que contém as funções da estrutura

char str[30];//String para a expressão principal
char c;//Variável que simula o resultado de uma expressão
int inv=0;//Variável de verifição para caractere inválidos na expressão
int i=0;//Índice para as variáveis temporárias
char reg;//Variável para o registrador

//Função que coloca o conteúdo da variável no registrador
char lq(char x)
{
     reg = x;
     if (x!='\0')//Caso queiramos alocar um operando fixo
        printf("\nLQ  %c",x);
     else //Caso queiramos alocar um operando temporário
        printf("\nLQ  Temp%d",i-1);
}

//Função que coloca o conteúdo do registrador na variável
//OBS: As únicas variáveis que recebem conteúdo do registrador são as variáveis temporárias
char st()
{
     printf("\nST  Temp%d",i);
}

//Função que imprime a linha correspondente à uma operação nas instruções
void operacao(char a,char ope,char b)
{
    switch(ope)
    {
       case'+'://No caso de um operador '+', imprime uma adição
           if (b!='\0')
              printf("\nAD  %c",b);
           else
              printf("\nAD  Temp%d",i);
       break;
       case'-'://No caso de um operador '-', imprime uma subtração
           if (b!='\0')
              printf("\nSB  %c",b);
           else
              printf("\nSB  Temp%d",i);
       break;
       case'*'://No caso de um operador '*', imprime uma multiplicação
           if (b!='\0')
              printf("\nML  %c",b);
           else
              printf("\nML  Temp%d",i);
       break;
       case'/'://No caso de um operador '/', imprime uma divisão
           if (b!='\0')
              printf("\nDV  %c",b);
           else
              printf("\nDV  Temp%d",i);
       break;
    }
}

int main ()
{
  printf("Digite a expressao:\n");
  scanf("%s",str);//Pede a expressão
  printf("\n\nInstrucoes:\n");
  Plhe *pn,*po;//Definindo a pilha dos operandos e dos operdadores
  pn = plhe_cria();//Criando a pilha dos operandos
  po = plhe_cria();//Criando a pilha dos operadores
  int k;
  for (k=0;(str[k] != '\0');k++)//Vai percorrer a string que representa a expressão
  {
    switch (str[k])
    {
      //Caso o caracter seja um operador
      case '-':
      case '+':
      case '*':
      case '/':
          plhe_ins(po,(str[k]));//Insere o operador na pilha dos operadores
          lq(pn->vet[pn->topo-2]);//Aloca o penúltimo operando no registrador
          //Faz a operação usando o operador e os dois últimos operandos
          operacao(reg , po->vet[po->topo-1] , pn->vet[pn->topo-1]);
          i++;//Icrementa a variável para o índice da variável temporária
          st();//Imprime a instrução de que o resultado é passado para a variável temporária
          plhe_rem(pn);//Remove um dos operandos usados na operação da pilha dos operandos
          plhe_rem(po);//Remove o operador usado na operação da pilha dos operadores
          plhe_rem(pn);//Remove um dos operandos usados na operação da pilha dos operandos
          plhe_ins(pn,c);//Insere na pilha dos operadores a variável que simula o resultado
       break;
       //Caso o caracter seja um operando válido
       case 'A':
       case 'B':
       case 'C':
       case 'D':
       case 'E':
       case 'F':
       case 'G':
       case 'H':
       case 'I':
       case 'J':
       case 'K':
       case 'L':
       case 'M':
       case 'N':
       case 'O':
       case 'P':
       case 'Q':
       case 'R':
       case 'S':
       case 'T':
       case 'U':
       case 'V':
       case 'X':
       case 'Y':
       case 'W':
       case 'Z':
          plhe_ins(pn,str[k]);//Insere o operando na pilha dos operandos
       break;
       default: inv++;//Incrementa a variável caso haja caracter inválido
    }
  }
  if (inv!=0)//Não mostra instruções caso haja caracter inválido
  {
     system("clear");
     printf("Existe um caracter invalido na expressao!");
  }
  return(0);
}
