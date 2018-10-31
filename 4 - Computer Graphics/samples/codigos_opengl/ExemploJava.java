/**
 * Classe Renderer, junto com a classe ExemploJava, mostra um exemplo de 
 * como trabalhar com Java e OpenGL utilizando a API JOGL. � aberta uma 
 * janela na qual � desenhado um "torus" com ilumina��o. � poss�vel fazer 
 * zoom in e zoom out usando o mouse, e mover a posi��o do observador 
 * virtual com as teclas de setas, HOME e END.
 * Este c�digo acompanha o livro "OpenGL - Uma Abordagem Pr�tica e Objetiva".
 * 
 * @author Marcelo Cohen e Isabel H. Manssour
 * @version 1.0
 */

import javax.swing.*;
import java.awt.*; 
import java.awt.event.*; 
import net.java.games.jogl.*;

public class ExemploJava
{
	private Renderer renderer;

	/**
	 * Construtor da classe ExemploJava que n�o recebe par�metros. Cria uma janela e insere  
	 * um componente canvas OpenGL.
	 */
	public ExemploJava()
	{
		// Cria janela
		JFrame janela = new JFrame("Desenho de um torus 3D com ilumina��o");   
		janela.setBounds(50,100,500,500); 
		janela.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);

		BorderLayout layout = new BorderLayout(); 
		Container caixa=janela.getContentPane();
		caixa.setLayout(layout); 

		// Cria um objeto GLCapabilities para especificar o n�mero de bits 
		// por pixel para RGBA
		GLCapabilities c = new GLCapabilities();
		c.setRedBits(8);
		c.setBlueBits(8);
		c.setGreenBits(8);
		c.setAlphaBits(8); 

		// Cria o objeto que ir� gerenciar os eventos
		renderer = new Renderer();

		// Cria um canvas, adiciona na janela, e especifica o objeto "ouvinte" 
		// para os eventos Gl, de mouse e teclado
		GLCanvas canvas = GLDrawableFactory.getFactory().createGLCanvas(c);
		janela.add(canvas,BorderLayout.CENTER);
		canvas.addGLEventListener(renderer);        
		canvas.addMouseListener(renderer);
		canvas.addMouseMotionListener(renderer);
		canvas.addKeyListener(renderer);
		janela.setVisible(true);
		canvas.requestFocus();
	}

	/**
	 * M�todo main que apenas cria um objeto ExemploJava.
	 */
	public static void main(String args[])
	{
		ExemploJava ej = new ExemploJava();
	}
}
