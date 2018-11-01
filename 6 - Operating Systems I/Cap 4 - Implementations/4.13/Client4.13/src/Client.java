import java.io.*; 
import java.net.*;

public class Client 
{
    public static void main(String[] args) throws IOException 
    {
        Socket sock = null;
        try 
        {
            while(true)
            {    
                sock = new Socket("127.0.0.1", 6013);
                System.out.println("Digite uma mensagem:\n");
                
                BufferedReader inFromUser = new BufferedReader(new InputStreamReader(System.in));      
                String envia = inFromUser.readLine();
                
                PrintWriter pout = new PrintWriter(sock.getOutputStream(),true);
                pout.println(envia);
                System.out.println("Mensagem enviada: " + envia);            
                
                BufferedReader inFromServer = new BufferedReader(new InputStreamReader(sock.getInputStream()));      
                String recebe = inFromServer.readLine();
                System.out.println("Resposta do Servidor: " + recebe);            
            }
        } catch (IOException ioe) {
            System.err.println(ioe);
        } finally {
            sock.close();
        }
    }
}