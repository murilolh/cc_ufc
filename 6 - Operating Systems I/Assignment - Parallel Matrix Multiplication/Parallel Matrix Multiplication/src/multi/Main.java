package multi;

import java.io.*;

public class Main {

    public static void main(String[] args)
    {
        try
        {
            Multiplicador M = new Multiplicador();
            M.iniciar();
        }catch(FileNotFoundException fnf)
        {
            System.out.println("ERRO: FileNotFoundException");
            fnf.printStackTrace();
        }catch(Exception e)
        {
            System.out.println("ERRO: Exception");
            e.printStackTrace();
        }

    }

}
