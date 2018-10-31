#include <GL/glut.h>
#include <stdlib.h>

void resize2D(int width, int height)
{
    const float ar = (float) width / (float) height;    
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //define que a projecao vai ser ortografica, ou seja, nao perspectiva
    glOrtho(-ar, ar, -1.0, 1.0, -1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

 void display2D(void)
{
    //manda limpar o frame buffer, limpando, assim, as cores da ultima vez
    // que a janela foi pintada.
    glClear(GL_COLOR_BUFFER_BIT);
    //define a cor do objeto. se vc quiser, brinque com esses valores, que sao
    // o R, o G e o B do objeto.
    glColor3d(0.34,0.24,0.67);
    glPushMatrix();
		//translada o objeto para a direita. brinque tambem com esses valores,
		// mas fique no intervalo [-1.0, 1.0]. os parametros sao o X, o Y e o Z
		// para onde o objeto vai ser deslocado.
		glTranslatef(0.2, 0.0, 0.0);
		//escalona o objeto. os parametros sao os escalonamentos no eixo X, no Y
		// e no Z
		glScalef(0.5, 0.5, 0.5);
		// o objeto desenhado vai ser um QUAD
        glBegin(GL_QUADS);
			//os vertices do QUAD
			glVertex2d(-1.0, -1.0);
			glVertex2d(1.0, -1.0);
			glVertex2d(1.0, 1.0);
			glVertex2d(-1.0, 1.0);
        glEnd();
    glPopMatrix();
	//todo a cena, ateh aqui, foi desenhada no frame buffer. o glFlush() avisa
	// ao OpenGL que o frame buffer deve ser desenhado na tela.
    glutSwapBuffers();
}

void key2D(unsigned char key, int x, int y)
{
    switch (key)
    {
	case 27 :
	case 'q':
		exit(0);
		break;
    }
    glutPostRedisplay();
}

void idle2D(void)
{
    //repinta a janela (refresh)
    glutPostRedisplay();
}

/* Program entry point */

int main(int argc, char *argv[])
{
    //inicia a glut. os argumentos sao os mesmos do main()
    glutInit(&argc, argv);
    //define o tamanho da janela no monitor
    glutInitWindowSize(640,480);
    //define a posicao da janela no monitor
    glutInitWindowPosition(10,10);
    //inicializa o modo de display da glut. GLUT_RGB indica que os objetos
    // vao ser desenhados usando valores R, G e B. GLUT_SINGLE indica que
    // somente um buffer sera utilizado.
    //mais informacoes sobre esses modos, no google =P
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    //cria a janela e define o nome da janela
    glutCreateWindow("GLUT 2D");
    //define a funcao que deve ser chamada quando a janela for redimensionada
    glutReshapeFunc(resize2D);
    //define a funcao que deve ser chamada sempre que a janela tiver que ser
    // repintada
    glutDisplayFunc(display2D);
    //define a funcao que deve ser chamada quando uma tecla for pressionada
    glutKeyboardFunc(key2D);
    //define a funcao que deve ser chamada quando nao houver nenhum evento
    // externo
    glutIdleFunc(idle2D);
    //define a cor de fundo da janela. os parametros sao R, G, B e a
    // transparencia. geralmente, a transparencia de programas simples, como
    // esse, sao definidas como 1 ou 0.
    // os valores de R, G e B sao entre 0 e 1
    glClearColor(1,1,1,1);
    //renderiza a janela enquanto ela nao for finalizada
    glutMainLoop();
    return EXIT_SUCCESS;
}
