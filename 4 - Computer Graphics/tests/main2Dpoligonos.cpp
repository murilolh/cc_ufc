#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

#define QUAD 1
#define TRI 2
#define CIR 3

void myinit(void)
{
    glClearColor(0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-5.0, 5.0, -5.0, 5.0);
    glMatrixMode(GL_MODELVIEW);
    glNewList(QUAD, GL_COMPILE);
	   glPushAttrib(GL_ALL_ATTRIB_BITS);
      glBegin(GL_QUADS);
		   glVertex2d(0, -1.0);
		   glVertex2d(2.0, -1.0);
		   glVertex2d(2.0, 1.0);
		   glVertex2d(0, 1.0);			
    	glEnd();
	   glPopAttrib();
    glEndList();
    glNewList(TRI, GL_COMPILE);
	   glPushAttrib(GL_ALL_ATTRIB_BITS);
      glBegin(GL_TRIANGLES);
		   glVertex2d(0.0, -1.0);
		   glVertex2d(2.0, -1.0);
		   glVertex2d(1.0, 1.0);			
   	glEnd();
	   glPopAttrib();
    glEndList();
    glNewList(CIR, GL_COMPILE);
   	glPushAttrib(GL_ALL_ATTRIB_BITS);
      glBegin(GL_POLYGON);
	      for(float i = 0; i < 6.2830; i+= 3.1415/24)
			   glVertex2f(cos(i),sin(i));
	   glEnd();
      glPopAttrib();
    glEndList();	
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(1,0,0);    glCallList(TRI);
    glTranslatef(3.5,0.0,0.0);
    glColor3d(0,1,0);
    glCallList(CIR);
    glTranslatef(-6.0,0.0,0.0);
    glColor3d(0,0,1);
    glCallList(QUAD);
    glLoadIdentity(); 
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
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(0,0);    
    glutCreateWindow("POLIGONOS 2D");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
	 myinit(); 
    glutMainLoop();
}

