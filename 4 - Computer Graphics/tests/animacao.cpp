#include <GL/glut.h>
#include <stdlib.h>

#define BOX 1

void myinit(void) 
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_FLAT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glNewList(BOX, GL_COMPILE);
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glBegin(GL_POLYGON);
			glColor3f(1.0, 0.0, 0.0);
			glVertex2f(-1.0, -1.0);
			glVertex2f( 1.0, -1.0);
			glVertex2f( 1.0,  1.0);
			glVertex2f(-1.0,  1.0);
		glEnd();
		glPopAttrib();
	glEndList();
}

void animate(void)
{
	int j=1;
	glColor3f(1.0, 0.0, 1.0);
	while (j > 0)
	{
		glClear(GL_COLOR_BUFFER_BIT);
 		for (int i=1; i < 5; i++)
		{
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				gluOrtho2D(-2.0*i, 2.0*i, -2.0*i, 2.0*i);
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				if(i==1)
					glViewport(50,150,100,100);
				if(i==2)
					glViewport(150,50,100,100);
				if(i==3)
					glViewport(250,150,100,100);
				if(i==4)
					glViewport(150,250,100,100);
				glBegin(GL_LINE_LOOP);
					glVertex2f(-2.0*i, -2.0*i);
					glVertex2f( 2.0*i, -2.0*i);
					glVertex2f( 2.0*i,  2.0*i);
					glVertex2f(-2.0*i,  2.0*i);
				glEnd();
				glRotatef(j*0.5,0., 0., 1.);
				glCallList(BOX);		
		}
		glutSwapBuffers();
		j++;
	}
}

void animate2(void)
{
	int j=1;
	glColor3f(1.0, 0.0, 1.0);
	while (j > 0)
	{
		glClear(GL_COLOR_BUFFER_BIT);
 		for (int i=1; i < 5; i++)
		{
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();				gluOrtho2D(-2.0*i, 2.0*i, -2.0*i, 2.0*i);
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();				glViewport((i-1)*100, (i-1)*100,  100, 100);
				glBegin(GL_LINE_LOOP);
					glVertex2f(-1.95*i, -1.95*i);					glVertex2f( 1.95*i, -1.95*i);
					glVertex2f( 1.95*i,  1.95*i);
					glVertex2f(-1.95*i,  1.95*i);
				glEnd();				glRotatef(j*0.5,0., 0., 1.);
				glCallList(BOX);		
		}		glutSwapBuffers();
		j++;
   }
}


void animate3(void)
{
	int j=1;	glColor3f(0.0, 0.0, 1.0);
	while (j > 0)	{
		glClear(GL_COLOR_BUFFER_BIT);
 		for (int i=1; i < 5; i++)
		{
			for (int k=1; k < 5; k++)
			{				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				if (k%2 == 0)
      			gluOrtho2D(-2.0*i, 2.0*i, -2.0*i, 2.0*i);
				else
   				gluOrtho2D(-2.0*(5-i), 2.0*(5-i), -2.0*(5-i), 2.0*(5-i));
				glMatrixMode(GL_MODELVIEW);				glLoadIdentity();
				glViewport((k-1)*100, (i-1)*100,  100, 100);
				if (k%2 == 0)				{
					glBegin(GL_LINE_LOOP);
						glVertex2f(-1.9*i, -1.9*i);
						glVertex2f( 1.9*i, -1.9*i);						glVertex2f( 1.9*i,  1.9*i);
						glVertex2f(-1.9*i,  1.9*i);
					glEnd();
				}				else
				{
					glBegin(GL_LINE_LOOP);
						glVertex2f(-1.9*(5-i), -1.9*(5-i));						glVertex2f( 1.9*(5-i), -1.9*(5-i));
						glVertex2f( 1.9*(5-i),  1.9*(5-i));
						glVertex2f(-1.9*(5-i),  1.9*(5-i));
					glEnd();				}
				glRotatef(j*0.5,0., 0., 1.);
				glCallList(BOX);				}
		}
		glutSwapBuffers();		j++;
	}
} 

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(0,0);
	glutCreateWindow("BOX Display List");
	myinit();
	glutDisplayFunc(animate);
   glutMainLoop();
}

