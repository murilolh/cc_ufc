//*****************************************************
//
// ExemploTextura1D.cpp 
// Um programa OpenGL simples que abre uma janela GLUT 
// e desenha um plano com uma textura 1D
//
// É possível ativar/desativar a repetição da textura
// usando a tecla "r" e controlar a quantidade de
// repetições com as teclas "+" e "-"
//
// Também é possível ativar/desativar a interpolação
// linear (GL_LINEAR) da textura usando a tecla 'f'
//
// Marcelo Cohen e Isabel H. Manssour
// Este código acompanha o livro 
// "OpenGL - Uma Abordagem Prática e Objetiva"
// 
//*****************************************************

#include <GL/glut.h>
#include <stdlib.h>

// Variáveis para controles de navegação
GLfloat angle, fAspect;
GLfloat rotX, rotY, rotX_ini, rotY_ini;
GLfloat obsX, obsY, obsZ, obsX_ini, obsY_ini, obsZ_ini;
int x_ini,y_ini,bot;

// Define uma textura 1D com 16 posições
#define TAM	16
GLubyte textura[] = { 0,0,0,0,64,64,64,64,128,128,128,128,192,192,192,192 };

// Desativa repetição da textura
char repete = 0;

// Desativa interpolação linear da textura
GLint filtro = GL_NEAREST;

// Define valor final da coordenada de textura
float final = 1.0;

// Armazena identificação da textura
GLuint textura_id;

// Função callback de redesenho da janela de visualização
void Desenha(void)
{
	// Limpa a janela de visualização com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_TEXTURE_1D);

	glBegin(GL_QUADS);
		glTexCoord1f(0);
		glVertex3f(-1,-1,0);
		glTexCoord1f(final);
		glVertex3f( 1,-1,0);
		glTexCoord1f(final);
		glVertex3f( 1, 1,0);
		glTexCoord1f(0);
		glVertex3f(-1, 1,0);
	glEnd();

	glDisable(GL_TEXTURE_1D);

	// Executa os comandos OpenGL
	glutSwapBuffers();
}

// Função usada para especificar a posição do observador virtual
void PosicionaObservador(void)
{
	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();
	// Posiciona e orienta o observador
	glTranslatef(-obsX,-obsY,-obsZ);
	glRotatef(rotX,1,0,0);
	glRotatef(rotY,0,1,0);
}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva 
	// (angulo, aspecto, zMin, zMax)
	gluPerspective(90,fAspect,0.1,500);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	PosicionaObservador();
}


// Função callback para eventos de teclado
void Teclado(unsigned char key, int x, int y)
{
	// Trata as diversas teclas
	switch(key)
	{
		case 27:	exit(0);
					break;
		case 'f':	if(filtro == GL_LINEAR) filtro = GL_NEAREST;
					else filtro = GL_LINEAR;
					break;
		case 'r':	repete = !repete;
					break;
		case '+':	if(final<=10.0) final += 0.1;
					break;
		case '-':	if(final>0) final -= 0.1;
					break;
	}

	// Ajusta os parâmetros de repetição
	if(repete)
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	else
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP);

	// Ajusta os filtros
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, filtro);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, filtro);
	
	glutPostRedisplay();
}

// Função callback para tratar eventos de teclas especiais
void TeclasEspeciais (int tecla, int x, int y)  
{
	switch (tecla)
	{
		case GLUT_KEY_HOME:	if(angle>=10)  angle -=5;
							break;
		case GLUT_KEY_END:	if(angle<=150) angle +=5;
							break;
	}
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
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

// Função callback para eventos de botões do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	if(state==GLUT_DOWN)
	{
		// Salva os parâmetros atuais
		x_ini = x;
		y_ini = y;
		obsX_ini = obsX;
		obsY_ini = obsY;
		obsZ_ini = obsZ;
		rotX_ini = rotX;
		rotY_ini = rotY;
		bot = button;
	}
	else bot = -1;
}

// Função callback para eventos de movimento do mouse
#define SENS_ROT	5.0
#define SENS_OBS	100.0
#define SENS_TRANSL	100.0
void GerenciaMovim(int x, int y)
{
	// Botão esquerdo ?
	if(bot==GLUT_LEFT_BUTTON)
	{
		// Calcula diferenças
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		// E modifica ângulos
		rotY = rotY_ini - deltax/SENS_ROT;
		rotX = rotX_ini - deltay/SENS_ROT;
	}
	// Botão direito ?
	else if(bot==GLUT_RIGHT_BUTTON)
	{
		// Calcula diferença
		int deltaz = y_ini - y;
		// E modifica distância do observador
		obsZ = obsZ_ini + deltaz/SENS_OBS;
	}
	// Botão do meio ?
	else if(bot==GLUT_MIDDLE_BUTTON)
	{
		// Calcula diferenças
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		// E modifica posições
		obsX = obsX_ini + deltax/SENS_TRANSL;
		obsY = obsY_ini - deltay/SENS_TRANSL;
	}
	PosicionaObservador();
	glutPostRedisplay();
}

// Função responsável por inicializar parâmetros e variáveis
void Inicializa (void)
{   
	// Define a cor de fundo da janela de visualização como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Gera um número de identificação para a textura
	glGenTextures(1,&textura_id);

	// Associa a textura aos comandos seguintes
	glBindTexture(GL_TEXTURE_1D, textura_id);

	// Envia a textura para uso pela OpenGL
	glTexImage1D(GL_TEXTURE_1D, 0, GL_LUMINANCE, TAM, 0, GL_LUMINANCE,
	       	GL_UNSIGNED_BYTE, textura);

	// Define os filtros de magnificação e minificação
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// Seleciona o modo de aplicação da textura
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	// Inicializa as variáveis usadas para alterar a posição do 
	// observador virtual
	rotX = 0;
	rotY = 0;
	obsX = obsY = 0;
	obsZ = 1.5;
}

// Programa Principal 
int main(void)
{
	// Define do modo de operação da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
 
	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(450,450); 
 
	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Texturas 1D");
 
	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);
  
	// Registra a função callback de teclado
	glutKeyboardFunc(Teclado);

	// Registra a função callback de teclas especiais
	glutSpecialFunc(TeclasEspeciais);

	// Registra a função callback para eventos de botões do mouse	
	glutMouseFunc(GerenciaMouse);
	 
	// Registra a função callback para eventos de movimento do mouse	
	glutMotionFunc(GerenciaMovim);

	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela);
    
	// Chama a função responsável por fazer as inicializações 
	Inicializa();
 
	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();
 
	return 0;
}
