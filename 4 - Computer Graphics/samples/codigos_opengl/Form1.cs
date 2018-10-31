/// <summary>
/// Aplicação que exemplifica como trabalhar com OpenGL e C# utilizando a CsGL. 
/// É aberta uma janela na qual é desenhado um "torus" com iluminação. É 
/// possível fazer zoom in e zoom out usando o mouse, e mover a posição do 
/// observador virtual com as teclas de setas, HOME e END.
/// 
/// Isabel H. Manssour e Marcelo Cohen
/// Este código acompanha o livro "OpenGL - Uma Abordagem Prática e Objetiva".
/// </summary>

using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using CsGL.OpenGL;
using CsGL.Util;

namespace AplicacaoOpenGL
{
	/// <summary>
	/// Classe responsável pela criação da janela.
	/// </summary>
	public class Form1 : System.Windows.Forms.Form
	{
		private System.ComponentModel.Container components = null;
		private OpenGLView view;

		public Form1()
		{
			InitializeComponent();

			view = new OpenGLView();
			view.Dock = DockStyle.Fill;
			Controls.Add(view);
		}

		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if (components != null) 
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			// 
			// Form1
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(522, 466);
			this.Name = "Form1";
			this.Text = "Desenho de um torus 3D com iluminação";
		}
		#endregion
		
		[STAThread]
		static void Main() 
		{
			Application.Run(new Form1());
		}
	}

	/// <summary>
	/// Classe responsável pela criação da viewport OpenGL.
	/// </summary>
	public class OpenGLView : CsGL.OpenGL.OpenGLControl
	{
		Modelo modelo;
	
		public OpenGLView()
		{
			modelo = new Modelo(this);
		}

		protected override void InitGLContext() 
		{
			modelo.Inicializa();
		}

		public override void glDraw() 
		{
			modelo.Desenha();
		}

		protected override void OnSizeChanged(EventArgs e)
		{
			base.OnSizeChanged(e);
			modelo.AlteraTamanhoJanela(e, Size);
		}
	}

	/// <summary>
	/// Classe responsável pelo desenho e gerenciamento do modelo.
	/// </summary>
	public class Modelo : CsGL.OpenGL.GL
	{
		internal OpenGLView view;
		private double angle, fAspect;
		private float rotX, rotY, obsZ;
		private Teclado teclado;
		private Mouse_ mouse;

		public Modelo(OpenGLView v)
		{
			// Especifica o ângulo da projeção perspectiva  
			angle=44;
			// Posição do observador virtual
			rotX = 0;
			rotY = 0;
			obsZ = 150;     
			// Inicializa o valor para correção de aspecto   
			fAspect = 1;    
			// Inicializa referência para a view
			view = v;
			// Cria os objetos responsáveis pelo tratamento de eventos
			teclado = new Teclado(this);
			mouse = new Mouse_(this);
		}

		public void Desenha()
		{
			GL.glClear(GL.GL_COLOR_BUFFER_BIT | GL.GL_DEPTH_BUFFER_BIT );
			GL.glLoadIdentity(); 

			DefineIluminacao();
			EspecificaParametrosVisualizacao(); 

			GL.glColor3f(0.0f, 0.0f, 1.0f);
			GL.glutSolidTorus(20.0, 35.0, 20, 40); 
		}

		public void Inicializa() 
		{
			GL.glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			GL.glEnable(GL.GL_COLOR_MATERIAL);
			GL.glEnable(GL.GL_LIGHTING);  
			GL.glEnable(GL.GL_LIGHT0);
			GL.glEnable(GL.GL_DEPTH_TEST);
			GL.glShadeModel(GL.GL_SMOOTH); 
		}

		public void AlteraTamanhoJanela(EventArgs e, Size s)
		{			
			fAspect = (double)s.Width /(double) s.Height;
			GL.glViewport(0, 0, s.Width, s.Height);
		}

		public void Invalidate() 
		{ 
			view.Invalidate(); 
		}

		public void DefineIluminacao ()
		{    
			float [] luzAmbiente =	new float[4];
			luzAmbiente[0] = luzAmbiente[1] = luzAmbiente[2] = 0.2F; 
			luzAmbiente[3] = 1.0F; 
			float [] luzDifusa = new float[4];
			luzDifusa[0] = luzDifusa[1] = luzDifusa[2] = 0.7F;
			luzDifusa[3] = 1.0F;     
			float [] luzEspecular = new float[4];
			luzEspecular[0] = luzEspecular[1] = luzEspecular[2] = luzEspecular[3] = 1.0F;
			float [] posicaoLuz = new float[4];
			posicaoLuz[0] = 0.0F;
			posicaoLuz[1] = 50.0F;
			posicaoLuz[2] = 50.0F;
			posicaoLuz[3] = 1.0F;

			// Capacidade de brilho do material
			float [] especularidade = new float[4];
			especularidade[0] = especularidade[1] = especularidade[2] = especularidade[3] = 1.0F; 
			int especMaterial = 60;

			// Define a refletância do material 
			GL.glMaterialfv(GL.GL_FRONT, GL.GL_SPECULAR, especularidade);
			// Define a concentração do brilho
			GL.glMateriali(GL.GL_FRONT, GL.GL_SHININESS, especMaterial);

			// Ativa o uso da luz ambiente 
			GL.glLightModelfv(GL.GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

			// Define os parâmetros da luz de número 0
			GL.glLightfv(GL.GL_LIGHT0, GL.GL_AMBIENT, luzAmbiente); 
			GL.glLightfv(GL.GL_LIGHT0, GL.GL_DIFFUSE, luzDifusa );
			GL.glLightfv(GL.GL_LIGHT0, GL.GL_SPECULAR, luzEspecular );
			GL.glLightfv(GL.GL_LIGHT0, GL.GL_POSITION, posicaoLuz );   
		}

		public void PosicionaObservador()
		{
			// Especifica sistema de coordenadas do modelo
			GL.glMatrixMode(GL.GL_MODELVIEW);
			// Inicializa sistema de coordenadas do modelo  
			GL.glLoadIdentity();
			DefineIluminacao();
			// Especifica posição do observador e do alvo   
			GL.glTranslatef(0.0f, 0.0f, -obsZ);    
			GL.glRotatef(rotX, 1.0f, 0.0f, 0.0f);  
			GL.glRotatef(rotY, 0.0f, 1.0f, 0.0f);
		}

		public void EspecificaParametrosVisualizacao()
		{
			// Especifica sistema de coordenadas de projeção
			GL.glMatrixMode(GL.GL_PROJECTION);
			// Inicializa sistema de coordenadas de projeção
			GL.glLoadIdentity();

			// Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)
			GL.gluPerspective(angle, fAspect, 0.5, 500);

			PosicionaObservador();
		}

		public void incrementaRotacaoX()
		{
			rotX++;
		}

		public void decrementaRotacaoX()
		{
			rotX--;
		}

		public void incrementaRotacaoY()
		{
			rotY++;
		}

		public void decrementaRotacaoY()
		{
			rotY--;
		}

		public void incrementaObservadorZ()
		{
			obsZ++;
		}

		public void decrementaObservadorZ()
		{
			obsZ--;
		}  

		public void zoomIn()
		{
			if (angle >= 10) angle -= 5;
		} 

		public void zoomOut()
		{
			if (angle <= 130) angle += 5;
		} 
	}

	/// <summary>
	/// Classe responsável pelo tratamento de eventos do teclado.
	/// </summary>
	public class Teclado : Keyboard
	{
		Modelo modelo;

		public Teclado(Modelo m) 
		{ 
			modelo = m; 
		}
	
		public override void KeyStateChanged(Event e) 
		{
			if (Keyboard.GetKeysState()[(int)Keys.Left])
				modelo.incrementaRotacaoY();
			if (Keyboard.GetKeysState()[(int)Keys.Right])
				modelo.decrementaRotacaoY();
			if (Keyboard.GetKeysState()[(int)Keys.Up])
				modelo.incrementaRotacaoX();
			if (Keyboard.GetKeysState()[(int)Keys.Down])
				modelo.decrementaRotacaoX();
			if (Keyboard.GetKeysState()[(int)Keys.Home])
				modelo.incrementaObservadorZ();
			if (Keyboard.GetKeysState()[(int)Keys.End])
				modelo.decrementaObservadorZ();
			if (Keyboard.GetKeysState()[(int)Keys.Escape])
				Application.Exit();
			modelo.Invalidate();
		}
	}

	/// <summary>
	/// Classe responsável pelo tratamento de eventos do mouse.
	/// </summary>
	public class Mouse_ : Mouse
	{
		Modelo modelo;

		public Mouse_(Modelo m) 
		{ 
			modelo = m; 
		}
	
		public override void MouseEvent(Event e, int dx, int dy)
		{
			if (e.button==1)
				modelo.zoomIn();
			if (e.button==2)
				modelo.zoomOut();
			modelo.Invalidate();
		}
	}
}
