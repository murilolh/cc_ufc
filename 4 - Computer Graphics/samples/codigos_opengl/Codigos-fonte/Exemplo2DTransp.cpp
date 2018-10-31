//*****************************************************
//
// Exemplo2DTransp.cpp
// Um programa OpenGL demonstrando o uso de
// blending para obter o efeito de transpar�ncia
//
// Marcelo Cohen e Isabel H. Manssour
// Este c�digo acompanha o livro 
// "OpenGL - Uma Abordagem Pr�tica e Objetiva"
// 
//*****************************************************

#include <stdlib.h>
#include <GL/glut.h>

bool ordem = true;

void DesenhaQuadrado()
{
	// Desenha um quadrado	
	glBegin(GL_QUADS);
		glVertex2f(-10,-10);
		glVertex2f(-10, 10);       
		glVertex2f( 10, 10);       
		glVertex2f( 10,-10);
	glEnd();
}

void Desenha(void)
{
	// Limpa a janela de visualiza��o com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	if(ordem)
		glColor4f(1, 0, 0, 0.5);
	else
		glColor4f(0, 0, 1, 0.5);

	glTranslatef(-5,-5,0);
	// Desenha um quadrado	
	DesenhaQuadrado();	

	if(ordem)
		glColor4f(0, 0, 1, 0.5);
	else
		glColor4f(1, 0, 0, 0.5);

	// Desenha outro quadrado	
	glTranslatef(10,10,0);
	DesenhaQuadrado();	

	glutSwapBuffers();
}

// Fun��o respons�vel por inicializar par�metros e vari�veis
void Inicializa (void)
{   
	// Define a cor de fundo da janela de visualiza��o como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

// Fun��o callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	switch(key)
	{
			case 27:	exit(0);
						break;
			case 't':	ordem = !ordem;
						break;
	}
	glutPostRedisplay();
}

// Fun��o callback chamada quando o tamanho da janela � alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Evita a divisao por zero
	if(h == 0) h = 1;

	// Especifica as dimens�es da Viewport
	glViewport(0, 0, w, h);

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de sele��o (esquerda, direita, inferior, 
	// superior) mantendo a propor��o com a janela de visualiza��o
	if (w <= h) 
		gluOrtho2D (-20, 20, -20*h/w, 20*h/w);
	else 
		gluOrtho2D (-20*w/h, 20*w/h, -20, 20);

	glMatrixMode(GL_MODELVIEW);
}

// Programa Principal 
int main(void)
{
	// Define do modo de opera��o da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	// Especifica a posi��o inicial da janela GLUT
	glutInitWindowPosition(5,5); 

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(450,450); 
 
	// Cria a janela passando como argumento o t�tulo da mesma
	glutCreateWindow("Transpar�ncia em 2D");

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

