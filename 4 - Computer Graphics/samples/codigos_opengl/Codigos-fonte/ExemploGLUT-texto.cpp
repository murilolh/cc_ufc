//*****************************************************
//
// ExemploGLUT-texto.cpp
// Um programa OpenGL simples que exibe textos
// usando a GLUT.
//
// Marcelo Cohen e Isabel H. Manssour
// Este código acompanha o livro 
// "OpenGL - Uma Abordagem Prática e Objetiva"
// 
//*****************************************************

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

// Função que recebe a fonte e um texto por parâmetro para ser exibido na 
// tela usando caracteres bitmap
void DesenhaTexto(void *font, char *string) 
{
	// Exibe caractere a caractere
	while(*string)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*string++); 
}

// Função que recebe a fonte e um texto por parâmetro para ser exibido na 
// tela usando fonte de linhas
void DesenhaTextoStroke(void *font, char *string) 
{  
	// Exibe caractere a caractere
	while(*string)
		glutStrokeCharacter(GLUT_STROKE_ROMAN,*string++); 
}

// Função callback de redesenho da janela de visualização
void Desenha(void)
{
	// Limpa a janela de visualização com a cor de fundo definida
	glClear(GL_COLOR_BUFFER_BIT);

	// Define a cor para os textos: preto
	glColor3f(0,0,0);

	// Posiciona o texto stroke usando transformações geométricas
	glPushMatrix();	
	glTranslatef(-50,0,0);
	glScalef(0.2, 0.2, 0.2); // diminui o tamanho do fonte
	glRotatef(45, 0,0,1); // rotaciona o texto
	glLineWidth(3); // define a espessura da linha
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"Stroke");
	glPopMatrix();

	// Posição no universo onde o texto bitmap será colocado 
	glRasterPos2f(0,0); 
	DesenhaTexto(GLUT_BITMAP_TIMES_ROMAN_24,"Bitmap");
	// Exibe o desenha na janela
	glutSwapBuffers();
}

// Função callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y) 
{
	if (key == 27) 
		exit(0);
}

// Inicializa projeção
void Inicializa(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100,100,-100,100);
	glMatrixMode(GL_MODELVIEW);
	
	// Define a cor de fundo de tela como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

// Programa Principal
int main(void)
{
	// Define do modo de operação da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB );

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(500,400);

	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Textos com a GLUT");

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

