#include <math.h>
//#include <windows.h>
#include <iostream.h>#include <stdio.h>
#include <GL/glut.h>

GLint base;
char text_string[1000];


void OurFont(char c);

void myinit(void) 
{	
	int i;

	/* Background to be cleared to black */
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_FLAT);

	base = glGenLists(256);
	for (i=0; i < 256; i++)
	{
		glNewList(base+i, GL_COMPILE);
			OurFont(i);
		glEndList();
	}


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0, 20.0, -1.0, 12.0);
	glMatrixMode(GL_MODELVIEW);

	cin >> 	 text_string;
	cout << text_string;

}

void OurFont(char c)

{	
	int i;
	float angle;

	switch(c)
	{
		case 'a':
			glBegin(GL_LINE_STRIP);
				
				glVertex2f(0.500, 0.350);
				glVertex2f(0.375, 0.100);
				glVertex2f(0.250, 0.000);
				glVertex2f(0.125, 0.100);

				glVertex2f(0.000, 0.350);
				glVertex2f(0.125, 0.600);
				glVertex2f(0.250, 0.700);
				glVertex2f(0.375, 0.600);

				glVertex2f(0.500, 0.350);
				glVertex2f(0.625, 0.100);
				glVertex2f(0.750, 0.000);
				glVertex2f(1.000, 0.100);
				
			glEnd();
			glTranslatef(1.0, 0.0, 0.0);
		break;
	
		case 'A':
			glBegin(GL_QUADS);
				
				glVertex2f(0.0, 0.0);
				glVertex2f(0.5, 1.0);
				glVertex2f(0.5, 0.8);
				glVertex2f(0.1, 0.0);

				glVertex2f(0.5, 1.0);
				glVertex2f(1.0, 0.0);
				glVertex2f(0.9, 0.0);
				glVertex2f(0.5, 0.8);

				glVertex2f(0.25, 0.3);
				glVertex2f(0.3,  0.4);
				glVertex2f(0.7,  0.4);
				glVertex2f(0.75, 0.3);
				
			glEnd();
			glTranslatef(1.0, 0.0, 0.0);
		break;

		case 'O':
			glTranslatef(0.5, 0.5, 0.0); 
			glBegin(GL_QUAD_STRIP);
				for(i=0; i<=12; i++)
				{		angle = 3.14/6.0 * i;
						glVertex2f(0.4*cos(angle), 0.4*sin(angle));
						glVertex2f(0.5*cos(angle), 0.5*sin(angle));
				}
			glEnd();
			glTranslatef(0.5, -0.5, 0.0);
		break;

	}
}


void display(void)
{

 	glClearColor (0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);	

	glColor3f (1.0, 0.0, 1.0);

	glListBase(base);

	glCallLists((GLint) strlen(text_string), GL_BYTE,text_string);

	glFlush();

}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("My own Fonts");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
}
