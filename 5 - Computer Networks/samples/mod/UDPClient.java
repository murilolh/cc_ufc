import java.io.*; 
import java.net.*;

class UDPClient 
{
   public static void main(String args[]) throws Exception
   {
     byte[] sendData = new byte[1024];
     byte[] receiveData = new byte[1024];
     InetAddress IPAddress;
     String nome;
     String sentence;
     String modifiedSentence;
     DatagramPacket sendPacket;
     DatagramPacket receivePacket;
     
     BufferedReader inFromUser = new BufferedReader(new InputStreamReader(System.in));      
     DatagramSocket clientSocket = new DatagramSocket();
     IPAddress = InetAddress.getByName("localhost");
     
     System.out.println("Digite seu nome: ");
     nome = inFromUser.readLine();
     nome =  "%$" + nome + "%$";
     sendData = nome.getBytes();
     DatagramPacket sendnome =new DatagramPacket(sendData, sendData.length, IPAddress, 9876);
     clientSocket.send(sendnome);

     receivePacket = new DatagramPacket(receiveData, receiveData.length);
     clientSocket.receive(receivePacket);
     sentence = new String(receivePacket.getData());
          
     if ((sentence.charAt(0) != 'O') || (sentence.charAt(1) != 'K'))
        System.out.println("Servidor Indisponível"); 
     else
     {
        System.out.println("Conexao Estabelecida");
        while(true)
        { 
           sentence = inFromUser.readLine();
           sendData = sentence.getBytes();
           sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, 9876);
           clientSocket.send(sendPacket);          
        }
     }
     clientSocket.close();
   }
}
