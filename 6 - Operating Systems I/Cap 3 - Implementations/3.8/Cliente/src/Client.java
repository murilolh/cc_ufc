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
                int bla = System.in.read();                                
                BufferedReader inFromServer = new BufferedReader(new InputStreamReader(sock.getInputStream()));      
                String recebe = inFromServer.readLine();
                System.out.println("Mensagem do Servidor: " + recebe);            
            }
        } catch (IOException ioe) {
            System.err.println(ioe);
        } finally {
            sock.close();
        }
    }
}