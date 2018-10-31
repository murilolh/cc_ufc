//*****************************************************
//
// ExemploTextura2D-spheremap.cpp 
// Um programa OpenGL simples que abre uma janela GLUT 
// e desenha um plano com uma textura 2D, utilizando
// sphere mapping
//
// É possível selecionar qualquer um dos filtros
// utilizando a tecla 'f'
//
// Marcelo Cohen e Isabel H. Manssour
// Este código acompanha o livro 
// "OpenGL - Uma Abordagem Prática e Objetiva"
// 
//*****************************************************

#include "bibutil.h"

// Variáveis para controles de navegação
GLfloat angle, fAspect;
GLfloat rotX, rotY, rotX_ini, rotY_ini;
GLfloat obsX, obsY, obsZ, obsX_ini, obsY_ini, obsZ_ini;
int x_ini,y_ini,bot;

// Define a textura
TEX *textura;

// Define array com todos os filtros possíveis
GLint filtros[] = {
       GL_NEAREST, GL_LINEAR,
       GL_NEAREST_MIPMAP_NEAREST,GL_LINEAR_MIPMAP_NEAREST,
       GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR
};

// Define parâmetros de iluminação
GLfloat luzAmb[4] = { 0.3, 0.3, 0.3, 1 };	// luz ambiente
GLfloat luzDif[4] = { 0.9, 0.9, 0.9, 1 };	// luz difusa
GLfloat posLuz[4] = { 0.1, 3, 0.2, 1 };		// posição da fonte de luz

// Define filtro inicial como GL_NEAREST
int filtro = 0;

// Define modo inicial como GL_MODULATE
GLint modo = GL_MODULATE;

// Função callback de redesenho da janela de visualização
void Desenha(void)
{
	// Limpa a janela de visualização com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Posiciona e orienta o observador
	glTranslatef(-obsX,-obsY,-obsZ);
	glRotatef(rotX,1,0,0);
	glRotatef(rotY,0,1,0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textura->texid);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	glutSolidTeapot(1);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);

	// Executa os comandos OpenGL
	glutSwapBuffers();
}

// Função callback para eventos de teclado
void Teclado(unsigned char key, int x, int y)
{
	// Trata as diversas teclas
	switch(key)
	{
		case 27:	exit(1);
		case 'f':	if(++filtro > 5) filtro = 0;
					break;
		case 'm':	if(modo == GL_REPLACE) modo = GL_MODULATE;
					else modo = GL_REPLACE;
					break;
	}

	// Ajusta os filtros
	printf("Filtro: %d\n",filtro);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtros[filtro]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtros[filtro]);
	
	glutPostRedisplay();
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
	gluPerspective(angle,fAspect,0.1,500);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
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
	glutPostRedisplay();
}

// Função responsável por inicializar parâmetros e variáveis
void Inicializa (char *arquivo)
{   
	// Define a cor de fundo da janela de visualização como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Carrega a textura e envia para OpenGL
	textura = CarregaTextura(arquivo,true);

	// Habilita Z-Buffer
	glEnable(GL_DEPTH_TEST);

	// Associa a textura aos comandos seguintes
	glBindTexture(GL_TEXTURE_2D, textura->texid);

	// Seleciona o modo de sphere mapping
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	
	// Define os filtros de magnificação e minificação
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtros[filtro]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtros[filtro]);

	// Seleciona o modo de aplicação da textura
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	// Iluminação
	glLightfv( GL_LIGHT0, GL_POSITION, posLuz );
	glLightfv( GL_LIGHT0, GL_AMBIENT,  luzAmb );
	glLightfv( GL_LIGHT0, GL_DIFFUSE,  luzDif );

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	// Inicializa as variáveis usadas para alterar a posição do 
	// observador virtual
	angle = 60;
	rotX = 0;
	rotY = 0;
	obsX = obsY = 0;
	obsZ = 3;
}

// Programa Principal 
int main(int argc, char **argv)
{
	if(argc==1)
	{
			puts("ExemploTextura2D-spheremap <textura>");
			exit(1);
	}

	// Define do modo de operação da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
 
	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(450,450); 
 
	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Sphere mapping");
 
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
	Inicializa(argv[1]);
 
	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();
 
	return 0;
}
