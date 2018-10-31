package UDPServer;

import java.net.*;

//Bibliotecas usadas na conexão com o banco de dados
//O banco de dados no MySQL deve estar disponível durante o uso do servidor
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

class UDPServer {

    public static void main(String args[]) throws Exception {
        String driver = "com.mysql.jdbc.Driver"; //Classe do driver JDBC
        String banco = "CAPIM"; //Nome do Banco criado
        String host = "localhost"; //Maquina onde está o banco
        String str_conn = "jdbc:mysql://" + host + ":3306/" + banco; //URL de conexão
        String usuario = "root"; //Usuário do banco
        String senha = "admin"; //Senha de conexão

        //Variável usada na conexão com o banco de dados
        Connection conn;
        //Socket usado
        DatagramSocket serverSocket = new DatagramSocket(12345);

        //Testa a conexao com o banco de dados
        try {
            Class.forName(driver); //Carrega o driver
            //Obtém a conexão com o banco
            conn = DriverManager.getConnection(str_conn, usuario, senha);
        } catch (ClassNotFoundException ex) {
            System.out.println("----------Não foi possível carregar o driver.----------");
            System.exit(0);//Sai em caso de problema com o banco
            ex.printStackTrace();
        }

        System.out.println("----------Servidor Inicializado----------");

        //Loop de escuta do servidor
        while (true) {
            //Variáveis usadas no recebimento
            byte[] receiveData = new byte[1024];
            DatagramPacket receivePacket;
            String sentence;
            InetAddress IPAddress;
            int port;

            Statement stmt;
            String sql1, sql2, sql3, sql4;
            ResultSet rs1, rs2, rs3;

            //Variáveis usadas para obter dados do usuário que enviou mensagens para o servidor
            String us_login, us_pass, us_ip;
            InetAddress u_ip;
            int us_port, us_status;

            receivePacket = new DatagramPacket(receiveData, receiveData.length);
            serverSocket.receive(receivePacket);
            sentence = new String(receivePacket.getData());
            u_ip = receivePacket.getAddress();//IP do cliente
            us_port = receivePacket.getPort();//Porta usada pelo cliente
            us_ip = u_ip.toString();//IP no tipo String

            System.out.println(sentence);

            System.out.println("----------Pacotes recebidos----------");

            //Objeto mensagem para interpretação e envio de respostas
            Mensagem msg;
            msg = new Mensagem(sentence);

            switch (sentence.charAt(0)) {
                case ('0')://Mensagem de login
                    //As mensagens de login têm a forma: 0%%<user_login>%%<user_pass>%%
                    System.out.println("OK - Mensagem lida - Tentativa de login - login 0");
                    us_login = msg.GetFirstS();//Recebe o nome de usuário
                    us_pass = msg.GetSecondS();//Recebe a senha
                    Class.forName(driver);
                    conn = DriverManager.getConnection(str_conn, usuario, senha);
                    stmt = conn.createStatement();
                    sql1 = "SELECT * FROM usuarios WHERE user_login = '" + us_login + "' AND user_pass = '" + us_pass + "'";
                    rs1 = stmt.executeQuery(sql1);//Verifica o login e a senha
                    if (rs1.first())//Caso exista o usuario, o servidor vai permitir o login, atualizando as informações do usuário
                    {
                        sql2 = "UPDATE usuarios SET user_ip = '" + us_ip + "', user_port = " + us_port + ", user_status = 1 WHERE user_login = '" + us_login + "'";
                        stmt.executeUpdate(sql2);//Atualiza as informações do usuário
                        System.out.println("Usuario " + us_login + " conectado     IP: " + us_ip + "     Porta: " + us_port);
                        msg.enviaOK(serverSocket, 0, u_ip, us_port);//Envia uma mensagem de OK para o cliente
                        System.out.println("OK - Mensagem enviada - Usuario logado com sucesso - login 0");
                    } else {
                        msg.enviaERR(serverSocket, 0, u_ip, us_port);//Envia uma mensagem de erro para o cliente
                        System.out.println("ERR - Mensagem enviada - Erro no login - login 0");
                    }
                    break;
                case ('1')://Mensagem de cadastro
                    //As mensagens de cadastro têm a forma: 0%%<user_login>%%<user_pass>%%
                    System.out.println("OK - Mensagem lida - Tentativa de cadastro -cadastro 1");
                    us_login = msg.GetFirstS();//Recebe o nome de usuário
                    us_pass = msg.GetSecondS();//Recebe a senha
                    Class.forName(driver);
                    conn = DriverManager.getConnection(str_conn, usuario, senha);
                    stmt = conn.createStatement();
                    sql1 = "SELECT user_login FROM usuarios WHERE user_login = '" + us_login + "'";
                    rs1 = stmt.executeQuery(sql1);//Verifica o nome de usuario
                    if (rs1.first())//Caso já exista o usuario
                    {
                        msg.enviaERR(serverSocket, 1, u_ip, us_port);
                        System.out.println("ERR - Mensagem enviada - Usuario ja cadastrado - cadastro 1");
                    } else {//Caso não exista, insere o usuário na tabela usuarios
                        sql2 = "INSERT INTO usuarios VALUES ('" + us_login + "' , '" + us_pass + "' ,'NULL',0,0)";
                        stmt.executeUpdate(sql2);
                        System.out.println("Novo usuario '" + us_login + "' adicionado ao sistema");
                        msg.enviaOK(serverSocket, 1, u_ip, us_port);
                        System.out.println("OK - Mensagem enviada - Cadastro efetuado com sucesso - cadastro 1");
                    }
                    break;
                case ('2')://Mensagem de texto msg: 
                    //As mensagens de texto têm a forma: 2%%<nome_origem>%%<nome_destino>%%<mensagem>%%
                    //Pacote repassado para o destino: 2%%<nome_origem>%%<mensagem>
                    System.out.println("OK - Mensagem lida - Envio de mensagem - mensagem 2");
                    String destino;
                    String mensagem;
                    String IP_destino;
                    int porta_destino;
                    int status_destino;
                    us_login = msg.GetFirstS();//Recebe o nome de usuário origem
                    destino = msg.GetSecondS();//Recebe o nome de usuário destino
                    mensagem = msg.GetMSG();//Recebe a mensagem
                    try {
                        Class.forName(driver);
                        conn = DriverManager.getConnection(str_conn, usuario, senha);
                        stmt = conn.createStatement();
                        sql1 = "SELECT * FROM usuarios WHERE user_login = '" + destino + "'";
                        rs1 = stmt.executeQuery(sql1);//Vai obter o ip e a porta do destino para o envio da mensagem
                        rs1.first();
                        IP_destino = rs1.getString("user_ip");
                        porta_destino = rs1.getInt("user_port");
                        status_destino = rs1.getInt("user_status");
                        if (status_destino == 0) {//Se o usuário estiver offline, manda uma mensagem de erro
                            msg.enviaERR(serverSocket, 9, u_ip, us_port);
                            System.out.println("ERR - Erro na repassagem da mensagem de '" + us_login + "' para '" + destino + "' - mensagem 2");
                        } else {
                            msg.enviaMSG(mensagem, serverSocket, us_login, IP_destino, porta_destino);
                            msg.enviaOK(serverSocket, 9, u_ip, us_port);
                            System.out.println("OK  - Mensagem repassada de '" + us_login + "' para '" + destino + "' - mensagem 2");
                        }
                    } catch (SQLException ex) {
                        msg.probSQL(ex);
                    }
                    break;
                case ('3')://Adicionar contato 
                    //As mensagens de adição de contato têm a forma: 3%%<nome de quem aceitou>%%<nome de quem requeriu>%%<resposta>%%
                    //Recebendo a confirmacao do segundo usuario, remove a requisicao da tabela
                    //Cria duas ligacoes: uma 1->2 e outra 2->1
                    System.out.println("OK - Mensagem lida - Adicao de amigo - adicionar 3");
                    String amigo;
                    String resposta;
                    us_login = msg.GetFirstS();
                    amigo = msg.GetSecondS();
                    resposta = msg.GetThirdS();//Recebe a resposta
                    Class.forName(driver);
                    conn = DriverManager.getConnection(str_conn, usuario, senha);
                    stmt = conn.createStatement();
                    sql1 = "DELETE FROM requisicoes WHERE name2 = '" + us_login + "' AND name1= '" + amigo + "'";
                    stmt.executeUpdate(sql1);//Deleta a requisicao
                    System.out.println("Requisicao de novo contato entre '" + us_login + "' e '" + amigo + "' deletada");
                    if (resposta.compareTo("SIM") == 0) {
                        sql2 = "INSERT INTO contatos VALUES ('" + us_login + "', '" + amigo + "')";
                        sql3 = "INSERT INTO contatos VALUES ('" + amigo + "', '" + us_login + "')";
                        stmt.executeUpdate(sql2);//Adiciona 1 ligacao
                        stmt.executeUpdate(sql3);//Adiciona a ligacao inversa
                        System.out.println("Novo contato entre '" + us_login + "' e '" + amigo + "' criado");
                        msg.enviaOK(serverSocket, 3, u_ip, us_port);
                        System.out.println("OK - Mensagem enviada - Ligacao de amizade feita - adicionar 3");
                    } else {
                        System.out.println("Novo contato entre '" + us_login + "' e '" + amigo + "' rejeitado");
                        msg.enviaERR(serverSocket, 3, u_ip, us_port);
                        System.out.println("OK - Mensagem enviada - Ligacao de amizade rejeitada - adicionar 3");
                    }
                    break;
                case ('4')://Mudanca de status   msg: 
                    //As mensagens de mudança de status têm a forma: 4%%<us_login>%%<status>%%
                    System.out.println("OK - Mensagem lida - Tentativa de mudanca de status - status 4");
                    us_login = msg.GetFirstS();
                    us_status = msg.GetSecondI();
                    Class.forName(driver);
                    conn = DriverManager.getConnection(str_conn, usuario, senha);
                    stmt = conn.createStatement();
                    sql1 = "UPDATE usuarios SET user_status = " + us_status + " WHERE user_login = '" + us_login + "'";
                    stmt.executeUpdate(sql1);//Atualiza o banco
                    System.out.println("Status do usuarios '" + us_login + "' modificado para: " + us_status);
                    msg.enviaOK(serverSocket, 4, u_ip, us_port);
                    System.out.println("OK - Mensagem enviada - Status modificado - status 4");
                    break;
                case ('5')://Receber requisição de novo contato 
                    //As mensagens de requisição de novo contato têm a forma: 5%%<nome do requisitante>%%<nome do amigo>%%
                    //Vai adicionar uma requisição na tabela e no próximo keepalive o amigo receberá a requisição
                    System.out.println("OK - Mensagem lida - Requisicao de amigo - requisicao 5");
                    String contato;
                    us_login = msg.GetFirstS();
                    contato = msg.GetSecondS();
                    Class.forName(driver);
                    conn = DriverManager.getConnection(str_conn, usuario, senha);
                    stmt = conn.createStatement();
                    sql1 = "SELECT user_login FROM usuarios WHERE user_login = '" + contato + "' AND user_login != '" + us_login + "'";
                    rs1 = stmt.executeQuery(sql1);
                    if (rs1.first()) {//Caso exista o usuario
                        sql2 = "SELECT * FROM contatos WHERE name1 = '" + us_login + "' AND name2 = '" + contato + "'";
                        rs2 = stmt.executeQuery(sql2);
                        if (rs2.first()) {//Caso ja exista relacao entre os usuarios
                            System.out.println("Relacao entre '" + us_login + "' e '" + contato + "' ja existe");
                            msg.enviaERRi(serverSocket, 5, 2, u_ip, us_port);
                            System.out.println("ERR - Mensagem enviada - Relacao entre os contatos ja existe - requisicao 5");
                        } else {
                            sql3 = "SELECT * FROM requisicoes WHERE name2 = '" + contato + "' AND name1= '" + us_login + "'";
                            rs3 = stmt.executeQuery(sql3);
                            if (rs3.first()) {//Caso ja exista a requisicao
                                System.out.println("Requisicao de novo contato entre '" + us_login + "' e '" + contato + "' ja exsite");
                                msg.enviaERRi(serverSocket, 5, 3, u_ip, us_port);
                                System.out.println("ERR - Mensagem enviada - Requisicao de amizade ja existe - requisicao 5");
                            } else {
                                sql4 = "INSERT INTO requisicoes VALUES ('" + contato + "', '" + us_login + "')";
                                stmt.executeUpdate(sql4);//Insere a requisicao
                                System.out.println("Requisicao de novo contato entre '" + us_login + "' e '" + contato + "' adicionada");
                                msg.enviaOK(serverSocket, 5, u_ip, us_port);
                                System.out.println("OK - Mensagem enviada - Requisicao de amizade feita - requisicao 5");
                            }
                        }
                    } else {
                        System.out.println("Usuario '" + contato + "' nao existe");
                        msg.enviaERRi(serverSocket, 5, 1, u_ip, us_port);
                        System.out.println("ERR - Mensagem enviada - Usuario nao existe - requisicao 5");
                    }
                    break;
                case ('6')://Keepalive 
                    //As mensagens de keepalive têm a forma: 6%%<user_login>%%
                    System.out.println("OK - Mensagem lida - Mensagem de Keepalive - keepalive 6");
                    us_login = msg.GetFirstS();
                    String on = "6%%";//Mensagem com os contatos online
                    String off = "6%%";//Mensagem com os contatos offline
                    String req = "6";//Mensagem as requisições de contato
                    Class.forName(driver);
                    conn = DriverManager.getConnection(str_conn, usuario, senha);
                    stmt = conn.createStatement();
                    //Mensagens:
                    //ON : 6%%<usuario>&&<status>%%<usuario>&&<status>%% ... %%<usuario>&&<status>%%&&&
                    //OFF : 6%%<usuario>%%<usuario>%% ... %%<usuario>%%&&&
                    //REQ : 6%%<usuario>%%&&& Caso nao tenha requisicao: 6%%&&&
                    sql1 = "SELECT c.name2, u.user_status FROM contatos c, usuarios u WHERE c.name1 = '" + us_login + "' AND u.user_login = c.name2";
                    rs1 = stmt.executeQuery(sql1);
                    while (rs1.next()) {
                        if ((rs1.getString("user_status").compareTo("0")) == 0) {
                            off = off + rs1.getString("name2") + "%%";
                        } else {
                            on = on + rs1.getString("name2") + "$$" + rs1.getString("user_status") + "%%";
                        }
                    }
                    off = off + "&&&";
                    on = on + "&&&";
                    //Vai obter as requisições
                    sql2 = "SELECT name1 FROM requisicoes WHERE name2 = '" + us_login + "'";
                    rs2 = stmt.executeQuery(sql2);
                    while (rs2.next()) {
                        req = req + "%%" + rs2.getString("name1");
                    }
                    req = req + "%%&&&";

                    msg.envia(on, serverSocket, u_ip, us_port);
                    msg.envia(off, serverSocket, u_ip, us_port);
                    msg.envia(req, serverSocket, u_ip, us_port);
                    msg.enviaOK(serverSocket, 6, u_ip, us_port);

                    System.out.println("OK - Mensagem enviada - Informacoes de keepalive enviadas - keepalive 6");
                    break;
                case ('7')://Pedido de aviso MSG: 7%%<user_login>%%
                    //As mensagens de pedido de aviso têm a forma: 7%%<user_login>%%
                    //Usuário pede para o servidor informar para todos seus amigos que ele está online
                    //Esse pedido só é feito quando o usuario se loga
                    System.out.println("OK - Mensagem lida - Mensagem de pedido de aviso - pedido 7");
                    us_login = msg.GetFirstS();
                    try {
                        Class.forName(driver);
                        conn = DriverManager.getConnection(str_conn, usuario, senha);
                        stmt = conn.createStatement();
                        sql1 = "SELECT u.user_ip, u.user_port FROM contatos c, usuarios u WHERE c.name1 = '" + us_login + "' AND u.user_login = c.name2 AND u.user_status != 0";
                        rs1 = stmt.executeQuery(sql1);
                        while (rs1.next()) {
                            String IP_des;
                            int port_des;
                            IP_des = rs1.getString("user_ip");
                            port_des = rs1.getInt("user_port");
                            msg.enviaAviso(serverSocket, us_login, IP_des, port_des);
                        }
                        msg.enviaOK(serverSocket, 7, u_ip, us_port);
                        System.out.println("OK - Mensagem enviada - Usuarios avisados - pedido 7");
                    } catch (SQLException ex) {
                        msg.probSQL(ex);
                    }
                    break;
                case ('8')://Remoção de contato   
                    //As mensagens de remoção de contato têm a forma: msg: 8%%<nome do requisitante>%%<nome do usuario a ser removido da lista>%%
                    System.out.println("OK - Mensagem lida - Remocao de contato - remover 8");
                    String user;
                    us_login = msg.GetFirstS();
                    user = msg.GetSecondS();
                    Class.forName(driver);
                    conn = DriverManager.getConnection(str_conn, usuario, senha);
                    stmt = conn.createStatement();
                    sql1 = "SELECT * FROM contatos WHERE name1 = '" + us_login + "' AND name2 = '" + user + "'";
                    rs1 = stmt.executeQuery(sql1);
                    if (rs1.first()) {//Caso exista a ligacao
                        Class.forName(driver);
                        conn = DriverManager.getConnection(str_conn, usuario, senha);
                        stmt = conn.createStatement();
                        sql2 = "DELETE FROM contatos WHERE name1 = '" + us_login + "' AND name2= '" + user + "'";
                        sql3 = "DELETE FROM contatos WHERE name1 = '" + user + "' AND name2= '" + us_login + "'";
                        stmt.executeUpdate(sql2);//Atualiza o banco
                        stmt.executeUpdate(sql3);//Atualiza o banco
                        System.out.println("Ligacao entre '" + us_login + "' e '" + user + "' removida");
                        msg.enviaOK(serverSocket, 8, u_ip, us_port);
                        System.out.println("OK - Mensagem enviada - Remocao feita - remover 8");
                    } else {
                        System.out.println("Usuario '" + user + "' nao existe");
                        msg.enviaERR(serverSocket, 8, u_ip, us_port);
                        System.out.println("ERR - Mensagem enviada - Contato nao existe - remover 8");
                    }
                    break;
                default:
                    System.out.println("----------Problemas na interpretacao da mensagem----------");
                    msg.enviaERR(serverSocket, 9, u_ip, us_port);
                    break;
            }
        }
    }
}
