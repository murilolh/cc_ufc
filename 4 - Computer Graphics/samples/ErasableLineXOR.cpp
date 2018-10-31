//#include <windows.h>		// Standard header for Windows
#include <GL/glut.h>
#include <stdlib.h>

// Globals
GLsizei wh = 500, ww = 500; // Initial window size
GLfloat size = 3.0;			// 1/2 of the side length of square
GLfloat xm=0, ym=0, xmm=0.5, ymm=0.5;
GLint   first;

int sub_menu;

void myinit(void) 
{
	
	// Set viewing conditions
	glViewport(0, 0, ww, wh);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1.0, 0.0, 1.0);
	glMatrixMode(GL_MODELVIEW);

	// Enable Logic Operation
	glEnable(GL_COLOR_LOGIC_OP);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

   	// Clear Background with black 
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void move(int x, int y)
{
	glColor3f(1.0, 0.0, 1.0);
	if(first == 1)
	{
		// A temporary line has already been drawn. 
		// So, drawing this line again in XOR mode restores the color
		// of the color buffer before the line was first drawn.
		// The same occurs with the rubberbanding rectangle.

		glBegin(GL_LINES);
			glVertex2f(xm, ym);
			glVertex2f(xmm, ymm);
		glEnd();
		glRectf(xm, ym, xmm, ymm);
		glFlush();
	}

	// If this is the first time a temporary line is drawn (first == 0) or
	// this is a new temporary line, compute the end position in world coordinates
	// and draw the line from the first point (xm, ym) to (xmm, ymm)

	xmm = (GLfloat)x/ww;
	ymm = (GLfloat)(wh - y)/wh;
	glRectf(xm, ym, xmm, ymm);
	glBegin(GL_LINES);
		glVertex2f(xm, ym);
		glVertex2f(xmm, ymm);
	glEnd();

	glFlush();
	first = 1;

}

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glColor3f(0.0, 1.0, 1.0);
		glRectf(0.2, 0.2, 0.8, 0.8);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glFlush();


}

void mouse (int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON		&& 	state == GLUT_DOWN) 
	{
		xm = (GLfloat)x/ww;
		ym = (GLfloat)(wh - y)/wh;
		glColor3f(0.0, 1.0, 0.0);
		glLogicOp(GL_XOR);
		first = 0;	 
	}
	else if (btn == GLUT_LEFT_BUTTON		&& 	state == GLUT_UP) 
	{
		// When the left button of the mouse is released,
		// The last temporary line and rectangle must be redraw in XOR mode
		// (this mode is active since the left button was first depressed) to
		// restore the frame buffer to its original color.

		glRectf(xm, ym, xmm, ymm);
		glBegin(GL_LINES);
			glVertex2f(xm, ym);
			glVertex2f(xmm, ymm);
		glEnd();
		glFlush();

		// Now the final color is restored and the final line 
		// is drawn to the current position	in COPY mode (permanent substitution)
		// of the bits in the frame buffer.

		glColor3f(0.0, 1.0, 0.0);
		glLogicOp(GL_COPY);
		xmm = (GLfloat)x/ww;
		ymm = (GLfloat)(wh - y)/wh;
		glBegin(GL_LINES);
			glVertex2f(xm, ym);
			glVertex2f(xmm, ymm);
		glEnd();
		glFlush();
	}
	else if (btn == GLUT_RIGHT_BUTTON	&& 	state == GLUT_DOWN) exit(0);
} 

void myReshape(GLsizei w, GLsizei h)
{
	// Adjust clipping box
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1.0, 0.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Adjust viewport and clear
	glViewport(0,0, w, h);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
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
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0,0);

	// Creating the OpenGL window
	glutCreateWindow("Desenhando Rubberband Lines");

	// Initializing graphics
	myinit();

	// Defining the callback functions
	glutDisplayFunc(display);  
	glutReshapeFunc(myReshape);
	glutMouseFunc(mouse);
	glutMotionFunc(move);

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
