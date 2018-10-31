//*****************************************************
//
// Exemplo3DOrtoZoom.cpp
// Um programa OpenGL simples que abre uma janela GLUT, 
// desenha um "torus" e permite fazer zoom in e 
// zoom out quando os botões do mouse são pressionados
// (utiliza a projeção parelela ortográfica).
//
// Marcelo Cohen e Isabel H. Manssour
// Este código acompanha o livro 
// "OpenGL - Uma Abordagem Prática e Objetiva"
// 
//*****************************************************

#include <stdlib.h>
#include <GL/glut.h>

GLfloat win, fAspect;

// Função callback de redesenho da janela de visualização
void Desenha(void)
{
	// Limpa a janela de visualização com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

	// Altera a cor do desenho para preto
	glColor3f(0.0f, 0.0f, 0.0f);

	// Função da GLUT para fazer o desenho de um "torus" 
	// com a cor corrente
	glutWireTorus(20.0, 35.0, 20, 40); 

	// Executa os comandos OpenGL
	glFlush();
}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção paralela ortográfica 
	// (esquerda, direita, inferior, superior, 
	// plano frontal, plano traseiro)
	glOrtho(-win, win, -win, win, -200.0, 200.0);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posição do observador e do alvo
	gluLookAt(0,60,150, 0,0,0, 0,1,0);
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divisão por zero
	if ( h == 0 ) h = 1;

	// Especifica as dimensões da viewport
	glViewport(0, 0, w, h);

	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}

// Função callback chamada quando são notificados os eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {  // zoom in
			win -= 5;
		}
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {  // zoom out
			win += 5;
		}
	EspecificaParametrosVisualizacao();
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

	// Inicializa a variável que especifica o tamanho do volume de 
	// visualização para a projeção paralela ortográfica
	win=100;
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
	glutCreateWindow("Desenho de um torus 3D");

	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);

	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a função callback que gerencia os eventos do mouse  
	glutMouseFunc(GerenciaMouse);

	// Registra a função callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);

	// Chama a função responsável por fazer as inicializações 
	Inicializa();

	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();

	return 0;
}
