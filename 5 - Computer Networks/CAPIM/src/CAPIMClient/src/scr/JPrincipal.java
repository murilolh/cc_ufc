package scr;

import javax.swing.JOptionPane;
import java.awt.event.*;

public class JPrincipal extends javax.swing.JFrame {

    public JPrincipal(String User, Mensagem msg) {
        Nick = User;
        msg1 = msg;
        initComponents(Nick);
        //EstouON();
        AguardaConversas();
        keepalive();

    }

    // <editor-fold defaultstate="collapsed" desc="Generated Code">
    private void initComponents(String Nick) {

        buttonGroup1 = new javax.swing.ButtonGroup();
        jMenuBar1 = new javax.swing.JMenuBar();
        jMenu1 = new javax.swing.JMenu();
        jMenu2 = new javax.swing.JMenu();
        PainelPrincipal = new javax.swing.JPanel();
        Rodape = new javax.swing.JLabel();
        jLabel1 = new javax.swing.JLabel();
        jScrollPane3 = new javax.swing.JScrollPane();
        UsersOnline = new javax.swing.JList();
        jLabel2 = new javax.swing.JLabel();
        jScrollPane2 = new javax.swing.JScrollPane();
        UserOff = new javax.swing.JList();
        CampoNickname = new javax.swing.JTextField(Nick);
        Status = new javax.swing.JList();
        Logotipo = new javax.swing.JLabel();
        jSeparator2 = new javax.swing.JSeparator();
        jLabel3 = new javax.swing.JLabel();
        Menu = new javax.swing.JMenuBar();
        MenuArquivo = new javax.swing.JMenu();
        jMenuItem2 = new javax.swing.JMenuItem();
        jSeparator1 = new javax.swing.JSeparator();
        jMenuItem1 = new javax.swing.JMenuItem();
        MenuContatos = new javax.swing.JMenu();
        BotaoAdicionar = new javax.swing.JMenuItem();
        BotaoExcluir = new javax.swing.JMenuItem();
        MenuAjuda = new javax.swing.JMenu();
        BotaoSobre = new javax.swing.JMenuItem();
        BotaoInformações = new javax.swing.JMenuItem();

        jMenu1.setText("File");
        jMenuBar1.add(jMenu1);

        jMenu2.setText("Edit");
        jMenuBar1.add(jMenu2);


        setTitle("CAPIM - Instant Messenger");
        setAlwaysOnTop(false);
        //setBounds(new java.awt.Rectangle(400, 100, 0, 0));
        setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));

        PainelPrincipal.setBackground(new java.awt.Color(153, 255, 153));

        Rodape.setIcon(new javax.swing.ImageIcon(getClass().getResource("/images/logo2.png"))); // NOI18N
        Rodape.setText("CAPIM - Redes 2009.1 - Computação UFC");

        jLabel1.setFont(new java.awt.Font("Tahoma", 1, 11));
        jLabel1.setText("Online:");


        UsersOnline.setModel(new javax.swing.AbstractListModel() {

            String[] strings = {};

            public int getSize() {
                return strings.length;
            }

            public Object getElementAt(int i) {
                return strings[i];
            }
        });
        UsersOnline.setSelectionMode(javax.swing.ListSelectionModel.SINGLE_SELECTION);
        UsersOnline.setFocusable(false);
        UsersOnline.addMouseListener(new java.awt.event.MouseAdapter() {

            public void mouseClicked(java.awt.event.MouseEvent evt) {
                UsersOnlineMouseClicked(evt);
            }
        });
        jScrollPane3.setViewportView(UsersOnline);

        jLabel2.setFont(new java.awt.Font("Tahoma", 1, 11));
        jLabel2.setText("Offline:");

        UserOff.setModel(new javax.swing.AbstractListModel() {

            String[] strings = {};

            public int getSize() {
                return strings.length;
            }

            public Object getElementAt(int i) {
                return strings[i];
            }
        });
        UserOff.setSelectionMode(javax.swing.ListSelectionModel.SINGLE_SELECTION);
        jScrollPane2.setViewportView(UserOff);

        CampoNickname.setBackground(new java.awt.Color(0, 153, 102));
        CampoNickname.setEditable(false);
        CampoNickname.setFont(new java.awt.Font("Comic Sans MS", 1, 14));
        CampoNickname.setForeground(new java.awt.Color(255, 255, 255));
        CampoNickname.setHorizontalAlignment(javax.swing.JTextField.LEFT);
        CampoNickname.setText(" " + Nick);
        CampoNickname.setAlignmentX(0.0F);
        CampoNickname.setAlignmentY(0.0F);
        CampoNickname.setBorder(null);

        Status.setFont(new java.awt.Font("Tahoma", 0, 10));
        Status.setModel(new javax.swing.AbstractListModel() {

            String[] strings = {"Online", "Ocupado", "Ausente"};

            public int getSize() {
                return strings.length;
            }

            public Object getElementAt(int i) {
                return strings[i];
            }
        });
        Status.setFocusable(false);
        Status.addMouseListener(new java.awt.event.MouseAdapter() {

            public void mouseClicked(java.awt.event.MouseEvent evt) {
                StatusMouseClicked(evt);
            }
        });

        Logotipo.setIcon(new javax.swing.ImageIcon(getClass().getResource("/images/logo3.png"))); // NOI18N

        jLabel3.setFont(new java.awt.Font("Tahoma", 1, 11));
        jLabel3.setText("LISTA DE CONTATOS");

        org.jdesktop.layout.GroupLayout PainelPrincipalLayout = new org.jdesktop.layout.GroupLayout(PainelPrincipal);
        PainelPrincipal.setLayout(PainelPrincipalLayout);
        PainelPrincipalLayout.setHorizontalGroup(
                PainelPrincipalLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING).add(Rodape, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 400, Short.MAX_VALUE).add(PainelPrincipalLayout.createSequentialGroup().addContainerGap().add(PainelPrincipalLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING).add(PainelPrincipalLayout.createSequentialGroup().add(CampoNickname, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 254, Short.MAX_VALUE).add(26, 26, 26)).add(PainelPrincipalLayout.createSequentialGroup().add(Status, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 144, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE).addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED))).add(10, 10, 10).add(Logotipo, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 100, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)).add(org.jdesktop.layout.GroupLayout.TRAILING, PainelPrincipalLayout.createSequentialGroup().addContainerGap().add(jSeparator2, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 380, Short.MAX_VALUE).addContainerGap()).add(PainelPrincipalLayout.createSequentialGroup().addContainerGap().add(jScrollPane2, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 380, Short.MAX_VALUE).addContainerGap()).add(PainelPrincipalLayout.createSequentialGroup().addContainerGap().add(jLabel2).addContainerGap(351, Short.MAX_VALUE)).add(PainelPrincipalLayout.createSequentialGroup().addContainerGap().add(jScrollPane3, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 380, Short.MAX_VALUE).addContainerGap()).add(PainelPrincipalLayout.createSequentialGroup().addContainerGap().add(jLabel1).addContainerGap(352, Short.MAX_VALUE)).add(org.jdesktop.layout.GroupLayout.TRAILING, PainelPrincipalLayout.createSequentialGroup().addContainerGap(147, Short.MAX_VALUE).add(jLabel3).add(141, 141, 141)));
        PainelPrincipalLayout.setVerticalGroup(
                PainelPrincipalLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING).add(org.jdesktop.layout.GroupLayout.TRAILING, PainelPrincipalLayout.createSequentialGroup().add(PainelPrincipalLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING).add(PainelPrincipalLayout.createSequentialGroup().addContainerGap().add(CampoNickname, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE).addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED).add(Status, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)).add(Logotipo)).addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED).add(jSeparator2, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 10, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE).addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED).add(jLabel3).addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED, 7, Short.MAX_VALUE).add(jLabel1).addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED).add(jScrollPane3, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 176, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE).addPreferredGap(org.jdesktop.layout.LayoutStyle.UNRELATED).add(jLabel2).addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED).add(jScrollPane2, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 112, Short.MAX_VALUE).addPreferredGap(org.jdesktop.layout.LayoutStyle.UNRELATED).add(Rodape)));

        Menu.setAutoscrolls(true);
        Menu.setFont(new java.awt.Font("Tahoma", 0, 10));

        MenuArquivo.setText("Arquivo");
        MenuArquivo.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        MenuArquivo.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        MenuArquivo.setPreferredSize(new java.awt.Dimension(80, 19));

        jMenuItem2.setText("Sair");
        jMenuItem2.setEnabled(true);
        jMenuItem2.setPreferredSize(new java.awt.Dimension(80, 19));
        jMenuItem2.addActionListener(new java.awt.event.ActionListener() {

            public void actionPerformed(java.awt.event.ActionEvent evt) {
                SairPrograma(evt);
            }
        });
        MenuArquivo.add(jMenuItem2);
        MenuArquivo.add(jSeparator1);

        jMenuItem1.setText("Fechar");
        jMenuItem1.setPreferredSize(new java.awt.Dimension(80, 19));
        jMenuItem1.addActionListener(new java.awt.event.ActionListener() {

            public void actionPerformed(java.awt.event.ActionEvent evt) {
                FecharJanela(evt);
            }
        });
        MenuArquivo.add(jMenuItem1);

        Menu.add(MenuArquivo);

        MenuContatos.setText("Contatos");
        MenuContatos.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        MenuContatos.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        MenuContatos.setPreferredSize(new java.awt.Dimension(80, 19));

        BotaoAdicionar.setText("Adicionar");
        BotaoAdicionar.addActionListener(new java.awt.event.ActionListener() {

            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BotaoAdicionarActionPerformed(evt);
            }
        });
        MenuContatos.add(BotaoAdicionar);

        BotaoExcluir.setText("Excluir");
        MenuContatos.add(BotaoExcluir);
        BotaoExcluir.addActionListener(new java.awt.event.ActionListener() {

            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BotaoExcluirActionPerformed(evt);
            }
        });

        Menu.add(MenuContatos);

        MenuAjuda.setText("Ajuda");
        MenuAjuda.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        MenuAjuda.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        MenuAjuda.setPreferredSize(new java.awt.Dimension(80, 19));

        BotaoSobre.setText("Sobre o CAPIM");
        MenuAjuda.add(BotaoSobre);

        BotaoInformações.setText("Mais informações");
        MenuAjuda.add(BotaoInformações);

        Menu.add(MenuAjuda);

        setJMenuBar(Menu);

        org.jdesktop.layout.GroupLayout layout = new org.jdesktop.layout.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
                layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING).add(PainelPrincipal, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE));
        layout.setVerticalGroup(
                layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING).add(PainelPrincipal, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE));

        pack();
        this.setLocationRelativeTo(null);
        setDefaultCloseOperation(javax.swing.WindowConstants.DO_NOTHING_ON_CLOSE);
        this.addWindowListener(new WindowAdapter() {

            public void windowClosing(WindowEvent evt) {
                //caixa de dialogo retorna um inteiro
                FecharPrograma(evt);
            }
        });
    }// </editor-fold>

    //public void windowClosing(WindowEvent e) {
    //}
    public void setUsersOnline(String[] args) {
        UsersOnline.setListData(args);
    }

    public void Conversas(String Amigo, String Conversa) {
        janela1 = new JConversa(Nick, Amigo);
        janela1.Conversas(Amigo, Conversa);
    }

    public void setUsersOffline(String[] args) {
        UserOff.setListData(args);
    }

    public void mostrarRequisicoes(String[] args) {

        while (!args[i].equals(".")) {
            text[0] = "3%%"; //adicionar
            text[1] = Nick;
            text[4] = ".%";
            String[] opcoes = new String[]{"Sim", "Não"};
            int retorno = JOptionPane.showOptionDialog(this, args[i] + " quer ser seu amigo. Você aceita?",
                    "Solicitação de Amizade",
                    JOptionPane.YES_NO_CANCEL_OPTION,
                    JOptionPane.QUESTION_MESSAGE,
                    null, opcoes, opcoes[0]);
            System.out.println("Retorno da confirmação: " + retorno);
            text[2] = args[i];
            if (retorno == 0) {
                try {
                    text[3] = "SIM";

                    msg1.msgusuario(text);

                    if (msg1.getCodigo().compareTo("OK") == 0)//mensagem de confirmação do servidor
                    {
                        System.out.println("Aceitacao SIM de amizade enviada");
                    }
                } catch (Exception e) {
                    System.err.println("Problema no envio da Aceitacao");
                }
            } else {
                try {
                    text[3] = "NAO";
                    msg1.msgusuario(text);

                    if (msg1.getCodigo().compareTo("OK") == 0)//mensagem de confirmação do servidor
                    {
                        System.out.println("Aceitacao NAO de amizade enviada");
                    }
                } catch (Exception e) {
                    System.err.println("Problema no envio da Aceitacao");
                }
            }
            i++;
        }
    }

    public void mostrarAvisos(String[] args) {

        while (!args[i].equals(".")) {
            JOptionPane.showMessageDialog(this, args[i] + "acabou de entrar. ", "Usuario online", JOptionPane.OK_OPTION);
            this.dispose(); //aqui tem que fechar a tela adicionar e ficar so a tela principal
            setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        }
        i++;
    }

    public void EstouON() {
        text[0] = "7%%"; //7%%<user_login>%%
        text[1] = Nick;
        text[2] = ".%";

        try {
            msg1.msgusuario(text);
            if (msg1.getCodigo().compareTo("OK") == 0) //mensagem de confirmação do servidor
            {
                System.out.println("Mensagem de status enviada");
            }

        } catch (Exception e) {
            System.err.println("Problema no envio de mudanca de status");
        }

    }

    public void AguardaConversas() {
        AguardaConversas conversa = new AguardaConversas("Conversar", this);
        conversa.start(); //inicia a thread do keepalie
    }

    public void keepalive() {
        KeepAlive keep = new KeepAlive("keep", Nick, this);
        keep.start(); //inicia a thread do keepalie
    }

    private void FecharPrograma(WindowEvent evt) {
        int resposta = JOptionPane.showConfirmDialog(null, "Deseja encerrar o CAPIM?", "Finalizar o sistema", JOptionPane.YES_NO_OPTION);
        //sim = 0, nao = 1
        if (resposta == 0) {

            text[0] = "4%%"; //4%%<us_login>%%<status>%%   Setar offline
            text[1] = Nick;
            text[2] = "0";
            text[3] = ".%";

            try {
                msg1.msgusuario(text);
                if (msg1.getCodigo().compareTo("OK") == 0) //mensagem de confirmação do servidor
                {
                    System.exit(0);
                }

            } catch (Exception exception) {
                System.err.println("Problema no envio de mudanca de status");
            }

            System.exit(0);
        }

    }

    private void FecharJanela(java.awt.event.ActionEvent evt) {
        setDefaultCloseOperation(javax.swing.WindowConstants.DISPOSE_ON_CLOSE);
        text[0] = "4%%"; //4%%<us_login>%%<status>%%   Setar offline
        text[1] = Nick;
        text[2] = "0";
        text[3] = ".%";

        try {
            msg1.msgusuario(text);
            if (msg1.getCodigo().compareTo("OK") == 0) //mensagem de confirmação do servidor
            {
                System.exit(0);
            }

        } catch (Exception e) {
            System.err.println("Problema no envio de mudanca de status");
        }

    }

    private void SairPrograma(java.awt.event.ActionEvent evt) {

        text[0] = "4%%"; //4%%<us_login>%%<status>%%   Setar offline
        text[1] = Nick;
        text[2] = "0";
        text[3] = ".%";

        try {
            msg1.msgusuario(text);
            if (msg1.getCodigo().compareTo("OK") == 0) //mensagem de confirmação do servidor
            {
                JLogin Janela1 = new JLogin();
                Janela1.setVisible(true);
                this.dispose();
            }

        } catch (Exception e) {
            System.err.println("Problema no envio de mudanca de status");
        }

    }

    private void BotaoAdicionarActionPerformed(java.awt.event.ActionEvent evt) {

        BotaoAdicionar.setEnabled(false);
        tela = new TelaAdicionar(Nick, msg1, this);
        tela.setVisible(true);
    }

    private void BotaoExcluirActionPerformed(java.awt.event.ActionEvent evt) {

        BotaoExcluir.setEnabled(false);
        Tela = new TelaExcluir(Nick, msg1, this);
        Tela.setVisible(true);
    }

    private void StatusMouseClicked(java.awt.event.MouseEvent evt) {
        text[0] = "4%%"; //4%%<us_login>%%<status>%%   Setar offline
        text[1] = Nick;
        text[3] = ".%";
        //Inativa cliques com botao direito
        if (evt.isMetaDown() || evt.isAltDown()) {
        } //dois cliques para setar status
        else if (evt.getClickCount() == 2) {

            //FriendOn = (String) UsersOnline.getSelectedValue();
            if (Status.getSelectedValue() == null) {
                return;
            } else if (Status.getSelectedValue() == "Online") {
                text[2] = "1";
            } else if (Status.getSelectedValue() == "Ocupado") {
                text[2] = "2";
            } else if (Status.getSelectedValue() == "Ausente") {
                text[2] = "3";
            }
        }
        try {
            msg1.msgusuario(text);
            if (msg1.getCodigo().compareTo("OK") == 0) //mensagem de confirmação do servidor
            {
                System.out.println("enviou mudança de status");
            }
        } catch (Exception e) {
            System.err.println("Problema no envio de mudanca de status");
        }
    }

    private void UsersOnlineMouseClicked(java.awt.event.MouseEvent evt) {
        //Inativa cliques com botao direito
        if (evt.isMetaDown() || evt.isAltDown()) {
        } //dois cliques para abrir janela de onversa
        else if (evt.getClickCount() == 2) {
            FriendOn = (String) UsersOnline.getSelectedValue();
            if (UsersOnline.getSelectedValue() == null) {
                return;
            } else {
                new JConversa(Nick, FriendOn).setVisible(true);
            }
        }

    }
    // Variables declaration - do not modify
    private JConversa janela1;
    private String Nick,  FriendOn;
    private String[] text = new String[5];
    private Mensagem msg1 = new Mensagem();
    private TelaAdicionar tela;
    private TelaExcluir Tela;
//private TelaAdicoesPendentes Tela;
    private int i = 0;
    public javax.swing.JMenuItem BotaoAdicionar;
    public javax.swing.JMenuItem BotaoExcluir;
    private javax.swing.JMenuItem BotaoInformações;
    private javax.swing.JMenuItem BotaoSobre;
    private javax.swing.JTextField CampoNickname;
    private javax.swing.JLabel Logotipo;
    private javax.swing.JMenuBar Menu;
    private javax.swing.JMenu MenuAjuda;
    private javax.swing.JMenu MenuArquivo;
    private javax.swing.JMenu MenuContatos;
    private javax.swing.JPanel PainelPrincipal;
    private javax.swing.JLabel Rodape;
    private javax.swing.JList Status;
    private javax.swing.JList UserOff;
    private javax.swing.JList UsersOnline;
    private javax.swing.ButtonGroup buttonGroup1;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JMenu jMenu1;
    private javax.swing.JMenu jMenu2;
    private javax.swing.JMenuBar jMenuBar1;
    private javax.swing.JMenuItem jMenuItem1;
    private javax.swing.JMenuItem jMenuItem2;
    private javax.swing.JScrollPane jScrollPane2;
    private javax.swing.JScrollPane jScrollPane3;
    private javax.swing.JSeparator jSeparator1;
    private javax.swing.JSeparator jSeparator2;
    // End of variables declaration
}
