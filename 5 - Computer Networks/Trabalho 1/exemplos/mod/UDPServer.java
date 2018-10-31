import java.io.*;
import java.net.*;

class UDPServer 
{
   public static void main(String args[]) throws Exception
   {
      String[] n_clientes = new String[100];
      InetAddress[] i_clientes = new InetAddress[100];
      int[] p_clientes = new int[100];
      int c=0;
      DatagramSocket serverSocket = new DatagramSocket(9876);
      System.out.println("Servidor Inicializado");
      while(true)
      {
          byte[] receiveData = new byte[1024];
          byte[] sendData = new byte[1024];
          DatagramPacket receivePacket;
          DatagramPacket sendPacket;
          String sentence;          
          InetAddress IPAddress;
          int port;
          int i;
          
          receivePacket = new DatagramPacket(receiveData,receiveData.length);
          serverSocket.receive(receivePacket);
          sentence = new String(receivePacket.getData());
          IPAddress = receivePacket.getAddress();
          port = receivePacket.getPort(); 
                    
          if (sentence.charAt(0) == '%' && sentence.charAt(1) == '$')
          {
              c++;
              
              int a = 2;
              int b = 3;
              while((sentence.charAt(a) != '%') || (sentence.charAt(b) != '$'))
              {
                 a++;
                 b++;
              }
              n_clientes[c] = sentence.substring(2,a);
              
              i_clientes[c] = IPAddress;
              p_clientes[c] = port;
              System.out.print("Cliente " + n_clientes[c]);
              System.out.print(" conectado     IP: " + i_clientes[c] );
              System.out.println("     Porta: " + p_clientes[c]);
              sentence  = "OK";              
              sendData = sentence.getBytes();
              sendPacket = new DatagramPacket(sendData, sendData.length, i_clientes[c], p_clientes[c]);
              serverSocket.send(sendPacket);              
          }
          else
          {
              String I_Cliente;
              String IP;
              IP = IPAddress.toString(); 
              for (i=1;i<=c;i++)
              {
                  I_Cliente = i_clientes[i].toString();
                  if((I_Cliente.compareTo(IP) == 0) && (p_clientes[i] == port))                  
                  {
                      sentence = n_clientes[i] + "%&" + sentence;                      
                      break;
                  }                  
              }
              
              sendData = sentence.getBytes();
              for (i=1;i<=c;i++)
              {       
                 sendPacket = new DatagramPacket(sendData, sendData.length, i_clientes[i], p_clientes[i]);
                 serverSocket.send(sendPacket); 
              }     
              System.out.println("Mensagem repassada: " + sentence);
          }
      }
   }
}
