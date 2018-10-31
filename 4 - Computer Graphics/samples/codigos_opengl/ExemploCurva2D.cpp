//*****************************************************
//
// ExemploCurva2D.cpp
// Um programa OpenGL simples que desenha uma curva
// paramétrica usando OpenGL
//
// Marcelo Cohen e Isabel H. Manssour
// Este código acompanha o livro 
// "OpenGL - Uma Abordagem Prática e Objetiva"
// 
//*****************************************************

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

// Total de pontos intermediários na curva
int prec = 10;

# define TOTAL	5
// Pontos de controle
float pontos[5][3] = {
	{ 0.0, 0.0, 0.0}, { 0.3, 0.8, 0.0}, 
	{ 0.7, 0.8, 0.0}, { 1.0, 0.0, 0.0},
	{ 0.5, 0.2, 0.0}
};

// Função callback de redesenho da janela de visualização
void Desenha(void)
{
	// Limpa a janela de visualização com a cor de fundo definida
	glClear(GL_COLOR_BUFFER_BIT);

	// Define a cor para o traçado da curva: preto
	glColor3f(0,0,0);

	// Define a espessura da linha
	glLineWidth(3);

	// Calcula incremento de acordo com o total
	// de pontos intermediários
	float delta = 1.0/(float)prec;

	// Traça a curva
	glBegin(GL_LINE_STRIP);
	for(float f = 0; f<=1.01; f+=delta)
		glEvalCoord1f(f);
	glEnd();

	// Define a cor para os pontos de controle: vermelho
	glColor3f(1,0,0);

	// Define tamanho de um ponto
	glPointSize(5);

	// Desenha os pontos de controle
	glBegin(GL_POINTS);
	for(int i=0;i<TOTAL;++i)
		glVertex3fv(pontos[i]);
	glEnd();

	// Exibe o desenho na janela
	glutSwapBuffers();
}

// Função callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y) 
{
	switch(key)
	{
		case '-':	if(prec>2) prec--;
					break;
		case '+':	prec++;
					break;
		case 27:	exit(0);
					break;
	}
	glutPostRedisplay();
}

// Inicializa projeção
void Inicializa(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-0.1,1.1,-0.1,1.1);
	glMatrixMode(GL_MODELVIEW);
	
	// Define a cor de fundo de tela como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Define significado dos pontos de controle
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, TOTAL, &pontos[0][0]);
	// Ativa geração de coordenadas
	glEnable(GL_MAP1_VERTEX_3);
}

// Programa Principal
int main(void)
{
	// Define do modo de operação da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB );

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(500,500);

	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Curvas 2D");

	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc (Desenha);

	// Registra a função callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);

	// Inicialização
	Inicializa();

	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();

	return 0;
}

