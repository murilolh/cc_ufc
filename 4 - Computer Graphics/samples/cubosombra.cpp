//#include <windows.h>		// Standard header for Windows
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

// Globals
GLsizei wh = 500, ww = 500; // Initial window size
float theta;
float dx, dy, dz, speed;
float rx = 0.0, ry = 0.0, rz = 0.0;
float tx = 0.0, ty = 0.0, tz = 0.0;
int button, up_or_down;
GLfloat vertices[8][3] = {	{-1.0, 1.0, 1.0}, { 1.0, 1.0, 1.0},
							{ 1.0, 1.0,-1.0}, {-1.0, 1.0,-1.0},
							{-1.0,-1.0, 1.0}, { 1.0,-1.0, 1.0},
							{ 1.0,-1.0,-1.0}, {-1.0,-1.0,-1.0}};
GLfloat normals[8][3] = {	{-1.0, 1.0, 1.0}, { 1.0, 1.0, 1.0},
							{ 1.0, 1.0,-1.0}, {-1.0, 1.0,-1.0},
							{-1.0,-1.0, 1.0}, { 1.0,-1.0, 1.0},
							{ 1.0,-1.0,-1.0}, {-1.0,-1.0,-1.0}};
GLfloat colors[8][3] = {	{0.0,  0.0, 0.0}, {1.0, 0.0, 0.0},
							{1.0,  1.0, 0.0}, {0.0, 1.0, 0.0},
							{0.0,  0.0, 1.0}, {1.0, 0.0, 1.0},
							{ 1.0, 1.0, 1.0}, {0.0, 1.0, 1.0}};
GLfloat PointLight[3] = { 5.0, 10.0, 1.0 };
GLfloat MShadow[16];

void colorcube(void);
void colorcubeshadow(void);
void display(void);
void quads(int a, int b, int c, int d);
void quad(int a, int b, int c, int d);

void myinit(void) 
{
	int i;

	// Initialize Shadow projection matrix
	for (i =0; i < 16; i++)
	{
		MShadow[i]	= 0.0;		
	};
	MShadow[0]	=   PointLight[1];
	MShadow[4]	= - PointLight[0];;
	MShadow[6]	= - PointLight[2];;
	MShadow[7]	= - 1.0;
	MShadow[10]	=   PointLight[1];
	MShadow[15]	=   PointLight[1];
	
	// Set viewing conditions
	glViewport(0, 0, ww, wh);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-8.0, 8.0, -8.0, 8.0, -6.0, 15.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

   	// Clear Background with black 
	glClearColor (0.8, 0.8, 0.8, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

void myReshape(GLsizei w, GLsizei h)
{
	// Adjust clipping box
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-8.0, 8.0, -8.0, 8.0, -6.0, 15.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Adjust viewport and clear
	glViewport(0,0, w, h);
	glClearColor (0.8, 0.8, 0.8, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	display();
	glFlush();

	// Set global size for use by the drawing routine

	ww = w;
	wh = h;
}

void display(void)
{
	glClearColor (0.8, 0.8, 0.8, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	gluLookAt(0.0, 7.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glPushMatrix();

	glTranslatef(0.0, 4.0, 0.0);

	glTranslatef(tx, ty, tz);

	// Rotate the cube

	glRotatef(theta, rx, ry, 0);

	colorcube();

	glPopMatrix();

	glMultMatrixf(MShadow);
 
	glTranslatef(0.0, 4.0, 0.0);
 
	glTranslatef(tx, ty, tz);

	// Rotate the cube

	glRotatef(theta, rx, ry, 0);

	glColor3f (0.0, 0.0, 0.0);

	colorcubeshadow();

	glutSwapBuffers();
}

void colorcube(void)
{
	// Draw faces of the cube 
	quad(6, 2, 1, 5);
	quad(3, 0, 1, 2);
	quad(5, 1, 0, 4);
	quad(4, 0, 3, 7);
	quad(6, 5, 4, 7);
	quad(7, 3, 2, 6);

	glBegin(GL_LINES);
		glColor3f (1.0, 0.0, 0.0	);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(2.0, 0.0, 0.0);

		glColor3f (1.0, 1.0, 0.0	);
		glVertex3f(0.0, 1.0, 1.0);
		glVertex3f(2.0, 1.0, 1.0);


		glColor3f (0.0, 1.0, 0.0	);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 2.0, 0.0);

		glColor3f (0.0, 1.0, 1.0	);
		glVertex3f(1.0, 0.0, 1.0);
		glVertex3f(1.0, 2.0, 1.0);


		glColor3f (0.0, 0.0, 1.0	);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 2.0);

		glColor3f (1.0, 0.0, 1.0	);
		glVertex3f(1.0, 1.0, 0.0);
		glVertex3f(1.0, 1.0, 2.0);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
		glColor3f (1.0, 0.0, 0.0	);
		glVertex3f(2.0, 0.0, 0.0);
		glVertex3f(1.7, 0.5, 0.0);
		glVertex3f(1.7, 0.0, 0.5);
		glVertex3f(1.7,-0.5, 0.0);
		glVertex3f(1.7, 0.0,-0.5);
		glVertex3f(1.7, 0.5, 0.0);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
		glColor3f (0.0, 1.0, 0.0	);
		glVertex3f(0.0, 2.0, 0.0);
		glVertex3f(0.0, 1.7, 0.5);
		glVertex3f(0.5, 1.7, 0.0);
		glVertex3f(0.0, 1.7,-0.5);
		glVertex3f(-0.5, 1.7,0.0);
		glVertex3f(0.0, 1.7, 0.5);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
		glColor3f (0.0, 0.0, 1.0	);
		glVertex3f(0.0, 0.0, 2.0);
		glVertex3f(0.5, 0.0, 1.7);
		glVertex3f(0.0, 0.5, 1.7);
		glVertex3f(-0.5, 0.0, 1.7);
		glVertex3f(0.0,-0.5, 1.7);
		glVertex3f(0.5, 0.0, 1.7);
	glEnd();

	glFlush();
}

void colorcubeshadow(void)
{
	// Draw faces of the cube 
	quads(6, 2, 1, 5);
	quads(3, 0, 1, 2);
	quads(5, 1, 0, 4);
	quads(4, 0, 3, 7);
	quads(6, 5, 4, 7);
	quads(7, 3, 2, 6);

	glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(2.0, 0.0, 0.0);

		glVertex3f(0.0, 1.0, 1.0);
		glVertex3f(2.0, 1.0, 1.0);


		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 2.0, 0.0);

		glVertex3f(1.0, 0.0, 1.0);
		glVertex3f(1.0, 2.0, 1.0);


		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 2.0);

		glVertex3f(1.0, 1.0, 0.0);
		glVertex3f(1.0, 1.0, 2.0);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(2.0, 0.0, 0.0);
		glVertex3f(1.7, 0.5, 0.0);
		glVertex3f(1.7, 0.0, 0.5);
		glVertex3f(1.7,-0.5, 0.0);
		glVertex3f(1.7, 0.0,-0.5);
		glVertex3f(1.7, 0.5, 0.0);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0.0, 2.0, 0.0);
		glVertex3f(0.0, 1.7, 0.5);
		glVertex3f(0.5, 1.7, 0.0);
		glVertex3f(0.0, 1.7,-0.5);
		glVertex3f(-0.5, 1.7,0.0);
		glVertex3f(0.0, 1.7, 0.5);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0.0, 0.0, 2.0);
		glVertex3f(0.5, 0.0, 1.7);
		glVertex3f(0.0, 0.5, 1.7);
		glVertex3f(-0.5, 0.0, 1.7);
		glVertex3f(0.0,-0.5, 1.7);
		glVertex3f(0.5, 0.0, 1.7);
	glEnd();

	glFlush();
}


void quad(int a, int b, int c, int d)
{
	// Draw the face connecting points a, b, c, and d
	glBegin(GL_QUADS);
		glColor3fv	(colors[a]	);
		glNormal3fv	(normals[a]	);
		glVertex3fv	(vertices[a]);

		glColor3fv	(colors[b]	);
		glNormal3fv	(normals[b]	);
		glVertex3fv	(vertices[b]);

		glColor3fv	(colors[c]	);
		glNormal3fv	(normals[c]	);
		glVertex3fv	(vertices[c]);

		glColor3fv	(colors[d]	);
		glNormal3fv	(normals[d]	);
		glVertex3fv	(vertices[d]);
	glEnd();
}

void quads(int a, int b, int c, int d)
{
	// Draw the face connecting points a, b, c, and d
	glBegin(GL_QUADS);
		glVertex3fv	(vertices[a]);
		glVertex3fv	(vertices[b]);
		glVertex3fv	(vertices[c]);
		glVertex3fv	(vertices[d]);
	glEnd();
}

void mousebtn (int btn, int state, int x, int y)
{
	button = btn;
	up_or_down = state;
} 


void mouse (int x, int y)
{
	float d1, d2;

	dx = (float)(x - ww/2)/((float)(ww/2));
	dy = (float)(wh/2 - y)/((float)(wh/2));
	dz = 0.;

	speed = 0;
	
	if (button == GLUT_LEFT_BUTTON)		
	{
		rx = dx;
		ry = dy;
		rz = 0.;
		speed = (float) sqrt(dx*dx + dy*dy);

	}
	if (button == GLUT_MIDDLE_BUTTON)	
	{
		if (dx >= 0)
		{  
			d1 = (float)(x - ww/2);
			d2 = (float)(wh/2 - y);
			tz = sqrt(d1*d1 + d2*d2)*0.01;

		}
		else
		{
			d1 = (float)(x - ww/2);
			d2 = (float)(wh/2 - y);
			tz = -sqrt(d1*d1 + d2*d2)*0.01;
		}
	}
	if (button == GLUT_RIGHT_BUTTON)
	{
		tx = (float)(x - ww/2)*0.01;
		ty = (float)(wh/2 - y)*0.01;
		tz = 0.0;

	}

} 

void moveCube(void)
{ 
	theta += 2*speed;
	if(theta > 360.0) theta -=360.0;

	glutPostRedisplay();
}

void keyboard(unsigned char key, int mousex, int mousey)
{
	if(key=='q' || key =='Q') exit(0);
}



int main(int argc, char **argv)
{
	// Negotiating window section
	glutInit(&argc, argv);

	// Seting the window properties
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0,0);

	// Creating the OpenGL window
	glutCreateWindow("Quadrado giratÛrio");

	// Initializing graphics
	myinit();

	// Defining the callback functions
	glutKeyboardFunc(keyboard);
	glutReshapeFunc	(myReshape);
	glutIdleFunc	(moveCube);
	glutMouseFunc	(mousebtn);
	glutMotionFunc	(mouse);
	glutDisplayFunc	(display);

	// Entering the main event loop
	glutMainLoop();
}