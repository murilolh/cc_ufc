//*****************************************************
//
// Exemplo3DWireframe.cpp 
// Um programa OpenGL que abre uma janela GLUT, desenha 
// o wireframe de um objeto representado por uma malha 
// de pol�gonos, e permite fazer zoom in e zoom out 
// pressionando os bot�es do mouse (proje��o perspectiva).
// IMPORTANTE:	� necess�rio incluir no projeto a 
//				biblioteca bibutil.cpp
//
// Marcelo Cohen e Isabel H. Manssour
// Este c�digo acompanha o livro 
// "OpenGL - Uma Abordagem Pr�tica e Objetiva"
// 
//*****************************************************

#include "bibutil.h"

// Vari�veis para controles de navega��o
GLfloat angle, fAspect;
GLfloat rotX, rotY, rotX_ini, rotY_ini;
GLfloat obsX, obsY, obsZ, obsX_ini, obsY_ini, obsZ_ini;
int x_ini,y_ini,bot;

// Apontador para o objeto
OBJ *objeto;

// Fun��o callback de redesenho da janela de visualiza��o
void Desenha(void)
{
	// Limpa a janela de visualiza��o com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

	// Altera a cor do desenho para cinza
	glColor3f(0.5f, 0.5f, 0.5f);

	// Desenha o wireframe do objeto 3D lido do arquivo com a cor corrente
	DesenhaObjeto(objeto);

	// Executa os comandos OpenGL
	glFlush();
}

// Fun��o usada para especificar a posi��o do observador virtual
void PosicionaObservador(void)
{
	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();
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
	gluPerspective(angle,fAspect,0.1,1200);

	PosicionaObservador();
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

// Fun��o callback chamada para gerenciar eventos de teclas normais (ESC)
void Teclado (unsigned char tecla, int x, int y)
{
	if(tecla==27) // ESC ?
	{
		// Libera mem�ria e finaliza programa
		LiberaObjeto(objeto);
		exit(0);
	}
	
}

void TeclasEspeciais (int tecla, int x, int y)  
{
	switch (tecla)
	{
		case GLUT_KEY_HOME:	if(angle>=10)  angle -=5;
							break;
		case GLUT_KEY_END:	if(angle<=150) angle +=5;
							break;
	}
	PosicionaObservador();
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
	char nomeArquivo[30];

	// Define a cor de fundo da janela de visualiza��o como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
 
	// Inicializa a vari�vel que especifica o �ngulo da proje��o
	// perspectiva
	angle=54;
 
	// Inicializa as vari�veis usadas para alterar a posi��o do 
	// observador virtual
	rotX = 0;
	rotY = 0;
	obsX = obsY = 0;
	obsZ = 10;

	// L� o nome do arquivo e chama a rotina de leitura
	printf("Digite o nome do arquivo que contem o modelo 3D: ");
	gets(nomeArquivo);
	
	// Carrega o objeto 3D
	objeto = CarregaObjeto(nomeArquivo,false);

	// Seta o modo de desenho como wireframe
	SetaModoDesenho('w');	// 's' para s�lido
}

// Programa Principal 
int main(void)
{
	// Define do modo de opera��o da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
 
	// Especifica a posi��o inicial da janela GLUT
	glutInitWindowPosition(5,5); 
	 
	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(450,450); 
 
	// Cria a janela passando como argumento o t�tulo da mesma
	glutCreateWindow("Desenho do wireframe de um objeto 3D");
 
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

	// Chama a fun��o respons�vel por fazer as inicializa��es 
	Inicializa();
 
	// Inicia o processamento e aguarda intera��es do usu�rio
	glutMainLoop();
 
	return 0;
}
