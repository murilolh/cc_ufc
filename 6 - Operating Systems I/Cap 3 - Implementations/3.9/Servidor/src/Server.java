import java.io.*;
import java.net.*;

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
            while (true) 
            {
                client = sock.accept();
                System.out.println("Conexao Aceita");
                
                BufferedReader inFromClient = new BufferedReader(new InputStreamReader(client.getInputStream()));
                String recebe = inFromClient.readLine();
                
                System.out.println("Mensagem recebida: " + recebe);
                
                PrintWriter pout = new PrintWriter(client.getOutputStream(),true);
                pout.println(recebe);

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