//*****************************************************
//
// Exemplo3DComAnimacao.cpp 
// Um programa OpenGL simples que abre uma janela GLUT 
// e desenha um teapot que gira ao redor do eixo y 
// para exemplificar a geração de motion blur.
//
// Marcelo Cohen e Isabel H. Manssour
// Este código acompanha o livro 
// "OpenGL - Uma Abordagem Prática e Objetiva"
// 
//*****************************************************

#include <stdlib.h>
#include <GL/glut.h>

// Posição inicial da esfera (sx,sy) e posição atual (tx,ty)
float sx=0.0,sy=-15;
float tx=sx, ty=sy;

// Velocidade de deslocamento no eixo x e no eixo y
float dx = 0.2, dy = 0.05;

// Quantidade de quadros a acumular por redesenho
int quadros = 5;

// Indica que é o primeiro redesenho
bool primeiro = true;
// True se animando
bool anima = true;
// True se gerando motion blur
bool blur = true;

// Variáveis para controles de navegação
GLfloat angle, fAspect;
GLfloat rotX, rotY, rotX_ini, rotY_ini;
GLfloat obsX, obsY, obsZ, obsX_ini, obsY_ini, obsZ_ini;
int x_ini,y_ini,bot;

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

// Desenha a esfera na posição atual
void DesenhaCena(void)
{
	glPushMatrix();

	glTranslatef(tx,ty,0);
	glColor3f(1.0f, 0.5f, 0.0f);
	glutSolidSphere(5.0,20,20);
	glPopMatrix();

	// Atualiza posição atual
	tx+=dx;
	ty+=dy;
	// Se "bater" nos lados, inverte o sentido do movimento
	if(tx >= 25 || tx <= -25) dx = -dx;
	if(ty >= 25 || ty < -25) dy = -dy;

	glFlush();
}

// Função callback de redesenho da janela de visualização
#define	Q 0.9
void Desenha(void)
{
	// Motion blur ativo ?
	if(blur)
	{
		// Ajusta posição inicial da esfera
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
			// Faz "fade out" na imagem acumulada até agora
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
		// Atualiza posição inicial como sendo a atual
		sx = tx;
		sy = ty;
	}
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

// Função callback para realizar a animação
void Anima(void)
{
	glutPostRedisplay();
}


// Função callback chamada para gerenciar eventos de teclas
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
		// Ativa/desativa animação
		case 'a': anima = !anima;
				  if(anima)
					glutIdleFunc(Anima);
				  else
					glutIdleFunc(NULL);
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
#define SENS_OBS	10.0
#define SENS_TRANSL	10.0
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

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divisão por zero
	if ( h == 0 ) h = 1;

	// Especifica as dimensões da viewport
	glViewport(0, 0, w, h);
 
	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	// Se o tamanho da janela mudar, é necessário recomeçar o processo
	primeiro = true;

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
   
	// Limpa accum buffer	
	glClear(GL_ACCUM_BUFFER_BIT);

	// Inicializa a variável que especifica o ângulo da projeção
	// perspectiva
	angle=45;
    
	// Inicializa as variáveis usadas para alterar a posição do 
	// observador virtual
	rotX = 0;
	rotY = 0;
	obsX = obsY = 0;
	obsZ = 55;
}

// Programa Principal 
int main(void)
{
	// Define o modo de operação da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_ACCUM); 
 
	// Especifica a posição inicial da janela GLUT
	glutInitWindowPosition(5,5); 
    
	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(450,450); 
 
	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Exemplo de motion blur");
 
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

	// Registra a função callback para quando o sistema estiver ocioso
	glutIdleFunc(Anima);

	// Chama a função responsável por fazer as inicializações 
	Inicializa();
 
	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();
 
	return 0;
}
