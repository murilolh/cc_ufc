//*****************************************************
//
// Exemplo3DGLSL.cpp
// Um programa OpenGL que abre uma janela GLUT 
// e desenha um torus iluminado por um spot - a ilumina��o
// � calculada por shadersi, gerando uma borda "suave"
//
// Navega��o via bot�es do mouse + movimento:
// - bot�o esquerdo: rotaciona objeto
// - bot�o direito:  aproxima/afasta
// - bot�o do meio:  translada objeto
//
// Teclas Home e End fazem zoom in/zoom out
// Teclas 0, 1 e 2 devem ser usadas para escolher a fonte
// de luz desejada (verde, vermelha ou azul)
// Setas movem fonte de luz em x e y
// PageUp/PageDown movem fonte de luz em z
//
// Marcelo Cohen e Isabel H. Manssour
// Este c�digo acompanha o livro
// "OpenGL - Uma Abordagem Pr�tica e Objetiva" 
// 
//*****************************************************

#include <GL/glew.h>
#include <bibutil.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

// Vari�veis para controles de navega��o
GLfloat angle=60, fAspect;
GLfloat rotX, rotY, rotX_ini, rotY_ini;
GLfloat obsX, obsY, obsZ, obsX_ini, obsY_ini, obsZ_ini;
GLfloat alvoX_ini,alvoY_ini;
int x_ini,y_ini,bot;

// Dimens�es da janela de visualiza��o
int largura, altura;

// Handle para programa GLSL
GLuint prog;

// Handle para vari�vel uniform "interna"
GLint uinterna;

// Posi��o da luz
float posLuz[4] = {0,12,0,1.0};

// Cor difusa da luz
GLfloat luzDifusa[4] = { 1,1,1,1 };

// Cor especular da luz
GLfloat luzEspecular[4] = { 1,1,1,1 };

// Dire��o da luz
float dirLuz[3];

// Alvo do spot (utilizado para calcular a dire��o)
float alvoSpot[3] = {0,0,0};

// True se usando shaders
bool usashaders = true;

// Coeficiente especular inicial
float e = 1;

// Diferen�a angular entre a borda interna e externa do spot (em graus)
float borda = 1;

// Borda externa do spot (em graus)
float cutoff = 20.0;

// Cosseno da borda interna, para ser empregado no fragment shader
float cosborda;

// Fun��o respons�vel pela especifica��o dos par�metros de ilumina�o
void DefineIluminacao (void)
{
	glLightfv(GL_LIGHT0, GL_POSITION, posLuz);
	glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,dirLuz);
	glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,e);
	glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,cutoff);
}

// Fun��o usada para especificar a posi��o do observador virtual
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

// Fun��o usada para especificar o volume de visualiza��o
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de proje��o
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de proje��o
	glLoadIdentity();
	// Especifica a proje��o perspectiva(angulo,aspecto,zMin,zMax)
	gluPerspective(angle,fAspect,0.1,1000);
	glMatrixMode(GL_MODELVIEW);
	PosicionaObservador();
}

// Fun��o callback chamada quando o tamanho da janela � alterado 
void AlteraTamanhoJanela(int w, int h)
{
	// Para previnir uma divis�o por zero
	if ( h == 0 ) h = 1;

	// Especifica as dimens�es da viewport
	glViewport(0, 0, w, h);
	
	// Calcula a corre��o de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	// Armazena dimens�es atuais
	largura = w;
	altura = h;

	EspecificaParametrosVisualizacao();
}

// Fun��o que calcula a dire��o do spot a partir
// do alvo especificado
void CalculaDirSpot(void)
{
	VERT dir;
	// Dire��o � calculada pelo alvo - posi��o do spot
	dir.x = alvoSpot[0] - posLuz[0];
	dir.y = alvoSpot[1] - posLuz[1];
	dir.z = alvoSpot[2] - posLuz[2];
	Normaliza(dir);
	dirLuz[0] = dir.x;
	dirLuz[1] = dir.y;
	dirLuz[2] = dir.z;
}

// Fun��o para desenhar um "ch�o" no ambiente
void DesenhaChao(void)
#define TAM 20
#define D 2
{
	// Flags para determinar a cor de cada quadrado
	bool flagx,flagz;
	// Define a normal apontando para cima
	glTranslatef(0,-0.8,0);
	flagx = false;
	// X varia de -TAM a TAM, de D em D
	for(float x=-TAM;x<TAM;x+=D)
	{
		// Flagx determina a cor inicial
		if(flagx) flagz = false;
		else flagz = true;
		// Z varia de -TAM a TAM, de D em D
		for(float z=-TAM;z<TAM;z+=D)
		{
			// Escolhe cor
			if(flagz) glColor3f(0.4,0.4,0.4);
			else glColor3f(1,1,1);
			// E desenha o quadrado
			glBegin(GL_QUADS);
			glNormal3f(0,1,0);
			glVertex3f(x,0,z);
			glVertex3f(x+D,0,z);
			glVertex3f(x+D,0,z+D);
			glVertex3f(x,0,z+D);
			glEnd();
			// Alterna cor
			flagz=!flagz;
		}
		// A cada coluna, alterna cor inicial
		flagx=!flagx;
	}
	glEnd();
}

// Fun��o callback de redesenho da janela
void Desenha(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	DefineIluminacao();

	glPushMatrix();
	glTranslatef(posLuz[0],posLuz[1],posLuz[2]);
	glDisable(GL_LIGHTING);
	glColor3f(1,0,0);
	glutSolidSphere(0.1,5,5);
	glEnable(GL_LIGHTING);
	glPopMatrix();
 
	if(usashaders)
	{
		// Ativa programa
		glUseProgram(prog);
		// E envia o valor atual da borda
		glUniform1f(uinterna, cosborda);
	}
	// Desenha o ch�o armazenado na display list
	glCallList(1);
	
	// Agora desenha um torus
	glColor3f(1,0.5,0);
	glTranslatef(0,3,0);
	glRotatef(45,0,1,0);
	glutSolidTorus(1,2,20,20);

	glUseProgram(0);

	glPopMatrix();
	glutSwapBuffers();
}

// Fun��o callback chamada para gerenciar eventos de teclas
void Teclado(unsigned char tecla, int x, int y)
{
	switch(tecla)
	{
		case 27:	exit(0);
					break;
		case ' ':	usashaders = !usashaders;
					break;
		case '+':	++e;
					break;
		case '-':	--e;
					break;
		case '.':	if(borda<cutoff) borda+=0.1;
					break;
		case ',':	if(borda>0.1) borda-=0.1;
					break;
	}
	// Calcula o cosseno da borda interna
	cosborda = cos((cutoff-borda)*M_PI/180.0);
	glutPostRedisplay();
}

// Fun��o callback para tratar eventos de teclas especiais
void TeclasEspeciais (int tecla, int x, int y)
{
	switch (tecla)
	{
		case GLUT_KEY_LEFT:			posLuz[0] -=2;
									break;
		case GLUT_KEY_RIGHT:		posLuz[0] +=2;
									break;
		case GLUT_KEY_UP:			posLuz[1] +=2;
									break;
		case GLUT_KEY_DOWN:			posLuz[1] -=2;
									break;
		case GLUT_KEY_PAGE_UP:		posLuz[2] -=2;
									break;
		case GLUT_KEY_PAGE_DOWN:	posLuz[2] +=2;
									break;
		case GLUT_KEY_HOME:			if(angle>=10) angle -=5;
									break;
		case GLUT_KEY_END:			if(angle<=150) angle +=5;
									break;
	}
	PosicionaObservador();
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
		obsZ_ini = obsZ;
		rotX_ini = rotX;
		rotY_ini = rotY;
		alvoX_ini = alvoSpot[0];
		alvoY_ini = alvoSpot[2];
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
		rotY = rotY_ini + deltax/SENS_ROT;
		rotX = rotX_ini + deltay/SENS_ROT;
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
		int deltaroty = y_ini - y;
		int deltarotx = x_ini - x;
		// E modifica alvo do spot
		alvoSpot[0] = alvoX_ini - deltarotx/10.0;
		alvoSpot[2] = alvoY_ini - deltaroty/10.0;
		// Recalcula dire��o a partir do alvo e posi��o
		CalculaDirSpot();
	}
	PosicionaObservador();
	glutPostRedisplay();
}
 
// Fun��o que recebe o nome de um arquivo-texto, carrega
// e retorna um apontador para o conte�do deste
GLchar *CarregaArquivo(char *nome)
{
	FILE *arq;
	char *conteudo = NULL;

	int f,cont;
	f = open(nome, O_RDONLY);
	// Descobre o tamanho do arquivo, indo at� o final
	cont = lseek(f, 0, SEEK_END);
	close(f);

	// Se for poss�vel abrir o arquivo...
	if (nome != NULL)
	{
		// Abre como arquivo-texto
		arq = fopen(nome,"rt");

		// Se conseguiu, l� o conte�do
		if (arq != NULL)
		{
			if (cont > 0)
			{
				// Aloca mem�ria para o conte�do do arquivo
				conteudo = (char *)malloc(sizeof(char) * (cont+1));
				// L� o arquivo
				cont = fread(conteudo,sizeof(char),cont,arq);
				// E marca o final com \0
				conteudo[cont] = '\0';
			}
			fclose(arq);
		}
	}
	// Finalmente, retorna o conte�do
	return conteudo;
}

// Fun��o que recebe o handle de um shader/programa e retorna
// o infolog da �ltima compila��o ou liga��o
void MostraInfoLog(GLuint shader)
{
	int tamanho = 0;	// tamanho do infolog
	int total = 0;		// total de caracteres escritos na string
	char *infolog;		// infolog

	// Obt�m tamanho do infolog
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &tamanho);

	// Se h� algo no infolog...
	if (tamanho > 1)
	{
		// Aloca mem�ria e obt�m o infolog
		infolog = (char *)malloc(tamanho);
		glGetShaderInfoLog(shader, tamanho, &total, infolog);
		// Exibe na tela
		puts(infolog);
		// Finalmente, libera o infolog
		free(infolog);
	}
}

// Fun��o que recebe os nomes de dois arquivos-texto, contendo
// os c�digos-fonte do vertex shader e do fragment shader
GLuint CompilaShaders(char *vertsrc, char *fragsrc)
{
	// Cria os dois shaders
 	GLuint v = glCreateShader(GL_VERTEX_SHADER);
	GLuint f = glCreateShader(GL_FRAGMENT_SHADER);

	// Carrega os arquivos	
	GLchar *vs = CarregaArquivo(vertsrc);
	GLchar *fs = CarregaArquivo(fragsrc);

	// Associa aos apontadores	
	const GLchar *ff = fs;
	const GLchar *vv = vs;

	// Envia os c�digos-fonte para OpenGL
	glShaderSource(v, 1, &vv,NULL);
	glShaderSource(f, 1, &ff,NULL);

	// E libera os mesmos
	free(vs);
	free(fs);

	// Compila o vertex shader e mostra o log da compila��o
	glCompileShader(v);
	MostraInfoLog(v);

	// Verifica se a compila��o teve sucesso
	GLint compilacaoOK;
	glGetShaderiv(v, GL_COMPILE_STATUS, &compilacaoOK);
	if(!compilacaoOK)
	{
		fprintf(stderr, "N�o foi poss�vel compilar o vertex shader %s\n",vertsrc);
		exit(1);
	}

	// Compila o fragment shader e mostra o log da compila��o
	glCompileShader(f);
	MostraInfoLog(f);

	// Verifica se a compila��o teve sucesso
	glGetShaderiv(v, GL_COMPILE_STATUS, &compilacaoOK);
	if(!compilacaoOK)
	{
		fprintf(stderr, "N�o foi poss�vel compilar o vertex shader %s\n",vertsrc);
		exit(1);
	}

	// Cria o programa GLSL
	GLuint prog = glCreateProgram();
	// E associa os shaders a ele
	glAttachShader(prog,f);
	glAttachShader(prog,v);

	// Faz a liga��o dos shaders
	glLinkProgram(prog);
	MostraInfoLog(prog);

	// Verifica se a liga��o teve sucesso
	GLint ligacaoOK;
	glGetShaderiv(prog, GL_LINK_STATUS,
		&ligacaoOK);
	if (!ligacaoOK)
	{
		fprintf(stderr, "N�o foi poss�vel fazer a liga��o dos shaders\n");
		exit(1);
	}

	// Finalmente, retorna o programa
	return prog;
}

// Fun��o respons�vel por inicializar par�metros e vari�veis
void Inicializa()
{
	// Inicializa a GLEW e verifica se houve algum erro
	GLint erro = glewInit();
	if(erro!=GLEW_OK)
	{
		printf("Erro na inicializa��o da GLEW\n");
		exit(1);
	}

	// Verifica se h� suporte para as extens�es GLSL
	if (GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
		puts("GLSL suportada");
	else
	{
		puts("*** Hardware n�o suporta GLSL");
		exit(1);
	}

	// Carrega e compila os shaders
	prog = CompilaShaders("spotlight2.vert","spotlight2.frag");

	// Armazena posi��o da vari�vel "interna"
	uinterna = glGetUniformLocation(prog,"interna");

	// Define a cor de fundo da janela de visualiza��o como branca
	glClearColor(1.0,1.0,1.0,1.0);

	// Habilita a defini��o da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);

	// Ajusta componente especular do material e shininess
	glMaterialfv(GL_FRONT,GL_SPECULAR,luzEspecular);
	glMaterialf (GL_FRONT,GL_SHININESS,100.0);
	
	// Define os par�metros da fonte de luz
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	// Cria uma display list para o ch�o	
	glNewList(1,GL_COMPILE);
	DesenhaChao();
	glEndList();

	// Inicializa o valor de cosborda
	cosborda = cos((cutoff-borda)*M_PI/180.0);

	// Calcula dire��o inicial do spot
	CalculaDirSpot();

	// Inicializa as vari�veis usadas para alterar a posi��o do 
	// observador virtual
	rotX = rotY = 0;
	obsX = obsY = 0;
	obsZ = 10;
}


// Programa Principal 
int main(void)
{
	// Define o modo de opera��o da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
 
	// Especifica a posi��o inicial da janela GLUT
	glutInitWindowPosition(5,5); 

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(450,450); 
 
	// Cria a janela passando como argumento o t�tulo da mesma
	glutCreateWindow("Spotlights usando GLSL");

	// Registra a fun��o callback de redesenho da janela de visualiza��o
	glutDisplayFunc(Desenha);
	
	// Registra a fun��o callback de redimensionamento da janela de visualiza��o
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a fun��o callback para tratamento das teclas normais 
	glutKeyboardFunc(Teclado);

	// Registra a fun��o callback para tratamento das teclas especiais
	glutSpecialFunc (TeclasEspeciais);

	// Registra a fun��o callback para eventos de bot�es do mouse	
	glutMouseFunc(GerenciaMouse);
	 
	// Registra a fun��o callback para eventos de movimento do mouse	
	glutMotionFunc(GerenciaMovim);

	// Chama a fun��o respons�vel por fazer as inicializa��es 
	Inicializa();

	glutMainLoop();
	return 0;
}
