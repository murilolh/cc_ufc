//*****************************************************
//
// ExemploTextura2D-matriz.cpp 
// Um programa OpenGL simples que abre uma janela GLUT 
// e desenha um plano com uma textura 2D, manipulando
// a matriz de textura
//
// � poss�vel ativar/desativar a repeti��o da textura
// usando a tecla 'r' e controlar a quantidade de
// repeti��es com as teclas '+' e '-'
//
// Tamb�m � poss�vel selecionar qualquer um dos filtros
// utilizando a tecla 'f'
//
// Finalmente, a dist�ncia do observador � controlada
// pelas teclas HOME e END, e a rota��o do plano com
// as setas
//
// Marcelo Cohen e Isabel H. Manssour
// Este c�digo acompanha o livro 
// "OpenGL - Uma Abordagem Pr�tica e Objetiva"
// 
//*****************************************************

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include "bibutil.h"

GLfloat fAspect;
GLfloat rotX, rotY;
GLdouble obsZ;

// Define uma textura 2D
TEX *textura;

// Define array com todos os filtros poss�veis
GLint filtros[] = {
       GL_NEAREST, GL_LINEAR,
       GL_NEAREST_MIPMAP_NEAREST,GL_LINEAR_MIPMAP_NEAREST,
       GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR
};

// Define par�metros de ilumina��o
GLfloat luzAmb[4] = { 0.3, 0.3, 0.3, 1 };	// luz ambiente
GLfloat luzDif[4] = { 1.0, 1.0, 1.0, 1 };	// luz difusa
GLfloat posLuz[4] = { 0, 0, 10, 1 };		// posi��o da fonte de luz

// Define escala da textura
GLfloat escala = 1.0;

// Define rota��o da textura
GLfloat rotacao = 0.0;

// Desativa repeti��o da textura
char repete = 0;

// Define filtro inicial como GL_NEAREST
GLint filtro = 0;

// Define modo inicial como GL_MODULATE
GLint modo = GL_MODULATE;

// Fun��o callback de redesenho da janela de visualiza��o
void Desenha(void)
{
	// Limpa a janela de visualiza��o com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textura->texid);

	glNormal3f(0,0,1);
	glBegin(GL_QUADS);
		glTexCoord2f(0,0);
		glVertex3f(-1,-1,0);
		glTexCoord2f(1,0);
		glVertex3f( 1,-1,0);
		glTexCoord2f(1,1);
		glVertex3f( 1, 1,0);
		glTexCoord2f(0,1);
		glVertex3f(-1, 1,0);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	// Executa os comandos OpenGL
	glutSwapBuffers();
}

// Fun��o usada para especificar a posi��o do observador virtual
void PosicionaObservador(void)
{
	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();
	// Seta posi��o da luz
	glLightfv( GL_LIGHT0, GL_POSITION, posLuz ); 
	// Especifica posi��o do observador e do alvo
	glTranslatef(0,0,-obsZ);
	glRotatef(rotX,1,0,0);
	glRotatef(rotY,0,1,0);
}

// Fun��o callback para eventos de teclado
void Teclado(unsigned char key, int x, int y)
{
	GLint valor;

	// Trata as diversas teclas
	switch(key)
	{
		case 27:	LiberaMateriais();
					exit(1);
					break;
		case 'f':	if(++filtro > 5) filtro = 0;
					break;
		case 'm':	modo = (modo == GL_REPLACE ? GL_MODULATE: GL_REPLACE);
					break;
		case 'r':	repete = !repete;
					break;
		case '+':	if(escala<=10.0) escala += 0.1;
					break;
		case '-':	if(escala>0) escala -= 0.1;
					break;
		case '/':	rotacao++;
					break;
		case '*':	rotacao--;
					break;
	}

	// Ajusta os par�metros de repeti��o
	if(repete)
		valor = GL_REPEAT;
	else
		valor = GL_CLAMP;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, valor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, valor);

	// Ajusta a escala e rota��o da textura
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glScalef(escala,escala,1);
	glRotatef(rotacao,0,0,1);
	glMatrixMode(GL_MODELVIEW);

	// Ajusta o modo de aplica��o da textura
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, modo);

	// Ajusta os filtros
	printf("Filtro: %d\n",filtro);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtros[filtro]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtros[filtro]);
	
	glutPostRedisplay();
}

// Fun��o callback para eventos de teclas especiais
void TecladoEspecial(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_LEFT:	rotY--;
							break;
		case GLUT_KEY_RIGHT:rotY++;
							break;
		case GLUT_KEY_UP:	rotX++;
							break;
		case GLUT_KEY_DOWN:	rotX--;
							break;
		case GLUT_KEY_HOME:	obsZ+=0.2;
							break;
		case GLUT_KEY_END:	obsZ-=0.2;
							break;
	}
	PosicionaObservador();
	glutPostRedisplay();
}

// Fun��o usada para especificar o volume de visualiza��o
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de proje��o
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de proje��o
	glLoadIdentity();

	// Especifica a proje��o perspectiva 
	// (angulo, aspecto, zMin, zMax)
	gluPerspective(90,fAspect,0.1,500);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	PosicionaObservador();
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

// Fun��o respons�vel por inicializar par�metros e vari�veis
void Inicializa (void)
{   
	// Define a cor de fundo da janela de visualiza��o como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Carrega a textura e envia para OpenGL
	textura = CarregaTextura("texturas/azulejo.jpg",true);

	// Associa a textura aos comandos seguintes
	glBindTexture(GL_TEXTURE_2D, textura->texid);

	// Define os filtros de magnifica��o e minifica��o
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtros[filtro]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtros[filtro]);

	// Seleciona o modo de aplica��o da textura
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, modo);

	// Seleciona o modo de repeti��o inicial
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	// Ilumina��o
	glLightfv( GL_LIGHT0, GL_AMBIENT,  luzAmb ); 
	glLightfv( GL_LIGHT0, GL_DIFFUSE,  luzDif );

	// Habilita normalize, pois vamos utilizar escala no objeto
	glEnable(GL_NORMALIZE);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	// Inicializa as vari�veis usadas para alterar a posi��o do 
	// observador virtual
	rotX = 0;
	rotY = 0;
	obsZ = 1.5;
}

// Programa Principal 
int main(void)
{
	// Define do modo de opera��o da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
 
	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(450,450); 
 
	// Cria a janela passando como argumento o t�tulo da mesma
	glutCreateWindow("Texturas 2D");
 
	// Registra a fun��o callback de redesenho da janela de visualiza��o
	glutDisplayFunc(Desenha);
  
	// Registra a fun��o callback de teclado
	glutKeyboardFunc(Teclado);

	// Registra a fun��o callback de teclas especiais
	glutSpecialFunc(TecladoEspecial);

	// Registra a fun��o callback de redimensionamento da janela de visualiza��o
	glutReshapeFunc(AlteraTamanhoJanela);
    
	// Chama a fun��o respons�vel por fazer as inicializa��es 
	Inicializa();
 
	// Inicia o processamento e aguarda intera��es do usu�rio
	glutMainLoop();
 
	return 0;
}
