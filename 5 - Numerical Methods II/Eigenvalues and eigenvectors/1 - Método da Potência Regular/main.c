//**************************************************************
//                                                             *
// Implementação de Métodos de Autovalores e Autovetores       *
// Métodos Numéricos II 2009.1                                 *
// Murilo Lima de Holanda                          Mat:0286740 *
//                                                             *
// Método da Potência Regular                                  *
//                                                             *
//**************************************************************

#include "regular.h" //Arquivo com funções de leitura e escrita no arquivo, 
#include <stdio.h>   //de manipulacao de vetores e matrizes necessarias para o metodo da potencia regular
#include <stdlib.h>
#include <cmath>

int main(int argc, char *argv[])
{   
    int i,j,k;
    int d,t;//Variaveis inteiras para a dimensao da matriz e a tolerancia em numero de casas decimais
    float M[MAX][MAX];//Matriz principal
    float dados[MAX];//Vetor que guarda os dados do arquivo
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
    d=(int)dados[1];//Dimensao da matriz
    float chute[d];//Vetor de chute inicial
    j=1;
    for(i=1;i<=d;i++)
    {
       chute[i] = dados[i+1];
       j++;
    }
    t=(int)dados[j+1];//Tolerancia em casas decimais
    E=tolerancia(t);//Tolerancia em valor real
    fd = fopen(argv[1], "r");  //Relê o arquivo.
    ler_matriz(fd,d,M);   
    
    float lambda[2];//Autovalores anterior e atual
    float x[d];//Autovetor atual normalizado
    float y0[d];//Autovetor atual
    float y1[d];//Proximo autovetor
    float e;//Erro
        
    igualar_vetores(y0,chute,d);
    lambda[0]=modulo(y0,d);
    result_inicio(d,t,E,M,chute,lambda[0]);
    k=0;
    do
    {
       normaliza(y0,d,x);//x recebe o vetor y0 normalizado
       mult_MV(M, x, d, y1);//O vetor y1 recebe o produto de M e x
       lambda[1] = escalar(y1, x, d);//O autovalor lambda[1] recebe o produto escalar de y1 e x

       e = fabs(lambda[1] - lambda[0]);
       e = e/fabs(lambda[0]);//Calcula o erro
       result_iter(k, d, y0, y1, x, lambda, e, E);
       lambda[0] = lambda[1];
       igualar_vetores(y0,y1,d);
       k++; 
    }
    while((e >= E) && (k < MAX));

    result_final(k-1, d, y1, lambda[0]);
    if(k<=MAX)
    	printf("Arquivo 'output.txt com os resultados gerado com sucesso!\n\n");
    else
    	printf("Arquivo 'output.txt gerado mas pode conter erros!\n\n");
}
