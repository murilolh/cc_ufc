//*****************************************************
//
// Linhas.cpp 
// Um programa OpenGL simples que abre uma janela GLUT 
// e faz o desenho de algumas linhas com cores, estilos 
// e espessuras diferentes
//
// Marcelo Cohen e Isabel H. Manssour
// Este código acompanha o livro 
// "OpenGL - Uma Abordagem Prática e Objetiva"
// 
//*****************************************************

#include <stdlib.h>
#include <GL/glut.h>
    
// Função callback de redesenho da janela de visualização
void Desenha(void) 
{
	// Limpa a janela de visualização com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

	// Habilita a alteração do estilo das linhas
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

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h) 
{
	// Evita a divisao por zero
	if (h == 0)
		h = 1;

	// Especifica as dimensões da Viewport
	glViewport(0, 0, w, h);

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de seleção (esquerda, direita, inferior, 
	// superior) mantendo a proporção com a janela de visualização
	if (w <= h)
		gluOrtho2D(-50.0f, 50.0f, -50.0f * h / w, 50.0f * h / w);
	else
		gluOrtho2D(-50.0f * w / h, 50.0f * w / h, -50.0f, 50.0f);
}

// Função callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}

// Função responsável por inicializar parâmetros e variáveis
void Inicializa(void) 
{
	// Define a cor de fundo da janela de visualização como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
} 

// Programa Principal 
int main(void) 
{
	// Define do modo de operação da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Especifica a posição inicial da janela GLUT
	glutInitWindowPosition(5, 5);

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(450, 450);

	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Desenho de Linhas");

	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);

	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a função callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);

	// Chama a função responsável por fazer as inicializações 
	Inicializa();

	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();

	return 0;
}
