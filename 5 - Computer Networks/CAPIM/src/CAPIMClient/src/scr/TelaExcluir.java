package scr;

import javax.swing.JOptionPane;

public class TelaExcluir extends javax.swing.JFrame {

    public TelaExcluir(String User, Mensagem msg, JPrincipal Janela) {
        janela = Janela;
        Nick = User;
        msg1 = msg;
        initComponents();
    }

    // <editor-fold defaultstate="collapsed" desc="Generated Code">
    private void initComponents() {

        buttonGroup1 = new javax.swing.ButtonGroup();
        PainelPrincipal = new javax.swing.JPanel();
        Excluir = new javax.swing.JButton();
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

        Excluir.setText("Excluir");
        Excluir.setAlignmentY(0.0F);
        Excluir.addActionListener(new java.awt.event.ActionListener() {

            public void actionPerformed(java.awt.event.ActionEvent evt) {
                ExcluirActionPerformed(evt);
            }
        });

        Texto.setFont(new java.awt.Font("Tahoma", 1, 11)); // NOI18N
        Texto.setText("Usuario:");

        Titulo.setBackground(new java.awt.Color(0, 204, 102));
        Titulo.setFont(new java.awt.Font("Tahoma", 1, 14)); // NOI18N
        Titulo.setIcon(new javax.swing.ImageIcon(getClass().getResource("/images/logo2.png"))); // NOI18N
        Titulo.setText("Excluir Contato");

        org.jdesktop.layout.GroupLayout PainelPrincipalLayout = new org.jdesktop.layout.GroupLayout(PainelPrincipal);
        PainelPrincipal.setLayout(PainelPrincipalLayout);
        PainelPrincipalLayout.setHorizontalGroup(
                PainelPrincipalLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING).add(PainelPrincipalLayout.createSequentialGroup().add(PainelPrincipalLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING).add(PainelPrincipalLayout.createSequentialGroup().addContainerGap().add(Texto)).add(PainelPrincipalLayout.createSequentialGroup().add(110, 110, 110).add(Excluir, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 93, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)).add(PainelPrincipalLayout.createSequentialGroup().add(82, 82, 82).add(Titulo)).add(PainelPrincipalLayout.createSequentialGroup().addContainerGap().add(CampoUsuario, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 271, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))).addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)));
        PainelPrincipalLayout.setVerticalGroup(
                PainelPrincipalLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING).add(PainelPrincipalLayout.createSequentialGroup().addContainerGap().add(Titulo, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 44, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE).add(11, 11, 11).add(Texto).addPreferredGap(org.jdesktop.layout.LayoutStyle.UNRELATED).add(CampoUsuario, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE).add(25, 25, 25).add(Excluir).addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)));

        org.jdesktop.layout.GroupLayout layout = new org.jdesktop.layout.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
                layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING).add(PainelPrincipal, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE));
        layout.setVerticalGroup(
                layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING).add(PainelPrincipal, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE));

        pack();
        this.setLocationRelativeTo(null);
    }// </editor-fold>

    private void ExcluirActionPerformed(java.awt.event.ActionEvent evt) {

        text[0] = "8%%";   // ID = 5%% -> requisicao
        text[1] = Nick;
        text[2] = CampoUsuario.getText();
        text[3] = ".%";

        if (text[2].isEmpty()) {
            //trata campo nao digitado
        } else {

            Excluir.setEnabled(false);
            CampoUsuario.setEnabled(false);
            setCursor(new java.awt.Cursor(java.awt.Cursor.WAIT_CURSOR));
            try {
                msg1.msgusuario(text);
                if (msg1.getCodigo().compareTo("OK") == 0) //mensagem de confirmação do servidor
                {
                    JOptionPane.showMessageDialog(this, "Requisicao de exclusão enviada com sucesso!", "Exclusao", JOptionPane.OK_OPTION);
                    this.dispose(); //aqui tem que fechar a tela Excluir e ficar so a tela principal
                    janela.BotaoExcluir.setEnabled(true);
                    setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
                } else if (msg1.getCodigo().compareTo("ERR") == 0) {
                    JOptionPane.showMessageDialog(this, "Você nao é amigo desse usuário!", "Erro", JOptionPane.OK_OPTION);
                    this.dispose(); //aqui tem que fechar a tela adicionar e ficar so a tela principal
                    janela.BotaoExcluir.setEnabled(true);
                    setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
                } else {
                    JOptionPane.showMessageDialog(this, "Falha no envio da requisição de exclusão!", "Erro", JOptionPane.OK_OPTION);
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
    private javax.swing.JButton Excluir;
    private javax.swing.JTextField CampoUsuario;
    private javax.swing.JPanel PainelPrincipal;
    private javax.swing.JLabel Texto;
    private javax.swing.JLabel Titulo;
    private javax.swing.ButtonGroup buttonGroup1;
    // End of variables declaration
}
