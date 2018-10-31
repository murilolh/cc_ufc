//*****************************************************
//
// ExemploImagemTransfer.cpp 
// Um programa OpenGL simples que abre uma janela GLUT, 
// carrega e desenha uma imagem JPEG, aplicando uma
// escala e "bias" à cor de cada pixel, e opcionalmente
// aplicando um mapeamento para cada componente de cor
//
// Marcelo Cohen e Isabel H. Manssour
// Este código acompanha o livro 
// "OpenGL - Uma Abordagem Prática e Objetiva"
// 
//*****************************************************

#include "bibutil.h"

TEX *imagem;

// Define um mapa de cor para cada componente
GLfloat cores_r[256], cores_g[256], cores_b[256];

// Indica sentido de cada mapa de cor (true = decrescente)
bool r,g,b;

GLsizei largura, altura;

// Função callback de redesenho da janela de visualização
void Desenha(void)
{
	// Limpa a janela de visualização com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

	// Altera a cor do desenho para preto
	glColor3f(0.0f, 0.0f, 0.0f);

	// Desenha algumas cópias da imagem
	for(int i=0;i<4;++i)
	{
		// Ajusta escala de cores
		glPixelTransferf(GL_RED_SCALE,i/3.0);
		glPixelTransferf(GL_BLUE_SCALE,i/3.0);
		glPixelTransferf(GL_GREEN_SCALE,i/3.0);
		
		// Ajusta a posição inicial de desenho da imagem
		glRasterPos2i(i*100, i*100);
		glDrawPixels(imagem->dimx, imagem->dimy,
			GL_RGB, GL_UNSIGNED_BYTE, imagem->data);
	}

	// Executa os comandos OpenGL 
	glFlush();
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Evita a divisao por zero
	if(h == 0) h = 1;

	// Atualiza as variáveis
	largura = w;
	altura = h;

	// Especifica as dimensões da Viewport
	glViewport(0, 0, largura, altura);	

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de seleção
	gluOrtho2D(0,largura-1,0,altura-1);
}

// Gera os mapas para cada componente, de acordo com
// o sentido selecionado
void GeraMapasCores()
{
	// Gera os três mapas
	for(int i=0;i<256;++i)
	{
		if(r)	cores_r[i] = (255-i)/255.0;
		else	cores_r[i] = i/255.0;
		if(g)	cores_g[i] = (255-i)/255.0;
		else	cores_g[i] = i/255.0;
		if(b)	cores_b[i] = (255-i)/255.0;
		else	cores_b[i] = i/255.0;
	}

	// Aplica os mapas
	glPixelMapfv(GL_PIXEL_MAP_R_TO_R,256,cores_r);
	glPixelMapfv(GL_PIXEL_MAP_G_TO_G,256,cores_g);
	glPixelMapfv(GL_PIXEL_MAP_B_TO_B,256,cores_b);
}

// Função callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	switch(key)
	{
		case 27:	exit(0);
					break;
		case 'r':	r = !r;
					GeraMapasCores();
					break;
		case 'g':	g = !g;
					GeraMapasCores();
					break;
		case 'b':	b = !b;
					GeraMapasCores();
					break;
	}
	glutPostRedisplay();
}

// Função responsável por inicializar parâmetros e variáveis
void Inicializa (void)
{   
	// Define a cor de fundo da janela de visualização como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Ajusta o alinhamento de dados sendo descompactados
	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);

	// Carrega a imagem
	imagem = CarregaJPG("texturas/azulejo.jpg");

	// Sentido = crescente
	r = g = b = false;
	
	// Gera os mapas iniciais para cada componente
	GeraMapasCores();

	// Habilita mapeamento de cor
	glPixelTransferi(GL_MAP_COLOR, GL_TRUE);
}

// Programa Principal 
int main(void)
{
	// Define do modo de operação da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 

	// Especifica a posição inicial da janela GLUT
	glutInitWindowPosition(5,5); 

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(450,450); 

	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Exemplo de Imagens");

	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);
 
	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela);
 
	// Registra a função callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);

	// Chama a função responsável por fazer as inicializações 
	Inicializa();

	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();

	return 0;
}

