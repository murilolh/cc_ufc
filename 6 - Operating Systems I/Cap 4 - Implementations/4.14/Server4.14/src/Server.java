import java.io.*;
import java.net.*;
import java.util.concurrent.*;

public class Server extends Thread{
    
    Socket cliente;
    
    public Server(Socket c){
        cliente = c;
    }        
    public void run(){
        try{
            System.out.println("Conexao Aceita");
                
            BufferedReader inFromClient = new BufferedReader(new InputStreamReader(cliente.getInputStream()));
            String recebe = inFromClient.readLine();
                
            System.out.println("Mensagem recebida: " + recebe);
                
            PrintWriter pout = new PrintWriter(cliente.getOutputStream(),true);

            pout.println(recebe);
            cliente.close();
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }
    
    public static void main(String[] args) throws IOException 
    {
        Socket client = null;
        ServerSocket sock = null;
        try 
        {
            sock = new ServerSocket(6013);
            System.out.println("----SERVIDOR INICIALIZADO-----");
            
            ExecutorService pool = Executors.newFixedThreadPool(10);

            while (true) 
            {
                client = sock.accept();
                pool.execute(new Server(client));                
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