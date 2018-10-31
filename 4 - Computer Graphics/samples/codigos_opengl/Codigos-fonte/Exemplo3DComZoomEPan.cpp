//*****************************************************
//
// Exemplo3DComZoomEPan.cpp 
// Um programa OpenGL simples que abre uma janela GLUT, 
// desenha um "torus" e permite fazer: zoom in e 
// zoom out quando os botões do mouse são pressionados
// (utiliza a projeção perspectiva); e pan quando as
// teclas page up, page down, seta para cima, seta para 
// baixo, seta para esquerda e seta para direita são
// pressionadas.
//
// Marcelo Cohen e Isabel H. Manssour
// Este código acompanha o livro 
// "OpenGL - Uma Abordagem Prática e Objetiva"
// 
//*****************************************************

#include <stdlib.h>
#include <GL/glut.h>

GLfloat angle, fAspect;
GLfloat deslocamentoX, deslocamentoY, deslocamentoZ;

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

	// Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)
	gluPerspective(angle,fAspect,0.5,500);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posição do observador, do alvo e do vetor up
	gluLookAt(0+deslocamentoX,0+deslocamentoY,150+deslocamentoZ, 
		0+deslocamentoX,0+deslocamentoY,0+deslocamentoZ, 
		0,1,0);
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

// Função callback chamada para gerenciar eventos de teclas especiais(F1,PgDn,...)
void TeclasEspeciais(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:		// desloca o volume de visualização para cima
								deslocamentoY -= 2;
								break;
		case GLUT_KEY_DOWN:		// desloca o volume de visualização para baixo
								deslocamentoY += 2;
								break;
		case GLUT_KEY_LEFT:		// desloca o volume de visualização para o lado esquerdo
								deslocamentoX += 2;
								break;
		case GLUT_KEY_RIGHT:	// desloca o volume de visualização para o lado direito
								deslocamentoX -= 2;
								break;
		case GLUT_KEY_PAGE_UP:	// desloca o volume de visualização para frente
								deslocamentoZ -= 2;
								break;
		case GLUT_KEY_PAGE_DOWN:// desloca o volume de visualização para trás
								deslocamentoZ += 2;
		break;
	}
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

// Função callback chamada quando são notificados os eventos do mouse
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

	// Inicializa a variável que especifica o ângulo da projeção
	// perspectiva
	angle=45;

	// Inicializa as variáveis utilizadas para implementação
	// da operação de pan
	deslocamentoX = 0.0f;
	deslocamentoY = 0.0f;
	deslocamentoZ = 0.0f;
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

	// Registra a função callback para tratamento das teclas especiais
	glutSpecialFunc(TeclasEspeciais); 

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
