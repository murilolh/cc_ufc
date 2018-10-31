//*****************************************************
//
// ExemploCpp.h
// Contém as declarações da classe ExemploCpp. Nesta 
// classe são implementados os métodos responsáveis
// por abrir uma janela GLUT, desenhar um "torus" com 
// iluminação, e permitir fazer zoom in e zoom out e 
// mover a posição do observador virtual com as teclas
// Home/End e o mouse. 
//
// Isabel H. Manssour e Marcelo Cohen
// Este código acompanha o livro 
// "OpenGL - Uma Abordagem Prática e Objetiva"
// 
//*****************************************************

#include <GL/glut.h>
#include <stdlib.h>

#ifndef __EXEMPLOCPP_H
#define __EXEMPLOCPP_H

class ExemploCpp
{
	private:
		static GLfloat angle, fAspect;
		static GLfloat rotX, rotY, rotX_ini, rotY_ini;
		static GLfloat obsX, obsY, obsZ, obsX_ini, obsY_ini, obsZ_ini;
		static int x_ini, y_ini, bot;
		static GLint identificadorJanela;
		static void Inicializa (void);
		static void DefineIluminacao (void);
		static void PosicionaObservador (void);
		static void EspecificaParametrosVisualizacao (void);
		static void Desenha (void);
		static void Teclado (unsigned char tecla, int x, int y);
		static void TeclasEspeciais (int tecla, int x, int y);
		static void AlteraTamanhoJanela (GLsizei w, GLsizei h);
		static void GerenciaMouse (int button, int state, int x, int y);
		static void GerenciaMovim (int x, int y);
	public:
		ExemploCpp (int largura=400, int altura=400, int posicaoX=100, int posicaoY=100, char *titulo="ExemploCpp");
		~ExemploCpp ();
		void inicializaLoopGlut (void);
};

#endif
