//*****************************************************
//
// ExemploGLUT.cpp
// Um programa OpenGL simples que mostra o 
// funcionamento da GLUT.
//
// Marcelo Cohen e Isabel H. Manssour
// Este código acompanha o livro 
// "OpenGL - Uma Abordagem Prática e Objetiva"
// 
//*****************************************************

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

// Função callback de redesenho da janela de visualização
void Desenha(void)
{
	printf("*** Callback de redesenho da tela\n");
	
	// Define a cor de fundo de tela como azul
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	// Limpa a janela de visualização com a cor de fundo definida
	glClear(GL_COLOR_BUFFER_BIT);
	// Exibe o desenho na janela
	glutSwapBuffers();
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	printf("*** Callback de redimensionamento da tela\n");
	printf(">>> Novo tamanho da janela: %d x %d \n\n", w, h);
}

// Função callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char tecla, int x, int y)  
{
	int modificadores;
	printf("*** Tratamento de teclas comuns\n");
	printf(">>> Tecla: %c\n",tecla);

	if (tecla == 27) 
		exit(0);

	if (tecla == 'a') // muda para tela cheia
		glutFullScreen();
	if (tecla == 'A') // muda posição da janela
	{
		glutReshapeWindow(500,400); 
		glutPositionWindow(100,100);
	}
	
	// Trata SHIFT, CTRL e ALT
	modificadores = glutGetModifiers();
	if (modificadores & GLUT_ACTIVE_SHIFT)
		printf("(SHIFT pressionado)\n");
	if (modificadores & GLUT_ACTIVE_CTRL)
		printf("(CTRL pressionado)\n");
	if (modificadores & GLUT_ACTIVE_ALT)
		printf("(ALT pressionado)\n");
}

// Função callback chamada para gerenciar eventos de teclas especiais(F1,PgDn,...)
void TeclasEspeciais (int tecla, int x, int y)  
{
	printf("*** Tratamento de teclas especiais\n");
	switch (tecla)
	{
		case GLUT_KEY_F1:	printf(">>> Tecla F1 pressionada\n");
							break;
		case GLUT_KEY_F2:	printf(">>> Tecla F2 pressionada\n");
							break;
		case GLUT_KEY_F3:	printf(">>> Tecla F3 pressionada\n");
							break;
	}
}

// Função que trata a opção selecionada do menu principal
void MenuPrincipal(int op)
{
	printf("*** Menu principal!\n");
}

// Função callback chamada quando são notificados os eventos do mouse
void GerenciaMouse (int button, int state, int x, int y)
{
	printf("*** Tratamento de Cliques de mouse\n");
	if (state == GLUT_DOWN) 
		printf(">>> Botao %d pressionado\n",button);
	if (state == GLUT_UP) 
		printf(">>> Botao %d liberado\n",button);
}

// Função que trata a opção selecionada do menu "Primitiva"
void MenuPrimitiva(int op)
{
	printf("*** Menu PRIMITIVA: ");	
	switch(op) {
		case 0:
			printf("Opcao QUADRADO");
			break;
		case 1:
			printf("Opcao TRIANGULO");
			break;
		case 2:
			printf("Opcao LOSANGO");
			break;
	}
	printf("\n");
	glutPostRedisplay();
}

// Função que trata a opção selecionada do menu "Cor"
void MenuCor(int op)
{
	printf("*** Menu COR: ");	
	switch(op) {
		case 0:
			printf("Opcao VERMELHO");
			break;
		case 1:
			printf("Opcao VERDE");
			break;
		case 2:
			printf("Opcao AZUL");
			break;
	}
	printf("\n");
	glutPostRedisplay();
}

// Função responsável por criar os menus
void CriaMenu() 
{
	int menu,submenu1,submenu2;

	// Cria submenu para seleção de cor
	submenu1 = glutCreateMenu(MenuCor);
	glutAddMenuEntry("Vermelho",0);
	glutAddMenuEntry("Verde",1);
	glutAddMenuEntry("Azul",2);

	// Cria submenu para seleção de primitiva
	submenu2 = glutCreateMenu(MenuPrimitiva);
	glutAddMenuEntry("Quadrado",0);
	glutAddMenuEntry("Triângulo",1);
	glutAddMenuEntry("Losango",2);

	// Cria menu principal...
	menu = glutCreateMenu(MenuPrincipal);
	// ... e adiciona ambos submenus a ele
	glutAddSubMenu("Cor",submenu1);
	glutAddSubMenu("Primitivas",submenu2);

	// Associa o menu ao botão direito do mouse
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// Programa Principal
int main(void)
{
	// Define do modo de operação da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB );

	// Especifica a posição inicial da janela GLUT
	glutInitWindowPosition(0,0);

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(500,400);

	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Programa de Teste da GLUT");

	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc (Desenha);

	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc (AlteraTamanhoJanela);

	// Registra a função callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);

	// Registra a função callback que gerencia os eventos do mouse   
	glutMouseFunc (GerenciaMouse);

	// Registra a função callback para tratamento das teclas especiais
	glutSpecialFunc (TeclasEspeciais);

	// Chama função para criar o menu
	CriaMenu();

	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();

	return 0;
}

