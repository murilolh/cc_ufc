//*****************************************************
//
// Exemplo3DComAnimacao.cpp 
// Um programa OpenGL simples que abre uma janela GLUT 
// e desenha um teapot que gira ao redor do eixo y 
// para exemplificar a gera��o de motion blur.
//
// Marcelo Cohen e Isabel H. Manssour
// Este c�digo acompanha o livro 
// "OpenGL - Uma Abordagem Pr�tica e Objetiva"
// 
//*****************************************************

#include <stdlib.h>
#include <GL/glut.h>

// Posi��o inicial da esfera (sx,sy) e posi��o atual (tx,ty)
float sx=0.0,sy=-15;
float tx=sx, ty=sy;

// Velocidade de deslocamento no eixo x e no eixo y
float dx = 0.2, dy = 0.05;

// Quantidade de quadros a acumular por redesenho
int quadros = 5;

// Indica que � o primeiro redesenho
bool primeiro = true;
// True se animando
bool anima = true;
// True se gerando motion blur
bool blur = true;

// Vari�veis para controles de navega��o
GLfloat angle, fAspect;
GLfloat rotX, rotY, rotX_ini, rotY_ini;
GLfloat obsX, obsY, obsZ, obsX_ini, obsY_ini, obsZ_ini;
int x_ini,y_ini,bot;

// Fun��o respons�vel pela especifica��o dos par�metros de ilumina��o
void DefineIluminacao (void)
{
	GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0}; 
	GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0};	   // "cor" 
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho" 
	GLfloat posicaoLuz[4]={0.0, 50.0, 50.0, 1.0};

	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0}; 
	GLint especMaterial = 60;

	// Define a reflet�ncia do material 
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentra��o do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

	// Ativa o uso da luz ambiente 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os par�metros da luz de n�mero 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );   
}

// Desenha a "cerca" ao redor da esfera
#define tamx 30
#define tamy 30
#define tamz 5
void DesenhaLados(void)
{
	glColor3f(0.2,0.8,0.3);

	glBegin(GL_QUADS);
	glNormal3f( 1,0,0);
	glVertex3f(-tamx,-tamy,-tamz);
	glVertex3f(-tamx,-tamy, tamz);
	glVertex3f(-tamx, tamy, tamz);
	glVertex3f(-tamx, tamy,-tamz);

	glNormal3f(-1,0,0);
	glVertex3f( tamx,-tamy,-tamz);
	glVertex3f( tamx,-tamy, tamz);
	glVertex3f( tamx, tamy, tamz);
	glVertex3f( tamx, tamy,-tamz);

	glNormal3f( 0,-1,0);
	glVertex3f(-tamx, tamy,-tamz);
	glVertex3f(-tamx, tamy, tamz);
	glVertex3f( tamx, tamy, tamz);
	glVertex3f( tamx, tamy,-tamz);

	glNormal3f( 0, 1,0);
	glVertex3f(-tamx,-tamy,-tamz);
	glVertex3f(-tamx,-tamy, tamz);
	glVertex3f( tamx,-tamy, tamz);
	glVertex3f( tamx,-tamy,-tamz);

	glEnd();
}

// Desenha a esfera na posi��o atual
void DesenhaCena(void)
{
	glPushMatrix();

	glTranslatef(tx,ty,0);
	glColor3f(1.0f, 0.5f, 0.0f);
	glutSolidSphere(5.0,20,20);
	glPopMatrix();

	// Atualiza posi��o atual
	tx+=dx;
	ty+=dy;
	// Se "bater" nos lados, inverte o sentido do movimento
	if(tx >= 25 || tx <= -25) dx = -dx;
	if(ty >= 25 || ty < -25) dy = -dy;

	glFlush();
}

// Fun��o callback de redesenho da janela de visualiza��o
#define	Q 0.9
void Desenha(void)
{
	// Motion blur ativo ?
	if(blur)
	{
		// Ajusta posi��o inicial da esfera
		tx = sx;
		ty = sy;
		for(int i=0;i<quadros;++i)
		{
			// Limpa a janela
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			// Desenha os lados
			DesenhaLados();
			// Se for o primeiro redesenho
			if(primeiro)
			{
				// Copia tela para accum buffer
				glAccum(GL_LOAD,1.0);
				primeiro = false;
			}
			DesenhaCena();
			// Faz "fade out" na imagem acumulada at� agora
			glAccum(GL_MULT, Q);
			// E acumula imagem corrente
			glAccum(GL_ACCUM, 1-Q);
		}
		// Retorna resultado na tela
		glAccum(GL_RETURN, 1.0);
	}
	else
	{
		// Modo normal
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		DesenhaLados();
		DesenhaCena();
	}

	// Se estiver animando...
	if(anima)
	{
		// Atualiza posi��o inicial como sendo a atual
		sx = tx;
		sy = ty;
	}
	glutSwapBuffers();
}

// Fun��o usada para especificar a posi��o do observador virtual
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

// Fun��o usada para especificar o volume de visualiza��o
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de proje��o
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de proje��o
	glLoadIdentity();

	// Especifica a proje��o perspectiva(angulo,aspecto,zMin,zMax)
	gluPerspective(angle,fAspect,0.5,500);

	PosicionaObservador();
}

// Fun��o callback para realizar a anima��o
void Anima(void)
{
	glutPostRedisplay();
}


// Fun��o callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
	switch(key)
	{
		// Controla total de quadros gerados a cada redesenho
		case '+': quadros--;
				  break;
		case '-': quadros++;
				  break;
		// Ativa/desativa motion blur
		case 'b': blur=!blur;
				  primeiro = true;
				  break;
		// Ativa/desativa anima��o
		case 'a': anima = !anima;
				  if(anima)
					glutIdleFunc(Anima);
				  else
					glutIdleFunc(NULL);
				  break;
	}
	glutPostRedisplay();
}

// Fun��o callback para tratar eventos de teclas especiais
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

// Fun��o callback para eventos de bot�es do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	if(state==GLUT_DOWN)
	{
		// Salva os par�metros atuais
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

// Fun��o callback para eventos de movimento do mouse
#define SENS_ROT	5.0
#define SENS_OBS	10.0
#define SENS_TRANSL	10.0
void GerenciaMovim(int x, int y)
{
	// Bot�o esquerdo ?
	if(bot==GLUT_LEFT_BUTTON)
	{
		// Calcula diferen�as
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		// E modifica �ngulos
		rotY = rotY_ini - deltax/SENS_ROT;
		rotX = rotX_ini - deltay/SENS_ROT;
	}
	// Bot�o direito ?
	else if(bot==GLUT_RIGHT_BUTTON)
	{
		// Calcula diferen�a
		int deltaz = y_ini - y;
		// E modifica dist�ncia do observador
		obsZ = obsZ_ini + deltaz/SENS_OBS;
	}
	// Bot�o do meio ?
	else if(bot==GLUT_MIDDLE_BUTTON)
	{
		// Calcula diferen�as
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		// E modifica posi��es
		obsX = obsX_ini + deltax/SENS_TRANSL;
		obsY = obsY_ini - deltay/SENS_TRANSL;
	}
	PosicionaObservador();
	glutPostRedisplay();
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

	// Se o tamanho da janela mudar, � necess�rio recome�ar o processo
	primeiro = true;

	EspecificaParametrosVisualizacao();
}

// Fun��o respons�vel por inicializar par�metros e vari�veis
void Inicializa (void)
{   
	// Define a cor de fundo da janela de visualiza��o como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
	// Habilita a defini��o da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de ilumina��o
	glEnable(GL_LIGHTING);  
	// Habilita a luz de n�mero 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);

	// Habilita o modelo de coloriza��o de Gouraud
	glShadeModel(GL_SMOOTH);
   
	// Limpa accum buffer	
	glClear(GL_ACCUM_BUFFER_BIT);

	// Inicializa a vari�vel que especifica o �ngulo da proje��o
	// perspectiva
	angle=45;
    
	// Inicializa as vari�veis usadas para alterar a posi��o do 
	// observador virtual
	rotX = 0;
	rotY = 0;
	obsX = obsY = 0;
	obsZ = 55;
}

// Programa Principal 
int main(void)
{
	// Define o modo de opera��o da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_ACCUM); 
 
	// Especifica a posi��o inicial da janela GLUT
	glutInitWindowPosition(5,5); 
    
	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(450,450); 
 
	// Cria a janela passando como argumento o t�tulo da mesma
	glutCreateWindow("Exemplo de motion blur");
 
	// Registra a fun��o callback de redesenho da janela de visualiza��o
	glutDisplayFunc(Desenha);
  
	// Registra a fun��o callback de redimensionamento da janela de visualiza��o
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a fun��o callback para tratamento das teclas normais 
	glutKeyboardFunc (Teclado);

	// Registra a fun��o callback para tratamento das teclas especiais
	glutSpecialFunc (TeclasEspeciais);
     
	// Registra a fun��o callback para eventos de bot�es do mouse	
	glutMouseFunc(GerenciaMouse);
	 
	// Registra a fun��o callback para eventos de movimento do mouse	
	glutMotionFunc(GerenciaMovim);

	// Registra a fun��o callback para quando o sistema estiver ocioso
	glutIdleFunc(Anima);

	// Chama a fun��o respons�vel por fazer as inicializa��es 
	Inicializa();
 
	// Inicia o processamento e aguarda intera��es do usu�rio
	glutMainLoop();
 
	return 0;
}
