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

import java.awt.event.*; 
import net.java.games.jogl.*;
import net.java.games.jogl.util.GLUT;

public class Renderer extends MouseAdapter implements GLEventListener, KeyListener, MouseMotionListener
{
	// Atributos
	private GL gl;
	private GLU glu;
	private GLUT glut;
	private GLDrawable glDrawable;
	private float angle, fAspect;
	private float rotX, rotY, rotX_ini, rotY_ini;
	private float obsX, obsY, obsZ, obsX_ini, obsY_ini, obsZ_ini;
	private int x_ini,y_ini,bot;

	/**
	 * Construtor da classe Renderer que n�o recebe par�metros.
	 */
	public Renderer()
	{
		// Especifica o �ngulo da proje��o perspectiva  
		angle=44;
		// Posi��o do observador virtual
		rotX = 0;
		rotY = 0;
		obsZ = 150;     
		// Inicializa o valor para corre��o de aspecto   
		fAspect = 1;    
	}

	/**
	 * M�todo definido na interface GLEventListener e chamado pelo objeto no qual ser� feito o desenho
	 * logo ap�s a inicializa��o do contexto OpenGL. 
	 */    
	public void init(GLDrawable drawable)
	{
		glDrawable = drawable;
		gl = drawable.getGL();
		glu = drawable.getGLU();       
		glut = new GLUT();

		drawable.setGL(new DebugGL(gl));        

		gl.glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		gl.glEnable(GL.GL_COLOR_MATERIAL);
		gl.glEnable(GL.GL_LIGHTING);  
		gl.glEnable(GL.GL_LIGHT0);
		gl.glEnable(GL.GL_DEPTH_TEST);
		gl.glShadeModel(GL.GL_SMOOTH);         
	}

	/**
	 * M�todo definido na interface GLEventListener e chamado pelo objeto no qual ser� feito o desenho
	 * para come�ar a fazer o desenho OpenGL pelo cliente.
	 */  
	public void display(GLDrawable drawable)
	{
		gl.glClear(GL.GL_COLOR_BUFFER_BIT | GL.GL_DEPTH_BUFFER_BIT );
		gl.glLoadIdentity();    

		defineIluminacao();
		especificaParametrosVisualizacao(); 

		gl.glColor3f(0.0f, 0.0f, 1.0f);

		glut.glutSolidTorus(gl, 20.0, 35.0, 20, 40);                 
	}

	/**
	 * M�todo definido na interface GLEventListener e chamado pelo objeto no qual ser� feito o desenho
	 * depois que a janela foi redimensionada.
	 */  
	public void reshape(GLDrawable drawable, int x, int y, int width, int height)
	{
		gl.glViewport(0, 0, width, height);
		fAspect = (float)width/(float)height;      
	}

	/**
	 * M�todo definido na interface GLEventListener e chamado pelo objeto no qual ser� feito o desenho
	 * quando o modo de exibi��o ou o dispositivo de exibi��o associado foi alterado.
	 */  
	public void displayChanged(GLDrawable drawable, boolean modeChanged, boolean deviceChanged) { }

	/**
	 * M�todo respons�vel pela especifica��o dos par�metros de ilumina��o.
	 */     
	public void defineIluminacao ()
	{    
		float luzAmbiente[]={0.2f, 0.2f, 0.2f, 1.0f}; 
		float luzDifusa[]={0.7f, 0.7f, 0.7f, 1.0f};     
		float luzEspecular[]={1.0f, 1.0f, 1.0f, 1.0f};
		float posicaoLuz[]={0.0f, 50.0f, 50.0f, 1.0f};

		// Capacidade de brilho do material
		float especularidade[]={1.0f, 1.0f, 1.0f, 1.0f}; 
		int especMaterial = 60;

		// Define a reflet�ncia do material 
		gl.glMaterialfv(GL.GL_FRONT, GL.GL_SPECULAR, especularidade);
		// Define a concentra��o do brilho
		gl.glMateriali(GL.GL_FRONT, GL.GL_SHININESS, especMaterial);

		// Ativa o uso da luz ambiente 
		gl.glLightModelfv(GL.GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

		// Define os par�metros da luz de n�mero 0
		gl.glLightfv(GL.GL_LIGHT0, GL.GL_AMBIENT, luzAmbiente); 
		gl.glLightfv(GL.GL_LIGHT0, GL.GL_DIFFUSE, luzDifusa );
		gl.glLightfv(GL.GL_LIGHT0, GL.GL_SPECULAR, luzEspecular );
		gl.glLightfv(GL.GL_LIGHT0, GL.GL_POSITION, posicaoLuz );   
	}

	/**
	 * M�todo usado para especificar a posi��o do observador virtual.
	 */    
	public void posicionaObservador()
	{
		// Especifica sistema de coordenadas do modelo
		gl.glMatrixMode(GL.GL_MODELVIEW);
		// Inicializa sistema de coordenadas do modelo  
		gl.glLoadIdentity();
		defineIluminacao();
		// Posiciona e orienta o observador
		gl.glTranslatef(-obsX,-obsY,-obsZ);
		gl.glRotatef(rotX, 1.0f, 0.0f, 0.0f);  
		gl.glRotatef(rotY, 0.0f, 1.0f, 0.0f);
	}
   
	/**
	 * M�todo usado para especificar o volume de visualiza��o.
	 */    
	public void especificaParametrosVisualizacao()
	{
		// Especifica sistema de coordenadas de proje��o
		gl.glMatrixMode(GL.GL_PROJECTION);
		// Inicializa sistema de coordenadas de proje��o
		gl.glLoadIdentity();

		// Especifica a proje��o perspectiva(angulo,aspecto,zMin,zMax)
		glu.gluPerspective(angle, fAspect, 0.5, 500);

		posicionaObservador();
	}

	/**
	 * M�todo da classe MouseAdapter que est� sendo sobrescrito para gerenciar os 
	 * eventos de bot�o de mouse.
	 */  
	public void mousePressed(MouseEvent e)
	{
		// Salva os par�metros atuais
		x_ini = e.getX();
		y_ini = e.getY();
		bot = e.getButton();
		obsX_ini = obsX;
		obsY_ini = obsY;
		obsZ_ini = obsZ;
		rotX_ini = rotX;
		rotY_ini = rotY;
	}

	/**
	 * M�todo da classe MouseAdapter que est� sendo sobrescrito para gerenciar os 
	 * eventos gerados quando um bot�o do mouse deixa de ser pressionado.
	 */  
	public void mouseReleased(MouseEvent e)
	{
		bot = -1;
	}

	/**
	 * M�todo definido na interface MouseMotionListener que est� sendo implementado para, 
	 * de acordo com o movimento do mouse, permitir mover a posi��o do observador
	 * virtual.
	 */
	public void mouseDragged(MouseEvent e)
	{
		float SENS_ROT		= 5.0f;
		float SENS_OBS		= 10.0f;
		float SENS_TRANSL	= 10.0f;

		int x = e.getX();
		int y = e.getY();

		// Bot�o esquerdo ?
		if (bot == MouseEvent.BUTTON1)
		{
			// Calcula diferen�as
			int deltax = x_ini - x;
			int deltay = y_ini - y;
			// E modifica �ngulos
			rotY = rotY_ini - deltax/SENS_ROT;
			rotX = rotX_ini - deltay/SENS_ROT;
		}
		// Bot�o direito ?
		else if (bot == MouseEvent.BUTTON3)
		{
			// Calcula diferen�a
			int deltaz = y_ini - y;
			// E modifica dist�ncia do observador
			obsZ = obsZ_ini + deltaz/SENS_OBS;
		}
		// Bot�o do meio ?
		else if (bot == MouseEvent.BUTTON2)
		{
			// Calcula diferen�as
			int deltax = x_ini - x;
			int deltay = y_ini - y;
			// E modifica posi��es
			obsX = obsX_ini + deltax/SENS_TRANSL;
			obsY = obsY_ini - deltay/SENS_TRANSL;
		}
		posicionaObservador();
		glDrawable.display();
	}

	/**
	 * M�todo definido na interface MouseMotionListener.
	 */       
	public void mouseMoved(MouseEvent e) { }

	/**
	 * M�todo definido na interface KeyListener que est� sendo implementado para, 
	 * de acordo com as teclas pressionadas, fazer zoom in/zoom out ou sair.
	 */        
	public void keyPressed(KeyEvent e)
	{
		switch (e.getKeyCode())
		{
			case KeyEvent.VK_HOME:		if(angle>=10)  angle -=5;
										break;
			case KeyEvent.VK_END:		if(angle<=150) angle +=5;
										break; 
			case KeyEvent.VK_ESCAPE:	System.exit(0);
										break;
		}  
		glDrawable.display();
	}

	/**
	 * M�todos definidos na interface KeyListener.
	 */      
	public void keyTyped(KeyEvent e) { }
	public void keyReleased(KeyEvent e) { }
}

