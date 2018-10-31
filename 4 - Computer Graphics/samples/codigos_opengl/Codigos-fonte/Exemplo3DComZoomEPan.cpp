//*****************************************************
//
// Exemplo3DComZoomEPan.cpp 
// Um programa OpenGL simples que abre uma janela GLUT, 
// desenha um "torus" e permite fazer: zoom in e 
// zoom out quando os bot�es do mouse s�o pressionados
// (utiliza a proje��o perspectiva); e pan quando as
// teclas page up, page down, seta para cima, seta para 
// baixo, seta para esquerda e seta para direita s�o
// pressionadas.
//
// Marcelo Cohen e Isabel H. Manssour
// Este c�digo acompanha o livro 
// "OpenGL - Uma Abordagem Pr�tica e Objetiva"
// 
//*****************************************************

#include <stdlib.h>
#include <GL/glut.h>

GLfloat angle, fAspect;
GLfloat deslocamentoX, deslocamentoY, deslocamentoZ;

// Fun��o callback de redesenho da janela de visualiza��o
void Desenha(void)
{
	// Limpa a janela de visualiza��o com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

	// Altera a cor do desenho para preto
	glColor3f(0.0f, 0.0f, 0.0f);

	// Fun��o da GLUT para fazer o desenho de um "torus" 
	// com a cor corrente
	glutWireTorus(20.0, 35.0, 20, 40); 

	// Executa os comandos OpenGL
	glFlush();
}

// Fun��o usada para especificar o volume de visualiza��o
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de proje��o
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de proje��o
	glLoadIdentity();

	// Especifica a proje��o perspectiva(angulo,aspecto,zMin,zMax)
	gluPerspective(angle,fAspect,0.5,500);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posi��o do observador, do alvo e do vetor up
	gluLookAt(0+deslocamentoX,0+deslocamentoY,150+deslocamentoZ, 
		0+deslocamentoX,0+deslocamentoY,0+deslocamentoZ, 
		0,1,0);
}

// Fun��o callback chamada quando o tamanho da janela � alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divis�o por zero
	if ( h == 0 ) h = 1;

	// Especifica as dimens�es da viewport
	glViewport(0, 0, w, h);

	// Calcula a corre��o de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}

// Fun��o callback chamada para gerenciar eventos de teclas especiais(F1,PgDn,...)
void TeclasEspeciais(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:		// desloca o volume de visualiza��o para cima
								deslocamentoY -= 2;
								break;
		case GLUT_KEY_DOWN:		// desloca o volume de visualiza��o para baixo
								deslocamentoY += 2;
								break;
		case GLUT_KEY_LEFT:		// desloca o volume de visualiza��o para o lado esquerdo
								deslocamentoX += 2;
								break;
		case GLUT_KEY_RIGHT:	// desloca o volume de visualiza��o para o lado direito
								deslocamentoX -= 2;
								break;
		case GLUT_KEY_PAGE_UP:	// desloca o volume de visualiza��o para frente
								deslocamentoZ -= 2;
								break;
		case GLUT_KEY_PAGE_DOWN:// desloca o volume de visualiza��o para tr�s
								deslocamentoZ += 2;
		break;
	}
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

// Fun��o callback chamada quando s�o notificados os eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {  // zoom in
			if (angle >= 10) angle -= 5;
		}
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {  // zoom out
			if (angle <= 130) angle += 5;
		}
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

// Fun��o callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y) 
{
	if (key == 27)
		exit(0);
}

// Fun��o respons�vel por inicializar par�metros e vari�veis
void Inicializa (void)
{   
	// Define a cor de fundo da janela de visualiza��o como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Inicializa a vari�vel que especifica o �ngulo da proje��o
	// perspectiva
	angle=45;

	// Inicializa as vari�veis utilizadas para implementa��o
	// da opera��o de pan
	deslocamentoX = 0.0f;
	deslocamentoY = 0.0f;
	deslocamentoZ = 0.0f;
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
	glutCreateWindow("Desenho de um torus 3D");

	// Registra a fun��o callback de redesenho da janela de visualiza��o
	glutDisplayFunc(Desenha);

	// Registra a fun��o callback de redimensionamento da janela de visualiza��o
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a fun��o callback para tratamento das teclas especiais
	glutSpecialFunc(TeclasEspeciais); 

	// Registra a fun��o callback que gerencia os eventos do mouse   
	glutMouseFunc(GerenciaMouse);

	// Registra a fun��o callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);

	// Chama a fun��o respons�vel por fazer as inicializa��es 
	Inicializa();

	// Inicia o processamento e aguarda intera��es do usu�rio
	glutMainLoop();

	return 0;
}
