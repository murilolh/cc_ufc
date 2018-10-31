//*****************************************************
//
// ExemploBitmap.cpp 
// Um programa OpenGL simples que abre uma janela GLUT, 
// e desenha um bitmap
//
// Marcelo Cohen e Isabel H. Manssour
// Este código acompanha o livro 
// "OpenGL - Uma Abordagem Prática e Objetiva"
// 
//*****************************************************

#include <stdlib.h>
#include <GL/glut.h>

// Define bitmap 16x16
GLubyte bitmap[32] = {
	0x00, 0x00, 0x03, 0xc0, 0x0c, 0x30, 0x10, 0x08,
	0x23, 0xc4, 0x24, 0x24, 0x48, 0x12, 0x48, 0x12,
	0x40, 0x02, 0x40, 0x02, 0x26, 0x64, 0x26, 0x64,
	0x10, 0x08, 0x0c, 0x30, 0x03, 0xc0, 0x00, 0x00
};

GLsizei largura, altura;
GLfloat win;

// Função callback de redesenho da janela de visualização
void Desenha(void)
{
	// Limpa a janela de visualização com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

	// Altera a cor do desenho para preto
	glColor3f(0.0f, 0.0f, 0.0f);

	// Ajusta a posição inicial de desenho do bitmap
	glRasterPos2i(0, 0);

	// Desenha 10 cópias
	for(int i=0;i<10;++i)
		glBitmap(16, 16, 0.0, 0.0, 16.0, 16.0, bitmap);

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

	// Estabelece a janela de seleção (esquerda, direita, inferior, 
	// superior) mantendo a proporção com a janela de visualização
	if (largura <= altura) 
		gluOrtho2D (-win, win, -win*altura/largura, win*altura/largura);
	else 
		gluOrtho2D (-win*largura/altura, win*largura/altura, -win, win);
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
	win = 5.0f;

	// Ajusta o alinhamento de dados sendo descompactados
	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
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
	glutCreateWindow("Exemplo de Bitmap");

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

