package multi;

public class Multiplicador {

    public Matriz A;
    public Matriz B;
    public Matriz C;

    public void iniciar() throws Exception
    {
        Arquivo file = new Arquivo();
        A = file.LerMatriz(1);
        B = file.LerMatriz(2);

        C = new Matriz(A.linhas,B.colunas);

        MultThread[][] threads = new MultThread[A.linhas+1][B.colunas+1];

        for(int i=1;i<=C.linhas;i++)
            for(int j=1;j<=C.colunas;j++)
            {
                threads[i][j] = new MultThread(i,j,A.colunas,A,B,C);
                threads[i][j].start();
            }

        for(int i=1;i<=C.linhas;i++)
            for(int j=1;j<=C.colunas;j++)
                threads[i][j].join();

        file.geraResultado(A,B,C);

    }

}
