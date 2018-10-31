//*****************************************************
//
// ExemploTriangulos2DFan.cpp 
// Um programa OpenGL simples que abre uma janela GLUT 
// e faz o desenho de uma seqüência de triângulos 
// conectados a partir de uma mesma origem
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

	// Altera a cor do desenho para cinza
	glColor3f(0.5f, 0.5f, 0.5f); 
  
	// Desenha uma seqüencia de triângulos
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(  0.0f,  0.0f);
		glVertex2f(-20.0f,  0.0f);
		glVertex2f(  0.0f, 20.0f);        
		glVertex2f( 20.0f,  0.0f);
		glVertex2f(  0.0f,-20.0f);
		glVertex2f(-20.0f,  0.0f);
	glEnd();

	// Altera a cor do desenho para preta
	glColor3f(0.0f, 0.0f, 0.0f); 
  
	// Desenha uma seqüencia de linhas
	glBegin(GL_LINES);
		glVertex2f(  0.0f,  0.0f);
		glVertex2f(-20.0f,  0.0f);
		glVertex2f(  0.0f,  0.0f);  
		glVertex2f(  0.0f, 20.0f);
		glVertex2f(  0.0f,  0.0f);               
		glVertex2f( 20.0f,  0.0f);
		glVertex2f(  0.0f,  0.0f);       
		glVertex2f(  0.0f,-20.0f);
	glEnd();
        
	// Executa os comandos OpenGL 
	glFlush();
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Evita a divisao por zero
	if(h == 0) h = 1;
                           
	// Especifica as dimensões da Viewport
	glViewport(0, 0, w, h);

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de seleção (esquerda, direita, inferior, 
	// superior) mantendo a proporção com a janela de visualização
	if (w <= h) 
		gluOrtho2D (-50.0f, 50.0f, -50.0f*h/w, 50.0f*h/w);
	else 
		gluOrtho2D (-50.0f*w/h, 50.0f*w/h, -50.0f, 50.0f);
}

// Função callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)  
{
	if (key == 27) 
		exit(0);
}

// Função responsável por inicializar parâmetros e variáveis
void Inicializa (void)
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
	glutInitWindowPosition(5,5); 
    
	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(450,450); 
 
	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Exemplo com GL_TRIANGLE_FAN");
 
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
