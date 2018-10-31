#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void decbin(int d)
{
    int div,res,i,j;
    char bin[30], aux;
    i=j=0;
    while(d!=0)
    {
      if (d%2==1)
         bin[i]='1';
      else
         bin[i]='0';
      d=d/2;
      i++;
    }
    bin[i]= '\0';
    while(j<i)
    {
      aux=bin[j];
      bin[j]=bin[i-1];
      bin[i-1]=aux;
      j++;
      i--;
    }
    printf("%s",bin);
}

int bindec(char b[30])
{
    int tam, resp;
    tam=strlen(b);
    resp=0;
    if (b[tam-1]=='1')
        resp=resp+1;
    if ((tam -1) >=1)
    {
        b[tam-1]= '\0';
        resp= resp + 2*(bindec(b));
    }
    return resp;
}

int menu()
{
  int o,dec;
  char str[30];
  printf("Digite a opcao desejada:\n\n");
  printf("1- D -> B\n");
  printf("2- B -> D\n");
  printf("0- Sair\n\n");
  scanf("%d",&o);
  system("clear");
  switch(o)
  {
     case 0:
          exit(1);
     break;
     case 1:
          printf("Digite o numero decimal a ser convertido em binario:\n");
          scanf("%d",&dec);
          printf("\n\nO numero em binario e: ");
          decbin(dec);
     break;
     case 2:
          printf("Digite o numero binario a ser convertido em decimal:\n");
          scanf("%s",&str);
          int tam, i;
          tam=strlen(str);
          for (i=0;i<tam;i++)
              if (str[i]!='0' && str[i]!='1')
              {
                 printf("\n\nNumero invalido!!");
                 system("clear");
                 menu();
              }
          printf("\n\nO numero em decimal e: %d", bindec(str));
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
  menu();
}
