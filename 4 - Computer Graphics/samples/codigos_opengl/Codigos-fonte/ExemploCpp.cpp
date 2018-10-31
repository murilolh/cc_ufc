//*****************************************************
//
// ExemploCpp.cpp 
// Classe que implementa os m�todos respons�veis
// por abrir uma janela GLUT, desenhar um "torus" com 
// ilumina��o, e permitir fazer zoom in e zoom out e 
// mover a posi��o do observador virtual com as teclas
// Home/End e o mouse. 
//
// Marcelo Cohen e Isabel H. Manssour
// Este c�digo acompanha o livro 
// "OpenGL - Uma Abordagem Pr�tica e Objetiva"
// 
//*****************************************************

#include "ExemploCpp.h"

// Inicializa��o dos atributos static

// �ngulo da proje��o perspectiva
GLfloat ExemploCpp::angle=45;

// Posi��o e orienta��o do observador virtual
GLfloat ExemploCpp::rotX = 0;
GLfloat ExemploCpp::rotY = 0;
GLfloat ExemploCpp::obsX = 0;
GLfloat ExemploCpp::obsY = 0;
GLfloat ExemploCpp::obsZ = 150;  

// Posi��o e orienta��o iniciais, durante
// o movimento do mouse
GLfloat ExemploCpp::rotX_ini = 0;
GLfloat ExemploCpp::rotY_ini = 0;
GLfloat ExemploCpp::obsX_ini = 0;
GLfloat ExemploCpp::obsY_ini = 0;
GLfloat ExemploCpp::obsZ_ini = 0;

// Posi��o na tela onde o movimento do mouse iniciou
int ExemploCpp::x_ini = 0;
int ExemploCpp::y_ini = 0;

// Bot�o pressionado
int ExemploCpp::bot = 0;

// Valor para corre��o de aspecto
GLfloat ExemploCpp::fAspect = 1;

// Identificador de uma janela
GLint ExemploCpp::identificadorJanela = 0;

// M�todo construtor que recebe por par�metro a largura, a altura, a posicao e o titulo da janela GLUT
ExemploCpp::ExemploCpp (int largura, int altura, int posicaoX, int posicaoY, char *titulo)
{
	// Define o modo de opera��o da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
	// Especifica a posi��o inicial da janela GLUT
	glutInitWindowPosition(posicaoX,posicaoY); 
	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(largura,altura); 
	// Cria a janela passando como argumento o t�tulo da mesma
	identificadorJanela = glutCreateWindow(titulo);
	// Registra o m�todo callback de redesenho da janela
	glutDisplayFunc(Desenha);
	// Registra o m�todo callback de redimensionamento da janela
	glutReshapeFunc(AlteraTamanhoJanela);
	// Registra o m�todo callback que gerencia os eventos do mouse   
	glutMouseFunc(GerenciaMouse);
	// Registra a fun��o callback para eventos de movimento do mouse	
	glutMotionFunc(GerenciaMovim);
	// Registra o m�todo callback para tratamento das teclas normais 
	glutKeyboardFunc (Teclado);
	// Registra o m�todo callback para tratamento das teclas especiais
	glutSpecialFunc (TeclasEspeciais);
	// Chama o m�todo respons�vel por fazer as inicializa��es 
	Inicializa();
}

// M�todo destrutor usado para eliminar a janela criada
ExemploCpp::~ExemploCpp ()
{
	glutDestroyWindow(identificadorJanela); 	
}

// M�todo respons�vel pela chamada da fun��o GLUT que inicia 
// o processamento e aguarda intera��es do usu�rio
void ExemploCpp::inicializaLoopGlut (void)
{
	glutMainLoop();
}

// M�todo respons�vel por inicializar par�metros e vari�veis
void ExemploCpp::Inicializa (void)
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

	// Habilita o modelo de coloriza��o de Gouraud
	glShadeModel(GL_SMOOTH);  
}

// M�todo respons�vel pela especifica��o dos par�metros de ilumina��o
void ExemploCpp::DefineIluminacao (void)
{
	GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0}; 
	GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0};	   // "cor" 
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho" 
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

// M�todo usado para especificar a posi��o do observador virtual
void ExemploCpp::PosicionaObservador(void)
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

// M�todo usado para especificar o volume de visualiza��o
void ExemploCpp::EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de proje��o
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de proje��o
	glLoadIdentity();

	// Especifica a proje��o perspectiva(angulo,aspecto,zMin,zMax)
	gluPerspective(angle,fAspect,0.5,500);

	PosicionaObservador();
}

// M�todo callback de redesenho da janela de visualiza��o
void ExemploCpp::Desenha(void)
{
	// Limpa a janela de visualiza��o com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	// Chama o m�todo que especifica os par�metros de ilumina��o
	DefineIluminacao();
    
	// Altera a cor do desenho para azul
	glColor3f(0.0f, 0.0f, 1.0f);

	// Fun��o da GLUT para fazer o desenho de um "torus" 
	// com a cor corrente
	glutSolidTorus(20.0, 35.0, 20, 40); 

	// Executa os comandos OpenGL
	glutSwapBuffers();
}

// M�todo callback chamado para gerenciar eventos de teclas normais (ESC)
void ExemploCpp::Teclado (unsigned char tecla, int x, int y)
{
	if(tecla==27) // ESC ?
		exit(0);
}

// M�todo callback chamado para gerenciar eventos de teclas especiais
void ExemploCpp::TeclasEspeciais (int tecla, int x, int y)  
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

// M�todo callback chamado quando o tamanho da janela � alterado 
void ExemploCpp::AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divis�o por zero
	if ( h == 0 ) h = 1;

	// Especifica as dimens�es da viewport
	glViewport(0, 0, w, h);
 
	// Calcula a corre��o de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}

// M�todo callback para eventos de bot�es do mouse
void ExemploCpp::GerenciaMouse(int button, int state, int x, int y)
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

// M�todo callback para eventos de movimento do mouse
#define SENS_ROT	5.0
#define SENS_OBS	5.0
#define SENS_TRANSL	5.0
void ExemploCpp::GerenciaMovim(int x, int y)
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

