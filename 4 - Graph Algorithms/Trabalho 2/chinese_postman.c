#include <stdlib.h>
#include <stdio.h>

#define INF 32768
#define MAX 360

int n,m,count,i,j;
int custo_total=0;

void MatCust(FILE *fd,int mat[MAX][MAX]) //Armazena os custos das ints em 'ar'
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
            if (i!=j)
                mat[i][j]=INF;
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
        if(mat[origem][destino]>mat[destino][origem] || mat[origem][destino]==INF
        || mat[origem][destino]==0)
        {
           mat[origem][destino]=atoi(&aux[count]);
           mat[destino][origem]=atoi(&aux[count]);
        }
        while(aux[count]!=',')
        {
            count++;
            if(aux[count+1]=='\0')
                break;
        }
        count++;
    }
}

void imprimir(int mat[MAX][MAX])
{
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
	        if (mat[i][j] == INF)
		        printf("INF ");
            else
    	        printf("%d ",mat[i][j]);
            if(mat[i][j]<10)
                printf("     ");
            else if(mat[i][j]<100)
		        printf("    ");
            else if((mat[i][j]<1000)  || (mat[i][j] == INF))
		        printf("   ");
            else if(mat[i][j]<10000)
		        printf("  ");
            else if(mat[i][j]<100000)
		        printf(" ");
            else
                printf(" ");
        }
        printf("\n");
    }
}

void Grau(int mat[MAX][MAX],int grau[MAX], int impar[MAX])
{
    for(i=1;i<n+1;i++)
        for(j=1;j<n+1;j++)
            if(mat[i][j]!=0 && mat[i][j]!=INF)
            {
                grau[i]=grau[i]+1;
                impar[i]=grau[i]%2;
            }
}


int Euler(int grau[MAX], int impar[MAX])
{
    for(i=1;i<=n+1;i++)
        if(impar[i]==1)
          return(1);
    return(0);
}

void matching(int dj[MAX][MAX],int grau[MAX])
{
    int x,y;
    int match=0;
    int aux=0;
    int aux2=1;
    int cust=INF;
    for(i=1;i<=n;i++)
        if(grau[i]%2>0)
            aux++;
    int v_impar[aux];
    for(i=0;i<=aux;i++)
        v_impar[i]=0;
    for(i=1;i<=n;i++)
        if(grau[i]%2>0)
        {
            v_impar[aux2]=i;
            aux2++;
        }
    printf("\nCusto do grafo: %d\n",custo_total);
    while(aux>0)
    {
        for (i=1;i<=aux;i++)
            for (j=1;j<=aux;j++)
            {
              if(dj[v_impar[i]][v_impar[j]]!=0)
                  if(cust>(dj[v_impar[i]][v_impar[j]]))
                  {
                      cust=dj[v_impar[i]][v_impar[j]];
                      x=i; y=j;
                }
            }
        match=match + cust;
        custo_total=custo_total+cust;
        if(y!=aux)     v_impar[x]=v_impar[aux];
        if(x!=aux-1)   v_impar[y]=v_impar[aux-1];
        aux=aux-2;
        cust=INF;
    }
    printf("\nCusto do matching: %d\n",match);
}

void dijkstra(int dj[MAX][MAX],int mat[MAX][MAX], int raiz)
{
    int p,prox;
    int perm[n+1];//Vetor que ve quais vertices ja foram analisados pelo algoritmo
    for (i=0;i<n+1;i++)//Coloca 0 em tds as posi��es indicando que nenhum vertice foi analisado
        perm[i]=0;
    perm[raiz]=1;//Coloca 1 na raiz, que vai ser analisada
    p=1;//Variavel que indica qts vertices foram analisados
    prox=raiz;
    while(p<n)//Enquanto tds os vertices nao forem analisados
    {
        int adj;//Variavel que vai indicar o vertice adjacente de menor custo
        int min = INF+1;
        for(j=1;j<=n;j++)
            if((perm[j]==0) && (dj[raiz][j] < min))//So pega vertices que nao foram analisados
            {
                adj = j;//Atualiza o vertice adjacente
                min = dj[prox][j];//Custo do vertice adjacente
            }
        for(j=1;j<=n;j++)
            if ((j!=prox) && (j!=adj))//Analisa tds os vertices, menos a raiz e o adjacente
                if(dj[raiz][j] > dj[raiz][adj] + dj[adj][j])//Compara as distancias
                    dj[raiz][j] = dj[raiz][adj] + dj[adj][j];//e pega a que for menor
        prox=adj;
        p++;//Incrementa o numero de vertices analisado
        perm[adj]=1;//O vertice adj ja foi analisado
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
    while(va[count]!=' ')  //  O numero de ints se encontra ap�s o primeiro espa�o, assim
        count++;           //incrementa-se o 'count' at� encontrar o primeiro espa�o.
    m=atoi(&va[count+1]);  //Armazena o n�mero de ints.
    if (m>n*(n-1) || (m<(n-1)) || (n<2) || (n>60)) //Teste pra ver se o grafo � v�lido
    {
        printf("\n\nGrafo Invalido!!");
        exit(1);
    }
    int mat[MAX][MAX],dj[MAX][MAX];
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
        {
            mat[i][j]=0;
            dj[i][j]=0;
        }
    fd = fopen(argv[1], "r");  //Reler o arquivo.
    MatCust(fd,mat);
    printf("\n\n\n            Matriz de custo\n\n");
    imprimir(mat);
    fd = fopen(argv[1], "r");  //Reler o arquivo.
    MatCust(fd,dj);
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            if(mat[i][j]!=0 && mat[i][j]!=INF && i<j)
                custo_total=custo_total+mat[i][j];
    int raiz;
    for (raiz=1;raiz<=n;raiz++)//Cada vertice do grafo tem que ser raiz uma vez
        dijkstra(dj,mat,raiz);
    int grau[n+1];// vetor que guarda o grau dos vertices
    int impar[n+1];// vetor que guarda os vertices impares
    for(i=0;i<n+1;i++)
        grau[i]=0;
    Grau(mat,grau,impar);
    if (Euler(grau,impar)==1)
    {
        matching(dj,grau);
        printf("\nEULERIANO: NAO");
    }
    else
        printf("\nEULERIANO: SIM");
    printf("\n\nO custo total e: %d",custo_total);
}
