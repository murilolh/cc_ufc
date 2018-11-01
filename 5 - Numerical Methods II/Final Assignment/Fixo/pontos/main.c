#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include "gauss_jacobi.h"

int ponto(int a, int b)
{
   int p=1;
   int i,j;
   for(i=1;i<=9;i++)
      for(j=1;j<=7;j++)
      {
         if((i==a) && (j==b))
           return p;
         else
           p++;
      }       
}

float contorno(int i, int j)
{  
    if((i==10) || (j==8))
       return 1;
    else if((i==0) || (j==0))
       return 0;
    else
       return -1;
}

int main()
{
    FILE *arquivo;
    int i,j,u,p,k,l;
    float deltax, deltay;
    float mascara[3][3];
    
    float A[64][64];
    float solucao[64];
    float resultado[64];
    float pontos[64][3];
       
    deltax= 1;
    deltay= 1;
    
    for(i=1;i<=63;i++)
      for(j=1;j<=63;j++)
         A[i][j]=0;
      
    for(i=1;i<=9;i++)
      for(j=1;j<=7;j++)  
          resultado[ponto(i,j)] = -1; 
    
    mascara[0][0] = 3/(4*deltax*deltay);
    mascara[0][1] = 2/pow(deltay,2);
    mascara[0][2] = -3/(4*deltax*deltay);
    mascara[1][0] = 1/pow(deltax,2);
    mascara[1][1] = (-2/pow(deltax,2)) + (-4/pow(deltay,2));
    mascara[1][2] = 1/pow(deltax,2);
    mascara[2][0] = -3/(4*deltax*deltay);
    mascara[2][1] = 2/pow(deltay,2);
    mascara[2][2] = 3/(4*deltax*deltay);
        
    for(i=1;i<=9;i++)
      for(j=1;j<=7;j++)
      {
          p = ponto(i,j);
          for(k=-1;k<=1;k++)
            for(l=-1;l<=1;l++)
            {
                u = contorno(i+k,j+l);
                if(u>=0)
                  resultado[p] = resultado[p] - mascara[k+1][l+1]*u;
                else
                  A[p][ponto(i+k,j+l)] = mascara[k+1][l+1];
            }
       }
      
      arquivo = fopen("arquivo.txt","w");
      fprintf(arquivo,"\n\n--------------------------MATRIZ OBTIDA------------------------\n\n");    
      for(i=1;i<=63;i++)
      {
         for(j=1;j<=63;j++)
            fprintf(arquivo,"%5.3f ",A[i][j]);
         fprintf(arquivo,"\n");
      }
      fprintf(arquivo,"\n\n--------------------------Vetor Resultado------------------------\n\n");
      for(i=1;i<=63;i++)
         fprintf(arquivo,"%5.3f    ",resultado[i]);
      
      gauss_jacobi(A,solucao,resultado);

      fprintf(arquivo,"\n\n--------------------------Solucao do Sistema------------------------\n\n");
      for(i=1;i<=63;i++)
         fprintf(arquivo,"%5.3f    ",solucao[i]);      
      
      int x=1;
      for(i=1;i<=9;i++)
         for(j=1;j<=7;j++)
         {
            pontos[x][1] = i;
            pontos[x][2] = j;
            pontos[x][3] = solucao[ponto(i,j)];
            x++;
         }
       
      fprintf(arquivo,"\n\n--------------------------PONTOS------------------------\n\n");   
      for(i=1;i<=63;i++)
         fprintf(arquivo,"%5.3f    %5.3f    %5.3f\n",pontos[i][1],pontos[i][2],pontos[i][3]);   
         
      fclose(arquivo);
}
