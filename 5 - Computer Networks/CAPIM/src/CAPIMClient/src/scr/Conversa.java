package scr;

import java.net.*;

public class Conversa extends Thread {

    // construtor Conversa atribui nome a thread chamando
    // construtor Thread
    public Conversa(String Friend, String conversa, JConversa janela) {
        super(Friend);
        Amigo = Friend;
        Conversa = conversa;
        Atualized = janela;
    }

// executa a thread
    public void run() {
        while (true) {
            try {
                receiveData = new byte[1024];
                receivePacket = new DatagramPacket(receiveData, receiveData.length);
                Socket.receive(receivePacket);
                sentence = new String(receivePacket.getData());
                a = 3;
                b = 4;
                d = 3;
                while ((sentence.charAt(a) != '%') || (sentence.charAt(b) != '%'))//Nome dos amigos
                {
                    a++;
                    b++;
                    c++;
                }
                Amigo = sentence.substring(d, a);
                d = b + 1;
                a += 2;
                b += 2;
                while ((sentence.charAt(a) != '%') || (sentence.charAt(b) != '%'))//Nome dos amigos
                {
                    a++;
                    b++;
                }
                Conversa = sentence.substring(d, a);
                if (!sentence.substring(d, a).equals(null)) {
                    Atualized.Conversas(Amigo, Conversa);
                }
            } catch (Exception e) {
             }
        }
    }
    // variaveis
    private JConversa Atualized;
    private int sleepTime;
    private String Login;
    private byte[] receiveData = new byte[1024];
    private String sentence = null;
    private DatagramPacket receivePacket;
    private DatagramSocket Socket;
    private String Amigo,  Conversa;
    private int a,  b,  c,  d,  i = 0;
}
