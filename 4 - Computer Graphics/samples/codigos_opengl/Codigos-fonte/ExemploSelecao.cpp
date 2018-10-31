//*****************************************************
//
// ExemploSelecao.cpp
// Um programa OpenGL que desenha três objetos e
// permite selecionar qualquer um deles
//
// Marcelo Cohen e Isabel H. Manssour
// Este código acompanha o livro 
// "OpenGL - Uma Abordagem Prática e Objetiva"
// 
//*****************************************************

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

// Variáveis para controles de navegação
GLfloat angle, fAspect;
GLfloat rotX, rotY, rotX_ini, rotY_ini;
GLfloat obsX, obsY, obsZ, obsX_ini, obsY_ini, obsZ_ini;
int x_ini,y_ini,bot;

// Constantes e nomes dos objetos
enum { ESFERA, CUBO, TORUS };
char *objetos[] = { "Esfera", "Cubo", "Torus" };

// Função responsável pela especificação dos parâmetros de iluminação
void DefineIluminacao (void)
{
	GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0}; 
	GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0};	   // "cor" 
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho" 
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

// Processa o vetor de seleção e retorna o nome
// do objeto mais próximo
GLuint ProcessaSelecao(GLint total, GLuint selecao[])
{
	GLuint *ptr;			// apontador para percorrer o vetor
	GLuint menor = 0;		// nome do objeto mais próximo até agora
	float menor_z = 1.0;	// menor distância até agora

	printf("total = %d\n", total);
	// Aponta para início do vetor
	ptr = selecao; 
	for(int i=0; i<total; ++i)
	{	
		// Para cada resultado
		printf("nomes na pilha: %d\n",*ptr++);
		// Converte as distâncias para números reais
		float zmin = (float) *ptr++/0xffffffff;
		float zmax = (float) *ptr++/0xffffffff;
		// Exibe distâncias min e max
		printf("z(min,max): (%f,%f) = ",zmin,zmax);
		// Se esse objeto tiver o menor z, ele é o mais próximo
		if(zmin < menor_z)
		{
			menor = *ptr;
			menor_z = zmin;
		}
		// Exibe o nome do objeto atual
		printf("%s\n",objetos[*ptr]);
		ptr++;
	}
	return menor;
}

// Função para desenhar os objetos que recebe
// true caso esteja no modo de seleção
void DesenhaObjetos(bool sel)
{
	glPushMatrix();

	glColor3f(0.0f, 1.0f, 0.0f);
	// Se no modo de seleção, carrega o nome do torus
	if(sel)
		glLoadName(TORUS);
	glutSolidTorus(0.3,0.6,20,20);
	glTranslatef(0.5,0.5,-1.0);
	glColor3f(1.0f, 0.0f, 0.0f);
	// Se no modo de seleção, carrega o nome da esfera
	if(sel)
		glLoadName(ESFERA);
	glutSolidSphere(0.6,20,20);
	glTranslatef(-1.2,-0.2,2.0);
	glColor3f(1.0f, 1.0f, 0.0f);
	// Se no modo de seleção, carrega o nome do cubo
	if(sel)
		glLoadName(CUBO);
	glutSolidCube(1);

	glPopMatrix();
}

// Função callback de redesenho da janela de visualização
void Desenha(void)
{
	// Limpa a janela de visualização com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DesenhaObjetos(false);

	// Executa os comandos OpenGL
	glutSwapBuffers();
}

#define TAM 100
void GerenciaMouse(int button, int state, int x, int y)
{
	GLuint selecao[TAM];	// vetor de seleção
	GLint total;			// total de registros no vetor
	GLint viewport[4];		// armazena limites da viewport

	bot = -1;
	if(state != GLUT_DOWN) return;

	if (button == GLUT_LEFT_BUTTON) 
	{
		// Informa o vetor de seleção
		glSelectBuffer (TAM, selecao);
		// Ativa o modo de seleção
		glRenderMode(GL_SELECT);

		// Inicializa pilha de nomes
		glInitNames();
		// E empilha um valor qualquer
		glPushName(0);

		// Salva a matriz de projeção atual
		glMatrixMode (GL_PROJECTION);
		glPushMatrix();

		// Obtém viewport atual
		glGetIntegerv (GL_VIEWPORT, viewport);
		// Cria uma região de seleção com 5x5 pixels
		// ao redor do cursor
		glLoadIdentity();
		gluPickMatrix ((GLdouble) x, (GLdouble) (viewport[3] - y), 
			5.0, 5.0, viewport);
		// Aplica projeção atual
		gluPerspective(angle,fAspect,0.5,500);
		// E retorna para modelview
		glMatrixMode(GL_MODELVIEW);
		// Chama a rotina de desenho, mas no modo de seleção
		DesenhaObjetos(true);

		// Restaura matriz de projeção anterior
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		// E finaliza, retornando para modelview
		glMatrixMode(GL_MODELVIEW);
		glFlush();

		// Realiza a seleção e obtém o total de registros
		total = glRenderMode(GL_RENDER);
		// Processa o vetor de seleção e obtém
		// o nome do objeto mais próximo
		int obj = ProcessaSelecao(total, selecao);
		printf("mais próximo: %s\n\n",objetos[obj]);

		glutPostRedisplay();
	}
	else
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
} 

// Função callback para eventos de movimento do mouse
#define SENS_ROT	5.0
#define SENS_OBS	15.0
#define SENS_TRANSL	20.0
void GerenciaMovim(int x, int y)
{
	// Botão do meio ?
	if(bot==GLUT_MIDDLE_BUTTON)
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
	PosicionaObservador();
	glutPostRedisplay();
}

// Função callback chamada para gerenciar eventos de teclas normais (ESC)
void Teclado (unsigned char tecla, int x, int y)
{
	switch(tecla)
	{
			case 27:	exit(0);
						break;
	}
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

	// Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_SMOOTH);
     
	// Inicializa a variável que especifica o ângulo da projeção
	// perspectiva
	angle=45;
    
	// Inicializa as variáveis usadas para alterar a posição do 
	// observador virtual
	rotX = 0;
	rotY = 0;
	obsX = obsY = 0;
	obsZ = 5;    
}

// Programa Principal 
int main(void)
{
	// Define o modo de operação da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
 
	// Especifica a posição inicial da janela GLUT
	glutInitWindowPosition(5,5); 
    
	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(450,450); 
 
	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Exemplo de seleção");
 
	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);
 
	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a função callback para tratamento das teclas normais 
	glutKeyboardFunc (Teclado);

	// Registra a função callback para tratamento das teclas especiais
	glutSpecialFunc (TeclasEspeciais);
    
	// Registra a função callback que gerencia os eventos do mouse   
	glutMouseFunc(GerenciaMouse);

	// Registra a função callback para eventos de movimento do mouse	
	glutMotionFunc(GerenciaMovim);

	// Chama a função responsável por fazer as inicializações 
	Inicializa();
 
	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();
 
	return 0;
}
