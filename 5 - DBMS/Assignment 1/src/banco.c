/*
banco.c
Funções de leitura dos arquivos, fazendo a iteracao entre banco e a aplicacao 
*/

#include "banco.h"

//Seleciona rids de um indice atraves de uma clausula dada
TipoLista* selecao(char tabela[12], char* atributo, int n_atributo, int operacao, void* valor)
{
   int i,j,n_paginas,n_folhas,altura,n_bytes,rid,valori,flag,n_no,is_string;
   char valors[30];
   char aindice[50];
   FILE *findice;
   TipoLista *C;   
   
   C = crialista();

   strcpy(aindice,"bd/indices/");
   strcat(aindice,tabela);
   strcat(aindice,"/");
   strcat(aindice,atributo);
   strcat(aindice,".txt");
   findice = fopen(aindice,"r");//Abre o arquivo do indice
   
   fscanf(findice,"%d",&n_paginas);
   fscanf(findice,"%d",&n_folhas);
   fscanf(findice,"%d",&altura);
   fscanf(findice,"%d",&n_bytes);

   if (n_atributo == 2)//Atributos string
      is_string = 1;
   else
      is_string = 0;  

   for(i=0;i<=altura;i++)
   {
      fscanf(findice,"%d",&flag);//Verifica se a tupla lida é uma folha
      fscanf(findice,"%d",&n_no);
      if (is_string == 1)
         fscanf(findice,"%s",valors);   	 
      else
         fscanf(findice,"%d",&valori);
      fscanf(findice,"%d",&rid);
      /*
      if(is_string == 1)
        printf("\n%d    %d    %d   %s >=  %s  =   %d\n",flag,n_no,rid,valors,valor,(strcmp(valors,valor)>=0));
      else
        printf("\n%d    %d    %d   %d >=  %d  =   %d\n",flag,n_no,rid,valori,valor,((int*)valori >= (int*)valor));  
      */
      if (i<altura)//Se o no lido nao for uma folha
      {
         if(((is_string == 1) && (strcmp(valors,valor)>=0)) || ((is_string == 0) && ((int*)valori >= (int*)valor)))
            fseek(findice,((n_no - 1)*n_bytes),SEEK_CUR);//Salta para o filho esquerdo do nó no arquivo
         else
            fseek(findice,((n_no)*n_bytes),SEEK_CUR);//Salta para o filho direito do nó no arquivo
      }
      else//Se o no lido for uma folha
      {
         if (flag == 1)//Caso a busca chegue um um no "nao-folha",aponta para a ultima folha da arvore
         { 
           fseek(findice,-(n_bytes),SEEK_END);
           fscanf(findice,"%d",&flag);
      	   fscanf(findice,"%d",&n_no);
      	   if (is_string == 1)
             fscanf(findice,"%s",valors);   	 
           else
             fscanf(findice,"%d",&valori);
           fscanf(findice,"%d",&rid);
         }
         switch(operacao)
   	 {
       	   case 1:// Operacao '=': A partir da pagina selecionada, seleciona as paginas sequentes ate encontrar uma que tenha valor diferente 
              while(((is_string == 1) && (strcmp(valors,valor) == 0)) || ((is_string == 0) && ((int*)valori == (int*)valor)))
              {
                 Inserir_ord(rid,C);  
                 if(n_no!= n_paginas)
                 {
                    fscanf(findice,"%d",&flag);
                    fscanf(findice,"%d",&n_no);
                    if (is_string == 1)
                       fscanf(findice,"%s",valors);
                    else
                       fscanf(findice,"%d",&valori);   	 
                    fscanf(findice,"%d",&rid);
                 }
                 else
                    break;                    
              }                 
           break;
           case 2:// Operacao '!=': A partir da primeira folha, recupera as tuplas que tem valor diferente
              fseek(findice,-(n_folhas*n_bytes),SEEK_END);
              do
              {
                  fscanf(findice,"%d",&flag);
                  fscanf(findice,"%d",&n_no);
                  if (is_string == 1)
                     fscanf(findice,"%s",valors);
                  else
                     fscanf(findice,"%d",&valori);   	     	 
                  fscanf(findice,"%d",&rid);
                  if (((is_string == 1) && (strcmp(valors,valor) != 0)) || ((is_string == 0) && ((int*)valori != (int*)valor))) 
                     Inserir_ord(rid,C);
              }while(((is_string == 1) && (n_no < n_paginas)) ||((is_string == 0) && (n_no < n_paginas)));                 
           break;
           case 3:// Operacao '>': A partir da pagina escolhida, salta as tuplas de valor igual e recupera as de valor maior
              while(((is_string == 1) && (strcmp(valors,valor) == 0)) || ((is_string == 0) && ((int*)valori == (int*)valor)))
              {
                 fscanf(findice,"%d",&flag);
                 fscanf(findice,"%d",&n_no);
                 if (is_string == 1)
                    fscanf(findice,"%s",valors); 
                 else
                    fscanf(findice,"%d",&valori);  	 
                 fscanf(findice,"%d",&rid);
              }
              while(n_no <= n_paginas)
              {
                 if(((is_string == 1) && (strcmp(valors,valor) > 0)) || ((is_string == 0) && ((int*)valori > (int*)valor)))
                   Inserir_ord(rid,C);
                 if(n_no != n_paginas)
                 {
                   fscanf(findice,"%d",&flag);
                   fscanf(findice,"%d",&n_no);
                   if ((is_string == 1))
                      fscanf(findice,"%s",valors);
                   else
                      fscanf(findice,"%d",&valori);   	 
                   fscanf(findice,"%d",&rid);
                 }
                 else
                   break;
              }
           break;
           case 4:// Operacao '<': A partir da primeira folha, seleciona as sequentes ate achar uma que nao tenha valor igual
              fseek(findice,-(n_folhas*n_bytes),SEEK_END);
              for(j=1;j<=n_folhas;j++)
              {
                 fscanf(findice,"%d",&flag);
                 fscanf(findice,"%d",&n_no);
                 if (is_string == 1)
                    fscanf(findice,"%s",valors);
                 else
                    fscanf(findice,"%d",&valori);                          	 
                 fscanf(findice,"%d",&rid);
                 if (((is_string == 1) && (strcmp(valors,valor) < 0)) || ((is_string == 0) && ((int*)valori < (int*)valor))) 
                    Inserir_ord(rid,C);
                 else
                    break; 
              }
           break;
         }
         return C;  
     }
   }  
}

//Faz a intersecao de dois conjuntos de rids
TipoLista* intersecao(TipoLista *A, TipoLista *B)
{
   TipoLista *R;  
   R = crialista();
   celula *auxA;
   celula *auxB;
   FILE *saida;
 
   auxA = A->primeiro->prox;
   auxB = B->primeiro->prox;
   while ((auxA!=NULL) && (auxB!=NULL))//Faz a intersecao 
   {     
        if(auxA->rid == auxB->rid)
        {
          Inserir(auxA->rid,R);
          auxA=auxA->prox;
          auxB=auxB->prox;
        }
        else if (auxA->rid > auxB->rid)
          auxB=auxB->prox;
        else
          auxA=auxA->prox;
   }
   
   saida = fopen("saida.txt","a");
   fprintf(saida,"---------------------------------------------- INTERSECAO ------------------------------------------------\n\n");
   fprintf(saida,"Conjunto de RIDS obtido pela clausula 1:\n\n\t");
   fclose(saida);
   ImprimeLista(A);
   saida = fopen("saida.txt","a");
   fprintf(saida,"\n\nConjunto de RIDS obtido pela clausula 2:\n\n\t");
   fclose(saida);
   ImprimeLista(B);
   saida = fopen("saida.txt","a");
   fprintf(saida,"\n\nIntersecao:\n\n\t");
   fclose(saida);
   ImprimeLista(R);
   saida = fopen("saida.txt","a");
   fprintf(saida,"\n\n");
   fclose(saida);
   
   return R;
}

//A partir de um conjnto de rids, busca e mostra o resultado
TipoLista* resultado(TipoLista *R, char tabela[12])
{
   int i,num_tuplas,num_attr;
   char tarq[20];
   FILE *arquivo;
   FILE *saida;   
   
   char attr1[20];
   char attr2[20];
   char attr3[20];
   char attr4[20];   
   
   int at1,at3,at4;
   char at2[35];  
  
   strcpy(tarq,"bd/");
   strcat(tarq,tabela);
   strcat(tarq,".txt");
   arquivo = fopen(tarq,"r");//Abre o arquivo da tabela selecionada
   saida = fopen("saida.txt","a");
   fprintf(saida,"----------------------------------------------- RESULTADO ------------------------------------------------\n\n");
   
   fscanf(arquivo,"%d",&num_tuplas);
   fscanf(arquivo,"%d",&num_attr);
   fscanf(arquivo,"%s",attr1);
   fscanf(arquivo,"%s",attr2);
   fscanf(arquivo,"%s",attr3);
   if (num_attr > 3) fscanf(arquivo,"%s",attr4);

   fprintf(saida,"|%10s",attr1);
   fprintf(saida,"|%30s",attr2);
   fprintf(saida,"|%10s",attr3);
   if (num_attr > 3) fprintf(saida,"|%10s",attr4);
   fprintf(saida,"|\n");

   for(i=1;i<=num_tuplas;i++)//Busca as tuplas que satisfazem a selecao  
   {
       fscanf(arquivo,"%d",&at1);
       fscanf(arquivo,"%s",at2);
       fscanf(arquivo,"%d",&at3);
       if (num_attr > 3) fscanf(arquivo,"%d",&at4);
       if (Buscar(at1,R)==1)//Busca o rid da tupla dentro do conjunto de rids
       {
           fprintf(saida,"|%10d",at1);
           fprintf(saida,"|%30s",at2);
           fprintf(saida,"|%10d",at3);
           if (num_attr > 3) fprintf(saida,"|%10d",at4);
           fprintf(saida,"|\n");
           Remover(at1,R);//Remove o rid ja selecionado            
       }       
   }
   fclose(saida);    
}
