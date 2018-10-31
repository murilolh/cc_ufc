//*****************************************************
//
// ExemploGLColorMask.cpp 
// Um programa OpenGL simples que abre uma janela GLUT, 
// desenha três "torus" com iluminação, um de cada cor,
// permite fazer zoom in e zoom out quando os botões do 
// mouse são pressionados e mover a posição do 
// observador virtual com as teclas de setas, HOME e END.
// Além disso, é possível utilizar uma máscara para RGB
// pressionando as teclas r,g,b,R,G e B.
//
// Marcelo Cohen e Isabel H. Manssour
// Este código acompanha o livro 
// "OpenGL - Uma Abordagem Prática e Objetiva"
// 
//*****************************************************

#include <GL/glut.h>
#include <stdlib.h>

GLfloat angle, fAspect;
GLfloat rotX, rotY;
GLdouble obsZ;
GLboolean r, g, b;

// Função responsável pela especificação dos parâmetros de iluminação
void DefineIluminacao (void)
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

// Função callback de redesenho da janela de visualização
void Desenha(void)
{
	// Limpa a janela de visualização com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	// Altera a máscara que é aplicada no color buffer
	glColorMask(r,g,b, GL_TRUE);

	// Chama a função que especifica os parâmetros de iluminação
	DefineIluminacao();

	// Altera a cor do desenho para azul
	glColor3f(0.0f, 0.0f, 1.0f);
	glPushMatrix();
		glTranslatef(0,25,0);
		glutSolidTorus(10.0, 16.0, 20, 40); 
	glPopMatrix();

	// Altera a cor do desenho para vermelho
	glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
		glTranslatef(-34,-24,0);
		glutSolidTorus(10.0, 16.0, 20, 40); 
	glPopMatrix();

	// Altera a cor do desenho para branco
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
		glTranslatef(34,-24,0);
		glutSolidTorus(10.0, 16.0, 20, 40); 
	glPopMatrix();

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
	// Especifica posição do observador e do alvo
	glTranslatef(0,0,-obsZ);
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

// Função callback chamada para gerenciar eventos de teclas normais (ESC)
void Teclado (unsigned char tecla, int x, int y)
{
	switch(tecla)
	{
		case 27:	// ESC ?
					exit(0);
					break;
		case 'r':	r = !r;
					break;
		case 'g':	g = !g;
					break;
		case 'b':	b = !b;
					break;
	}
	glutPostRedisplay();
}

// Função callback chamada para gerenciar eventos de teclas especiais (F1,PgDn,...)
void TeclasEspeciais (int tecla, int x, int y)  
{
	switch (tecla)
	{
		case GLUT_KEY_LEFT:	rotY--;
							break;
		case GLUT_KEY_RIGHT:rotY++;
							break;
		case GLUT_KEY_UP:	rotX++;
							break;
		case GLUT_KEY_DOWN:	rotX--;
							break;
		case GLUT_KEY_HOME:	obsZ++;
							break;
		case GLUT_KEY_END:	obsZ--;
							break;
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

// Função callback chamada quando são notificados os eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN)   // Zoom in
			if (angle >= 10) angle -= 5;
		
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN)   // Zoom out
			if (angle <= 130) angle += 5;
		
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

// Função responsável por inicializar parâmetros e variáveis
void Inicializa (void)
{   
	// Define a cor de fundo da janela de visualização como preto
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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
     
	// Inicializa a variável que especifica o ângulo da projeção
	// perspectiva
	angle=45;
    
	// Inicializa as variáveis usadas para alterar a posição do 
	// observador virtual
	rotX = 0;
	rotY = 0;
	obsZ = 150;   
	
	// Inicializa as variáveis usadas na chamada da função glColorMask
	r = g = b = GL_TRUE;
}

// Programa Principal 
int main(void)
{
	// Define o modo de operação da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
 
	// Especifica a posição inicial da janela GLUT
	glutInitWindowPosition(5,5); 
    
	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(450,450); 
 
	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Desenho de 3 torus para testar o uso de máscara para color buffer");
 
	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);
  
	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a função callback que gerencia os eventos do mouse   
	glutMouseFunc(GerenciaMouse);

	// Registra a função callback para tratamento das teclas normais 
	glutKeyboardFunc (Teclado);

	// Registra a função callback para tratamento das teclas especiais
	glutSpecialFunc (TeclasEspeciais);
     
	// Chama a função responsável por fazer as inicializações 
	Inicializa();
 
	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();
 
	return 0;
}
