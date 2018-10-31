package scr;

public class KeepAlive extends Thread {

    // construtor KeepAlive atribui nome a thread chamando
    // construtor Thread
    public KeepAlive(String name, String User, JPrincipal janela) {
        super(name);
        Login = User;
        Atualized = janela;
    }

// executa a thread
    public void run() {

        text[0] = "6%%";
        text[1] = Login;
        text[2] = ".%";

        while (true) {

            sleepTime = 10000;

            try {
                try {
                    msg.msgusuario(text);

                    if (msg.getCodigo().compareTo("OK") == 0)//mensagem de confirmação do servidor
                    {
                        System.out.println("Servidor recebeu KeepAlive");
                        Atualized.setUsersOnline(msg.getAmigosON());
                        Atualized.setUsersOffline(msg.getAmigosOFF());
                        Atualized.mostrarRequisicoes(msg.getRequisicoes());
                    }
                } catch (Exception e) {
                    System.err.println("Resposta do KeepAlive nao lida");
                }
                Thread.sleep(sleepTime);
            }
            catch (InterruptedException exception) {
                System.err.println(exception.toString());
            }
        }
    }
    // variaveis
    private int sleepTime;
    private String Login;
    private String[] text = new String[3];
    private JPrincipal Atualized;
    private Mensagem msg = new Mensagem();
}
