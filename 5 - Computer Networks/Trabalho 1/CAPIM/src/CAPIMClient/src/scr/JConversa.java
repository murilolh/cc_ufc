package scr;

import java.awt.event.*;
import javax.swing.*;

public class JConversa extends javax.swing.JFrame {

    public JConversa(String User, String Friend) {
        Nick = User;
        Destino = Friend;
        initComponents(Nick, Destino);
    }

    // <editor-fold defaultstate="collapsed" desc="Generated Code">
    private void initComponents(String Nick, String Destino) {

        listModel = new javax.swing.DefaultListModel();
        buttonGroup1 = new javax.swing.ButtonGroup();
        jPanel2 = new javax.swing.JPanel();
        jScrollPane3 = new javax.swing.JScrollPane();
        QuadroDigita = new javax.swing.JTextArea();
        Enviar = new javax.swing.JButton();
        Logotipo = new javax.swing.JLabel();
        CampoNickname = new javax.swing.JTextField();
        jSeparator1 = new javax.swing.JSeparator();
        jScrollPane1 = new javax.swing.JScrollPane();
        QuadroConversa = new javax.swing.JTextArea();
        jLabel1 = new javax.swing.JLabel();
        jScrollPane2 = new javax.swing.JScrollPane();

        Menu = new javax.swing.JMenuBar();
        MenuArquivo = new javax.swing.JMenu();
        jMenuItem1 = new javax.swing.JMenuItem();
        jMenu3 = new javax.swing.JMenu();

        setDefaultCloseOperation(javax.swing.WindowConstants.DISPOSE_ON_CLOSE);
        setTitle("CAPIM - " + Destino + " - Conversa");
        setAlwaysOnTop(true);
        setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));

        jPanel2.setBackground(new java.awt.Color(204, 255, 204));

        QuadroDigita.setColumns(20);
        QuadroDigita.setRows(5);
        QuadroDigita.setBorder(javax.swing.BorderFactory.createMatteBorder(1, 1, 1, 1, new java.awt.Color(0, 204, 204)));
        QuadroDigita.setCaretColor(new java.awt.Color(0, 153, 153));
        QuadroDigita.addKeyListener(new java.awt.event.KeyAdapter() {

            public void keyReleased(java.awt.event.KeyEvent evt) {
                EnviarKeyReleased(evt);
            }
        });
        jScrollPane3.setViewportView(QuadroDigita);

        Enviar.setLabel("Enviar");
        Enviar.addActionListener(new java.awt.event.ActionListener() {

            public void actionPerformed(java.awt.event.ActionEvent evt) {
                EnviarActionPerformed(evt);
            }
        });

        Logotipo.setIcon(new javax.swing.ImageIcon(getClass().getResource("/images/logo3.png"))); // NOI18N

        CampoNickname.setBackground(new java.awt.Color(0, 153, 102));
        CampoNickname.setEditable(false);
        CampoNickname.setFont(new java.awt.Font("Comic Sans MS", 1, 14));
        CampoNickname.setForeground(new java.awt.Color(255, 255, 255));
        CampoNickname.setHorizontalAlignment(javax.swing.JTextField.LEFT);
        CampoNickname.setText(" " + Nick);
        CampoNickname.setAlignmentX(0.0F);
        CampoNickname.setAlignmentY(0.0F);
        CampoNickname.setBorder(null);

        jSeparator1.setBorder(javax.swing.BorderFactory.createEmptyBorder(1, 1, 1, 1));

        QuadroConversa.setColumns(20);
        QuadroConversa.setEditable(false);
        QuadroConversa.setRows(5);
        jScrollPane1.setViewportView(QuadroConversa);

        jLabel1.setIcon(new javax.swing.ImageIcon(getClass().getResource("/images/logo2.png"))); // NOI18N
        jLabel1.setText("CAPIM - Redes 2009.1 - Computação UFC");

        listModel.addElement(" " + Destino);
        Destinatarios = new JList(listModel);
        Destinatarios.setVisibleRowCount(2);
        jScrollPane2.setViewportView(Destinatarios);

        org.jdesktop.layout.GroupLayout jPanel2Layout = new org.jdesktop.layout.GroupLayout(jPanel2);
        jPanel2.setLayout(jPanel2Layout);
        jPanel2Layout.setHorizontalGroup(
                jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING).add(jPanel2Layout.createSequentialGroup().addContainerGap().add(jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING).add(org.jdesktop.layout.GroupLayout.TRAILING, jScrollPane1, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 380, Short.MAX_VALUE).add(jScrollPane3, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 380, Short.MAX_VALUE).add(org.jdesktop.layout.GroupLayout.TRAILING, jLabel1, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 380, Short.MAX_VALUE).add(jSeparator1, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 380, Short.MAX_VALUE).add(org.jdesktop.layout.GroupLayout.TRAILING, Enviar).add(jPanel2Layout.createSequentialGroup().add(jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING).add(CampoNickname, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 275, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE).add(jScrollPane2, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 276, Short.MAX_VALUE)).addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED).add(Logotipo))).addContainerGap()));
        jPanel2Layout.setVerticalGroup(
                jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING).add(jPanel2Layout.createSequentialGroup().addContainerGap().add(jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING).add(Logotipo, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 50, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE).add(jPanel2Layout.createSequentialGroup().add(CampoNickname, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE).addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED).add(jScrollPane2, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 36, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))).add(18, 18, 18).add(jScrollPane1, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 197, Short.MAX_VALUE).addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED).add(jSeparator1, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 6, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE).addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED).add(jScrollPane3, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 99, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE).addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED).add(Enviar).addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED).add(jLabel1).addContainerGap()));

        Menu.setFont(new java.awt.Font("Tahoma", 0, 10));

        MenuArquivo.setText("Arquivo");
        MenuArquivo.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        MenuArquivo.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        MenuArquivo.setPreferredSize(new java.awt.Dimension(80, 19));

        jMenuItem1.setText("Fechar");
        jMenuItem1.setPreferredSize(new java.awt.Dimension(80, 19));
        jMenuItem1.addActionListener(new java.awt.event.ActionListener() {

            public void actionPerformed(java.awt.event.ActionEvent evt) {
                FecharActionPerformed(evt);
            }
        });
        MenuArquivo.add(jMenuItem1);

        Menu.add(MenuArquivo);

        jMenu3.setText("Editar");
        jMenu3.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        jMenu3.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        jMenu3.setPreferredSize(new java.awt.Dimension(80, 19));
        Menu.add(jMenu3);

        setJMenuBar(Menu);

        org.jdesktop.layout.GroupLayout layout = new org.jdesktop.layout.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
                layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING).add(jPanel2, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE));
        layout.setVerticalGroup(
                layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING).add(jPanel2, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE));

        pack();
    }// </editor-fold>

    private void EnviaMensagem() {
        msg = String.valueOf(QuadroDigita.getText());
        QuadroConversa.append(" " + Nick + " diz: " + msg + "\n");
        QuadroDigita.setText("");
        text[0] = "2%%";   // ID = 2%% -> conversa
        text[1] = Nick;
        text[2] = Destino;
        text[3] = msg;
        text[4] = ".%";

        try {
            msg2.msgusuario(text);
            if (msg2.getCodigo().compareTo("OK") == 0) //mensagem de confirmação do servidor
            {
                System.err.println("Conversa Enviada");
            } else if (msg2.getCodigo().compareTo("ERR") == 0) //mensagem de confirmação do servidor
            {
                System.err.println("Usuario esta Offline");
            } else {
                System.err.println(msg2.getCodigo());
            }
        } catch (Exception e) {
            System.err.println("Problema no envio da conversa");
        }
    }

    private void EnviarActionPerformed(java.awt.event.ActionEvent evt) {
        EnviaMensagem();
    }

    public void Conversas(String Amigo, String Conversa) {
        this.setVisible(true);
        QuadroConversa.append(" " + Amigo + " diz: " + Conversa + "\n");
        Conversa conversa = new Conversa(Amigo, Conversa, this);
        conversa.start();
    }

    private void EnviarKeyReleased(java.awt.event.KeyEvent evt) {
        if (evt.getKeyCode() == KeyEvent.VK_ENTER) {
            EnviaMensagem();
        //falta tratar pq ele tah pulando linha
        }
    }

    private void FecharActionPerformed(java.awt.event.ActionEvent evt) {
        setDefaultCloseOperation(javax.swing.WindowConstants.DISPOSE_ON_CLOSE);
        this.dispose();
    }
    public String Destino;
    private String Nick;
    private String[] text = new String[6];
    private Mensagem msg2 = new Mensagem();
    private String msg;
    // Variables declaration - do not modify
    private javax.swing.JTextField CampoNickname;
    private javax.swing.JList Destinatarios;
    private javax.swing.DefaultListModel listModel;
    private javax.swing.JButton Enviar;
    private javax.swing.JLabel Logotipo;
    private javax.swing.JMenuBar Menu;
    private javax.swing.JMenu MenuArquivo;
    public javax.swing.JTextArea QuadroConversa;
    private javax.swing.JTextArea QuadroDigita;
    private javax.swing.ButtonGroup buttonGroup1;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JMenu jMenu3;
    private javax.swing.JMenuItem jMenuItem1;
    private javax.swing.JPanel jPanel2;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JScrollPane jScrollPane2;
    private javax.swing.JScrollPane jScrollPane3;
    private javax.swing.JSeparator jSeparator1;
    // End of variables declaration
}
