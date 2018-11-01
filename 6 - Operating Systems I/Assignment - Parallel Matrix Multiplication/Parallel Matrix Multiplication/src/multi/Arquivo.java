package multi;

public class Arquivo {

    public TextFile arquivo = new TextFile();
    public String caminho = "C://Matriz.txt";
    public String resultado = "C://Resultado.txt";

    public Matriz LerMatriz(int numero) throws Exception
    {
        Matriz M;
        String texto;
        char[] valores = new char[10];
        String linhas = "";
        String colunas = "";
        String elem = "";
        int c;
        int l;

        arquivo.open(caminho,"INPUT");

        for(int j=1;j<numero;j++)
        {
            texto = arquivo.read();
            texto.getChars(0,3,valores,0);
            linhas = linhas + valores[0];
            l = Integer.parseInt(linhas);

            for(int i=1;i<=l;i++)
                texto = arquivo.read();
        }

        linhas = "";
        valores = new char[10];
        texto = arquivo.read();
        texto.getChars(0,3,valores,0);
        linhas = linhas + valores[0];
        colunas = colunas + valores[2];
        l = Integer.parseInt(linhas);
        c = Integer.parseInt(colunas);

        M = new Matriz(l,c);

        for(int i=1;i<=l;i++)
        {
            texto = arquivo.read();
            valores = new char[10];
            texto.getChars(0,texto.length(),valores,0);
            int n = 0;
            for(int j=1;j<=c;j++)
            {
                elem = elem + valores[n];
                while((valores.length > n+1) && ((valores[n+1] == '0') || (valores[n+1] == '1') || (valores[n+1] == '2') || (valores[n+1] == '3') || (valores[n+1] == '4') || (valores[n+1] == '5') || (valores[n+1] == '6') || (valores[n+1] == '7') || (valores[n+1] == '8') || (valores[n+1] == '9')))
                {
                   elem = elem + valores[n+1];
                   n++;
                }
                M.setDado(i,j,Integer.parseInt(elem));
                elem = "";
                n = n+2;
            }
        }

        arquivo.close();

        return M;
    }

    public void geraResultado(Matriz A, Matriz B, Matriz C) throws Exception
    {
        arquivo.open(resultado,"OUTPUT");

        arquivo.write("------------------ MATRIZ A --------------------------------\n");
        arquivo.write("Linhas: " + A.linhas);
        arquivo.write("\nColunas: " + A.colunas + "\n");
        for(int i=1;i<=A.linhas;i++)
        {
            for(int j=1;j<=A.colunas;j++)
            {
                arquivo.write(A.getDado(i,j) + " ");
            }
            arquivo.write("\n");
        }

        arquivo.write("------------------ MATRIZ B --------------------------------\n");
        arquivo.write("Linhas: " + B.linhas);
        arquivo.write("\nColunas: " + B.colunas + "\n");
        for(int i=1;i<=B.linhas;i++)
        {
            for(int j=1;j<=B.colunas;j++)
            {
                arquivo.write(B.getDado(i,j) + " ");
            }
            arquivo.write("\n");
        }

        arquivo.write("------------------ MATRIZ C --------------------------------\n");
        arquivo.write("Linhas: " + C.linhas);
        arquivo.write("\nColunas: " + C.colunas + "\n");
        for(int i=1;i<=C.linhas;i++)
        {
            for(int j=1;j<=C.colunas;j++)
            {
                arquivo.write(C.getDado(i,j) + " ");
            }
            arquivo.write("\n");
        }

        arquivo.close();
    }

}
