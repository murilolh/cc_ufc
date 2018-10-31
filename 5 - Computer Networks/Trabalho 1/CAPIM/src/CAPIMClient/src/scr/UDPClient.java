package scr;

import java.net.*;

class UDPClient {

    public UDPClient(Mensagem ms) {
        texto = ms;
    }

    public DatagramSocket Enviar(String msg) throws Exception {

        DatagramSocket clientSocket = new DatagramSocket();
        sendData = new byte[1024];
        IPAddress = InetAddress.getByName("localhost");

        sendData = msg.getBytes();
        sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, 12345);
        clientSocket.send(sendPacket);
        return clientSocket;
    }

    public void Receber(DatagramSocket Socket) throws Exception {

        receiveData = new byte[1024];
        receivePacket = new DatagramPacket(receiveData, receiveData.length);
        Socket.receive(receivePacket);
        sentence = new String(receivePacket.getData());
        texto.msgservidor(sentence, Socket);

    }
    private byte[] sendData = new byte[1024];
    private byte[] receiveData = new byte[1024];
    private InetAddress IPAddress;
    private Mensagem texto;
    private String sentence = null;
    private DatagramPacket sendPacket;
    private DatagramPacket receivePacket;
}

