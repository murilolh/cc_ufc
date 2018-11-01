//**************************************************************
//                                                             *
// Implementação de Seleção usando Interseção de rids          *
// Sistemas de Gerenciamento de Bancos de Dados 2009.1         *
// Cícero Antônio Cavalcante de Araújo             Mat:0286731 *
// Joaquim Carneiro de Azevedo Neto                Mat:------- *
// Leandro Monteiro Guimarães                      Mat:0286756 *
// Murilo Lima de Holanda                          Mat:0286740 *
//                                                             *
//**************************************************************

#include "banco.h"//Funções de leitura dos arquivos, fazendo a iteracao entre banco e a aplicacao 

int main()
{
   int i,j,ERR1,ERR2,ERR3,tabela, num_tuplas, num_attr;
   int atributo[2],operacao[2],valori[2];
   char valors1[30];
   char valors2[30];
   FILE *saida;
   
   void* valor[2];
   char* atrib[2];
   char tab[12];   

   TipoLista *A;
   TipoLista *B;
   TipoLista *R;
   
   FILE *arquivo;
   char *nomes[] = {"QUEIJO","LEITE","PAIS"};
   char arq[20];
   
   char attr1[20];
   char attr2[20];
   char attr3[20];
   char attr4[20];  
   
   char op[4]; 
   op[0]= '=';
   op[1]= '!';
   op[2]= '>';
   op[3]= '<';
   
   ERR1=0;
   do//Escolha da tabela
   {
     system("clear");
     printf("------------- INTERSECAO DE RIDS -------------\n");
     printf("Em qual tabela deseja fazer a selecao:\n");
     for(i=1;i<=3;i++)
        printf("%d - %s\n",i,nomes[i-1]);
     printf("\n0 - Sair\n");
     scanf("%d",&tabela);
     if (tabela == 0) 
        exit(0);
     else if ((tabela<0) || (tabela>3))
        ERR1=1;
     else
     {
        ERR1=0;
        strcpy(tab,nomes[tabela-1]);
        strcpy(arq,"bd/");
        strcat(arq,tab);
        strcat(arq,".txt");        
     }
   }while(ERR1==1);

   //Entra no arquivo da tabela escolhida
   arquivo = fopen(arq, "r");
   fscanf(arquivo,"%d",&num_tuplas);
   fscanf(arquivo,"%d",&num_attr);
   fscanf(arquivo,"%s",attr1);
   fscanf(arquivo,"%s",attr2);
   fscanf(arquivo,"%s",attr3);
   if (num_attr > 3) fscanf(arquivo,"%s",attr4);   
   
   system("clear");
   for(i=1;i<=2;i++)//Escolha das clausulas da selecao
   {
        ERR1=ERR2=ERR3=0;
        do 
        {
           if((ERR1 == 1) || (ERR2 == 1) || (ERR3 == 1)) printf("Erro na leitura da clausula %d\n",i);
           printf("----------------------------------------------\n");
           printf("Qual o atributo da %d clausula da selecao:\n",i);
   	   printf("1 - %s\n",attr1);
   	   printf("2 - %s\n",attr2);
   	   printf("3 - %s\n",attr3);
   	   if (num_attr > 3) printf("4 - %s\n",attr4);
   	   scanf("%d",&atributo[i-1]);
           if((atributo[i-1] < 1) || (atributo[i-1] > num_attr)) 
              ERR1 = 1;
           else
           { 
              ERR1 = 0;
              printf("----------------------------------------------\n");
   	      printf("Qual a operacao da clausula %d da selecao:\n",i);
              for(j=0;j<=3;j++)
              {
   	         printf("%d - %c",j+1,op[j]);
                 if (j==1) printf("%c",op[0]);
                 printf("\n");
              }              
   	      scanf("%d",&operacao[i-1]);
              if((operacao[i-1] < 1) || (operacao[i-1] > 4))
                ERR2 = 1;
              else
              {
                 ERR2 = 0;
   	         printf("----------------------------------------------\n");
    	         printf("Qual o valor da clausula %d da selecao:\n",i);
   	         if (atributo[i-1] == 2)//Atributos string
                   if(i==1)   	 
   	              scanf("%s",valors1);
                   else
                      scanf("%s",valors2);
   	         else
                 {
   	           scanf("%d",&valori[i-1]);
                   if (valori[i-1] < 0)
                      ERR3 = 1;
                   else
                      ERR3 = 0;
                 }                  
              }
            }
            system("clear");
        }while((ERR1 == 1) || (ERR2 == 1) || (ERR3 == 1));        
   }

   //Nesse momento temos todos os dados da consulta
   saida = fopen("saida.txt","w");
   fprintf(saida,"------------------------------------------------- SQL ----------------------------------------------------\n");
   fprintf(saida,"     SELECT *\n     FROM %s\n     WHERE ",tab);
   for(i=1;i<=2;i++)
   {
      switch(atributo[i-1])
      {
        case 1:
           atrib[i-1]=(char*)&attr1;
        break;
        case 2:
           atrib[i-1]=(char*)&attr2;
        break;
        case 3:
           atrib[i-1]=(char*)&attr3;
        break;
        case 4:
           atrib[i-1]=(char*)&attr4;
        break;    
      }
      fprintf(saida,"%s %c",atrib[i-1],op[operacao[i-1]-1]);
      if (operacao[i-1] == 2) fprintf(saida,"%c",op[0]);
      if (atributo[i-1] == 2)//Atributos string
      {
         if(i==1)   	 
   	   valor[i-1] = &valors1;
         else
           valor[i-1] = &valors2;   	 
   	 fprintf(saida," '%s'",valor[i-1]);
      }
      else
      {
         valor[i-1] = (int*)valori[i-1];   	 
   	 fprintf(saida," %d",valor[i-1]);
      }   	 
      if (i==1)
   	 fprintf(saida," AND\n           ");
      else
   	 fprintf(saida,"\n\n");
   }
   fclose(saida);
   
   A=crialista();//Sub-conjunto de rids obtido pela primeira consulta
   B=crialista();//Sub-conjunto de rids obtido pela segunda consulta
   R=crialista();//Sub-conjunto de rids obtido pela intersecao
   
   A = selecao(tab,atrib[0],atributo[0],operacao[0],valor[0]);//Obtem o conjunto de rids da primeira selecao
   B = selecao(tab,atrib[1],atributo[1],operacao[1],valor[1]);//Obtem o conjunto de rids da segunda selecao
   R = intersecao(A,B);//Faz a intersecao
   resultado(R,tab);//Recupera e escreve o resultado em arquivo
   printf("Arquivo saida.txt gerado com sucesso!\n");
}
