//*****************************************************
//
// ExemploImagemZoom.cpp 
// Um programa OpenGL simples que abre uma janela GLUT, 
// carrega e desenha uma imagem JPEG, fazendo zoom.
//
// Marcelo Cohen e Isabel H. Manssour
// Este código acompanha o livro 
// "OpenGL - Uma Abordagem Prática e Objetiva"
// 
//*****************************************************

#include "bibutil.h"

TEX *imagem;

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
		// Ajusta a posição inicial de desenho da imagem
		glRasterPos2i(i*100, i*100);

		// Ajusta o fator de pixel zoom
		glPixelZoom(1+i*0.2,1+i*0.2);

		// Desenha a imagem
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

// Função callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
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
}

// Programa Principal 
int main(void)
{
	// Define do modo de operação da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 

	// Especifica a posição inicial da janela GLUT
	glutInitWindowPosition(5,5); 

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(520,520); 

	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Exemplo de Pixel Zoom");

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

