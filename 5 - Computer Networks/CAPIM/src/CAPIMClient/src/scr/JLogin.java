package scr;

import javax.swing.JOptionPane;

public class JLogin extends javax.swing.JFrame {

    public JLogin() {
        initComponents();
    }

    public static void main(String[] args) {
        JLogin Janela1 = new JLogin();
        Janela1.setVisible(true);
    }

    // <editor-fold defaultstate="collapsed" desc="Generated Code">
    private void initComponents() {

        buttonGroup1 = new javax.swing.ButtonGroup();
        PainelPrincipal = new javax.swing.JPanel();
        Rodape = new javax.swing.JLabel();
        Logotipo = new javax.swing.JLabel();
        LabelUser = new javax.swing.JLabel();
        LabelSenha = new javax.swing.JLabel();
        CampoSenha = new javax.swing.JPasswordField();
        CampoUser = new javax.swing.JTextField();
        Entrar = new javax.swing.JButton();
        Cadastre = new javax.swing.JButton();
        Menu = new javax.swing.JMenuBar();
        MenuArquivo = new javax.swing.JMenu();
        jMenuItem2 = new javax.swing.JMenuItem();
        jMenuItem1 = new javax.swing.JMenuItem();
        MenuContatos = new javax.swing.JMenu();
        BotaoAdicionar = new javax.swing.JMenuItem();
        BotaoExcluir = new javax.swing.JMenuItem();
        MenuAjuda = new javax.swing.JMenu();
        BotaoSobre = new javax.swing.JMenuItem();
        BotaoInformações = new javax.swing.JMenuItem();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("CAPIM - Instant Messenger");
        setAlwaysOnTop(false);

        //setBounds(new java.awt.Rectangle(200, 100, 0, 0));
        setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        setResizable(false);

        PainelPrincipal.setBackground(new java.awt.Color(204, 255, 204));

        Rodape.setIcon(new javax.swing.ImageIcon(getClass().getResource("/images/logo2.png"))); // NOI18N
        Rodape.setText("CAPIM - Redes 2009.1 - Computação UFC");

        Logotipo.setIcon(new javax.swing.ImageIcon(getClass().getResource("/images/logo.png"))); // NOI18N

        LabelUser.setText("Usuário:");

        LabelSenha.setText("Senha:");

        CampoUser.setPreferredSize(new java.awt.Dimension(90, 20));

        Entrar.setText("Entrar");
        Entrar.setAlignmentY(0.0F);
        Entrar.addActionListener(new java.awt.event.ActionListener() {

            public void actionPerformed(java.awt.event.ActionEvent evt) {
                EntrarActionPerformed(evt);
            }
        });

        Cadastre.setFont(new java.awt.Font("Tahoma", 1, 11)); // NOI18N
        Cadastre.setForeground(new java.awt.Color(0, 102, 0));
        Cadastre.setText("Cadastre-se já!");
        Cadastre.setContentAreaFilled(false);
        Cadastre.setFocusCycleRoot(true);
        Cadastre.addMouseListener(new java.awt.event.MouseAdapter() {

            public void mousePressed(java.awt.event.MouseEvent evt) {
                CadastreMousePressed(evt);
            }
        });

        org.jdesktop.layout.GroupLayout PainelPrincipalLayout = new org.jdesktop.layout.GroupLayout(PainelPrincipal);
        PainelPrincipal.setLayout(PainelPrincipalLayout);
        PainelPrincipalLayout.setHorizontalGroup(
                PainelPrincipalLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING).add(Rodape, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 400, Short.MAX_VALUE).add(PainelPrincipalLayout.createSequentialGroup().add(123, 123, 123).add(Logotipo).addContainerGap(127, Short.MAX_VALUE)).add(PainelPrincipalLayout.createSequentialGroup().add(70, 70, 70).add(PainelPrincipalLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING).add(PainelPrincipalLayout.createSequentialGroup().add(PainelPrincipalLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING).add(LabelUser).add(LabelSenha)).addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED).add(PainelPrincipalLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING, false).add(CampoSenha).add(CampoUser, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 180, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))).add(org.jdesktop.layout.GroupLayout.TRAILING, PainelPrincipalLayout.createSequentialGroup().add(84, 84, 84).add(Entrar, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 93, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE).add(47, 47, 47))).addContainerGap(106, Short.MAX_VALUE)).add(org.jdesktop.layout.GroupLayout.TRAILING, PainelPrincipalLayout.createSequentialGroup().addContainerGap(133, Short.MAX_VALUE).add(Cadastre, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 137, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE).add(130, 130, 130)));
        PainelPrincipalLayout.setVerticalGroup(
                PainelPrincipalLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING).add(PainelPrincipalLayout.createSequentialGroup().add(68, 68, 68).add(Logotipo).add(63, 63, 63).add(PainelPrincipalLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING).add(LabelUser).add(CampoUser, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 25, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)).addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED).add(PainelPrincipalLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE).add(CampoSenha, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 25, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE).add(LabelSenha)).add(18, 18, 18).add(Entrar).addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED, 56, Short.MAX_VALUE).add(Cadastre, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 30, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE).add(45, 45, 45).add(Rodape)));

        Menu.setAutoscrolls(true);
        Menu.setFont(new java.awt.Font("Tahoma", 0, 10));

        MenuArquivo.setText("Arquivo");
        MenuArquivo.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        MenuArquivo.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        MenuArquivo.setPreferredSize(new java.awt.Dimension(80, 19));

        jMenuItem2.setText("Sair");
        jMenuItem2.setEnabled(false);
        jMenuItem2.setPreferredSize(new java.awt.Dimension(80, 19));
        MenuArquivo.add(jMenuItem2);

        jMenuItem1.setText("Fechar");
        jMenuItem1.setPreferredSize(new java.awt.Dimension(60, 19));
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
        BotaoAdicionar.setEnabled(false);

        MenuContatos.add(BotaoAdicionar);

        BotaoExcluir.setText("Excluir");
        BotaoExcluir.setEnabled(false);
        MenuContatos.add(BotaoExcluir);

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
    }// </editor-fold>

    private void CadastreMousePressed(java.awt.event.MouseEvent evt) {
        new JCadastro().setVisible(true);
        this.dispose();
    }

    private void FecharJanela(java.awt.event.ActionEvent evt) {

        this.dispose();
    }

    private void EntrarActionPerformed(java.awt.event.ActionEvent evt) {

        text[0] = "0%%";   // ID = 1%% -> login
        text[1] = CampoUser.getText();
        text[2] = CampoSenha.getText();
        text[3] = ".%";

        if (text[1].isEmpty() || text[2].isEmpty()) {
            JOptionPane.showMessageDialog(this, "Preencha todos os campos corretamente!", "Erro", JOptionPane.ERROR_MESSAGE);
            CampoUser.setText("");
            CampoSenha.setText("");
        } else {
            Entrar.setEnabled(false);
            CampoUser.setEnabled(false);
            CampoSenha.setEnabled(false);
            setCursor(new java.awt.Cursor(java.awt.Cursor.WAIT_CURSOR));

            try {

                msg.msgusuario(text);
                if (msg.getCodigo().compareTo("OK") == 0)//mensagem de confirmação do servidor
                {
                    JOptionPane.showMessageDialog(this, "Login efetuado com sucesso!", "Confirmação", JOptionPane.PLAIN_MESSAGE);
                    new JPrincipal(text[1], msg).setVisible(true);  //aqui tem que fechar a tela de login e abrir a principal
                    this.dispose();
                } else if (msg.getCodigo().compareTo("ERR") == 0) {
                    JOptionPane.showMessageDialog(this, "Usuario ou senha incorretos. Digite novamente!", "Dados incorretos", JOptionPane.WARNING_MESSAGE);
                    setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
                } else {
                    JOptionPane.showMessageDialog(this, "Login nao efetuado", "Erro", JOptionPane.WARNING_MESSAGE);
                }
            } catch (Exception e) {
                JOptionPane.showMessageDialog(this, "Erro no envio dos dados", "Erro", JOptionPane.WARNING_MESSAGE);
            }
            Entrar.setEnabled(true); //tratamento para nova tentativa de cadastro
            CampoUser.setEnabled(true);
            CampoSenha.setEnabled(true);
            CampoUser.setText("");
            CampoSenha.setText("");
            setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        }
    }
    private String[] text = new String[4];
    private Mensagem msg = new Mensagem();
    // Variables declaration - do not modify
    private javax.swing.JMenuItem BotaoAdicionar;
    private javax.swing.JMenuItem BotaoExcluir;
    private javax.swing.JMenuItem BotaoInformações;
    private javax.swing.JMenuItem BotaoSobre;
    private javax.swing.JButton Cadastre;
    private javax.swing.JPasswordField CampoSenha;
    private javax.swing.JTextField CampoUser;
    private javax.swing.JButton Entrar;
    private javax.swing.JLabel LabelSenha;
    private javax.swing.JLabel LabelUser;
    private javax.swing.JLabel Logotipo;
    private javax.swing.JMenuBar Menu;
    private javax.swing.JMenu MenuAjuda;
    private javax.swing.JMenu MenuArquivo;
    private javax.swing.JMenu MenuContatos;
    private javax.swing.JPanel PainelPrincipal;
    private javax.swing.JLabel Rodape;
    private javax.swing.ButtonGroup buttonGroup1;
    private javax.swing.JMenuItem jMenuItem1;
    private javax.swing.JMenuItem jMenuItem2;
    // End of variables declaration
}
