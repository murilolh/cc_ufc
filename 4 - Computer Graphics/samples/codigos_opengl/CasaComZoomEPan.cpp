//*****************************************************
//
// CasaComZoomEPan.cpp
// Um programa OpenGL simples que abre uma janela GLUT, 
// desenha uma casa e permite que seja aplicado zoom in, 
// zoom out e a operação de pan.
//
// Marcelo Cohen e Isabel H. Manssour
// Este código acompanha o livro 
// "OpenGL - Uma Abordagem Prática e Objetiva"
// 
//*****************************************************

#include <stdlib.h>
#include <GL/glut.h>

GLfloat win, deslocamentoX, deslocamentoY;
GLsizei largura, altura;

// Função callback de redesenho da janela de visualização
void Desenha(void)
{
	// Limpa a janela de visualização com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

	// Desenha uma casinha composta de um quadrado e um triângulo

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

void EspecificaParametrosDeVisualizacao(void)
{
	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de seleção (esquerda, direita, inferior, 
	// superior) mantendo a proporção com a janela de visualização
	if (largura <= altura) 
		gluOrtho2D (-win+deslocamentoX, win+deslocamentoX, 
			-win*altura/largura+deslocamentoY, win*altura/largura+deslocamentoY);
	else 
		gluOrtho2D (-win*largura/altura+deslocamentoX, win*largura/altura+deslocamentoX, 
			-win+deslocamentoY, win+deslocamentoY);

	glMatrixMode(GL_MODELVIEW);
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

	EspecificaParametrosDeVisualizacao();
}

// Função callback chamada para gerenciar eventos de teclas especiais(F1,PgDn,...)
void TeclasEspeciais(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:			// desloca a window para cima
									deslocamentoY += 2;
									break;
		case GLUT_KEY_DOWN:			// desloca a window para baixo
									deslocamentoY -= 2;
									break;
		case GLUT_KEY_LEFT:			// desloca a window para o lado esquerdo
									deslocamentoX -= 2;
									break;
		case GLUT_KEY_RIGHT:		// desloca a window para o lado direito
									deslocamentoX += 2;
									break;
		case GLUT_KEY_PAGE_UP:		if (win > 0)
										win -= 5.0f; // diminui o tamanho da window (zoom in)
									break;
		case GLUT_KEY_PAGE_DOWN:	if (win < 900)
										win += 5.0f; // aumenta o tamanho da window (zoom out)
									break;
	}
	EspecificaParametrosDeVisualizacao();
	glutPostRedisplay();
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
	win = 50.0f;
	deslocamentoX = 0.0f;
	deslocamentoY = 0.0f;	
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
	glutCreateWindow("Exemplo com Zoom e Pan");
 
	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);

	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a função callback para tratamento das teclas especiais
	glutSpecialFunc(TeclasEspeciais); 

	// Registra a função callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);

	// Chama a função responsável por fazer as inicializações 
	Inicializa();
 
	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();
 
	return 0;
}
