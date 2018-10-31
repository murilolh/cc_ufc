//*****************************************************
//
// Exemplo3DComAnimacao.cpp 
// Um programa OpenGL simples que abre uma janela GLUT 
// e desenha um "teapot" que gira ao redor do eixo y 
// para exemplificar a animação com objetos 3D.
//
// Marcelo Cohen e Isabel H. Manssour
// Este código acompanha o livro 
// "OpenGL - Uma Abordagem Prática e Objetiva"
// 
//*****************************************************

#include <stdlib.h>
#include <GL/glut.h>

GLfloat fAspect;
GLfloat angulo;

// Função callback de redesenho da janela de visualização
void Desenha(void)
{
	// Limpa a janela de visualização com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

	// Altera a cor do desenho para preto
	glColor3f(0.0f, 0.0f, 0.0f);

	glPushMatrix();

	// Aplica uma rotação no torus
	glRotatef(angulo, 0,1,0);

	// Função da GLUT para fazer o desenho de um "teapot" 
	// com a cor corrente
	glutWireTeapot(40.0);

	glPopMatrix();

	// Executa os comandos OpenGL
	glutSwapBuffers();
}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)
	gluPerspective(45,fAspect,0.5,500);

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

// Função callback chamada pela GLUT a cada intervalo de tempo
void Anima(int value)
{
	// Muda o angulo de rotação, e se chegar a 360, passa para zero
	if( ++angulo > 360.0f )
		angulo = 0.0f;

	// Redesenha o "teapot" em outra posição
	glutPostRedisplay();
	glutTimerFunc(60,Anima, 1);
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
	angulo = 0.0f;
}

// Programa Principal 
int main(void)
{
	// Define do modo de operação da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 

	// Especifica a posição inicial da janela GLUT
	glutInitWindowPosition(5,5); 

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(450,450); 

	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Animação de um teapot 3D");

	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);

	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a função callback que será chamada a cada intervalo de tempo
	glutTimerFunc(60, Anima, 1);

	// Registra a função callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);

	// Chama a função responsável por fazer as inicializações 
	Inicializa();

	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();

	return 0;
}
