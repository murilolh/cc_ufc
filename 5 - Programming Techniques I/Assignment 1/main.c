//**************************************************************
//                                                             *
// 1º Trabalho - Técnicas de Programação 2009.1                *
// Equipe:                                                     *
// Murilo Lima de Holanda(líder)                Mat:0286740    *
// Leandro Monteiro Guimarães                   Mat:0286756    *
// Leidiane Nascimento de Freitas               Mat:0272980    *
// Victor Pessoa de Azevedo Lia Fook            Mat:-------    *
//                                                             *
//**************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <cstring>//Biblioteca usada na manipulação de strings
#include "figuras.h"//Definição das estruruas e funções de manipulação das estruturas de dados usadas e das figuras

int funcao(Figura* fig);
int main();

int main()
{
    Figura* fig;
    fig = crialista();
    system("clear");
    funcao(fig);    
}

int funcao(Figura* fig)
{
    int o,t;
    char nome[10];
    char cor[10];
    float raio, lado, base, altura, a_total;
    printf("---------------------------------------------\n");      
    printf("O que deseja fazer?\n\n");
    printf("1 -Inserir figura\n");
    printf("2 -Remover figura\n");
    printf("3 -Listar figuras\n");
    printf("4 -Ordenar figuras por area\n");
    printf("5 -Ordenar figuras por nome\n");
    printf("6 -Imprimir area total\n");
    printf("0 -Sair\n");
    scanf("%d",&o);
    system("clear");
    switch(o)
    {
       case 0:
          exit(0);        
       break;
       case 1:
          t=escolha_tipo();
          system("clear");
          printf("Qual o nome da figura a ser inserida\n");
          scanf("%s",&nome);
          printf("\nQual o cor da figura a ser inserida\n");
          scanf("%s",&cor);
          switch(t)
          {
              case 1:
                printf("\nQual o raio do circulo a ser inserido\n");
                scanf("%f",&raio);  
                inserir_cir(fig,nome,cor,raio);
                system("clear");
                printf("O circulo %s foi inserido com sucesso!\n\n",fig->circ->primeiro->nome);
              break;         
              case 2:
                printf("\nQual o lado do quadrado a ser inserido\n");
                scanf("%f",&lado);   
                inserir_quad(fig,nome,cor,lado);
                system("clear");
                printf("O quadrado %s foi inserido com sucesso!\n\n",fig->quad->primeiro->nome);      
              break;
              case 3:
                printf("\nQual a base do triangulo a ser inserido\n");
                scanf("%f",&base); 
                printf("\nQual a altura do triangulo a ser inserido\n");
                scanf("%f",&altura);  
                inserir_tri(fig,nome,cor,base,altura);
                system("clear");
                printf("O triangulo %s foi inserido com sucesso!\n\n",fig->tri->primeiro->nome);
              break; 
          }
       break;
       case 2:
          int r;
          system("clear");
          printf("Qual o nome da figura a ser removida\n");
          scanf("%s",&nome);
          r = remover(fig,nome);
          switch(r)
          {
             case 0:
                   printf("\n\nNao existe figura com o nome %s!\n\n",nome);
             break; 
             case 1:
                   printf("\n\nO circulo de nome %s foi removido com sucesso!\n\n",nome);
             break;
             case 2:
                   printf("\n\nO quadrado de nome %s foi removido com sucesso!\n\n",nome);
             break;
             case 3:
                   printf("\n\nO triangulo de nome %s foi removido com sucesso!\n\n",nome);
             break;            
          }
       break;
       case 3:
          listar(fig);
       break;
       case 4:
          ordenar(1,fig);//O flag "1" indica a ordenação por área
       break;
       case 5:
          ordenar(2,fig);//O flag "2" indica a ordenação por nome
       break;
       case 6:
          system("clear");
          printf("A area total das figuras e: \n%10.2f\n\n",area_total(fig));
       break;
       default:
          system("clear");
          funcao(fig);   
    }
    funcao(fig);
}
