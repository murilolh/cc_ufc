package scr;

import java.net.*;

public class Mensagem {

    public Mensagem() {
    }

    public void msgusuario(String[] msg) throws Exception {
        if (msg[0].equals("2%%")) {
            DatagramSocket Socket = new DatagramSocket();
            EncapsulaConversa(msg, Socket);
        } else {
            DatagramSocket Socket = new DatagramSocket();
            Encapsula(msg, Socket);
        }
    }

    public void msgservidor(String msg, DatagramSocket Socket) throws Exception {

        DatagramSocket Socket1 = Socket;
        if (msg.charAt(0) == '0' || msg.charAt(0) == '1' || msg.charAt(0) == '3' ||
                msg.charAt(0) == '4' || msg.charAt(0) == '5' ||
                msg.charAt(0) == '7' || msg.charAt(0) == '8' || msg.charAt(0) == '9') {
            InterpretaSimples(msg);
        } else if (msg.charAt(0) == '2') {//Mensagem de texto msg: 2%%<nome_origem>%%<nome_destino>%%<mensagem>%%
            //Pacote repassado para o destino: 2%%<origem>%%<mensagem>
            a = 3;
            b = 4;
            d = 3;
            i = 0;
            while ((msg.charAt(a) != '%') || (msg.charAt(b) != '%'))//Nome dos amigos
            {
                a++;
                b++;
                c++;
            }
            Amigo = msg.substring(d, a);
            if (a == 3 || b == 4) {
                Recebido = 1;
                return;
            }
            d = b + 1;
            a += 2;
            b += 2;

            while ((msg.charAt(a) != '%') || (msg.charAt(b) != '%'))//Nome dos amigos
            {
                a++;
                b++;
            }
            Conversa = msg.substring(d, a);
        } else if (msg.charAt(0) == '6') {
            a = 3;
            b = 4;
            c = 5;
            d = 3;
            i = 0;
            switch (Recebido) {
                case (0):  //ON : 6%%<usuario>&&<status>%%<usuario>&&<status>%% ... %%<usuario>&&<status>%%&&&
                    AmigosON = new String[20];
                    AmigosONStatus = new String[20];
                    while ((msg.charAt(a) != '&') || (msg.charAt(b) != '&') || (msg.charAt(c) != '&'))//Encontrar o codigo de fim de mensagem
                    {
                        while ((msg.charAt(a) != '$') || (msg.charAt(b) != '$'))//Status dos amigos
                        {
                            a++;
                            b++;
                            c++;
                        }
                        AmigosON[i] = msg.substring(d, a);
                        if (a == 3 || b == 4) {
                            Recebido = 1;
                            cliente.Receber(Socket1);
                            break;
                        }
                        d = b + 1;
                        a += 2;
                        b += 2;
                        c += 2;
                        while ((msg.charAt(a) != '%') || (msg.charAt(b) != '%'))//Nome dos amigos
                        {
                            a++;
                            b++;
                            c++;
                        }

                        AmigosONStatus[i] = msg.substring(d, a);
                        d = b + 1;
                        a += 2;
                        b += 2;
                        c += 2;
                        i++;
                    }
                    Recebido = 1;
                    cliente.Receber(Socket1);
                    break;
                case (1): //OFF : 6%%<usuario>%%<usuario>%% ... %%<usuario>%%&&&
                    AmigosOFF = new String[10];
                    while ((msg.charAt(a) != '&') || (msg.charAt(b) != '&') || (msg.charAt(c) != '&'))//Encontrar o codigo de fim de mensagem
                    {
                        while ((msg.charAt(a) != '%') || (msg.charAt(b) != '%'))//Nome dos amigos
                        {
                            a++;
                            b++;
                            c++;
                        }
                        if (a == 3 || b == 4) {
                            Recebido = 2;
                            cliente.Receber(Socket1);
                            break;
                        }
                        AmigosOFF[i] = msg.substring(d, a);
                        d = b + 1;
                        a += 2;
                        b += 2;
                        c += 2;

                        i++;
                    }
                    Recebido = 2;
                    cliente.Receber(Socket1);
                    break;
                case (2): //REQ : 6%%<usuario>%%&&& Caso nao tenha requisicao: 6%%%%&&&
                    Requisicoes = new String[20];
                    while ((msg.charAt(a) != '&') && (msg.charAt(b) != '&') && (msg.charAt(c) != '&'))//Encontrar o codigo de fim de mensagem
                    {
                        while ((msg.charAt(a) != '%') || (msg.charAt(b) != '%'))//Nome dos amigos
                        {
                            a++;
                            b++;
                            c++;
                        }
                        if (a == 3 || b == 4) {
                            Recebido = 3;
                            Requisicoes[i] = ".";
                            cliente.Receber(Socket1);
                            break;
                        }
                        Requisicoes[i] = msg.substring(d, a);
                        d = b + 1;
                        a += 2;
                        b += 2;
                        c += 2;
                       i++;
                    }
                    Requisicoes[i] = ".";
                    Recebido = 3;
                    cliente.Receber(Socket1);
                    break;
                case (3): //Resposta final
                    a = 3;
                    b = 4;
                    while ((msg.charAt(a) != '%') || (msg.charAt(b) != '%'))//Encontrar o codigo do servidor
                    {
                        a++;
                        b++;
                    }
                    codigo = msg.substring(3, a);
                    Recebido = 0;
                    break;
                default:
                    break;
            }
        }
    }

    public String getCodigo() {
        return codigo;
    }

    public String[] getAmigosON() {
        return AmigosON;
    }

    public String[] getAmigosONStatus() {
        return AmigosONStatus;
    }

    public String[] getAmigosOFF() {
        return AmigosOFF;
    }

    public String[] getRequisicoes() {
        return Requisicoes;
    }

    public void Encapsula(String[] msg, DatagramSocket Socket) throws Exception {
        texto = msg[0];
        a = 1;
        while (!msg[a].equals(".%")) {
            texto = texto + msg[a] + "%%";
            a++;
        }
        Socket = cliente.Enviar(texto);
        cliente.Receber(Socket);
    }

    public void EncapsulaConversa(String[] msg, DatagramSocket Socket) throws Exception {
        texto = msg[0];
        a = 1;
        while (!msg[a].equals(".%")) {
            texto = texto + msg[a] + "%%";
            a++;
        }
        Socket = cliente.Enviar(texto);
        cliente.Receber(Socket);
    }

    public void InterpretaSimples(String msg) {
        a = 3;
        b = 4;
        while ((msg.charAt(a) != '%') || (msg.charAt(b) != '%'))//Encontrar o codigo do servidor
        {
            a++;
            b++;

        }
        codigo = msg.substring(3, a);
    }
//variaveis
    private String texto;
    private String codigo;
    private String Amigo, Conversa;
    private UDPClient cliente = new UDPClient(this);
    private String[] AmigosON;
    private String[] AmigosONStatus;
    private String[] AmigosOFF;
    private String[] Requisicoes;
    private int a,  b,  c,  d,  i;
    private int Recebido = 0;
}