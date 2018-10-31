//*****************************************************
//
// Linhas.cpp 
// Um programa OpenGL simples que abre uma janela GLUT 
// e faz o desenho de algumas linhas com cores, estilos 
// e espessuras diferentes
//
// Marcelo Cohen e Isabel H. Manssour
// Este c�digo acompanha o livro 
// "OpenGL - Uma Abordagem Pr�tica e Objetiva"
// 
//*****************************************************

#include <stdlib.h>
#include <GL/glut.h>
    
// Fun��o callback de redesenho da janela de visualiza��o
void Desenha(void) 
{
	// Limpa a janela de visualiza��o com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

	// Habilita a altera��o do estilo das linhas
	glEnable(GL_LINE_STIPPLE);

	// Altera a cor do desenho para vermelho
	glColor3f(1.0f, 0.0f, 0.0f);

	// Altera a espessura da linha
	glLineWidth(0.8);

	// Altera o estilo da linha 
	glLineStipple(1, 0xFFFF);
	glBegin(GL_LINES);
		glVertex2f(-40.0f, 40.0f);
		glVertex2f(40.0f, 40.0f);
	glEnd();

	// Altera a cor do desenho para verde
	glColor3f(0.0f, 1.0f, 0.0f);

	// Altera a espessura da linha
	glLineWidth(1.6);

	// Altera o estilo da linha 
	glLineStipple(4, 0x1F2F);
	glBegin(GL_LINES);
		glVertex2f(-40.0f, 30.0f);
		glVertex2f(40.0f, 30.0f);
	glEnd();

	// Altera a cor do desenho para azul
	glColor3f(0.0f, 0.0f, 1.0f);
    
	// Altera a espessura da linha
	glLineWidth(2.4);
    
	// Altera o estilo da linha 
	glLineStipple(1, 0x01010);
	glBegin(GL_LINES);
		glVertex2f(-40.0f, 20.0f);
		glVertex2f(40.0f, 20.0f);
	glEnd();

	// Altera a cor do desenho para preto
	glColor3f(0.0f, 0.0f, 0.0f);

	// Altera a espessura da linha
	glLineWidth(3.2);

	// Altera o estilo da linha 
	glLineStipple(2, 0xF020);
	glBegin(GL_LINES);
		glVertex2f(-40.0f, 10.0f);
		glVertex2f(40.0f, 10.0f);
	glEnd();

	// Altera a cor do desenho para magenta
	glColor3f(1.0f, 0.0f, 1.0f);

	// Altera a espessura da linha
	glLineWidth(4.0);

	// Altera o estilo da linha 
	glLineStipple(3, 0x00FF);
	glBegin(GL_LINES);
		glVertex2f(-40.0f, 0.0f);
		glVertex2f(40.0f, 0.0f);
	glEnd();

	// Altera a cor do desenho para preto
	glColor3f(0.0f, 0.0f, 0.0f);

	// Altera a espessura da linha
	glLineWidth(4.8);

	// Altera o estilo da linha 
	glLineStipple(3, 0x0F0F);
	glBegin(GL_LINES);
		glVertex2f(-40.0f, -10.0f);
		glVertex2f(40.0f, -10.0f);
	glEnd();

	// Altera a cor do desenho para azul
	glColor3f(0.0f, 0.0f, 1.0f);

	// Altera a espessura da linha
	glLineWidth(5.6);

	// Altera o estilo da linha 
	glLineStipple(5, 0x5555);
	glBegin(GL_LINES);
		glVertex2f(-40.0f, -20.0f);
		glVertex2f(40.0f, -20.0f);
	glEnd();

	// Altera a cor do desenho para verde
	glColor3f(0.0f, 1.0f, 0.0f);

	// Altera a espessura da linha
	glLineWidth(6.4);

	// Altera o estilo da linha 
	glLineStipple(1, 0x3F07);
	glBegin(GL_LINES);
		glVertex2f(-40.0f, -30.0f);
		glVertex2f(40.0f, -30.0f);
	glEnd();

	// Altera a cor do desenho para vermelho
	glColor3f(1.0f, 0.0f, 0.0f);
    
	// Altera a espessura da linha
	glLineWidth(7.2);
    
	// Altera o estilo da linha 
	glLineStipple(4, 0x3F07);
	glBegin(GL_LINES);
		glVertex2f(-40.0f, -40.0f);
		glVertex2f(40.0f, -40.0f);
	glEnd();

	// Executa os comandos OpenGL 
	glFlush();
}

// Fun��o callback chamada quando o tamanho da janela � alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h) 
{
	// Evita a divisao por zero
	if (h == 0)
		h = 1;

	// Especifica as dimens�es da Viewport
	glViewport(0, 0, w, h);

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de sele��o (esquerda, direita, inferior, 
	// superior) mantendo a propor��o com a janela de visualiza��o
	if (w <= h)
		gluOrtho2D(-50.0f, 50.0f, -50.0f * h / w, 50.0f * h / w);
	else
		gluOrtho2D(-50.0f * w / h, 50.0f * w / h, -50.0f, 50.0f);
}

// Fun��o callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}

// Fun��o respons�vel por inicializar par�metros e vari�veis
void Inicializa(void) 
{
	// Define a cor de fundo da janela de visualiza��o como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
} 

// Programa Principal 
int main(void) 
{
	// Define do modo de opera��o da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Especifica a posi��o inicial da janela GLUT
	glutInitWindowPosition(5, 5);

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(450, 450);

	// Cria a janela passando como argumento o t�tulo da mesma
	glutCreateWindow("Desenho de Linhas");

	// Registra a fun��o callback de redesenho da janela de visualiza��o
	glutDisplayFunc(Desenha);

	// Registra a fun��o callback de redimensionamento da janela de visualiza��o
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a fun��o callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);

	// Chama a fun��o respons�vel por fazer as inicializa��es 
	Inicializa();

	// Inicia o processamento e aguarda intera��es do usu�rio
	glutMainLoop();

	return 0;
}
