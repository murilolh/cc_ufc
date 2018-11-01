import java.io.*;
import java.net.*;
import java.util.*;

public class Server 
{
    public static void main(String[] args) throws IOException 
    {
        Socket client = null;
        ServerSocket sock = null;
        try 
        {
            sock = new ServerSocket(6013);
            System.out.println("----SERVIDOR INICIALIZADO-----");
            Random rd = new Random();
            while (true) 
            {
                client = sock.accept();
                System.out.println("Conexao Aceita");
                
                String[] fortunes = new String[30];                
                fortunes[1]= "aaaaaaa";
                fortunes[2]= "bbbbbbb";
                fortunes[3]= "ccccccc";
                fortunes[4]= "ddddddd";
                fortunes[5]= "eeeeeee";
                fortunes[6]= "fffffff";
                fortunes[7]= "ggggggg";
                fortunes[8]= "hhhhhhh";
                fortunes[9]= "iiiiiii";
                fortunes[10]= "jjjjjjj";
                fortunes[11]= "kkkkkkk";
                fortunes[12]= "lllllll";
                fortunes[13]= "mmmmmmm";
                fortunes[14]= "nnnnnnn";
                fortunes[15]= "ooooooo";
                fortunes[16]= "ppppppp";
                fortunes[17]= "qqqqqqq";
                fortunes[18]= "rrrrrrr";
                fortunes[19]= "sssssss";
                fortunes[20]= "ttttttt";
                fortunes[21]= "uuuuuuu";
                fortunes[22]= "vvvvvvv";
                fortunes[23]= "wwwwwww";
                fortunes[24]= "xxxxxxx";
                fortunes[25]= "yyyyyyy";
                fortunes[26]= "zzzzzzz";
                int r = rd.nextInt(26);
                PrintWriter pout = new PrintWriter(client.getOutputStream(),true);
                pout.println(fortunes[r]);

                client.close();
            }
        } catch (IOException e) {
            System.out.println(e.getMessage());
        } finally {
            if (sock != null)
                sock.close();
            if (client != null)
                client.close();
        }
    }
}
