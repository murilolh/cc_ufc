package scr;

import javax.swing.JOptionPane;

public class TelaAdicionar extends javax.swing.JFrame {

    public TelaAdicionar(String User, Mensagem msg, JPrincipal Janela) {
        janela = Janela;
        Nick = User;
        msg1 = msg;
        initComponents();
    }

    // <editor-fold defaultstate="collapsed" desc="Generated Code">
    private void initComponents() {

        buttonGroup1 = new javax.swing.ButtonGroup();
        PainelPrincipal = new javax.swing.JPanel();
        Adicionar = new javax.swing.JButton();
        Texto = new javax.swing.JLabel();
        CampoUsuario = new javax.swing.JTextField();
        Titulo = new javax.swing.JLabel();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("CAPIM - Instant Messenger");
        setAlwaysOnTop(false);
        //setBounds(new java.awt.Rectangle(0, 0, 0, 0));
        setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        setResizable(false);

        PainelPrincipal.setBackground(new java.awt.Color(204, 255, 204));

        Adicionar.setText("Adicionar");
        Adicionar.setAlignmentY(0.0F);
        Adicionar.addActionListener(new java.awt.event.ActionListener() {

            public void actionPerformed(java.awt.event.ActionEvent evt) {
                AdicionarActionPerformed(evt);
            }
        });

        Texto.setFont(new java.awt.Font("Tahoma", 1, 11)); // NOI18N
        Texto.setText("Usuario:");

        Titulo.setBackground(new java.awt.Color(0, 204, 102));
        Titulo.setFont(new java.awt.Font("Tahoma", 1, 14)); // NOI18N
        Titulo.setIcon(new javax.swing.ImageIcon(getClass().getResource("/images/logo2.png"))); // NOI18N
        Titulo.setText("Adicionar Contato");

        org.jdesktop.layout.GroupLayout PainelPrincipalLayout = new org.jdesktop.layout.GroupLayout(PainelPrincipal);
        PainelPrincipal.setLayout(PainelPrincipalLayout);
        PainelPrincipalLayout.setHorizontalGroup(
                PainelPrincipalLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING).add(PainelPrincipalLayout.createSequentialGroup().add(PainelPrincipalLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING).add(PainelPrincipalLayout.createSequentialGroup().addContainerGap().add(Texto)).add(PainelPrincipalLayout.createSequentialGroup().add(110, 110, 110).add(Adicionar, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 93, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)).add(PainelPrincipalLayout.createSequentialGroup().add(82, 82, 82).add(Titulo)).add(PainelPrincipalLayout.createSequentialGroup().addContainerGap().add(CampoUsuario, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 271, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))).addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)));
        PainelPrincipalLayout.setVerticalGroup(
                PainelPrincipalLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING).add(PainelPrincipalLayout.createSequentialGroup().addContainerGap().add(Titulo, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 44, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE).add(11, 11, 11).add(Texto).addPreferredGap(org.jdesktop.layout.LayoutStyle.UNRELATED).add(CampoUsuario, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE).add(25, 25, 25).add(Adicionar).addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)));

        org.jdesktop.layout.GroupLayout layout = new org.jdesktop.layout.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
                layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING).add(PainelPrincipal, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE));
        layout.setVerticalGroup(
                layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING).add(PainelPrincipal, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE));

        pack();
        this.setLocationRelativeTo(null);
    }// </editor-fold>

    private void AdicionarActionPerformed(java.awt.event.ActionEvent evt) {

        text[0] = "5%%";   // ID = 5%% -> requisicao
        text[1] = Nick;
        text[2] = CampoUsuario.getText();
        text[3] = ".%";

        if (text[2].isEmpty()) {
            //trata campo nao digitado
        } else {
            Adicionar.setEnabled(false);
            CampoUsuario.setEnabled(false);
            setCursor(new java.awt.Cursor(java.awt.Cursor.WAIT_CURSOR));
            try {
                msg1.msgusuario(text);

                if (msg1.getCodigo().compareTo("OK") == 0) //mensagem de confirmação do servidor
                {
                    JOptionPane.showMessageDialog(this, "Requisicao de amizade enviada com sucesso!", "Confirmação", JOptionPane.PLAIN_MESSAGE);
                    this.dispose(); //aqui tem que fechar a tela adicionar e ficar so a tela principal
                    janela.BotaoAdicionar.setEnabled(true);
                    setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
                } else if (msg1.getCodigo().compareTo("ERR1") == 0) {
                    JOptionPane.showMessageDialog(this, "Usuário inexistente!", "Erro", JOptionPane.WARNING_MESSAGE);
                    this.dispose(); //aqui tem que fechar a tela adicionar e ficar so a tela principal
                    janela.BotaoAdicionar.setEnabled(true);
                    setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
                } else if (msg1.getCodigo().compareTo("ERR2") == 0) {
                    JOptionPane.showMessageDialog(this, "Esse usuario já é seu amigo!", "Erro", JOptionPane.WARNING_MESSAGE);
                    this.dispose(); //aqui tem que fechar a tela adicionar e ficar so a tela principal
                    janela.BotaoAdicionar.setEnabled(true);
                    setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
                } else if (msg1.getCodigo().compareTo("ERR3") == 0) {
                    JOptionPane.showMessageDialog(this, "Voce ja fez uma requisicao de amizade para este usuário!", "Erro", JOptionPane.WARNING_MESSAGE);
                    this.dispose(); //aqui tem que fechar a tela adicionar e ficar so a tela principal
                    janela.BotaoAdicionar.setEnabled(true);
                    setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
                } else {
                    JOptionPane.showMessageDialog(this, "Falha no envio da requisicao de amizade!", "Erro", JOptionPane.ERROR_MESSAGE);
                }
            } catch (Exception e) {
                JOptionPane.showMessageDialog(this, "Erro no envio dos dados!", "Erro", JOptionPane.ERROR_MESSAGE);
            }
        }
    }
    private JPrincipal janela;
    private String Nick;
    private String[] text = new String[4];
    private Mensagem msg1;
    // Variables declaration - do not modify
    private javax.swing.JButton Adicionar;
    private javax.swing.JTextField CampoUsuario;
    private javax.swing.JPanel PainelPrincipal;
    private javax.swing.JLabel Texto;
    private javax.swing.JLabel Titulo;
    private javax.swing.ButtonGroup buttonGroup1;
    // End of variables declaration
}
