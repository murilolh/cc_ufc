/*
figuras.c
Funções de manipulação das estruturas de dados usadas e das figuras*/
#include "figuras.h"
#include <stdio.h>
#include <stdlib.h>
#include <cstring>//Biblioteca usada na manipulação de strings

//Cria uma lista vazia de termos genéricos
TipoLista* crialistatermos() 
{
    TipoLista* Lista = (TipoLista*) malloc(sizeof(TipoLista));
    Lista->primeiro = (celula*) malloc(sizeof(celula));
    Lista->primeiro->prox = NULL;
    return(Lista);
}

//Insere ordenadamente termos na lista de acordo com o critério de ordenação
void Inserir_ord(int f,char nome[10], char cor[10], float area, int tipo, TipoLista *Lista)
{
    celula *aux;
    celula *novo_noh;
    novo_noh = (celula*) malloc(sizeof(celula));
    strcpy(novo_noh->nome,nome);
    strcpy(novo_noh->cor,cor);
    novo_noh->area = area;
    novo_noh->tipo = tipo;
    novo_noh->prox=NULL;
    aux=Lista->primeiro;       
    if(aux->prox==NULL)
        Lista->primeiro->prox=novo_noh;
    else
    {
        while (aux->prox!=NULL) 
        {     
            if ((f==1 && (aux->prox->area >  novo_noh->area)) || (f==2 && (strcmp(aux->prox->nome,novo_noh->nome)>0)))
            {
                novo_noh->prox=aux->prox;
                aux->prox = novo_noh;      
                return;                             
            }
            aux=aux->prox;
        }
        aux->prox=novo_noh;
    }                
}

//Cria uma lista vazia de Círculos
ListaCir* criaCir()
{
    ListaCir* Lista = (ListaCir*) malloc(sizeof(ListaCir));
    Lista->primeiro = (Circulo*) malloc(sizeof(Circulo));
    Lista->primeiro = NULL;
    Lista->Area_total=0;    
    return(Lista);
}

//Cria uma lista vazia de Quadrados
ListaQuad* criaQuad()
{
    ListaQuad* Lista = (ListaQuad*) malloc(sizeof(ListaQuad));
    Lista->primeiro = (Quadrado*) malloc(sizeof(Quadrado));
    Lista->primeiro = NULL; 
    Lista->Area_total=0;
    return(Lista); 
}

//Cria uma lista vazia de Triângulos
ListaTri* criaTri()
{
    ListaTri* Lista = (ListaTri*) malloc(sizeof(ListaTri));
    Lista->primeiro = (Triangulo*) malloc(sizeof(Triangulo));
    Lista->primeiro = NULL; 
    Lista->Area_total=0; 
    return(Lista);   
}

//Cria uma estrutura com uma lista vazia de cada tipo de figura
Figura* crialista() 
{
    Figura* Lista = (Figura*) malloc(sizeof(Figura));
    Lista->circ = criaCir();
    Lista->quad = criaQuad();
    Lista->tri = criaTri();   
    return(Lista);
}

//Retorna o tipo de figura escolhido
int escolha_tipo()
{
    int o;
    system("clear");
    printf("Qual o tipo de figura?\n\n");
    printf("1 -Circulo\n");
    printf("2 -Quadrado\n");
    printf("3 -Triangulo\n");
    scanf("%d",&o);
    if (o>0 && o<4) 
      return o;
    else
      return escolha_tipo();
}

//Insere um círculo
void inserir_cir(Figura *fig, char nome[10], char cor[10], float raio)
{
    Circulo* novo_noh = (Circulo*)malloc(sizeof(Circulo));
    strcpy(novo_noh->nome,nome);
    strcpy(novo_noh->cor,cor);
    novo_noh->raio=raio;
    novo_noh->area=3.14*raio*raio;
    novo_noh->prox=fig->circ->primeiro;
    fig->circ->primeiro=novo_noh;
    fig->circ->Area_total=fig->circ->Area_total+novo_noh->area;
}

//Insere um quadrado
void inserir_quad(Figura *fig, char nome[10], char cor[10], float lado)
{
    Quadrado* novo_noh = (Quadrado*)malloc(sizeof(Quadrado));
    strcpy(novo_noh->nome,nome);
    strcpy(novo_noh->cor,cor);
    novo_noh->lado=lado;
    novo_noh->area=lado*lado;
    novo_noh->prox=fig->quad->primeiro;
    fig->quad->primeiro=novo_noh;
    fig->quad->Area_total=fig->quad->Area_total+novo_noh->area;
}

//Insere um triângulo
void inserir_tri(Figura *fig, char nome[10], char cor[10], float base, float altura)
{
    Triangulo* novo_noh = (Triangulo*)malloc(sizeof(Triangulo));
    strcpy(novo_noh->nome,nome);
    strcpy(novo_noh->cor,cor);
    novo_noh->base=base;
    novo_noh->altura=altura;
    novo_noh->area=(base*altura)/2;
    novo_noh->prox=fig->tri->primeiro;
    fig->tri->primeiro=novo_noh;
    fig->tri->Area_total=fig->tri->Area_total+novo_noh->area;
}

//Remove uma figura qualquer de acordo com o seu nome
int remover(Figura *fig, char nome[10])
{
    Circulo *aux_circ = fig->circ->primeiro;
    Quadrado *aux_quad = fig->quad->primeiro;    
    Triangulo *aux_tri  = fig->tri->primeiro;
    if (aux_circ != NULL)
    {
        if(strcmp(aux_circ->nome,nome)==0)
        {
           fig->circ->Area_total = fig->circ->Area_total - aux_circ->area;
           fig->circ->primeiro = fig->circ->primeiro->prox;
           return 1;          
        }
        else
        {    
     	   while(aux_circ->prox!=NULL)
   	   {
               if(strcmp(aux_circ->prox->nome,nome)==0)
       	       {
           	   fig->circ->Area_total = fig->circ->Area_total - aux_circ->prox->area;
          	   aux_circ->prox = aux_circ->prox->prox; 
                   return 1;           
               }
               aux_circ=aux_circ->prox;
           }
        }
    }
    if (aux_quad != NULL)
    {
        if(strcmp(aux_quad->nome,nome)==0)
        {
           fig->quad->Area_total = fig->quad->Area_total - aux_quad->area;
           fig->quad->primeiro = fig->quad->primeiro->prox;
           return 2;          
        }
        else
        {    
     	   while(aux_quad->prox!=NULL)
   	   {
               if(strcmp(aux_quad->prox->nome,nome)==0)
       	       {
           	   fig->quad->Area_total = fig->quad->Area_total - aux_quad->prox->area;
          	   aux_quad->prox = aux_quad->prox->prox; 
                   return 2;           
               }
               aux_quad=aux_quad->prox;
           }
        }
    }
    if (aux_tri != NULL)
    {
        if(strcmp(aux_tri->nome,nome)==0)
        {
           fig->tri->Area_total = fig->tri->Area_total - aux_tri->area;
           fig->tri->primeiro = fig->tri->primeiro->prox;
           return 3;          
        }
        else
        {    
     	   while(aux_tri->prox!=NULL)
   	   {
               if(strcmp(aux_tri->prox->nome,nome)==0)
       	       {
           	   fig->tri->Area_total = fig->tri->Area_total - aux_tri->prox->area;
          	   aux_tri->prox = aux_tri->prox->prox; 
                   return 3;           
               }
               aux_tri=aux_tri->prox;
           }
        }
    }    
    return 0;
}

//Lista todas as figuras
void listar(Figura *fig)
{
    Circulo *aux_circ = fig->circ->primeiro;
    Quadrado *aux_quad = fig->quad->primeiro;    
    Triangulo *aux_tri  = fig->tri->primeiro;
    system("clear");
    printf("       Circulos:\n");
    printf("Nome     Cor     Raio     Area\n");
    while (aux_circ!=NULL)
    {
        printf("\n%s  %s  %10.2f  %10.2f\n",aux_circ->nome,aux_circ->cor,aux_circ->raio,aux_circ->area);
        aux_circ=aux_circ->prox;
    }
    printf("\n\n       Quadrados:\n");
    printf("Nome     Cor     Lado     Area\n");
    while (aux_quad!=NULL)
    {
        printf("\n%s  %s  %10.2f  %10.2f\n",aux_quad->nome,aux_quad->cor,aux_quad->lado,aux_quad->area);
        aux_quad=aux_quad->prox;
    }
    printf("\n\n       Triangulos:\n");
    printf("Nome     Cor     Base     Altura     Area\n");
    while (aux_tri!=NULL)
    {
        printf("\n%s  %s  %10.2f  %10.2f  %10.2f\n",aux_tri->nome,aux_tri->cor,aux_tri->base,aux_tri->altura,aux_tri->area);
        aux_tri=aux_tri->prox;
    }    
}

//Ordena todos as figuras de acordo com o critério de ordenação em uma lista encadeada
TipoLista* listatermos(int f,Figura *fig)
{
   TipoLista *Lista;
   Lista = crialistatermos();
   Circulo *aux_circ = fig->circ->primeiro;
   Quadrado *aux_quad = fig->quad->primeiro;    
   Triangulo *aux_tri  = fig->tri->primeiro;
   while (aux_circ!=NULL)
   {
        Inserir_ord(f,aux_circ->nome, aux_circ->cor, aux_circ->area, 1, Lista);
        aux_circ=aux_circ->prox;        
   }
   while (aux_quad!=NULL)
   {
        Inserir_ord(f,aux_quad->nome, aux_quad->cor, aux_quad->area, 2, Lista);
        aux_quad=aux_quad->prox;
   }    
   while (aux_tri!=NULL)
   {
        Inserir_ord(f,aux_tri->nome, aux_tri->cor, aux_tri->area, 3, Lista);
        aux_tri=aux_tri->prox;
   }   
   return(Lista);     
}

//Imprime a lista de termos genéricos
void imprime_lista(TipoLista *Lista)
{
   celula *aux;
   aux = Lista->primeiro->prox;
   printf("Tipo     Nome     Cor     Area\n\n");
   while (aux!=NULL)
   {
        switch(aux->tipo)
        {
           case 1:
              printf("Circulo   ");
           break;
           case 2:
              printf("Quadrado   ");
           break;
           case 3:
              printf("Triangulo   ");
           break;
        }
        printf("%s   %s   %10.2f\n",aux->nome,aux->cor,aux->area);
        aux=aux->prox;
   }
   free(Lista);
}

//Ordena as figuras de acordo com o critério de ordenação
void ordenar(int f,Figura *fig)
{
   TipoLista *Lista;
   Lista = listatermos(f,fig);
   system("clear");
   if(f==1)
       printf("\n       Lista Ordenada por area:\n");
   else 	 
       printf("\n       Lista Ordenada por nome:\n");
   imprime_lista(Lista); 
}

//Retorna a área total das figuras
float area_total(Figura *fig)
{
    return(fig->circ->Area_total + fig->quad->Area_total + fig->tri->Area_total);
}

