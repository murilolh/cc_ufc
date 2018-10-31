//*****************************************************
//
// ExemploImagemCopia.cpp 
// Um programa OpenGL simples que abre uma janela GLUT, 
// desenha alguns objetos 2D na tela e a seguir, copia
// uma região da tela para outro local.
//
// Marcelo Cohen e Isabel H. Manssour
// Este código acompanha o livro 
// "OpenGL - Uma Abordagem Prática e Objetiva"
// 
//*****************************************************

#include "bibutil.h"

// Define a imagem
GLubyte *imagem;

GLsizei largura, altura;

// Função callback de redesenho da janela de visualização
void Desenha(void)
{
	// Limpa a janela de visualização com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

	// Inicializa as transformações
	glLoadIdentity();

	// Desenha 3 triângulos coloridos
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

	// Define a posição de desenho
	glRasterPos2i(150, 150);
	// Exibe a imagem na nova posição
	glDrawPixels(200, 200, GL_RGB, GL_UNSIGNED_BYTE, imagem);

	// Executa os comandos OpenGL 
	glFlush();
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Evita a divisao por zero
	if(h == 0) h = 1;

	// Atualiza as variáveis
	largura = w;
	altura = h;

	// Especifica as dimensões da Viewport
	glViewport(0, 0, largura, altura);	

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de seleção
	gluOrtho2D(0,largura-1,0,altura-1);
	
	// Retorna para modelview
	glMatrixMode(GL_MODELVIEW);
}

// Função callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if(key == 27)
	{
		// Libera a memória ocupada pela imagem
		if (imagem != NULL)
			free(imagem);
		exit(0);
	}
}

// Função responsável por inicializar parâmetros e variáveis
void Inicializa (void)
{   
	// Define a cor de fundo da janela de visualização como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Ajusta o alinhamento de dados sendo descompactados
	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);

	// Aloca memória para a imagem
	imagem = (GLubyte *) malloc(200*200*3);	// Cada pixel ocupa 3 bytes (RGB)
}

// Programa Principal 
int main(void)
{
	// Define do modo de operação da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 

	// Especifica a posição inicial da janela GLUT
	glutInitWindowPosition(5,5); 

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(450,450); 

	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Exemplo de Cópia de Imagens");

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

