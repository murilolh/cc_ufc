/*Equipe:Leandro Monteiro Guimarães         Matrícula:             0286756
	     Murilo Lima de Holanda                                    0286740
	     Paulo Sérgio V. Alves Júnior                              0288809 */

/*Obs: O algoritmo só funcionará se o arquivo a ser lido estiver no seguinte padrão: 
Linha 1:         n m(n=vértices m=arestas, separados por um espaço
Linhas 2 a m-1:  a,o,d,c(a aresta 'a' é incidente aos vértices 'o' e 'd' e tem custo 'c')                         
*/

//Obs2: O arquivo *.txt tem que ser passado como parâmetro para o programa

#include <stdlib.h>
#include <stdio.h>

#define INF 32768
#define MAX 60

int n,m,count,i,j;

void dijkstra(int ar[MAX][MAX], int raiz)
{ 
      int p,prox;
      int perm[n+1];//Vetor que ve quais vertices ja foram analisados pelo algoritmo	
      for (i=0;i<n+1;i++)//Coloca 0 em tds as posições indicando que nenhum vertice foi analisado
          perm[i]=0; 
      perm[raiz]=1;//Coloca 1 na raiz, que vai ser analisada
      p=1;//Variavel que indica qts vertices foram analisados
      prox=raiz;
      while(p<n)//Enquanto tds os vertices nao forem analisados
      {
         int adj;//Variavel que vai indicar o vertice adjacente de menor custo
         int min = INF+1;
         for(j=1;j<=n;j++)
           if((perm[j]==0) && (ar[raiz][j] < min))//So pega vertices que nao foram analisados
           {
               adj = j;//Atualiza o vertice adjacente
               min = ar[prox][j];//Custo do vertice adjacente              
           }
         for(j=1;j<=n;j++) 
           if ((j!=prox) && (j!=adj))//Analisa tds os vertices, menos a raiz e o adjacente             
              if(ar[raiz][j] > ar[raiz][adj] + ar[adj][j])//Compara as distancias
                 ar[raiz][j] = ar[raiz][adj] + ar[adj][j];//e pega a que for menor
         prox=adj;
         p++;//Incrementa o numero de vertices analisado      
         perm[adj]=1;//O vertice adj ja foi analisado          
      }
}

void MatCust(FILE *fd,int ar[MAX][MAX]) //Armazena os custos das arestas em 'ar'
{
    int origem,destino,custo;
    char aux[(m+1)*16];  //Vetor auxiliarpara guardar todos os caracteres do arquivo.
    count=0;
    while (!feof(fd))  //Guarda os caracteres do arquivo em 'aux'.
    {
        aux[count]=getc(fd);
        count++;
    }
    for(i=1;i<=n;i++)//Inicia a matriz com 0 se e infinito
        for(j=1;j<=n;j++)
        {
            if (i==j)
                ar[i][j]=0;
            else
                ar[i][j]=INF;
        }
    count=0;
    while(aux[count]!=',')
        count++;
    count++;
    while (aux[count] != '\0')
    {
        origem=atoi(&aux[count]);
        while(aux[count]!=',')
            count++;
        count++;
        destino=atoi(&aux[count]);
        while(aux[count]!=',')
            count++;
        count++;
        if(origem>n || destino>n)  //Testa se vertice pertence ao grafo.
        {
             printf("\nExistem vertices invalidos no seu grafo.\n\n");
             exit(0);
        }
        ar[origem][destino]=atoi(&aux[count]);
        while(aux[count]!=',')
        {
            count++;
            if(aux[count+1]=='\0')
                break;
        }
        count++;
    }
}

void Imprimir(int ar[MAX][MAX])
{
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
	    if (ar[i][j] == INF)
		printf("INF ");
	    else
            	printf("%d ",ar[i][j]);
            if(ar[i][j]<10)
		printf("     ");
            else if(ar[i][j]<100)
		printf("    ");
            else if((ar[i][j]<1000)  || (ar[i][j] == INF))
		printf("   ");
            else if(ar[i][j]<10000)
		printf("  ");
	    else if(ar[i][j]<100000)
		printf(" ");
            else printf(" ");
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    system("clear");
    if (argc<2)
    {
        printf("Voce deve digitar um parametro!\n\n");
        exit(1);
    }
    char va[8];
    FILE *fd;
    fd = fopen(argv[1], "r");
    count=0;
    while (count<8)  //  Salva a primeira linha do arquivo num vetor auxiliar para que se 
    {                // possa descobrir o valor de m e n. 
        va[count]=getc(fd);
        count++;
    }
    count=0;
    n=atoi(&va[count]); //Armazena o numero de vertices.
    while(va[count]!=' ')  //  O numero de arestas se encontra após o primeiro espaço, assim 
        count++;           //incrementa-se o 'count' até encontrar o primeiro espaço.
    m=atoi(&va[count+1]);  //Armazena o número de arestas.
    if (m>n*(n-1) || (m<(n-1)) || (n<2) || (n>MAX)) //Teste pra ver se o grafo é válido
    {
        printf("\n\nGrafo Invalido!!");
        exit(1);
    }
    fd = fopen(argv[1], "r");  //Reler o arquivo.
    int ar[MAX][MAX];
    MatCust(fd,ar);
    printf("\n\nNumero de vertices = %d       Numero de arestas = %d\n\n\n",n,m);
    printf("\n\n                         Matriz de custo:\n\n\n");
    Imprimir(ar);
    int raiz;
    for (raiz=1;raiz<=n;raiz++)//Cada vertice do grafo tem que ser raiz uma vez
        dijkstra(ar,raiz);
    printf("\n\n                        Matriz de distancia:\n\n\n");
    Imprimir(ar);
    printf("\n\n");
}

