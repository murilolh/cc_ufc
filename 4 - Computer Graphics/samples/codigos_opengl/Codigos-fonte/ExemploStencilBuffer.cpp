//*****************************************************
//
// ExemploStencilBuffer.cpp 
// Um programa OpenGL que abre uma janela GLUT, desenha 
// quatro cubos, permite fazer zoom in e zoom out 
// com as teclas Home e End e alterar o observador com
// o mouse. Al�m disso, quando a tecla 'm' � pressionada,
// bloqueia ou restringe o desenho de uma regi�o da tela
// equivalente a uma esfera que se move ao longo do eixo x. 
//
// Marcelo Cohen e Isabel H. Manssour
// Este c�digo acompanha o livro 
// "OpenGL - Uma Abordagem Pr�tica e Objetiva"
// 
//*****************************************************

#include <GL/glut.h>
#include <stdlib.h>

// Vari�veis para controles de navega��o
GLfloat angle, fAspect;
GLfloat rotX, rotY, rotX_ini, rotY_ini;
GLfloat obsX, obsY, obsZ, obsX_ini, obsY_ini, obsZ_ini;
int x_ini,y_ini,bot;

// Transla��o e velocidade da esfera
GLfloat tx=0, passo=0.8;

// Tipo de teste a ser realizado
GLboolean igual = true;

// Fun��o respons�vel pela especifica��o dos par�metros de ilumina��o
void DefineIluminacao (void)
{
	GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0}; 
	GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0};
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};
	GLfloat posicaoLuz[4]={0.0, 50.0, 50.0, 1.0};

	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0}; 
	GLint especMaterial = 60;

	// Define a reflet�ncia do material 
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentra��o do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

	// Ativa o uso da luz ambiente 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os par�metros da luz de n�mero 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );   
}

// Inicializa o stencil buffer
void InicializaStencilBuffer()
{
	GLint referencia = 1; // Valor a ser comparado com o conte�do do stencil buffer
	GLuint mascara = 1; // M�scara de bits para ser usada na compara��o
     
	// Stencil buffer ser� limpo com o valor 0
	glClearStencil(0);
	// Limpa o stencil buffer
	glClear(GL_STENCIL_BUFFER_BIT);

	// Determina que o teste do stencil buffer sempre vai ser verdadeiro,
	// e nesse caso, associa o valor de refer�ncia a cada pixel desenhado
	glStencilFunc(GL_ALWAYS, referencia, mascara); 
	
	// Define como o valor de refer�ncia afeta o stencil buffer
	// Neste caso, o valor atual ser� substitu�do pelo valor de ref,
	// n�o importanto o resultado do teste de profundidade.
	glStencilOp(GL_REPLACE,GL_REPLACE,GL_REPLACE);

	// Desenha a esfera e preenche o stencil buffer	
	glPushMatrix();
		glTranslatef(tx, 0.0f, 0.0f);
		glutSolidSphere(20, 20, 20);
	glPopMatrix();

	// E n�o altera mais o stencil buffer
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
}

void DesenhaObjetos(void)
{
	// Desenha quatro cubos
	glPushMatrix();
		glTranslatef(-40.0f, 0.0f, 0.0f);
		glRotatef(45,1,1,1);
		glColor3f(1.0f, 1.0f, 0.0f);
		glutSolidTeapot(18);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(40.0f, 0.0f, 0.0f);
		glRotatef(45,1,-1,0);
		glColor3f(0.0f, 1.0f, 0.0f);
		glutSolidTorus(10,16,20,20); 
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0f, 25.0f, -25.0f);
		glRotatef(45,1,0.5,0);
		glColor3f(1.0f, 0.2f, 0.8f);
		glutSolidCone(16,35,10,10); 
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0f, -25.0f, -25.0f);
		glRotatef(45,1,-0.5,0);
		glColor3f(0.0f, 0.3f, 0.7f);
		glutSolidSphere(20,20,20);
	glPopMatrix();
}

// Fun��o callback de redesenho da janela de visualiza��o
void Desenha(void)
{ 
	// Chama a fun��o que especifica os par�metros de ilumina��o
	DefineIluminacao();

	// Chama a fun��o que faz a inicializa��o do stencil buffer
	InicializaStencilBuffer();

	// Limpa a janela e o depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (igual)
		// Passa se o valor for igual a 1
		glStencilFunc(GL_EQUAL, 1, 1);
	else
		// Passa se o valor for diferente de 1
		glStencilFunc(GL_NOTEQUAL, 1, 1);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	DesenhaObjetos();

	if (!igual)
		// Passa se o valor for igual a 1
		glStencilFunc(GL_EQUAL, 1, 1);
	else
		// Passa se o valor for diferente de 1
		glStencilFunc(GL_NOTEQUAL, 1, 1);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	DesenhaObjetos();

	// Executa os comandos OpenGL
	glutSwapBuffers();
}

// Fun��o usada para especificar a posi��o do observador virtual
void PosicionaObservador(void)
{
	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();
	DefineIluminacao();
	// Posiciona e orienta o observador
	glTranslatef(-obsX,-obsY,-obsZ);
	glRotatef(rotX,1,0,0);
	glRotatef(rotY,0,1,0);
}

// Fun��o usada para especificar o volume de visualiza��o
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de proje��o
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de proje��o
	glLoadIdentity();

	// Especifica a proje��o perspectiva(angulo,aspecto,zMin,zMax)
	gluPerspective(angle,fAspect,0.5,500);

	PosicionaObservador();
}

// Fun��o callback chamada para gerenciar eventos de teclas normais (ESC)
void Teclado (unsigned char tecla, int x, int y)
{
	if(tecla==27) // ESC ?
		exit(0);
	if(tecla=='m')
		igual = !igual;
}

// Fun��o callback chamada quando o tamanho da janela � alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divis�o por zero
	if ( h == 0 ) h = 1;

	// Especifica as dimens�es da viewport
	glViewport(0, 0, w, h);
 
	// Calcula a corre��o de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}

// Fun��o callback chamada pela GLUT a cada intervalo de tempo
void Anima(int value)
{
	tx = tx + passo;
                
	// Inverte a dire��o da transla��o 
	if(tx > 40 || tx < -40)
		passo = -passo;

	glutPostRedisplay();
	glutTimerFunc(120,Anima, 1);
}

// Fun��o callback para tratar eventos de teclas especiais
void TeclasEspeciais (int tecla, int x, int y)  
{
	switch (tecla)
	{
		case GLUT_KEY_HOME:	if(angle>=10)  angle -=5;
							break;
		case GLUT_KEY_END:	if(angle<=150) angle +=5;
							break;
	}
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

// Fun��o callback para eventos de bot�es do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	if(state==GLUT_DOWN)
	{
		// Salva os par�metros atuais
		x_ini = x;
		y_ini = y;
		obsX_ini = obsX;
		obsY_ini = obsY;
		obsZ_ini = obsZ;
		rotX_ini = rotX;
		rotY_ini = rotY;
		bot = button;
	}
	else bot = -1;
}

// Fun��o callback para eventos de movimento do mouse
#define SENS_ROT	5.0
#define SENS_OBS	15.0
#define SENS_TRANSL	20.0
void GerenciaMovim(int x, int y)
{
	// Bot�o esquerdo ?
	if(bot==GLUT_LEFT_BUTTON)
	{
		// Calcula diferen�as
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		// E modifica �ngulos
		rotY = rotY_ini - deltax/SENS_ROT;
		rotX = rotX_ini - deltay/SENS_ROT;
	}
	// Bot�o direito ?
	else if(bot==GLUT_RIGHT_BUTTON)
	{
		// Calcula diferen�a
		int deltaz = y_ini - y;
		// E modifica dist�ncia do observador
		obsZ = obsZ_ini + deltaz/SENS_OBS;
	}
	// Bot�o do meio ?
	else if(bot==GLUT_MIDDLE_BUTTON)
	{
		// Calcula diferen�as
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		// E modifica posi��es
		obsX = obsX_ini + deltax/SENS_TRANSL;
		obsY = obsY_ini - deltay/SENS_TRANSL;
	}
	PosicionaObservador();
	glutPostRedisplay();
}

// Fun��o respons�vel por inicializar par�metros e vari�veis
void Inicializa (void)
{   
	// Define a cor de fundo da janela de visualiza��o como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
	// Habilita a defini��o da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de ilumina��o
	glEnable(GL_LIGHTING);  
	// Habilita a luz de n�mero 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);
    // Habilita o stencil buffer
    glEnable(GL_STENCIL_TEST);

	// Habilita o modelo de coloriza��o de Gouraud
	glShadeModel(GL_SMOOTH);
     
	// Inicializa a vari�vel que especifica o �ngulo da proje��o
	// perspectiva
	angle=45;
    
	// Inicializa as vari�veis 
	rotX = 0;
	rotY = 0;
	obsZ = 150;    
}

// Programa Principal 
int main(void)
{
	// Define o modo de opera��o da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL); 
 
	// Especifica a posi��o inicial da janela GLUT
	glutInitWindowPosition(5,5); 
    
	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(450,450); 
 
	// Cria a janela passando como argumento o t�tulo da mesma
	glutCreateWindow("Exemplo de utiliza��o do stencil buffer");
 
	// Registra a fun��o callback de redesenho da janela de visualiza��o
	glutDisplayFunc(Desenha);
  
	// Registra a fun��o callback de redimensionamento da janela de visualiza��o
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a fun��o callback para tratamento das teclas normais 
	glutKeyboardFunc (Teclado);

	// Registra a fun��o callback para tratamento das teclas especiais
	glutSpecialFunc (TeclasEspeciais);

	// Registra a fun��o callback para eventos de bot�es do mouse	
	glutMouseFunc(GerenciaMouse);
	 
	// Registra a fun��o callback para eventos de movimento do mouse	
	glutMotionFunc(GerenciaMovim);

	// Registra a fun��o callback que ser� chamada a cada intervalo de tempo
	glutTimerFunc(120, Anima, 1);
     
	// Chama a fun��o respons�vel por fazer as inicializa��es 
	Inicializa();
 
	// Inicia o processamento e aguarda intera��es do usu�rio
	glutMainLoop();
 
	return 0;
}
