import java.net.*;
import java.io.*;

public class Server extends Thread{
    
    Socket cliente = null;
    
    public Server(Socket c){
        cliente = c;
    }
    
    public void run(){
        try {
            PrintWriter pout = new PrintWriter(cliente.getOutputStream(),true);
            pout.println(new java.util.Date().toString());
            pout.close();
            cliente.close();
            System.out.println("Cliente Servido");
        }catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }    

    public static void main(String[] args) throws IOException {
        Socket client = null;
        ServerSocket sock = null;
        System.out.println("----Servidor Inicializado----");
        try {
            sock = new ServerSocket(6013);
            while (true) {
                client = sock.accept();
                Thread current = new Server(client);
                current.start();                
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