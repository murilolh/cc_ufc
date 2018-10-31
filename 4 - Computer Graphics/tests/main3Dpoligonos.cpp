#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

#define QUAD 1
#define TRI 2
#define CIR 3

void myinit(void)
{
    glClearColor(0,0,0,0);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5.0, 5.0, -5.0, 5.0,-5.0,5.0);
    glMatrixMode(GL_MODELVIEW);
    glNewList(QUAD, GL_COMPILE);
	   glPushAttrib(GL_ALL_ATTRIB_BITS);
      glBegin(GL_QUADS);
         glColor3d(1,0,0);
		   glVertex3d(0, -1.0, 0);
		   glVertex3d(2.0, -1.0, 0);
		   glVertex3d(2.0, 1.0, 0);
		   glVertex3d(0, 1.0, 0);
		   
		   glColor3d(0,1,0);
		   glVertex3d(0, -1.0, 2);
		   glVertex3d(0, -1.0, 0);
		   glVertex3d(0, 1.0, 2);
		   glVertex3d(0, 1.0, 0);
		   
		   glColor3d(0,0,1);
		   glVertex3d(0, -1.0, 2);
		   glVertex3d(2, -1.0, 2);
		   glVertex3d(2 ,1.0, 2);
		   glVertex3d(0, 1.0, 2);
		   
		   glColor3d(1,1,0);
		   glVertex3d(2, -1.0, 0);
		   glVertex3d(2.0, -1.0, 2);
		   glVertex3d(2.0, 1.0, 2);
		   glVertex3d(2, 1.0, 0);
		   
		   glColor3d(1,0,1);
		   glVertex3d(0, 1.0, 0);
		   glVertex3d(0, 1.0, 2);
		   glVertex3d(2.0, 1.0, 2);
		   glVertex3d(2, 1.0, 0);
		   
		   glColor3d(0,1,1);
		   glVertex3d(0, -1.0, 0);
		   glVertex3d(2.0, -1.0, 0);
		   glVertex3d(2.0, -1.0, 2);
		   glVertex3d(0, -1.0, 2);	
		   	
    	glEnd();
	   glPopAttrib();
    glEndList();    
}

void display(void)
{
	 glClear(GL_COLOR_BUFFER_BIT);
	 glLoadIdentity();
	 glRotatef((3.141528/2)*50,0,1,0);
	 glCallList(QUAD);   
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
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

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize(600,600);
    glutInitWindowPosition(0,0);    
    glutCreateWindow("POLIGONOS 2D");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
	 myinit(); 
    glutMainLoop();
}

