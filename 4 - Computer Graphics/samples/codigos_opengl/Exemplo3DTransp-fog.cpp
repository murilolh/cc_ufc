//*****************************************************
//
// Exemplo3DTransp-fog.cpp
// Um programa OpenGL demonstrando o uso de
// blending para obter o efeito de neblina
//
// Marcelo Cohen e Isabel H. Manssour
// Este código acompanha o livro 
// "OpenGL - Uma Abordagem Prática e Objetiva"
// 
//*****************************************************

#include <stdlib.h>
#include <GL/glut.h>

// Variáveis para controles de navegação
GLfloat angle, fAspect;
GLfloat rotX, rotY, rotX_ini, rotY_ini;
GLfloat obsX, obsY, obsZ, obsX_ini, obsY_ini, obsZ_ini;
int x_ini,y_ini,bot;

// Modos possíveis de neblina
GLint modos_neblina[3] = { GL_LINEAR, GL_EXP, GL_EXP2 };
// Modo inicial
int modo = 0;

void Desenha(void)
{
	// Limpa a janela de visualização com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glColor3f(1,0,0);
	glutSolidCube(1);

	// Desenha outro na frente, à esquerda
	glTranslatef(-1.5,0,1.5);
	glColor3f(0,1,0);
	glutSolidCube(1.0);

	// Agora atrás, à direita
	glTranslatef(3,0,-3);
	glColor3f(0,0,1);
	glutSolidCube(1.0);

	glPopMatrix();
	glutSwapBuffers();
}

// Função callback chamada para gerenciar eventos de teclas normais (ESC)
void Teclado (unsigned char tecla, int x, int y)
{
	switch(tecla)
	{
		case 27:	// ESC ?
					exit(0);
		case 'n':	if(++modo>2) modo = 0;
					// Altera o modo atual
					glFogi(GL_FOG_MODE, modos_neblina[modo]);
					break;
	}
	glutPostRedisplay();
}

// Função responsável pela especificação dos parâmetros de iluminação
void DefineIluminacao (void)
{
	GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0}; 
	GLfloat luzDifusa[4]={1.0,1.0,1.0,1.0};
	GLfloat posicaoLuz[4]={0.0, 0.0, 5.0, 1.0};

	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );   

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK,GL_DIFFUSE);
}

// Função responsável por inicializar parâmetros e variáveis
void Inicializa (void)
{   
	// Define a cor de fundo da janela de visualização como branca
	glClearColor(1, 1, 1, 1);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMatrixMode(GL_MODELVIEW);
	DefineIluminacao();
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	glEnable(GL_DEPTH_TEST);

	// Cor da neblina
	GLfloat cor_neblina[4] = {1, 1, 1, 1};

	// Parâmetros da neblina
	glFogi(GL_FOG_MODE, modos_neblina[modo]);
	glFogfv(GL_FOG_COLOR, cor_neblina);
	glFogf(GL_FOG_DENSITY, 0.25);
	glFogf(GL_FOG_START, 1.0);
	glFogf(GL_FOG_END, 10.0);

	glEnable(GL_FOG);
	// Inicializa a variável que especifica o ângulo da projeção
	// perspectiva
	angle=45;
    
	// Inicializa as variáveis usadas para alterar a posição do 
	// observador virtual
	rotX = 0;
	rotY = 0;
	obsX = obsY = 0;
	obsZ = 5;
}

// Função usada para especificar a posição do observador virtual
void PosicionaObservador(void)
{
	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();
	
	// Ajusta iluminação
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

	// Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)
	gluPerspective(angle,fAspect,0.5,500);

	PosicionaObservador();
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Evita a divisao por zero
	if(h == 0) h = 1;

	// Especifica as dimensões da Viewport
	glViewport(0, 0, w, h);

	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
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
#define SENS_OBS	100.0
#define SENS_TRANSL	100.0
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
	glutCreateWindow("Modos de Neblina");

	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);

	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a função callback para tratamento das teclas ASCII
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

