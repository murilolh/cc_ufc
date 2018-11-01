package multi;

public class Matriz {

    public int linhas = 0;
    public int colunas = 0;
    public int[][] M;

    public Matriz(int l, int c)
    {
        linhas = l;
        colunas = c;
        M = new int[linhas+1][colunas+1];
    }

    public void setDado(int l, int c, int d)
    {
        M[l][c] = d;
    }

    public int getDado(int l, int c)
    {
        return M[l][c];
    }

}
