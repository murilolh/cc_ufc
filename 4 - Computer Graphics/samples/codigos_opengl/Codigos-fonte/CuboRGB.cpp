//*****************************************************
//
// CuboRGB.cpp 
// Um programa OpenGL simples que abre uma janela GLUT, 
// desenha o cubo RGB com iluminação, permite fazer 
// zoom in e zoom out quando os botões do mouse são 
// pressionados e mover a posição do observador virtual
// com as teclas de setas, HOME e END.
//
// Marcelo Cohen e Isabel H. Manssour
// Este código acompanha o livro 
// "OpenGL - Uma Abordagem Prática e Objetiva"
// 
//*****************************************************

#include <GL/glut.h>
#include <stdlib.h>

// Variáveis para controles de navegação
GLfloat angle, fAspect;
GLfloat rotX, rotY, rotX_ini, rotY_ini;
GLfloat obsX, obsY, obsZ, obsX_ini, obsY_ini, obsZ_ini;
int x_ini,y_ini,bot;

// Função responsável pela especificação dos parâmetros de iluminação
void DefineIluminacao (void)
{
	GLfloat luzAmbiente[4]={0.25,0.25,0.25,1.0}; 
	GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0};	   // "cor" 
	GLfloat posicaoLuz0[4]={0.0, 80.0, 0.0, 1.0};
	GLfloat posicaoLuz1[4]={0.0, -80.0, 0.0, 1.0}; 

	// Ativa o uso da luz ambiente 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz0 );   

	// Define os parâmetros da luz de número 1
	glLightfv(GL_LIGHT1, GL_AMBIENT, luzAmbiente); 
	glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuz1 ); 
}

// Função que desenha um cubo cujas cores dos vértices
// mostram como é o espaço RGB
void DesenhaCuboRGB(void)
{
	// Desenhas as linhas das "bordas" do cubo
	glColor3f(0.0f, 0.0f, 0.0f); 
	glLineWidth(1.6f);
	glBegin(GL_LINE_LOOP);	// frontal
		glVertex3f(40.0, 40.0, 40.0);
		glVertex3f(-40.0, 40.0, 40.0);
		glVertex3f(-40.0, -40.0, 40.0);
		glVertex3f(40.0, -40.0, 40.0);
	glEnd();
	glBegin(GL_LINE_LOOP);	//  posterior
		glVertex3f(40.0, 40.0, -40.0);
		glVertex3f(40.0, -40.0, -40.0);
		glVertex3f(-40.0, -40.0, -40.0); 
		glVertex3f(-40.0, 40.0, -40.0);
	glEnd();
	glBegin(GL_LINES);	//  laterais
		glVertex3f(-40.0, 40.0, -40.0);
		glVertex3f(-40.0, 40.0, 40.0); 
		glVertex3f(-40.0, -40.0, -40.0);
		glVertex3f(-40.0, -40.0, 40.0);     
		glVertex3f(40.0, 40.0, -40.0);
		glVertex3f(40.0, 40.0, 40.0); 
		glVertex3f(40.0, -40.0, -40.0);
		glVertex3f(40.0, -40.0, 40.0);  
	glEnd();
 
	// Desenha as faces do cubo preenchidas
	// Face frontal
	glBegin(GL_QUADS);
		glNormal3f(0.0, 0.0, 1.0);	// Normal da face
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(40.0, 40.0, 40.0);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-40.0, 40.0, 40.0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-40.0, -40.0, 40.0);
		glColor3f(1.0f, 0.0f, 0.0f);  
		glVertex3f(40.0, -40.0, 40.0);
	// Face posterior
		glNormal3f(0.0, 0.0, -1.0);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(40.0, 40.0, -40.0);
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(40.0, -40.0, -40.0);
		glColor3f(0.0f, 0.0f, 1.0f);  
		glVertex3f(-40.0, -40.0, -40.0);
		glColor3f(0.0f, 1.0f, 1.0f);  
		glVertex3f(-40.0, 40.0, -40.0);
	// Face lateral esquerda
		glNormal3f(-1.0, 0.0, 0.0);
		glColor3f(0.0f, 1.0f, 0.0f);  
		glVertex3f(-40.0, 40.0, 40.0);
		glColor3f(0.0f, 1.0f, 1.0f);  
		glVertex3f(-40.0, 40.0, -40.0);
		glColor3f(0.0f, 0.0f, 1.0f);  
		glVertex3f(-40.0, -40.0, -40.0);
		glColor3f(0.0f, 0.0f, 0.0f);  
		glVertex3f(-40.0, -40.0, 40.0);
	// Face lateral direita
		glNormal3f(1.0, 0.0, 0.0);
		glColor3f(1.0f, 1.0f, 0.0f);  
		glVertex3f(40.0, 40.0, 40.0);
		glColor3f(1.0f, 0.0f, 0.0f);  
		glVertex3f(40.0, -40.0, 40.0);
		glColor3f(1.0f, 0.0f, 1.0f);  
		glVertex3f(40.0, -40.0, -40.0);
		glColor3f(1.0f, 1.0f, 1.0f);  
		glVertex3f(40.0, 40.0, -40.0);
	// Face superior
		glNormal3f(0.0, 1.0, 0.0);
		glColor3f(0.0f, 1.0f, 1.0f);  
		glVertex3f(-40.0, 40.0, -40.0);
		glColor3f(0.0f, 1.0f, 0.0f);  
		glVertex3f(-40.0, 40.0, 40.0);
		glColor3f(1.0f, 1.0f, 0.0f);  
		glVertex3f(40.0, 40.0, 40.0);
		glColor3f(1.0f, 1.0f, 1.0f);  
		glVertex3f(40.0, 40.0, -40.0);
	// Face inferior
		glNormal3f(0.0, -1.0, 0.0);
		glColor3f(0.0f, 0.0f, 1.0f);  
		glVertex3f(-40.0, -40.0, -40.0);
		glColor3f(1.0f, 0.0f, 1.0f);  
		glVertex3f(40.0, -40.0, -40.0);
		glColor3f(1.0f, 0.0f, 0.0f);  
		glVertex3f(40.0, -40.0, 40.0);
		glColor3f(0.0f, 0.0f, 0.0f);  
		glVertex3f(-40.0, -40.0, 40.0);
	glEnd();
}

// Função callback de redesenho da janela de visualização
void Desenha(void)
{
	// Limpa a janela de visualização com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	// Chama a função que especifica os parâmetros de iluminação
	DefineIluminacao();

	DesenhaCuboRGB();

	// Executa os comandos OpenGL
	glutSwapBuffers();
}

// Função usada para especificar a posição do observador virtual
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

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva 
	// (angulo, aspecto, zMin, zMax)
	gluPerspective(angle,fAspect,0.5,1000);

	PosicionaObservador();
}

// Função callback chamada para gerenciar eventos de teclas normais (ESC)
void Teclado (unsigned char tecla, int x, int y)
{
	if(tecla==27) // ESC ?
		exit(0);
}

// Função callback para tratar eventos de teclas especiais
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

// Função callback para eventos de botões do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	if(state==GLUT_DOWN)
	{
		// Salva os parâmetros atuais
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

// Função callback para eventos de movimento do mouse
#define SENS_ROT	5.0
#define SENS_OBS	10.0
#define SENS_TRANSL	10.0
void GerenciaMovim(int x, int y)
{
	// Botão esquerdo ?
	if(bot==GLUT_LEFT_BUTTON)
	{
		// Calcula diferenças
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		// E modifica ângulos
		rotY = rotY_ini - deltax/SENS_ROT;
		rotX = rotX_ini - deltay/SENS_ROT;
	}
	// Botão direito ?
	else if(bot==GLUT_RIGHT_BUTTON)
	{
		// Calcula diferença
		int deltaz = y_ini - y;
		// E modifica distância do observador
		obsZ = obsZ_ini + deltaz/SENS_OBS;
	}
	// Botão do meio ?
	else if(bot==GLUT_MIDDLE_BUTTON)
	{
		// Calcula diferenças
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		// E modifica posições
		obsX = obsX_ini + deltax/SENS_TRANSL;
		obsY = obsY_ini - deltay/SENS_TRANSL;
	}
	PosicionaObservador();
	glutPostRedisplay();
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divisão por zero
	if ( h == 0 ) h = 1;

	// Especifica as dimensões da viewport
	glViewport(0, 0, w, h);
 
	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}

// Função responsável por inicializar parâmetros e variáveis
void Inicializa (void)
{   
	// Define a cor de fundo da janela de visualização como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);  
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);
	// Habilita a luz de número 1
	glEnable(GL_LIGHT1);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);

	// Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_SMOOTH);
     
	// Inicializa a variável que especifica o ângulo da projeção
	// perspectiva
	angle=45;
    
	// Inicializa as variáveis usadas para alterar a posição do 
	// observador virtual
	rotX = 0;
	rotY = 0;
	obsX = obsY = 0;
	obsZ = 150;    
}

// Programa Principal 
int main(void)
{
	// Define do modo de operação da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
 
	// Especifica a posição inicial da janela GLUT
	glutInitWindowPosition(5,5); 

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(450,450); 
 
	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Cubo RGB");
 
	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);
  
	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a função callback para tratamento das teclas normais 
	glutKeyboardFunc (Teclado);

	// Registra a função callback para tratamento das teclas especiais
	glutSpecialFunc (TeclasEspeciais);
     
	// Registra a função callback para eventos de botões do mouse	
	glutMouseFunc(GerenciaMouse);
	 
	// Registra a função callback para eventos de movimento do mouse	
	glutMotionFunc(GerenciaMovim);

	// Chama a função responsável por fazer as inicializações 
	Inicializa();
 
	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();
 
	return 0;
}
