#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void Display(void);
void quad(int a, int b, int c, int d);

// Globals
GLsizei wh = 500, ww = 500; // Initial window size
GLfloat theta=0.0;

GLfloat vertices[8][3] = {	{-1.0, 1.0, 1.0}, { 1.0, 1.0, 1.0},
								{ 1.0, 1.0,-1.0}, {-1.0, 1.0,-1.0},
								{-1.0,-1.0, 1.0}, { 1.0,-1.0, 1.0},
								{ 1.0,-1.0,-1.0}, {-1.0,-1.0,-1.0}};
	GLfloat normals[8][3] = {	{-1.0, 1.0, 1.0}, { 1.0, 1.0, 1.0},
								{ 1.0, 1.0,-1.0}, {-1.0, 1.0,-1.0},
								{-1.0,-1.0, 1.0}, { 1.0,-1.0, 1.0},
								{ 1.0,-1.0,-1.0}, {-1.0,-1.0,-1.0}};
	GLfloat colors[8][3] = {	{0.0,  1.0, 1.0}, {1.0, 1.0, 1.0},
								{1.0,  1.0, 0.0}, {0.0, 1.0, 0.0},
								{0.0,  0.0, 1.0}, {1.0, 0.0, 1.0},
								{ 1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};


//! This method gets called every time the graphics
//! has to be drawn.

void display(void)
{
	Display		();
	glFlush		();
	glutSwapBuffers	();
}



//! This method draws the scene.
void Display(void)
{

	glClearColor (0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();

    glTranslatef(0.0, 0.0, -2.0);

	// Rotate the wireframe of the sphere around x axis of 45 degrees
	
	glRotatef(theta, 1.0, 0.0, 0.0);
	glRotatef( 45.0, 1.0, 0.0, 0.0); // Second operation
	glRotatef(-45.0, 0.0, 1.0, 0.0); // First  operation

	// Draw faces
	quad(6, 2, 1, 5); // Face x+
	quad(3, 0, 1, 2); // Face y+
	quad(5, 1, 0, 4); // Face z+
	quad(4, 0, 3, 7); // Face x-
	quad(6, 5, 4, 7); // Face y-
	quad(7, 3, 2, 6); // Face z-

	// Draw axes
	
	glBegin (GL_LINES);
	
		// Draw the x-axis (Red axis)
		glColor3f ( 1.0,  0.0,  0.0);
		glVertex3f(-1.5, -1.0, -1.0);
		glVertex3f( 1.5, -1.0, -1.0);
		
		glVertex3f( 1.5, -1.0, -1.0);
		glVertex3f( 1.3, -0.8, -1.0);
		  
		glVertex3f( 1.5, -1.0, -1.0);
		glVertex3f( 1.3, -1.2, -1.0);
		
		glVertex3f( 1.5, -1.0, -1.0);
		glVertex3f( 1.3, -1.0, -0.8);
		  
		glVertex3f( 1.5, -1.0, -1.0);
		glVertex3f( 1.3, -1.0, -1.2);
		
		// Draw the y-axis (Green axis)
		glColor3f ( 0.0,  1.0,  0.0);
		glVertex3f(-1.0, -1.5, -1.0);
		glVertex3f(-1.0,  1.5, -1.0);
		
		glVertex3f(-1.0,  1.5, -1.0);
		glVertex3f(-1.0,  1.3, -0.8);
		  
		glVertex3f(-1.0,  1.5, -1.0);
		glVertex3f(-1.0,  1.3, -1.2);
		
		glVertex3f(-1.0,  1.5, -1.0);
		glVertex3f(-0.8,  1.3, -1.0);
		  
		glVertex3f(-1.0,  1.5, -1.0);
		glVertex3f(-1.2,  1.3, -1.0);
		
		// Draw the z-axis (Blue axis)
		glColor3f ( 0.0,  0.0,  1.0);
		glVertex3f(-1.0, -1.0, -1.5);
		glVertex3f(-1.0, -1.0,  1.5);
		
		glVertex3f(-1.0, -1.0,  1.5);
		glVertex3f(-0.8, -1.0,  1.3);
		
		glVertex3f(-1.0, -1.0,  1.5);
		glVertex3f(-1.2, -1.0,  1.3);
		
		glVertex3f(-1.0, -1.0,  1.5);
		glVertex3f(-1.0, -0.8,  1.3);
		
		glVertex3f(-1.0, -1.0,  1.5);
		glVertex3f(-1.0, -1.2,  1.3);

	glEnd();
	

	glFlush();

}

//! Initialization of all OpenGL specific parameters.
void myinit(void)
{
	glClearColor	(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-4.0, 4.0, -4.0, 4.0, -4.0, 4.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


//	glShadeModel	(GL_FLAT);
}

// This method draws a Face abcd
void quad(int a, int b, int c, int d)
{
	glBegin(GL_QUADS);
		glColor3fv (colors[a]);
		glNormal3fv(normals[a]);
		glVertex3fv(vertices[a]);
		
		glColor3fv(colors[b]);
		glNormal3fv(normals[b]);
		glVertex3fv(vertices[b]);
		
		glColor3fv(colors[c]);
		glNormal3fv(normals[c]);
		glVertex3fv(vertices[c]);
		
		glColor3fv(colors[d]);
		glNormal3fv(normals[d]);
		glVertex3fv(vertices[d]);
	glEnd();
}

//! This method updates the viewport when the OpenGL Window is resized.
void myReshape(GLsizei w, GLsizei h)
{
	// Adjust clipping box
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-4.0, 4.0, -4.0, 4.0, -4.0, 4.0);
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

// When no event occurs the idle function is called
void idle (void)
{
	theta = theta + 0.01;
	display();
}

// This function is called when a pop-up menu is activated with the right button of the mouse.
void top_menu(int id)
{
	if(id == 1) exit(0);	
}


int main(int argc, char **argv)
{
	// Negotiating window section
	glutInit(&argc, argv);

	// Seting the window properties
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0,0);

	// Creating the OpenGL window
	glutCreateWindow("Color Cube");

	// Initializing graphics
	myinit();

	// Defining the callback functions
	glutDisplayFunc(display);  
	glutReshapeFunc(myReshape);
	glutIdleFunc(idle);

	// Creating a pop-up menu

	glutCreateMenu(top_menu);
	glutAddMenuEntry("Quit",1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// Entering the main event loop
	glutMainLoop();
}

