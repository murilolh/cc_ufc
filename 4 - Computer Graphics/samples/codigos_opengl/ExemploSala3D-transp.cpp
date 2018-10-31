//*****************************************************
//
// ExemploSala3D-transp.cpp
// Um programa OpenGL que desenha uma sala de aula
// completa, utilizando iluminação, materiais e transparência
//
// Navegação via botões do mouse + movimento:
// (com a tecla SHIFT pressionada, o movimento é mais lento)
// - botão esquerdo: rotaciona observador
// - botão direito:  eleva/desce o observador
//
// Teclas Home e End fazem zoom in/zoom out
// a,z - avança/recua observador
// seta esquerda/seta direita - anda para os lados
//
// Controles de Iluminação/Rendering em geral:
// 1,2,3 - acende/apaga conjunto de luzes no teto (frente, meio, fundos)
// 4 - acende/apaga luz externa ("Sol")
// 5 - acende/apaga luz do observador
// n - ativa/desativa a neblina
// t - chaveia entre os modos de desenho: wireframe/sólidos
// 
// Marcelo Cohen e Isabel H. Manssour
// Este código acompanha o livro 
// "OpenGL - Uma Abordagem Prática e Objetiva"
// 
//*****************************************************

#include <GL/glut.h>
#include <math.h>
#include "bibutil.h"
#include <vector>

// Posição Z da fila de mesas no fundo
#define Z_INI	-320

// Posição X da primeira columa de mesas
#define X_INI	-220

using namespace std;

// Variáveis para controle da projeção
GLfloat fAspect;
GLfloat ang_cam = 60;

// Objetos
OBJ *plano, *mesa, *mesapeq, *cadeira,
	*quadro, *porta, *janela, *lamp, *vidro;

// Apontador para material da fonte de luz
MAT *mat_luz;

// Tipos possíveis para objetos sobre as mesas
OBJ *tipos[7];

// Estrutura para definir um objeto genérico
// na cena (i.e. objetos sobre as mesas)
typedef struct
{
	OBJ *objeto;
	float transl[3];
	float rot[4];
	int mesa; 	// identifica a mesa onde o objeto está
} OBJETO;

// Define um vetor de objetos
vector<OBJETO *> objetos(0);

// Define os limites de uma mesa
typedef struct
{
	float x,z;		// centro da mesa
	float y;		// altura para os objetos
} MESA;

MESA limites[37];	// 36 mesas + professor

// Luminosidade base de uma lâmpada
#define LOW	0.3

// Define parâmetros de iluminação
// Luz 1: puntual no teto, frente
GLfloat luzAmb1[4] = { 0.1, 0.1, 0.1, 1 };	// luz ambiente
GLfloat luzDif1[4] = { LOW, LOW, LOW, 1.0 };	// luz difusa
GLfloat luzEsp1[4] = { 0.0, 0.0, 0.0, 1.0 };	// luz especular
GLfloat posLuz1[4] = { 0, 200, 250, 1 };	// posição da fonte de luz
// Luz 2: puntual no teto, meio da sala 
GLfloat luzDif2[4] = { LOW, LOW, LOW, 1.0 };	// luz difusa
GLfloat posLuz2[4] = { 0, 200, 0, 1 };	// posição da fonte de luz
// Luz 3: puntual no teto, atrás
GLfloat luzDif3[4] = { LOW, LOW, LOW, 1.0 };	// luz difusa
GLfloat posLuz3[4] = { 0, 200, -250, 1 };	// posição da fonte de luz
// Luz 4: direcional, simulando o Sol 
GLfloat luzDif4[4] = { 0.4, 0.2, 0.0, 1.0 };	// luz difusa
GLfloat posLuz4[4] = { 1, 0.2, 0, 0 };		// direção da fonte de luz
// Luz 5: spot, na posição da câmera, apontando para a frente
GLfloat luzDif5[4] = { LOW*2, LOW*2, LOW*2, 1.0 };	// luz difusa
GLfloat posLuz5[4] = { 0, 0, 0, 1.0 };		// pos em relação à câmera
GLfloat dirLuz5[4] = { 0, 0, -1, 0.0 };		// aponta para a frente

bool luzes[5] = {true, true, true, true, false};

// Define variáveis para navegação
GLfloat rotX=0, rotY=0, rotX_ini, rotY_ini;
GLfloat obsX=0, obsY=150, obsZ=100, obsY_ini;
int x_ini,y_ini,bot;

// Define modo de desenho inicial: sólido
char modo_des = 's';

// Arquivo de cena e arquivo de câmera
char arqcena[20];
char arqcam[20];

// Desenha os vidros de uma janela, centralizados na posição
// especificada (x,y,z) e com o deslocamento informado
// de abertura (a)
void DesenhaVidros(float x, float y, float z, float a)
{
	// Adicionamos 25, pois é o deslocamento mínimo
	// em relação ao centro
	a+=25;
	glPushMatrix();
	glTranslatef(x,y,z);
	glRotatef(-90,0,1,0);
	// Vidros de trás
	glTranslatef(-a,0,0);
	DesenhaObjeto(vidro);
	glTranslatef(a*2,0,0);
	DesenhaObjeto(vidro);
	// Vidros da frente
	glTranslatef(75-a,0,3);
	DesenhaObjeto(vidro);
	glTranslatef(-150,0,0);
	DesenhaObjeto(vidro);
	glPopMatrix();
}

// Desenha 4 paredes
void DesenhaParedes(void)
{
	// Desenha a porta
	glPushMatrix();
	glTranslatef(-301,100,300);
	glRotatef(90,0,1,0);
	DesenhaObjeto(porta);
	glPopMatrix();

	/**********************************
	***          Paredes            ***
	**********************************/

	// Seta cor da parede
	glColor3ub(196,210,184);
	// Parede dos fundos
	glPushMatrix();
	glTranslatef(0,150,-400);
	glScalef(6,3,1);
	DesenhaObjeto(plano);
	glPopMatrix();

	// Parede da frente
	glPushMatrix();
	glTranslatef(0,150,400);
	glRotatef(180,0,1,0);
	glScalef(6,3,1);
	DesenhaObjeto(plano);
	glPopMatrix();

	// Parede esquerda
	glPushMatrix();
	glTranslatef(-300,150,0);
	glRotatef(90,0,1,0);
	glScalef(8,3,1);
	DesenhaObjeto(plano);
	glPopMatrix();

	//
	// Parede direita
	// 

	// Parte inferior
	glPushMatrix();
	glTranslatef(300,37.5,0);
	glRotatef(-90,0,1,0);
	glScalef(8,0.75,1);	// 8 m x 75 cm
	DesenhaObjeto(plano);
	glPopMatrix();

	// Parte superior
	glPushMatrix();
	glTranslatef(300,300-37.5,0);
	glRotatef(-90,0,1,0);
	glScalef(8,0.75,1);
	DesenhaObjeto(plano);
	glPopMatrix();

	//
	// Parte do meio
	// 

	// fundos
	glPushMatrix();
	glTranslatef(300,150,-375);
	glRotatef(-90,0,1,0);
	glScalef(0.5,1.5,1);
	DesenhaObjeto(plano);
	glPopMatrix();

	// antes do meio
	glPushMatrix();
	glTranslatef(300,150,-125);
	glRotatef(-90,0,1,0);
	glScalef(0.5,1.5,1);
	DesenhaObjeto(plano);
	glPopMatrix();

	// depois do meio
	glPushMatrix();
	glTranslatef(300,150,125);
	glRotatef(-90,0,1,0);
	glScalef(0.5,1.5,1);
	DesenhaObjeto(plano);
	glPopMatrix();

	// frente
	glPushMatrix();
	glTranslatef(300,150,375);
	glRotatef(-90,0,1,0);
	glScalef(0.5,1.5,1);
	DesenhaObjeto(plano);
	glPopMatrix();

	/**********************************
	***          Janelas            ***
	**********************************/

	// Janela dos fundos
	glPushMatrix();
	glTranslatef(300,150,-250);
	glRotatef(-90,0,1,0);
	DesenhaObjeto(janela);
	glPopMatrix();

	// Janela do meio
	glPushMatrix();
	glTranslatef(300,150,0);
	glRotatef(-90,0,1,0);
	DesenhaObjeto(janela);
	glPopMatrix();

	// Janela da frente
	glPushMatrix();
	glTranslatef(300,150,250);
	glRotatef(-90,0,1,0);
	DesenhaObjeto(janela);
	glPopMatrix();

	//
	// Lâmpadas
	//

	// 3 colunas de lâmpadas
	for(int x=-150;x<=300;x+=300)
	{
		int cont = 0;
		// 3 filas de lâmpadas
		for(int z=-250;z<=300;z+=250,cont++)
		{
			float emissao = 0.0;
			// Seta o coeficiente de emissão para
			// as luzes que estiverem ativas
			if(luzes[2-cont]) emissao = 1.0;
			mat_luz->ke[0] = mat_luz->ke[1] = mat_luz->ke[2] = emissao;
			glPushMatrix();
			glTranslatef(x,297,z);
			glRotatef(90,1,0,0);
			glRotatef(90,0,0,1);
			DesenhaObjeto(lamp);
			glPopMatrix();
		}
	}
}

// Desenha o chão
void DesenhaChao(void)
{
	glColor3ub(145,105,54);
	glPushMatrix();
	glTranslatef(0,0,0);
	glRotatef(-90,1,0,0);
	glScalef(6,8,1);
	DesenhaObjeto(plano);
	glPopMatrix();
}

// Desenha o teto
void DesenhaTeto(void)
{
	glColor3ub(212,199,183);
	glPushMatrix();
	glTranslatef(0,300,0);
	glRotatef(90,1,0,0);
	glScalef(6,8,1);
	DesenhaObjeto(plano);
	glPopMatrix();
}

// Desenha a mesa
void DesenhaMesa(void)
{
   	glPushMatrix();

	// Posiciona a mesa
	glTranslatef(limites[36].x,limites[36].y-12,limites[36].z);
	DesenhaObjeto(mesa);

	// Posiciona e orienta a cadeira
	glTranslatef(0,-15,30);
	glRotatef(180,0,1,0);
	DesenhaObjeto(cadeira);

	glPopMatrix();
}

// Desenha as mesas dos alunos
void DesenhaMesas(void)
{
	int i;
	// Desenha todas as mesas, exceto a do professor
	for(i=0;i<36;++i)
	{
		glPushMatrix();
		// Posiciona uma mesa
		glTranslatef(limites[i].x,limites[i].y-10,limites[i].z);
		DesenhaObjeto(mesapeq);
		// Posiciona a cadeira em relação à mesa
		glTranslatef(0,-10,-30);
		DesenhaObjeto(cadeira);
		glPopMatrix();
	}
}

// Desenha os objetos sobre todas as mesas
void DesenhaObjetos()
{
	int i;
	// Varre o array de objetos
	for(i=0;i<objetos.size();++i)
	{
		glPushMatrix();
		// Obtém a mesa associada ao objeto
		MESA mesa = limites[objetos[i]->mesa];
		// Usa o centro da mesa como origem para desenhar o objeto
		glTranslatef(mesa.x,mesa.y,mesa.z);
		// Acumula translação e rotação do próprio objeto
		glTranslatef(objetos[i]->transl[0],objetos[i]->transl[1],objetos[i]->transl[2]);
		glRotatef(objetos[i]->rot[0],objetos[i]->rot[1],objetos[i]->rot[2],objetos[i]->rot[3]);
		DesenhaObjeto(objetos[i]->objeto);
		glPopMatrix();
	}
}

// Desenha o quadro-negro
void DesenhaQuadro()
{
	glPushMatrix();
	// Posiciona, orienta e desenha o quadro
	glTranslatef(0,160,398);
	glRotatef(180,0,1,0);
	DesenhaObjeto(quadro);
	glPopMatrix();
}

// Desenha o "céu"
void DesenhaCeu()
{
	// Somente no modo de desenho sólido
	if(modo_des=='s')
	{
		// Desenha um plano com gradiente,
		// para simular o céu
		glDisable(GL_LIGHTING);
		glBegin(GL_QUAD_STRIP);
		glColor3ub(239,235,55); // horizonte
		glVertex3f(310,70,-500);
		glVertex3f(310,70, 500);
		glColor3ub(255,136,0);
		glVertex3f(310,85,-500);
		glVertex3f(310,85,500);
		glColor3ub(170,11,61);
		glVertex3f(310,100,-500);
		glVertex3f(310,100,500);
		glColor3ub(28,17,145);
		glVertex3f(310,150,-500);
		glVertex3f(310,150,500);
		glColor3ub(0,0,0);
		glVertex3f(310,250,-500);
		glVertex3f(310,250,500);
		glEnd();
		glEnable(GL_LIGHTING);
	}
}

// Desenha toda a cena
void Desenha(void)
{
	// Limpa a janela de visualização com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// A partir deste ponto, deve-se posicionar
	// as fontes de luz, observador e desenhar
	// todos os objetos

	// Fonte de luz 5 vai estar sempre na posição
	// do observador, olhando para z=-1, ou seja,
	// para a frente
	glLightfv( GL_LIGHT4, GL_POSITION, posLuz5);
	glLightfv( GL_LIGHT4, GL_SPOT_DIRECTION, dirLuz5);

	// Posiciona e orienta observador
	glRotatef(rotX,1,0,0);
	glRotatef(rotY,0,1,0);
	glTranslatef(-obsX,-obsY,-obsZ);

	// Desenha toda a cena

	glColor3f(1,1,1);   // branco

	// Agora posiciona demais fontes de luz
	glLightfv( GL_LIGHT0, GL_POSITION, posLuz1 ); 
	glLightfv( GL_LIGHT1, GL_POSITION, posLuz2 ); 
	glLightfv( GL_LIGHT2, GL_POSITION, posLuz3 ); 
	glLightfv( GL_LIGHT3, GL_POSITION, posLuz4 ); 

	// E desenha todos os elementos da cena
	DesenhaCeu();
	DesenhaParedes();
	DesenhaQuadro();
	DesenhaChao();
	DesenhaTeto();
	DesenhaMesa();
	DesenhaMesas();
	DesenhaObjetos();

	// Desabilitamos alterações no Z-Buffer
	// e habilitamos "blending" para
	// desenhar os vidros

	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);

	// Vidros da janela dos fundos...
	DesenhaVidros(303,150,-250,10);

	// Vidros da janela do meio...
	DesenhaVidros(303,150,0,30);

	// Vidros da janela da frente
	DesenhaVidros(303,150,250,7);

	// Restauramos o estado anterior	
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);

	glutSwapBuffers();
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
	gluPerspective(ang_cam,fAspect,0.1,1000);

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

// Liga/desliga luzes de acordo com o estado
void SetaLuzes()
{
	for(int luz=0;luz<5;++luz)
	{
		if(luzes[luz]) glEnable(GL_LIGHT0+luz);
		else glDisable(GL_LIGHT0+luz);
	}
}

// Limpa o vetor de objetos
void LiberaObjetos()
{
	objetos.clear();
}

// Recupera objetos salvos num arquivo texto
void RestauraObjetos()
{
	float t[3];
	float r[4];
	OBJETO *ptr;
	int tipo,mesa;
	FILE *arq;

	LiberaObjetos();

	puts("Carregando cena...");
	if ((arq = fopen(arqcena,"r"))==NULL)
	{
		perror("ExemploSala3D");
		exit(1);
	}
	while(!feof(arq))
	{
		fscanf(arq,"%d %f %f %f %f %f %f %f %d\n",
			&tipo,&t[0],&t[1],&t[2],
			&r[0],&r[1],&r[2],&r[3],&mesa);
		ptr = (OBJETO *) malloc(sizeof(OBJETO));
		objetos.push_back(ptr);
		ptr->transl[0] = t[0];
		ptr->transl[1] = t[1];
		ptr->transl[2] = t[2];
		ptr->rot[0] = r[0];
		ptr->rot[1] = r[1];
		ptr->rot[2] = r[2];
		ptr->rot[3] = r[3];
		ptr->objeto = tipos[tipo];
		ptr->mesa = mesa;
	}
	fclose(arq);
	puts("*** Cena restaurada");
}

// Salva posição e orientação da câmera,
// e estado das 5 fontes de luz
void SalvaCamera()
{
	FILE *arq;
	arq = fopen(arqcam,"w");
	fprintf(arq,"%f %f %f %f %f %f\n",ang_cam,obsX,obsY,obsZ,rotX,rotY);
	fprintf(arq,"%d %d %d %d %d\n",luzes[0],luzes[1],luzes[2],luzes[3],luzes[4]);
	puts("Camera salva");
	fclose(arq);
}

// Restaura posição e orientação da câmera,
// e estado das 5 fontes de luz
void RestauraCamera()
{
	FILE *arq;
	if((arq = fopen(arqcam,"r"))==NULL)
	{
		perror("ExemploSala3D");
		exit(1);
	}
	fscanf(arq,"%f %f %f %f %f %f",&ang_cam,&obsX,&obsY,&obsZ,&rotX,&rotY);
	fscanf(arq,"%d %d %d %d %d",&luzes[0],&luzes[1],&luzes[2],&luzes[3],&luzes[4]);
	puts("Camera restaurada");
	EspecificaParametrosVisualizacao();
	SetaLuzes();
	fclose(arq);
}

// Função callback para eventos de teclado
void Teclado(unsigned char key, int x, int y)
{
	float sina,cosa;

	// Pré-calcula o seno e cosseno do ângulo horizontal
	// (multiplicado por um fator de 5)
	sina = 5*sin(rotY*M_PI/180.0);
	cosa = 5*cos(rotY*M_PI/180.0);

	// Trata as diversas teclas
	switch(key)
	{
		// Avança / avança devagar
		case 'a':	obsX = obsX + sina;
					obsZ = obsZ - cosa;
					break;
		case 'A':	obsX = obsX + 0.2*sina;
					obsZ = obsZ - 0.2*cosa;
					break;
		// Recua / recua devagar
		case 'z':	obsX = obsX - sina;
					obsZ = obsZ + cosa;
					break;
		case 'Z':	obsX = obsX - 0.2*sina;
					obsZ = obsZ + 0.2*cosa;
					break;
		// Alterna entre os modos de desenho sólido e wireframe
		case 't':	if(modo_des == 's') modo_des = 'w';
					else modo_des = 's';
					SetaModoDesenho(modo_des);
					break;
		// Ativa / desativa neblina
		case 'n':	if(glIsEnabled(GL_FOG))
							glDisable(GL_FOG);
					else
							glEnable(GL_FOG);
					break;
		// Habilita/desabilita fontes de luz
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':	luzes[key-'1'] = !luzes[key-'1'];
					SetaLuzes();
					break;
		// Sai do programa
		case 27:	// Libera todos os objetos carregados...
					LiberaObjeto(NULL);
					// e materiais
					LiberaMateriais();
					exit(1);
				break;
	}
	glutPostRedisplay();
}

// Função callback para eventos de teclas especiais
void TecladoEspecial(int key, int x, int y)
{
	float sina,cosa;

	// Deslocamento lateral normal
	float delta = 2.0;

	bool shift = glutGetModifiers()&GLUT_ACTIVE_SHIFT;

	// Se a tecla shift estiver pressionada,
	// o deslocamento lateral será menor
	if(shift) delta = 0.4;

	// Pré-calcula o seno e cosseno do ângulo
	// de direção atual + 90 graus, ou seja,
	// a direção para deslocamento lateral
	sina = delta*sin((rotY+90)*M_PI/180.0);
	cosa = delta*cos((rotY+90)*M_PI/180.0);

	// Trata as teclas especiais
	switch(key)
	{
		// Controles de deslocamento lateral
		case GLUT_KEY_LEFT:		obsX = obsX - sina;
								obsZ = obsZ + cosa;
								break;
		case GLUT_KEY_RIGHT:	obsX = obsX + sina;
								obsZ = obsZ - cosa;
								break;
		// Controles de zoom in /out
		case GLUT_KEY_HOME:		if(ang_cam++ > 150) ang_cam = 150;
								EspecificaParametrosVisualizacao();
								break;
		case GLUT_KEY_END:		if(ang_cam-- < 5) ang_cam = 5;
								EspecificaParametrosVisualizacao();
								break;
		// Controles para salvar / restaurar câmera
		case GLUT_KEY_F11:		SalvaCamera();
								break;
		case GLUT_KEY_F12:		RestauraCamera();
								break;
	}
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
		obsY_ini = obsY;
		rotX_ini = rotX;
		rotY_ini = rotY;
		bot = button;
	}
	else bot = -1;
}

// Função callback para eventos de movimento do mouse
#define SENS_ROT	5.0
#define SENS_OBS	10.0
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
		int deltay = y_ini - y;
		// E modifica altura do observador
		obsY = obsY_ini + deltay/SENS_OBS;
	}
	glutPostRedisplay();
}


// Define limites de cada mesa e preenche
// o vetor
void DefineLimitesMesas()
{
	int l,c,pos;
	float x,z;
	z = Z_INI;
	// Pos indica em qual mesa estamos
	pos = 0;
	// 6 filas
	for(l=0;l<=5;++l)
	{
		x = X_INI;
		// 3 colunas, 2 mesas em cada
		for(c=0;c<3;++c)
		{
			// X e Z contêm as coordenadas do CENTRO
			// da mesa
			limites[pos].x = x;
			limites[pos].z = z;	
			limites[pos].y = 57;
			pos++;
			
			// Para a segunda mesa, soma 61 cm em x
			x = x + 61;
			limites[pos].x = x;
			limites[pos].z = z;	
			limites[pos].y = 57;
			pos++;
			// Para a próxima coluna, soma 120 cm
			x = x+120;
		}
		z = z+95;
	}
	// Define centro da mesa do professor
	limites[pos].x = 200;
	limites[pos].z = 300;	
	limites[pos].y = 70;
	printf("Total de mesas: %d\n",pos);
}

// Função responsável por inicializar parâmetros e variáveis
void Inicializa (void)
{   
	// Define a cor de fundo da janela de visualização como preto
	glClearColor(0,0,0,1);

	// Ajusta iluminação
	glLightfv( GL_LIGHT0, GL_AMBIENT,  luzAmb1 ); 
	glLightfv( GL_LIGHT0, GL_DIFFUSE,  luzDif1 );
	glLightfv( GL_LIGHT0, GL_SPECULAR, luzEsp1 );
	glLightfv( GL_LIGHT1, GL_AMBIENT,  luzAmb1 ); 
	glLightfv( GL_LIGHT1, GL_DIFFUSE,  luzDif2 );
	glLightfv( GL_LIGHT2, GL_AMBIENT,  luzAmb1 ); 
	glLightfv( GL_LIGHT2, GL_DIFFUSE,  luzDif3 );
	glLightfv( GL_LIGHT3, GL_AMBIENT,  luzAmb1 ); 
	glLightfv( GL_LIGHT3, GL_DIFFUSE,  luzDif4 );
	glLightfv( GL_LIGHT4, GL_AMBIENT,  luzAmb1 );
	glLightfv( GL_LIGHT4, GL_DIFFUSE,  luzDif5 );

	// Habilita todas as fontes de luz
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT4);
	glEnable(GL_LIGHTING);

	// Define coeficientes ambiente e difuso
	// do material
	GLfloat matAmb[4] = { 0.2,0.2,0.2,1 };
	GLfloat matDif[4] = { 1,1,1,1 };

	// Material
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,matAmb);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,matDif);

	// Seleciona o modo de GL_COLOR_MATERIAL
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	// Seta modo de blending
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	// Habilita normalização automática
	glEnable(GL_NORMALIZE);

	// Habilita Z-Buffer
	glEnable(GL_DEPTH_TEST);

	// Cor da neblina
	GLfloat cor_neblina[4] = {0.4, 0.4, 0.4, 1};

	// Parâmetros da neblina
	glFogi(GL_FOG_MODE, GL_EXP2);
	glFogfv(GL_FOG_COLOR, cor_neblina);
	glFogf(GL_FOG_DENSITY, 0.0035);

	// Carrega objetos
	plano = CarregaObjeto("parede.obj",false);
	mesa = CarregaObjeto("mesagrande.obj",false);
	mesapeq = CarregaObjeto("mesapeq.obj",false);
	cadeira = CarregaObjeto("cadeira2.obj",false);
	quadro = CarregaObjeto("quadronegro.obj",false);
	porta = CarregaObjeto("porta.obj",false);
	janela = CarregaObjeto("janela.obj",false);
	vidro = CarregaObjeto("vidro.obj",true);
	lamp = CarregaObjeto("lampada.obj",false);

	// Carrega objetos que podem estar sobre as mesas
	tipos[0] = CarregaObjeto("lapis.obj",false);
	tipos[1] = CarregaObjeto("livro.obj",false);
	tipos[2] = CarregaObjeto("papel1.obj",false);
	tipos[3] = CarregaObjeto("papel2.obj",false);
	tipos[4] = CarregaObjeto("papel3.obj",false);
	tipos[5] = CarregaObjeto("cuiabomba.obj",false);
	tipos[6] = CarregaObjeto("borracha.obj",false);

	// Preenche o array com o centro de cada mesa
	DefineLimitesMesas();

	// Recupera apontador para o material das lâmpadas
	// (usado durante o desenho, para "ligar" e "desligar")
	mat_luz = ProcuraMaterial("Luz");

	// Carrega cena salva
	RestauraObjetos();
	RestauraCamera();

	// Seta o modo de desenho inicial
	SetaModoDesenho(modo_des);
}

// Programa Principal 
int main(int argc, char **argv)
{
	// Verifica se há parâmetros suficientes
	if(argc<3)
	{
		// Não, informa que serão utilizados os nomes padrão
		printf("Usando arquivos padrão: sala3d.txt e camera.txt\n");
		strcpy(arqcena,"sala3d.txt");
		strcpy(arqcam,"camera.txt");
	}
	else
	{
		// Sim, copia para as variáveis que guardam o nome
		// do arquivo de cena e de câmera
		strcpy(arqcena,argv[1]);
		strcpy(arqcam,argv[2]);
	}
	// Define o modo de operação da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH ); 
 
	// Especifica o tamanho inicial em pixels da janela GLUT
	//glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500); 
 
	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("ExemploSala3D com iluminação e materiais");
 
	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);
  
	// Registra a função callback de teclado
	glutKeyboardFunc(Teclado);

	// Registra a função callback de teclas especiais
	glutSpecialFunc(TecladoEspecial);

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
