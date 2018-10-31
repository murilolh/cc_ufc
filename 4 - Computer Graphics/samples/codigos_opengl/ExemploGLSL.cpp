//*****************************************************
//
// Exemplo3DGLSL.cpp
// Um programa OpenGL que abre uma janela GLUT 
// e desenha um torus iluminado por um spot - a iluminação
// é calculada por shadersi, gerando uma borda "suave"
//
// Navegação via botões do mouse + movimento:
// - botão esquerdo: rotaciona objeto
// - botão direito:  aproxima/afasta
// - botão do meio:  translada objeto
//
// Teclas Home e End fazem zoom in/zoom out
// Teclas 0, 1 e 2 devem ser usadas para escolher a fonte
// de luz desejada (verde, vermelha ou azul)
// Setas movem fonte de luz em x e y
// PageUp/PageDown movem fonte de luz em z
//
// Marcelo Cohen e Isabel H. Manssour
// Este código acompanha o livro
// "OpenGL - Uma Abordagem Prática e Objetiva" 
// 
//*****************************************************

#include <GL/glew.h>
#include <bibutil.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

// Variáveis para controles de navegação
GLfloat angle=60, fAspect;
GLfloat rotX, rotY, rotX_ini, rotY_ini;
GLfloat obsX, obsY, obsZ, obsX_ini, obsY_ini, obsZ_ini;
GLfloat alvoX_ini,alvoY_ini;
int x_ini,y_ini,bot;

// Dimensões da janela de visualização
int largura, altura;

// Handle para programa GLSL
GLuint prog;

// Handle para variável uniform "interna"
GLint uinterna;

// Posição da luz
float posLuz[4] = {0,12,0,1.0};

// Cor difusa da luz
GLfloat luzDifusa[4] = { 1,1,1,1 };

// Cor especular da luz
GLfloat luzEspecular[4] = { 1,1,1,1 };

// Direção da luz
float dirLuz[3];

// Alvo do spot (utilizado para calcular a direção)
float alvoSpot[3] = {0,0,0};

// True se usando shaders
bool usashaders = true;

// Coeficiente especular inicial
float e = 1;

// Diferença angular entre a borda interna e externa do spot (em graus)
float borda = 1;

// Borda externa do spot (em graus)
float cutoff = 20.0;

// Cosseno da borda interna, para ser empregado no fragment shader
float cosborda;

// Função responsável pela especificação dos parâmetros de iluminaç¿o
void DefineIluminacao (void)
{
	glLightfv(GL_LIGHT0, GL_POSITION, posLuz);
	glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,dirLuz);
	glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,e);
	glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,cutoff);
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
	// Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)
	gluPerspective(angle,fAspect,0.1,1000);
	glMatrixMode(GL_MODELVIEW);
	PosicionaObservador();
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(int w, int h)
{
	// Para previnir uma divisão por zero
	if ( h == 0 ) h = 1;

	// Especifica as dimensões da viewport
	glViewport(0, 0, w, h);
	
	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	// Armazena dimensões atuais
	largura = w;
	altura = h;

	EspecificaParametrosVisualizacao();
}

// Função que calcula a direção do spot a partir
// do alvo especificado
void CalculaDirSpot(void)
{
	VERT dir;
	// Direção é calculada pelo alvo - posição do spot
	dir.x = alvoSpot[0] - posLuz[0];
	dir.y = alvoSpot[1] - posLuz[1];
	dir.z = alvoSpot[2] - posLuz[2];
	Normaliza(dir);
	dirLuz[0] = dir.x;
	dirLuz[1] = dir.y;
	dirLuz[2] = dir.z;
}

// Função para desenhar um "chão" no ambiente
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

// Função callback de redesenho da janela
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
	// Desenha o chão armazenado na display list
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

// Função callback chamada para gerenciar eventos de teclas
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

// Função callback para tratar eventos de teclas especiais
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

// Função callback para eventos de botões do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	if(state==GLUT_DOWN)
	{
		// Salva os parâmetros atuais			
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
		rotY = rotY_ini + deltax/SENS_ROT;
		rotX = rotX_ini + deltay/SENS_ROT;
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
		int deltaroty = y_ini - y;
		int deltarotx = x_ini - x;
		// E modifica alvo do spot
		alvoSpot[0] = alvoX_ini - deltarotx/10.0;
		alvoSpot[2] = alvoY_ini - deltaroty/10.0;
		// Recalcula direção a partir do alvo e posição
		CalculaDirSpot();
	}
	PosicionaObservador();
	glutPostRedisplay();
}
 
// Função que recebe o nome de um arquivo-texto, carrega
// e retorna um apontador para o conteúdo deste
GLchar *CarregaArquivo(char *nome)
{
	FILE *arq;
	char *conteudo = NULL;

	int f,cont;
	f = open(nome, O_RDONLY);
	// Descobre o tamanho do arquivo, indo até o final
	cont = lseek(f, 0, SEEK_END);
	close(f);

	// Se for possível abrir o arquivo...
	if (nome != NULL)
	{
		// Abre como arquivo-texto
		arq = fopen(nome,"rt");

		// Se conseguiu, lê o conteúdo
		if (arq != NULL)
		{
			if (cont > 0)
			{
				// Aloca memória para o conteúdo do arquivo
				conteudo = (char *)malloc(sizeof(char) * (cont+1));
				// Lê o arquivo
				cont = fread(conteudo,sizeof(char),cont,arq);
				// E marca o final com \0
				conteudo[cont] = '\0';
			}
			fclose(arq);
		}
	}
	// Finalmente, retorna o conteúdo
	return conteudo;
}

// Função que recebe o handle de um shader/programa e retorna
// o infolog da última compilação ou ligação
void MostraInfoLog(GLuint shader)
{
	int tamanho = 0;	// tamanho do infolog
	int total = 0;		// total de caracteres escritos na string
	char *infolog;		// infolog

	// Obtém tamanho do infolog
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &tamanho);

	// Se há algo no infolog...
	if (tamanho > 1)
	{
		// Aloca memória e obtém o infolog
		infolog = (char *)malloc(tamanho);
		glGetShaderInfoLog(shader, tamanho, &total, infolog);
		// Exibe na tela
		puts(infolog);
		// Finalmente, libera o infolog
		free(infolog);
	}
}

// Função que recebe os nomes de dois arquivos-texto, contendo
// os códigos-fonte do vertex shader e do fragment shader
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

	// Envia os códigos-fonte para OpenGL
	glShaderSource(v, 1, &vv,NULL);
	glShaderSource(f, 1, &ff,NULL);

	// E libera os mesmos
	free(vs);
	free(fs);

	// Compila o vertex shader e mostra o log da compilação
	glCompileShader(v);
	MostraInfoLog(v);

	// Verifica se a compilação teve sucesso
	GLint compilacaoOK;
	glGetShaderiv(v, GL_COMPILE_STATUS, &compilacaoOK);
	if(!compilacaoOK)
	{
		fprintf(stderr, "Não foi possível compilar o vertex shader %s\n",vertsrc);
		exit(1);
	}

	// Compila o fragment shader e mostra o log da compilação
	glCompileShader(f);
	MostraInfoLog(f);

	// Verifica se a compilação teve sucesso
	glGetShaderiv(v, GL_COMPILE_STATUS, &compilacaoOK);
	if(!compilacaoOK)
	{
		fprintf(stderr, "Não foi possível compilar o vertex shader %s\n",vertsrc);
		exit(1);
	}

	// Cria o programa GLSL
	GLuint prog = glCreateProgram();
	// E associa os shaders a ele
	glAttachShader(prog,f);
	glAttachShader(prog,v);

	// Faz a ligação dos shaders
	glLinkProgram(prog);
	MostraInfoLog(prog);

	// Verifica se a ligação teve sucesso
	GLint ligacaoOK;
	glGetShaderiv(prog, GL_LINK_STATUS,
		&ligacaoOK);
	if (!ligacaoOK)
	{
		fprintf(stderr, "Não foi possível fazer a ligação dos shaders\n");
		exit(1);
	}

	// Finalmente, retorna o programa
	return prog;
}

// Função responsável por inicializar parâmetros e variáveis
void Inicializa()
{
	// Inicializa a GLEW e verifica se houve algum erro
	GLint erro = glewInit();
	if(erro!=GLEW_OK)
	{
		printf("Erro na inicialização da GLEW\n");
		exit(1);
	}

	// Verifica se há suporte para as extensões GLSL
	if (GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
		puts("GLSL suportada");
	else
	{
		puts("*** Hardware não suporta GLSL");
		exit(1);
	}

	// Carrega e compila os shaders
	prog = CompilaShaders("spotlight2.vert","spotlight2.frag");

	// Armazena posição da variável "interna"
	uinterna = glGetUniformLocation(prog,"interna");

	// Define a cor de fundo da janela de visualização como branca
	glClearColor(1.0,1.0,1.0,1.0);

	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);

	// Ajusta componente especular do material e shininess
	glMaterialfv(GL_FRONT,GL_SPECULAR,luzEspecular);
	glMaterialf (GL_FRONT,GL_SHININESS,100.0);
	
	// Define os parâmetros da fonte de luz
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	// Cria uma display list para o chão	
	glNewList(1,GL_COMPILE);
	DesenhaChao();
	glEndList();

	// Inicializa o valor de cosborda
	cosborda = cos((cutoff-borda)*M_PI/180.0);

	// Calcula direção inicial do spot
	CalculaDirSpot();

	// Inicializa as variáveis usadas para alterar a posição do 
	// observador virtual
	rotX = rotY = 0;
	obsX = obsY = 0;
	obsZ = 10;
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
	glutCreateWindow("Spotlights usando GLSL");

	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);
	
	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a função callback para tratamento das teclas normais 
	glutKeyboardFunc(Teclado);

	// Registra a função callback para tratamento das teclas especiais
	glutSpecialFunc (TeclasEspeciais);

	// Registra a função callback para eventos de botões do mouse	
	glutMouseFunc(GerenciaMouse);
	 
	// Registra a função callback para eventos de movimento do mouse	
	glutMotionFunc(GerenciaMovim);

	// Chama a função responsável por fazer as inicializações 
	Inicializa();

	glutMainLoop();
	return 0;
}
