//*****************************************************
//
// ExemploStencilBuffer.cpp 
// Um programa OpenGL que abre uma janela GLUT, desenha 
// quatro cubos, permite fazer zoom in e zoom out 
// com as teclas Home e End e alterar o observador com
// o mouse. Além disso, quando a tecla 'm' é pressionada,
// bloqueia ou restringe o desenho de uma região da tela
// equivalente a uma esfera que se move ao longo do eixo x. 
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

// Translação e velocidade da esfera
GLfloat tx=0, passo=0.8;

// Tipo de teste a ser realizado
GLboolean igual = true;

// Função responsável pela especificação dos parâmetros de iluminação
void DefineIluminacao (void)
{
	GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0}; 
	GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0};
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};
	GLfloat posicaoLuz[4]={0.0, 50.0, 50.0, 1.0};

	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0}; 
	GLint especMaterial = 60;

	// Define a refletância do material 
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

	// Ativa o uso da luz ambiente 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );   
}

// Inicializa o stencil buffer
void InicializaStencilBuffer()
{
	GLint referencia = 1; // Valor a ser comparado com o conteúdo do stencil buffer
	GLuint mascara = 1; // Máscara de bits para ser usada na comparação
     
	// Stencil buffer será limpo com o valor 0
	glClearStencil(0);
	// Limpa o stencil buffer
	glClear(GL_STENCIL_BUFFER_BIT);

	// Determina que o teste do stencil buffer sempre vai ser verdadeiro,
	// e nesse caso, associa o valor de referência a cada pixel desenhado
	glStencilFunc(GL_ALWAYS, referencia, mascara); 
	
	// Define como o valor de referência afeta o stencil buffer
	// Neste caso, o valor atual será substituído pelo valor de ref,
	// não importanto o resultado do teste de profundidade.
	glStencilOp(GL_REPLACE,GL_REPLACE,GL_REPLACE);

	// Desenha a esfera e preenche o stencil buffer	
	glPushMatrix();
		glTranslatef(tx, 0.0f, 0.0f);
		glutSolidSphere(20, 20, 20);
	glPopMatrix();

	// E não altera mais o stencil buffer
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
}

void DesenhaObjetos(void)
{
	// Desenha quatro cubos
	glPushMatrix();
		glTranslatef(-40.0f, 0.0f, 0.0f);
		glRotatef(45,1,1,1);
		glColor3f(1.0f, 1.0f, 0.0f);
		glutSolidTeapot(18);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(40.0f, 0.0f, 0.0f);
		glRotatef(45,1,-1,0);
		glColor3f(0.0f, 1.0f, 0.0f);
		glutSolidTorus(10,16,20,20); 
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0f, 25.0f, -25.0f);
		glRotatef(45,1,0.5,0);
		glColor3f(1.0f, 0.2f, 0.8f);
		glutSolidCone(16,35,10,10); 
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0f, -25.0f, -25.0f);
		glRotatef(45,1,-0.5,0);
		glColor3f(0.0f, 0.3f, 0.7f);
		glutSolidSphere(20,20,20);
	glPopMatrix();
}

// Função callback de redesenho da janela de visualização
void Desenha(void)
{ 
	// Chama a função que especifica os parâmetros de iluminação
	DefineIluminacao();

	// Chama a função que faz a inicialização do stencil buffer
	InicializaStencilBuffer();

	// Limpa a janela e o depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (igual)
		// Passa se o valor for igual a 1
		glStencilFunc(GL_EQUAL, 1, 1);
	else
		// Passa se o valor for diferente de 1
		glStencilFunc(GL_NOTEQUAL, 1, 1);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	DesenhaObjetos();

	if (!igual)
		// Passa se o valor for igual a 1
		glStencilFunc(GL_EQUAL, 1, 1);
	else
		// Passa se o valor for diferente de 1
		glStencilFunc(GL_NOTEQUAL, 1, 1);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	DesenhaObjetos();

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
	DefineIluminacao();
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

	// Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)
	gluPerspective(angle,fAspect,0.5,500);

	PosicionaObservador();
}

// Função callback chamada para gerenciar eventos de teclas normais (ESC)
void Teclado (unsigned char tecla, int x, int y)
{
	if(tecla==27) // ESC ?
		exit(0);
	if(tecla=='m')
		igual = !igual;
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
	tx = tx + passo;
                
	// Inverte a direção da translação 
	if(tx > 40 || tx < -40)
		passo = -passo;

	glutPostRedisplay();
	glutTimerFunc(120,Anima, 1);
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
#define SENS_OBS	15.0
#define SENS_TRANSL	20.0
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
    
	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);  
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);
    // Habilita o stencil buffer
    glEnable(GL_STENCIL_TEST);

	// Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_SMOOTH);
     
	// Inicializa a variável que especifica o ângulo da projeção
	// perspectiva
	angle=45;
    
	// Inicializa as variáveis 
	rotX = 0;
	rotY = 0;
	obsZ = 150;    
}

// Programa Principal 
int main(void)
{
	// Define o modo de operação da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL); 
 
	// Especifica a posição inicial da janela GLUT
	glutInitWindowPosition(5,5); 
    
	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(450,450); 
 
	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Exemplo de utilização do stencil buffer");
 
	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);
  
	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a função callback para tratamento das teclas normais 
	glutKeyboardFunc (Teclado);

	// Registra a função callback para tratamento das teclas especiais
	glutSpecialFunc (TeclasEspeciais);

	// Registra a função callback para eventos de botões do mouse	
	glutMouseFunc(GerenciaMouse);
	 
	// Registra a função callback para eventos de movimento do mouse	
	glutMotionFunc(GerenciaMovim);

	// Registra a função callback que será chamada a cada intervalo de tempo
	glutTimerFunc(120, Anima, 1);
     
	// Chama a função responsável por fazer as inicializações 
	Inicializa();
 
	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();
 
	return 0;
}
