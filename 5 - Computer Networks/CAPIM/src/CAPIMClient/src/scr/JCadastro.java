package scr;

import javax.swing.JOptionPane;

public class JCadastro extends javax.swing.JFrame {

    public JCadastro() {
        initComponents();
    }

    // <editor-fold defaultstate="collapsed" desc="Generated Code">
    private void initComponents() {

        buttonGroup1 = new javax.swing.ButtonGroup();
        PainelPrincipal = new javax.swing.JPanel();
        Rodape = new javax.swing.JLabel();
        Logotipo = new javax.swing.JLabel();
        LabelUser = new javax.swing.JLabel();
        LabelSenha = new javax.swing.JLabel();
        LabelSenha1 = new javax.swing.JLabel();
        CampoSenha = new javax.swing.JPasswordField();
        CampoUser = new javax.swing.JTextField();
        CampoSenha1 = new javax.swing.JPasswordField();
        Cadastrar = new javax.swing.JButton();
        jLabel2 = new javax.swing.JLabel();
        Menu = new javax.swing.JMenuBar();
        MenuArquivo = new javax.swing.JMenu();
        jMenuItem2 = new javax.swing.JMenuItem();
        jMenuItem1 = new javax.swing.JMenuItem();
        MenuContatos = new javax.swing.JMenu();
        BotaoAdcionar = new javax.swing.JMenuItem();
        BotaoExcluir = new javax.swing.JMenuItem();
        MenuAjuda = new javax.swing.JMenu();
        BotaoSobre = new javax.swing.JMenuItem();
        BotaoInformações = new javax.swing.JMenuItem();

        setDefaultCloseOperation(javax.swing.WindowConstants.DISPOSE_ON_CLOSE);
        setTitle("CAPIM - Instant Messenger");
        setAlwaysOnTop(false);
        //setBounds(new java.awt.Rectangle(400, 100, 0, 0));
        setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        setResizable(false);

        PainelPrincipal.setBackground(new java.awt.Color(204, 255, 204));

        Rodape.setIcon(new javax.swing.ImageIcon(getClass().getResource("/images/logo2.png"))); // NOI18N
        Rodape.setText("CAPIM - Redes 2009.1 - Computação UFC");

        Logotipo.setIcon(new javax.swing.ImageIcon(getClass().getResource("/images/logo.png"))); // NOI18N

        LabelUser.setText("Usuário:");

        LabelSenha.setText("Senha:");

        LabelSenha1.setText("Senha novamente:");

        CampoUser.setPreferredSize(new java.awt.Dimension(90, 20));

        Cadastrar.setText("Cadastrar");
        Cadastrar.setAlignmentY(0.0F);
        Cadastrar.addActionListener(new java.awt.event.ActionListener() {

            public void actionPerformed(java.awt.event.ActionEvent evt) {
                CadastrarActionPerformed(evt);
            }
        });

        jLabel2.setFont(new java.awt.Font("Monotype Corsiva", 0, 24));
        jLabel2.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        jLabel2.setText("Cadastro de Usuários");
        jLabel2.setMaximumSize(new java.awt.Dimension(150, 38));
        jLabel2.setMinimumSize(new java.awt.Dimension(150, 38));
        jLabel2.setPreferredSize(new java.awt.Dimension(150, 38));

        org.jdesktop.layout.GroupLayout PainelPrincipalLayout = new org.jdesktop.layout.GroupLayout(PainelPrincipal);
        PainelPrincipal.setLayout(PainelPrincipalLayout);
        PainelPrincipalLayout.setHorizontalGroup(
                PainelPrincipalLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING).add(Rodape, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 400, Short.MAX_VALUE).add(PainelPrincipalLayout.createSequentialGroup().add(123, 123, 123).add(Logotipo).addContainerGap(127, Short.MAX_VALUE)).add(PainelPrincipalLayout.createSequentialGroup().add(33, 33, 33).add(PainelPrincipalLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING).add(PainelPrincipalLayout.createSequentialGroup().add(PainelPrincipalLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING).add(LabelUser).add(LabelSenha).add(LabelSenha1)).addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED).add(PainelPrincipalLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING, false).add(CampoSenha).add(CampoUser, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 180, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE).add(CampoSenha1, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 180, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))).add(PainelPrincipalLayout.createSequentialGroup().add(73, 73, 73).add(jLabel2, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 210, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))).addContainerGap(84, Short.MAX_VALUE)).add(org.jdesktop.layout.GroupLayout.TRAILING, PainelPrincipalLayout.createSequentialGroup().addContainerGap(170, Short.MAX_VALUE).add(Cadastrar, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 93, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE).add(137, 137, 137)));
        PainelPrincipalLayout.setVerticalGroup(
                PainelPrincipalLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING).add(PainelPrincipalLayout.createSequentialGroup().add(68, 68, 68).add(Logotipo).add(41, 41, 41).add(jLabel2, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE).add(18, 18, 18).add(PainelPrincipalLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING).add(LabelUser).add(CampoUser, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 25, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)).addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED).add(PainelPrincipalLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE).add(CampoSenha, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 25, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE).add(LabelSenha)).addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED).add(PainelPrincipalLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE).add(CampoSenha1, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 25, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE).add(LabelSenha1)).add(18, 18, 18).add(Cadastrar).addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED, 66, Short.MAX_VALUE).add(Rodape)));

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

        BotaoAdcionar.setText("Adcionar");
        BotaoAdcionar.setEnabled(false);
        MenuContatos.add(BotaoAdcionar);

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
        BotaoSobre.addActionListener(new java.awt.event.ActionListener() {

            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BotaoSobreActionPerformed(evt);
            }
        });

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

    private void FecharJanela(java.awt.event.ActionEvent evt) {
        setDefaultCloseOperation(javax.swing.WindowConstants.DISPOSE_ON_CLOSE);
    }

    private void CadastrarActionPerformed(java.awt.event.ActionEvent evt) {

        text[0] = "1%%";   // ID = 1%% -> cadastro
        text[1] = CampoUser.getText();
        text[2] = CampoSenha.getText();
        text[3] = ".%";

        if (text[1].isEmpty() || text[2].isEmpty() || CampoSenha1.getText().isEmpty()) {
            JOptionPane.showMessageDialog(this, "Preencha todos os campos corretamente!", "Dados Incorretos", JOptionPane.WARNING_MESSAGE);
            CampoSenha.setText("");
            CampoSenha1.setText("");
        } else if (!text[2].equals(CampoSenha1.getText())) {
            JOptionPane.showMessageDialog(this, "Senha inválida. Digite novamente ", "Senha digitada incorretamente", JOptionPane.WARNING_MESSAGE);
            CampoSenha.setText("");
            CampoSenha1.setText("");
        } else {
            Cadastrar.setEnabled(false);
            CampoUser.setEnabled(false);
            CampoSenha.setEnabled(false);
            setCursor(new java.awt.Cursor(java.awt.Cursor.WAIT_CURSOR));
            try {
                msg.msgusuario(text);
                if (msg.getCodigo().compareTo("OK") == 0) //mensagem de confirmação do servidor
                {
                    JOptionPane.showMessageDialog(this, "Cadastro efetuado com sucesso!", "Confirmação", JOptionPane.PLAIN_MESSAGE);
                    new JLogin().setVisible(true);
                    this.dispose();   //aqui tem que fechar a tela de cadastro e ficar so a tela de login
                } else if (msg.getCodigo().compareTo("ERR") == 0) {
                    JOptionPane.showMessageDialog(this, "Esse usuário ja esta cadastrado!", "Erro", JOptionPane.WARNING_MESSAGE);
                    setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
                } else {
                    JOptionPane.showMessageDialog(this, "Cadastro nao efetuado", "Problemas no cadastro", JOptionPane.WARNING_MESSAGE);
                }
            } catch (Exception e) {
                JOptionPane.showMessageDialog(this, "Erro no envio dos dados", "Erro", JOptionPane.ERROR_MESSAGE);
            }
            setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
            Cadastrar.setEnabled(true);   //tratamento para nova tentativa de cadastro
            CampoUser.setEnabled(true);
            CampoSenha.setEnabled(true);
            CampoSenha1.setEnabled(true);
            CampoUser.setText("");
            CampoSenha.setText("");
            CampoSenha1.setText("");

        }
    }

    private void BotaoSobreActionPerformed(java.awt.event.ActionEvent evt) {
    }
    private String[] text = new String[4];
    private String resposta;
    private Mensagem msg = new Mensagem();

    // Variables declaration - do not modify
    private javax.swing.JMenuItem BotaoAdcionar;
    private javax.swing.JMenuItem BotaoExcluir;
    private javax.swing.JMenuItem BotaoInformações;
    private javax.swing.JMenuItem BotaoSobre;
    private javax.swing.JPasswordField CampoSenha;
    private javax.swing.JPasswordField CampoSenha1;
    private javax.swing.JTextField CampoUser;
    private javax.swing.JButton Cadastrar;
    private javax.swing.JLabel LabelSenha;
    private javax.swing.JLabel LabelSenha1;
    private javax.swing.JLabel LabelUser;
    private javax.swing.JLabel Logotipo;
    private javax.swing.JMenuBar Menu;
    private javax.swing.JMenu MenuAjuda;
    private javax.swing.JMenu MenuArquivo;
    private javax.swing.JMenu MenuContatos;
    private javax.swing.JPanel PainelPrincipal;
    private javax.swing.JLabel Rodape;
    private javax.swing.ButtonGroup buttonGroup1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JMenuItem jMenuItem1;
    private javax.swing.JMenuItem jMenuItem2;
    // End of variables declaration
}
