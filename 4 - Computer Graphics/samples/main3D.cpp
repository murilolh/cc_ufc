/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#include <GL/glut.h>

#include <stdlib.h>

static int slices = 16;
static int stacks = 16;

//propriedades da luz
static const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
static const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
static const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
static const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

//propriedades dos objetos
static const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
static const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
static const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
static const GLfloat high_shininess[] = { 100.0f };

//essas propriedades serao discutidas em sala, nao se preocupem!

/* GLUT callback Handlers */

 void resize3D(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //define que a projecao vai ser perspectiva, ou seja, nao ortografica
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

 void display3D(void)
{
    //glutGet(GLUT_ELAPSED_TIME) retorna o tempo desde que o programa foi
    // iniciado
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;

    //limpa o buffer de cores e o de profundidade
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,0,0);

    glPushMatrix();
        glTranslated(-2.4,1.2,-6);
        //faz uma rotacao de 60 graus no eixo X
        glRotated(60,1,0,0);
        //faz uma rotacao de a graus no eixo Z
        glRotated(a,0,0,1);
        //funcao predefinida da glut para desenhar uma esfera preenchida
        glutSolidSphere(1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(0,1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutSolidCone(1,1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(2.4,1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutSolidTorus(0.2,0.8,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(-2.4,-1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        //funcao predefinida da glut para desenhar uma esfera wireframe
        glutWireSphere(1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(0,-1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutWireCone(1,1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(2.4,-1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutWireTorus(0.2,0.8,slices,stacks);
    glPopMatrix();

    //essa cena utiliza dois frame buffers, o back buffer e o front buffer.
    // o front buffer contem a cena que estah sendo desenhada na janela,
    // enquanto que o back buffer contem a cena que vai ser desenhada na
    // na proxima atualizacao (refresh) da cena.
    //glutSwapBuffers() serve justamente para trocar esses buffers, e fazer
    // com que o back buffer seja o novo front buffer, e que o antigo front
    // buffer seja o novo back buffer. entendeu???
    glutSwapBuffers();
}

void key3D(unsigned char key, int x, int y)
{
    switch (key)
    {
	case 27 :
	case 'q':
		exit(0);
		break;

	case '+':
		slices++;
		stacks++;
	break;

	case '-':
		if (slices>3 && stacks>3)
		{
			slices--;
			stacks--;
		}
		break;
    }

	glutPostRedisplay();
}

void idle3D(void)
{
    glutPostRedisplay();
}

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
	//GLUT_DOUBLE indica que dois buffers serao utilizados. um deles vai conter
	// a cena que esta sendo desenhada na tela, e a outra eh onde a nova cena
	// serah desenhada.
	//GLUT_DEPTH indica que esta cena utilizara um buffer de profundidade
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT 3D");

    glutReshapeFunc(resize3D);
    glutDisplayFunc(display3D);
    glutKeyboardFunc(key3D);
    glutIdleFunc(idle3D);

    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //define que a luz 0 sera utilizada. o OpenGL suporta ateh 8 luzes.
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    //define que havera interacao enter as luzes e os objetos
    glEnable(GL_COLOR_MATERIAL);
    //define que a cena vai ter luz
    glEnable(GL_LIGHTING);

    //define as propriedades da luz 0
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    //define as propriedades do material dos objetos
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutMainLoop();

    return EXIT_SUCCESS;
}