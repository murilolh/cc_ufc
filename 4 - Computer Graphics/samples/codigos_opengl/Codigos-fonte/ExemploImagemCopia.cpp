//*****************************************************
//
// ExemploImagemCopia.cpp 
// Um programa OpenGL simples que abre uma janela GLUT, 
// desenha alguns objetos 2D na tela e a seguir, copia
// uma regi�o da tela para outro local.
//
// Marcelo Cohen e Isabel H. Manssour
// Este c�digo acompanha o livro 
// "OpenGL - Uma Abordagem Pr�tica e Objetiva"
// 
//*****************************************************

#include "bibutil.h"

// Define a imagem
GLubyte *imagem;

GLsizei largura, altura;

// Fun��o callback de redesenho da janela de visualiza��o
void Desenha(void)
{
	// Limpa a janela de visualiza��o com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

	// Inicializa as transforma��es
	glLoadIdentity();

	// Desenha 3 tri�ngulos coloridos
	for(int i=0;i<3;++i)
	{
		switch(i)
		{
			case 0:	glColor3f(1.0f, 0.0f, 0.0f);
					break;
			case 1:	glColor3f(0.0f, 1.0f, 0.0f);
					break;
			case 2:	glColor3f(0.0f, 0.0f, 1.0f);
					break;
		}
		glBegin(GL_TRIANGLES);
			glVertex2f(20,20);
			glVertex2f(150,260);
			glVertex2f(280,20);
		glEnd();
		glTranslatef(20,20,0);
	}

	// Copia pixels da janela para imagem
	glReadPixels(0,0,200,200,GL_RGB,GL_UNSIGNED_BYTE,imagem);

	// Define a posi��o de desenho
	glRasterPos2i(150, 150);
	// Exibe a imagem na nova posi��o
	glDrawPixels(200, 200, GL_RGB, GL_UNSIGNED_BYTE, imagem);

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

	// Estabelece a janela de sele��o
	gluOrtho2D(0,largura-1,0,altura-1);
	
	// Retorna para modelview
	glMatrixMode(GL_MODELVIEW);
}

// Fun��o callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if(key == 27)
	{
		// Libera a mem�ria ocupada pela imagem
		if (imagem != NULL)
			free(imagem);
		exit(0);
	}
}

// Fun��o respons�vel por inicializar par�metros e vari�veis
void Inicializa (void)
{   
	// Define a cor de fundo da janela de visualiza��o como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Ajusta o alinhamento de dados sendo descompactados
	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);

	// Aloca mem�ria para a imagem
	imagem = (GLubyte *) malloc(200*200*3);	// Cada pixel ocupa 3 bytes (RGB)
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
	glutCreateWindow("Exemplo de C�pia de Imagens");

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

