package UDPServer;

import java.net.*;

import java.sql.SQLException;

public class Mensagem {

    public Mensagem(String mensagem) {
        msg = mensagem;
    }

    public String GetFirstS() throws Exception {
        String first;
        int a, b;
        a = 3;
        b = 4;
        while ((msg.charAt(a) != '%') || (msg.charAt(b) != '%'))//Encontrar o login
        {
            a++;
            b++;
        }
        first = msg.substring(3, a);
        return first;
    }

    public String GetSecondS() throws Exception {
        String second;
        int a, b, c;
        a = 3;
        b = 4;
        while ((msg.charAt(a) != '%') || (msg.charAt(b) != '%')) {
            a++;
            b++;
        }
        c = b + 1;
        a = a + 2;
        b = b + 2;
        while ((msg.charAt(a) != '%') || (msg.charAt(b) != '%')) {
            a++;
            b++;
        }
        second = msg.substring(c, a);
        return second;
    }

    public int GetSecondI() throws Exception {
        String us_stat;
        Character stat;
        int us_status;
        int a, b, c;
        a = 3;
        b = 4;
        while ((msg.charAt(a) != '%') || (msg.charAt(b) != '%'))//Encontrar o login
        {
            a++;
            b++;
        }
        c = b + 1;
        a = a + 2;
        b = b + 2;
        while ((msg.charAt(a) != '%') || (msg.charAt(b) != '%'))//Encontrar o status
        {
            a++;
            b++;
        }
        us_stat = msg.substring(c, a);
        stat = us_stat.charAt(0);
        us_status = Character.getNumericValue(stat);
        return us_status;
    }

    public String GetMSG() throws Exception {
        String mensagem;
        int a, b, c;
        a = 3;
        b = 4;
        while ((msg.charAt(a) != '%') || (msg.charAt(b) != '%'))//Encontrar o login
        {
            a++;
            b++;
        }
        a = a + 2;
        b = b + 2;
        while ((msg.charAt(a) != '%') || (msg.charAt(b) != '%'))//Encontrar o amigo
        {
            a++;
            b++;
        }
        c = b + 1;
        a = a + 2;
        b = b + 2;
        while ((msg.charAt(a) != '%') || (msg.charAt(b) != '%'))//Encontrar a mensagem
        {
            a++;
            b++;
        }
        mensagem = msg.substring(c, a);
        return mensagem;
    }

    public String GetThirdS() throws Exception {
        String third;
        int a, b, c;
        a = 3;
        b = 4;
        while ((msg.charAt(a) != '%') || (msg.charAt(b) != '%')) {
            a++;
            b++;
        }
        a = a + 2;
        b = b + 2;
        while ((msg.charAt(a) != '%') || (msg.charAt(b) != '%')) {
            a++;
            b++;
        }
        c = b + 1;
        a = a + 2;
        b = b + 2;
        while ((msg.charAt(a) != '%') || (msg.charAt(b) != '%')) {
            a++;
            b++;
        }
        third = msg.substring(c, a);
        return third;
    }

    public void enviaOK(DatagramSocket serverSocket, int type, InetAddress IP, int port) throws Exception {
        String sentence;
        DatagramPacket sendPacket;
        byte[] sendData = new byte[1024];
        sentence = type + "%%OK%%";
        sendData = sentence.getBytes();
        sendPacket = new DatagramPacket(sendData, sendData.length, IP, port);
        serverSocket.send(sendPacket);
    }

    public void enviaERR(DatagramSocket serverSocket, int type, InetAddress IP, int port) throws Exception {
        String sentence;
        DatagramPacket sendPacket;
        byte[] sendData = new byte[1024];
        sentence = type + "%%ERR%%";
        sendData = sentence.getBytes();
        sendPacket = new DatagramPacket(sendData, sendData.length, IP, port);
        serverSocket.send(sendPacket);
    }

    public void enviaERRi(DatagramSocket serverSocket, int type, int err, InetAddress IP, int port) throws Exception {
        String sentence;
        DatagramPacket sendPacket;
        byte[] sendData = new byte[1024];
        sentence = type + "%%ERR" + err + "%%";
        sendData = sentence.getBytes();
        sendPacket = new DatagramPacket(sendData, sendData.length, IP, port);
        serverSocket.send(sendPacket);
    }

    public void envia(String sentence, DatagramSocket serverSocket, InetAddress IP, int port) throws Exception {
        DatagramPacket sendPacket;
        byte[] sendData = new byte[1024];
        sendData = sentence.getBytes();
        sendPacket = new DatagramPacket(sendData, sendData.length, IP, port);
        serverSocket.send(sendPacket);
    }

    public void enviaMSG(String sentence, DatagramSocket serverSocket, String origem, String IP, int port) throws Exception {
        InetAddress IP_destino;
        IP = IP.substring(1);
        IP_destino = InetAddress.getByName(IP);
        DatagramPacket sendPacket;
        byte[] sendData = new byte[1024];
        sentence = "2%%" + origem + "%%" + sentence + "%%";
        sendData = sentence.getBytes();
        sendPacket = new DatagramPacket(sendData, sendData.length, IP_destino, 20000);
        serverSocket.send(sendPacket);
    }

    public void enviaAviso(DatagramSocket serverSocket, String usuario, String IP, int port) throws Exception {
        String sentence;
        InetAddress IP_destino;
        IP = IP.substring(1);
        IP_destino = InetAddress.getByName(IP);
        DatagramPacket sendPacket;
        byte[] sendData = new byte[1024];
        sentence = "7%%" + usuario + "%%";
        sendData = sentence.getBytes();
        sendPacket = new DatagramPacket(sendData, sendData.length, IP_destino, port);
        serverSocket.send(sendPacket);
    }

    public void probSQL(SQLException ex) throws Exception {
        System.out.println("----------Problema com o SQL----------");
        System.exit(0);
        ex.printStackTrace();
    }
    private String msg;
}
    

