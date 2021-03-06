//**************************************************************
//                                                             *
// Implementação de Métodos de Autovalores e Autovetores       *
// Métodos Numéricos II 2009.1                                 *
// Murilo Lima de Holanda                          Mat:0286740 *
//                                                             *
// Método QR                                                   *
//                                                             *
//**************************************************************

#include "qr.h" //Arquivo com funções de leitura e escrita no arquivo, 
#include <stdio.h>   //de manipulacao de vetores e matrizes necessarias para o metodo QR
#include <stdlib.h>
#include <cmath>

int main(int argc, char *argv[])
{   
    int i,j,k;
    int d,t;//Variaveis inteiras para a dimensao da matriz e a tolerancia em numero de casas decimais
    float M[MAX][MAX];//Matriz principal
    float X[MAX][MAX];//Matriz de resultante do Metodo QR que guarda os autovetores
    float dados[2];//Vetor que guarda a dimensao da matriz e a tolerancia
    float E;//Tolerancia 
    FILE *fd;

    system("clear");
    if (argc<2)
    {
        printf("Voce deve digitar um parametro!\n\n");
        exit(1);
    }
    fd = fopen(argv[1], "r");
    ler_dados(fd,dados);
    d=(int)dados[0];//Dimensao da matriz
    t=(int)dados[1];//Tolerancia em casas decimais
    E=tolerancia(t);//Tolerancia em valor real
    fd = fopen(argv[1], "r");  //Relê o arquivo.
    ler_matriz(fd,d,M);  
    
    result_inicio(d,t,E,M);
    householder(d,E,M,X);//Aplica Householder na matriz M, guardando a matriz de householder em X
    qr(d,E,M,X);//Aplica o metodo QR na matriz M, gerando a matriz X com os autovetores da matriz M inicial
    result_final(d,M,X);   
    
    printf("Arquivo 'output.txt com os resultados gerado com sucesso!\n\n");    
}
