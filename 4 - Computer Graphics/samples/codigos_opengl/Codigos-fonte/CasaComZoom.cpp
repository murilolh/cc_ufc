//*****************************************************
//
// CasaComZoom.cpp 
// Um programa OpenGL simples que abre uma janela GLUT, 
// desenha uma casa e permite que seja aplicado zoom in 
// e zoom out.
//
// Marcelo Cohen e Isabel H. Manssour
// Este c�digo acompanha o livro 
// "OpenGL - Uma Abordagem Pr�tica e Objetiva"
// 
//*****************************************************

#include <stdlib.h>
#include <GL/glut.h>

GLfloat win;
GLsizei largura, altura;

// Fun��o callback de redesenho da janela de visualiza��o
void Desenha(void)
{
	// Limpa a janela de visualiza��o com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

	// Desenha uma casinha composta de um quadrado e um tri�ngulo

	// Altera a cor do desenho para azul
	glColor3f(0.0f, 0.0f, 1.0f);
	// Desenha a casa
	glBegin(GL_QUADS);
		glVertex2f(-15.0f,-15.0f);
		glVertex2f(-15.0f,  5.0f);
		glVertex2f( 15.0f,  5.0f);
		glVertex2f( 15.0f,-15.0f);
	glEnd();

	// Altera a cor do desenho para branco
	glColor3f(1.0f, 1.0f, 1.0f);  
	// Desenha a porta e a janela  
	glBegin(GL_QUADS);
		glVertex2f(-4.0f,-14.5f);
		glVertex2f(-4.0f,  0.0f);
		glVertex2f( 4.0f,  0.0f);
		glVertex2f( 4.0f,-14.5f);
		glVertex2f( 7.0f,-5.0f);
		glVertex2f( 7.0f,-1.0f);
		glVertex2f(13.0f,-1.0f);
		glVertex2f(13.0f,-5.0f);
	glEnd();

	// Altera a cor do desenho para azul
	glColor3f(0.0f, 0.0f, 1.0f);
	// Desenha as "linhas" da janela  
	glBegin(GL_LINES);
		glVertex2f( 7.0f,-3.0f);
		glVertex2f(13.0f,-3.0f);
		glVertex2f(10.0f,-1.0f);
		glVertex2f(10.0f,-5.0f);
	glEnd();

	// Altera a cor do desenho para vermelho
	glColor3f(1.0f, 0.0f, 0.0f); 
	// Desenha o telhado
	glBegin(GL_TRIANGLES);
		glVertex2f(-15.0f, 5.0f);   
		glVertex2f(  0.0f,17.0f);
		glVertex2f( 15.0f, 5.0f);
	glEnd();

	// Executa os comandos OpenGL 
	glFlush();
}

// Fun��o callback chamada quando o tamanho da janela � alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Evita a divisao por zero
	if(h == 0) h = 1;

	// Atualiza as vari�veis
	largura = w;
	altura = h;

	// Especifica as dimens�es da Viewport
	glViewport(0, 0, largura, altura);	

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de sele��o (esquerda, direita, inferior, 
	// superior) mantendo a propor��o com a janela de visualiza��o
	if (largura <= altura) 
		gluOrtho2D (-win, win, -win*altura/largura, win*altura/largura);
	else 
		gluOrtho2D (-win*largura/altura, win*largura/altura, -win, win);
}

// Fun��o callback chamada para gerenciar eventos de teclas especiais(F1,PgDn,...)
void TeclasEspeciais(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
	{
		if (win > 0) 
			win -= 5.0f; // diminui o tamanho da window (zoom in)
	}
	else if (key == GLUT_KEY_DOWN) 
	{
		if (win < 900)
			win += 5.0f; // aumenta o tamanho da window (zoom out)
	}

	if (key == GLUT_KEY_UP || key == GLUT_KEY_DOWN) 
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		if (largura <= altura) 
			gluOrtho2D (-win, win, -win*altura/largura, win*altura/largura);
		else 
			gluOrtho2D (-win*largura/altura, win*largura/altura, -win, win); 
		glutPostRedisplay();
	}
}

// Fun��o callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}

// Fun��o respons�vel por inicializar par�metros e vari�veis
void Inicializa (void)
{   
	// Define a cor de fundo da janela de visualiza��o como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	win = 50.0f;
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
	glutCreateWindow("Exemplo com Zoom");

	// Registra a fun��o callback de redesenho da janela de visualiza��o
	glutDisplayFunc(Desenha);
 
	// Registra a fun��o callback de redimensionamento da janela de visualiza��o
	glutReshapeFunc(AlteraTamanhoJanela);
 
	// Registra a fun��o callback para tratamento das teclas especiais
	glutSpecialFunc(TeclasEspeciais); 

	// Registra a fun��o callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);

	// Chama a fun��o respons�vel por fazer as inicializa��es 
	Inicializa();

	// Inicia o processamento e aguarda intera��es do usu�rio
	glutMainLoop();

	return 0;
}
