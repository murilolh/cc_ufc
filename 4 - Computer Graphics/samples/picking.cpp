//#include <windows.h>		// Standard header for Windows
//#include <OpenGL/glaux.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 1024		// This is the size of the selection buffer

// Globals
GLsizei   wh = 500, ww = 500; // Initial window size
GLdouble  pick_xsize = 5., pick_ysize = 5.;

int sub_menu;

// Function signatures
void drawObjects(GLenum mode);
void processHits(GLint hits, GLuint buffer[]);

void myinit(void) 
{
	
	// Set viewing conditions
	glViewport(0, 0, ww, wh);					// The viewport is the whole OpenGLwindow
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();							// Initialize the projection matrix with [I]
	glOrtho(-2.0,  2.0, -2.0, 2.0, -2.0, 2.0);	// Computes the projection matrix and multiply [I][O]

	glMatrixMode(GL_MODELVIEW);

   	// Clear Background with black 
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);		// Clears the frame buffer with black

}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);		// Clears the frame buffer with black
	drawObjects(GL_RENDER);				// Draws the scene
	glFlush();
}

void mouse (int button, int state, int x, int y)
{
	GLuint	nameBuffer[BUFSIZE];		// Buffer where the IDs of the objects picked are stored
	GLint	hits;
	GLint	viewport[4];				// Array to recover the parameters of the viewport

	if (button == GLUT_LEFT_BUTTON	&& 	state == GLUT_DOWN) 
	{
		// Initialize the name stack

		glSelectBuffer(BUFSIZE, nameBuffer); // Defines the SELECT buffer for picking 

		glGetIntegerv(GL_VIEWPORT, viewport);// Recovers viewport information
		
		printf("Viewport parameters %d, %d, %d, %d.\n", viewport[0],viewport[1],viewport[2],viewport[3]);

		glRenderMode(GL_SELECT);			 // Starts SELECT mode

		glInitNames();						 // Initialized the name stack for storing pickable objects
		glPushName(0);						 // Storing names cannot start on an empty stack

		// Set up viewing for selection mode

		glMatrixMode(GL_PROJECTION);

		// Save original viewing matrix

		glPushMatrix();					// Current viewing matrix is saved on the viewing stack
		glLoadIdentity();				// Makes [I] the current viewing matrix

		// pick_xsize x pick_ysize pick area around the cursor
		// must invert mouse y to get in worl coords

		gluPickMatrix((GLdouble)x, (GLdouble)(viewport[3] - y), pick_xsize, pick_ysize, viewport );

		// Same clipping window as in reshape callback

		glOrtho(-2.0,  2.0, -2.0, 2.0, -2.0, 2.0);

		// Change to Modeling mode and render the scene

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// Render objects in SELECT mode
		// In this mode the IDs of the objects rendered will be stored in the name stack

	   	drawObjects(GL_SELECT);	
		
		// Back to Projection mode and restore the viewing matrix

		glMatrixMode(GL_PROJECTION);

		// Restore viewing matrix

		glPopMatrix();

		// Back to Modeling mode for normal rendering

		glMatrixMode(GL_MODELVIEW);

		// Return to normal render mode	and returns the number of 
		// distinct objects that were inside the frustum in the selection mode

		hits = glRenderMode(GL_RENDER);

		// Process hits from selection mode rendering

		processHits(hits, nameBuffer);

		// Normal render  (calls the display callback function)

		glutPostRedisplay();
	}
} 

void drawObjects(GLenum mode)
{
	// Draws the objects of the scene.
	// When the mode is GL_SELECT, stores all the pickable objects' IDs in the name stack
	
	// Draws a magenta rectangle
	if(mode == GL_SELECT) glLoadName(3); //glPushName(3); //glLoadName(3);
	glColor3f(1.0, 0.0, 1.0);
	glRectf(-1.5, -1.5, 0.1, 2.0);

	// Draws the Red square
	if(mode == GL_SELECT) glLoadName(1); //glPushName(1); //glLoadName(1);
	glColor3f(1.0, 0.0, 0.0);
	glRectf(-0.5, -0.5, 1.0, 1.0);

	// Draws the Blue square
	if(mode == GL_SELECT) glLoadName(2); //glPushName(2); //glLoadName(2);
	glColor3f(0.0, 0.0, 1.0);
	glRectf(-1.0, -1.0, 0.5, 0.5);

	
	glFlush();

}

void processHits(GLint hits, GLuint buffer[])
{

	// hits: the number of pickable objects that were rendered inside
	//       the frustum of the SELECT mode
	// buffer: array where the picked objects' IDs were stored

	GLint i, j, names;
	GLuint  *ptr;

	printf("The content of the bufer is:\n");
	printf("Buffer{");
	for (i = 0; i < 4*hits; i++)
	{
		printf("%d, ", buffer[i]);
	}
	printf("}\n\n");

	if (hits == 0)
	{
			printf("hits = %d. No objects were selected.\n", hits);
	}
	else
	{
		printf("hits = %d. %d objects were selected\n", hits, hits);
		
		// ptr is a pointer to the begining of the buffer
		// each record of the buffer stores
		//		. number of names on the name stack when the hit occurred
		//      . zmin and zmax of intersection points of all objects intersecting
		//		  the view volume
		//		. the IDs stored in the name stack at the time of the hit, with
		//		  the bottommost element first

		ptr = (GLuint *) buffer;

		// Loop over number of hits

		for (i = 0; i < hits; i++)
		{
			// Get the number of names on the name stack
			names = *ptr;

			// Skip over number of names and depths

			ptr += 3;

			// Check each name in record

			printf("\n");
			printf("Hit %d \n", i+1);

			for (j = 0; j < names; j++)
			{
				if(*ptr==1) printf("red rectangle\n");
				if(*ptr==2) printf("blue rectangle\n");
				if(*ptr==3) printf("magenta rectangle\n");

				// Go to next hit record

				ptr++;
			}
		}
	}
}

void myReshape(GLsizei w, GLsizei h)
{
	// Adjust clipping box
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0,  2.0, -2.0, 2.0, -2.0, 2.0);
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

int main(int argc, char **argv)
{
	// Negotiating window section
	glutInit(&argc, argv);

	// Seting the window properties
	glutInitDisplayMode(GLUT_DEPTH  | GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0,0);

	// Creating the OpenGL window
	glutCreateWindow("Desenhando Quadrados Coloridos");

	// Initializing graphics
	myinit();

	// Defining the callback functions
	glutReshapeFunc(myReshape);
	glutMouseFunc(mouse);
	glutDisplayFunc(display);

	// Creating a pop-up menu

	glutCreateMenu(top_menu);
	glutAddMenuEntry("Quit",1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// Entering the main event loop
	glutMainLoop();
	
	return 0;
}
