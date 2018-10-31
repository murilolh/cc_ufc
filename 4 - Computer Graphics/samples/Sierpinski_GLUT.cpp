#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int rand();
void myinit(void) 
{
	glClearColor (0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-10.0, 510.0, -10.0, 510.0);
	glMatrixMode(GL_MODELVIEW);
}

void display(void)
{
	typedef GLfloat point2[2];
   point2 vertices[3] = {{0.0, 0.0},{250.0, 500.0},{500.0, 0.0}};
	int j, k;
	GLfloat r, g, b;
	point2 p = {250.0, 150.0};
   glClearColor (0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f (1.0, 0.0, 0.0);
	for (k = 0; k < 10000000; k++)
	{
		j = rand()%3;
		//glColor3f ((GLfloat)(rand()%3), (GLfloat)(rand()%3), (GLfloat)(rand()%3));
		p[0] = (p[0] + vertices[j][0])/2.0;
		p[1] = (p[1] + vertices[j][1])/2.0;
		r = (p[0] + p[1])/500.;
		g = (p[0] + vertices[j][1])/1000.;
		b = (p[1] + vertices[j][0])/1000.;
		glColor3f (r, g, b);
		glBegin(GL_POINTS); 
	        glVertex2fv(p);
		glEnd();
	}
	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Sierpinski Gasket");
	myinit();
	glutDisplayFunc(display);
	glutMainLoop();
}
