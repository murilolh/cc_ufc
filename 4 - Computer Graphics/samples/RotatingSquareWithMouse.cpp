//#include <windows.h>		// Standard header for Windows
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Globals
GLsizei wh = 500, ww = 500; // Initial window size
float theta = 0.;
int size;
float raio = 200;
bool  decrease = true;
time_t time_init, time_curr;
double dt = 31;


int sub_menu;
void idle(void);


void myinit(void) 
{
	
	// Set viewing conditions
	glViewport(0, 0, ww, wh);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-(GLdouble)ww/2, (GLdouble)ww/2, -(GLdouble)wh/2, (GLdouble)wh/2);
	glMatrixMode(GL_MODELVIEW);

   	// Clear Background with black 
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glFlush();

}


void display(void)
{
	float thetar, angler, hside;

	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0, 1.0, 1.0);
 
 /*
	{
		if(decrease == TRUE)
		{
			if (raio > 10)
			{
				raio = raio*0.8;
			}
			else
			{
				decrease = FALSE;
				raio = raio*1.2;
			}
		}
		else
		{
			if (raio > 200)
			{
				decrease =	TRUE;
				raio = raio*0.8;
			}
			else
			{
				raio = raio*1.2;
			}
		}
		
	}
*/
	glBegin(GL_POLYGON);
		angler = (45./360.)*(2.*3.14);
		hside = raio*cos(angler);
		glVertex2f( hside,	hside);
		glVertex2f(-hside,  hside);
		glVertex2f(-hside, -hside);
		glVertex2f( hside, -hside);
	glEnd();							 

	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
		thetar = (theta/360.)*(2.*3.14);
		glVertex2f( raio*cos(thetar),	raio*sin(thetar));
		glVertex2f(-raio*sin(thetar),   raio*cos (thetar));
		glVertex2f(-raio*cos(thetar),  -raio*sin(thetar));
		glVertex2f( raio*sin(thetar),  -raio*cos(thetar));
	glEnd();							 

	glFlush();
//	glutSwapBuffers();


}

void mouse (int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON		&& 	state == GLUT_DOWN) 
	{
		glutIdleFunc(idle);
	}
	if (btn == GLUT_MIDDLE_BUTTON	&& 	state == GLUT_DOWN) glutIdleFunc(NULL);
} 

void idle(void)
{  	
	for (int i=0; i < 10000000; i++)
	{
	}

	theta+= 1.;
	if(theta >= 360.) theta -= 360;

	glutPostRedisplay();
}


void myReshape(GLsizei w, GLsizei h)
{
	//raio = 0.8*(w/2);

	// Adjust clipping box
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-(GLdouble)w/2, (GLdouble)w/2, -(GLdouble)h/2, (GLdouble)h/2);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Adjust viewport and clear
	glViewport(0,0, w, h);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	display();
	glFlush();

	// Set global size for use by the drawing routine

	ww = w;
	wh = h;

}

void top_menu(int id)
{
	if(id == 1) exit(0);	
}

void size_menu(int id)
{
	if(id == 2) size = size*2;
	else if(id == 3) size = size/2;
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	// Negotiating window section
	glutInit(&argc, argv);

	// Seting the window properties
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0,0);

	// Creating the OpenGL window
	glutCreateWindow("Quadrado giratório");

	// Initializing graphics
	myinit();

	// Defining the callback functions
	glutReshapeFunc(myReshape);
	glutMouseFunc(mouse);
	glutDisplayFunc(display);

	// Creating a pop-up menu
	sub_menu =	glutCreateMenu(size_menu);
				glutAddMenuEntry("Increase square size",2);
				glutAddMenuEntry("Decrease square size",3);

	glutCreateMenu(top_menu);
	glutAddMenuEntry("Quit",1);
	glutAddSubMenu("Resize",sub_menu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// Entering the main event loop
	glutMainLoop();

	return 0;
}