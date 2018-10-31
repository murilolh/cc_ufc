//Aluno: Murilo Lima de Holanda  Mat: 0286740
//     CALCULADORA PARENTIZADA
//Calcula o resultado de express�o dada nos par�meteros
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define N 50 //N�mero m�ximo de elementos na pilha
float c;     //Vari�vel que receber� o resultado das express�es
int i;
int inv=0;   //Vari�vel incrementada em caso de caracter inv�lido
struct pilha //Definindo a estrutura pilha
{
    int x;
    char nome;
    float vet[N];
};

typedef struct pilha Pilha;

Pilha* pilha_cria(char m) //Fun��o que cria uma pilha vazia
{
    Pilha* p = (Pilha*) malloc(sizeof(Pilha));
    p->x = 0;
    p->nome = m;
    return(p);
}

void pilha_push (Pilha*p, float v) //Fun��o que coloca um elemento na pilha
{
    if (p->x == N)
    {
             printf("Capacidade da pilha estourou.\n");
             exit(1);
     }
     p->vet[p->x]=v;
     p->x++;
}

int pilha_pop (Pilha* p) //Fun��o que retira um elemento da pilha
{
     float v;
     v = p->vet[p->x-1];
     p->x--;
     return (0);
}

//Fun��o que far� a opera��o e retornar� o resultado
void operador(float a,char ope,float b)
{
    switch(ope)
    {
       case'+':
           c=a+b;
           break;
       case'-':
           c=a-b;
           break;
       case'*':
           c=a*b;
           break;
       case'/':
           c=a/b;
           break;
    }
}

int main (int argc, char *argv[])
{
    Pilha *pn,*po; //Definindo as pilhas
    pn = pilha_cria ('N');//Criando a pilha dos operandos
    po = pilha_cria ('O');//Criando a pilha dos operadores
    for (i=0;(argv[1][i] != '\0');i++)//L� a express�o at� o fim da mesma
    {
       switch (argv[1][i])//Testa o caracter
       {
           case '-':
           case '+':
           case '*':
           case '/':
                //Caso o caracter seja um operador, coloca o mesmo na pilha
                pilha_push(po,(argv[1][i]));
           case '(':
                break;
           case ')':
                break;
           case '0':
           case '1':
           case '2':
           case '3':
           case '4':
           case '5':
           case '6':
           case '7':
           case '8':
           case '9':
                /*Caso a sequencia de caracteres
                  forme um operando, coloca o mesmo na pilha   */
                pilha_push(pn,atoi((&argv[1][i])));
                while (isdigit(argv[1][i+1]))
                   i++;
                /*Quando houver um ")" ele executa a opera��o anterior com
                os dois operandos anterires */
                while ((argv[1][i+1])==')')
                {
                   operador(pn->vet[pn->x-2],po->vet[po->x-1],pn->vet[pn->x-1]);
                   pilha_pop(pn);
                   pilha_pop(po);
                   pilha_pop(pn);
                   pilha_push(pn,c);
                   i++;
                }
             break;
             default: inv++;
       }
    }
    /*  S� d� o resultado da express�o se n�o existirem caracteres inv�lidos
      na mesma   */
    if (inv==0)
       printf("O resultado da expressao e:\n\n%0.3f\n",c);
    else
       printf("Existe um caracter invalido na expressao!\n");
    return(0);
}
