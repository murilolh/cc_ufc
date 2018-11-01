package multi;

public class MultThread extends Thread{

    public int linha = 0;
    public int coluna = 0;
    public int d = 0;
    public Matriz A;
    public Matriz B;
    public Matriz C;

    public MultThread(int l, int c, int d, Matriz A, Matriz B, Matriz C)
    {
        linha = l;
        coluna = c;
        this.d = d;
        this.A = A;
        this.B = B;
        this.C = C;
    }

    @Override
    public void run()
    {
         C.setDado(linha,coluna,0);
         for(int k=1;k<=d;k++)
            C.setDado(linha, coluna, C.getDado(linha,coluna) + A.getDado(linha,k)*B.getDado(k,coluna));
    }

}
