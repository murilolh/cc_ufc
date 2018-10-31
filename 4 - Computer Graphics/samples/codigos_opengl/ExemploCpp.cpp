//*****************************************************
//
// ExemploCpp.cpp 
// Classe que implementa os métodos responsáveis
// por abrir uma janela GLUT, desenhar um "torus" com 
// iluminação, e permitir fazer zoom in e zoom out e 
// mover a posição do observador virtual com as teclas
// Home/End e o mouse. 
//
// Marcelo Cohen e Isabel H. Manssour
// Este código acompanha o livro 
// "OpenGL - Uma Abordagem Prática e Objetiva"
// 
//*****************************************************

#include "ExemploCpp.h"

// Inicialização dos atributos static

// Ângulo da projeção perspectiva
GLfloat ExemploCpp::angle=45;

// Posição e orientação do observador virtual
GLfloat ExemploCpp::rotX = 0;
GLfloat ExemploCpp::rotY = 0;
GLfloat ExemploCpp::obsX = 0;
GLfloat ExemploCpp::obsY = 0;
GLfloat ExemploCpp::obsZ = 150;  

// Posição e orientação iniciais, durante
// o movimento do mouse
GLfloat ExemploCpp::rotX_ini = 0;
GLfloat ExemploCpp::rotY_ini = 0;
GLfloat ExemploCpp::obsX_ini = 0;
GLfloat ExemploCpp::obsY_ini = 0;
GLfloat ExemploCpp::obsZ_ini = 0;

// Posição na tela onde o movimento do mouse iniciou
int ExemploCpp::x_ini = 0;
int ExemploCpp::y_ini = 0;

// Botão pressionado
int ExemploCpp::bot = 0;

// Valor para correção de aspecto
GLfloat ExemploCpp::fAspect = 1;

// Identificador de uma janela
GLint ExemploCpp::identificadorJanela = 0;

// Método construtor que recebe por parâmetro a largura, a altura, a posicao e o titulo da janela GLUT
ExemploCpp::ExemploCpp (int largura, int altura, int posicaoX, int posicaoY, char *titulo)
{
	// Define o modo de operação da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
	// Especifica a posição inicial da janela GLUT
	glutInitWindowPosition(posicaoX,posicaoY); 
	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(largura,altura); 
	// Cria a janela passando como argumento o título da mesma
	identificadorJanela = glutCreateWindow(titulo);
	// Registra o método callback de redesenho da janela
	glutDisplayFunc(Desenha);
	// Registra o método callback de redimensionamento da janela
	glutReshapeFunc(AlteraTamanhoJanela);
	// Registra o método callback que gerencia os eventos do mouse   
	glutMouseFunc(GerenciaMouse);
	// Registra a função callback para eventos de movimento do mouse	
	glutMotionFunc(GerenciaMovim);
	// Registra o método callback para tratamento das teclas normais 
	glutKeyboardFunc (Teclado);
	// Registra o método callback para tratamento das teclas especiais
	glutSpecialFunc (TeclasEspeciais);
	// Chama o método responsável por fazer as inicializações 
	Inicializa();
}

// Método destrutor usado para eliminar a janela criada
ExemploCpp::~ExemploCpp ()
{
	glutDestroyWindow(identificadorJanela); 	
}

// Método responsável pela chamada da função GLUT que inicia 
// o processamento e aguarda interações do usuário
void ExemploCpp::inicializaLoopGlut (void)
{
	glutMainLoop();
}

// Método responsável por inicializar parâmetros e variáveis
void ExemploCpp::Inicializa (void)
{   
	// Define a cor de fundo da janela de visualização como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);  
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);

	// Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_SMOOTH);  
}

// Método responsável pela especificação dos parâmetros de iluminação
void ExemploCpp::DefineIluminacao (void)
{
	GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0}; 
	GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0};	   // "cor" 
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho" 
	GLfloat posicaoLuz[4]={0.0, 50.0, 50.0, 1.0};

	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0}; 
	GLint especMaterial = 60;

	// Define a refletância do material 
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

	// Ativa o uso da luz ambiente 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );   
}

// Método usado para especificar a posição do observador virtual
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

// Método usado para especificar o volume de visualização
void ExemploCpp::EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)
	gluPerspective(angle,fAspect,0.5,500);

	PosicionaObservador();
}

// Método callback de redesenho da janela de visualização
void ExemploCpp::Desenha(void)
{
	// Limpa a janela de visualização com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	// Chama o método que especifica os parâmetros de iluminação
	DefineIluminacao();
    
	// Altera a cor do desenho para azul
	glColor3f(0.0f, 0.0f, 1.0f);

	// Função da GLUT para fazer o desenho de um "torus" 
	// com a cor corrente
	glutSolidTorus(20.0, 35.0, 20, 40); 

	// Executa os comandos OpenGL
	glutSwapBuffers();
}

// Método callback chamado para gerenciar eventos de teclas normais (ESC)
void ExemploCpp::Teclado (unsigned char tecla, int x, int y)
{
	if(tecla==27) // ESC ?
		exit(0);
}

// Método callback chamado para gerenciar eventos de teclas especiais
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

// Método callback chamado quando o tamanho da janela é alterado 
void ExemploCpp::AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divisão por zero
	if ( h == 0 ) h = 1;

	// Especifica as dimensões da viewport
	glViewport(0, 0, w, h);
 
	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}

// Método callback para eventos de botões do mouse
void ExemploCpp::GerenciaMouse(int button, int state, int x, int y)
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

// Método callback para eventos de movimento do mouse
#define SENS_ROT	5.0
#define SENS_OBS	5.0
#define SENS_TRANSL	5.0
void ExemploCpp::GerenciaMovim(int x, int y)
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

