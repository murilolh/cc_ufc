// Program to draw a colored sphere

#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define X 0.525731112119133606
#define Z 0.850650808352039932
#define NV 4	// Number of Vertices
#define NF 4	// Number of Faces
#define DEPTH 6	// Depth of recursion

bool NormalPerVertex = true;	// The shading must be computed considering the normal of surface at each vertex
GLsizei wh = 500, ww = 500;		// Initial window size
GLfloat  theta = 0.0;

void subdivide(float *v1, float *v2, float *v3, long depth, int nfv);

//! This method draws the scene.
void Display(void)
{
	// Array of vertex coordinates of a regular thetrahedron embeded in a unit sphere
	
	GLfloat vdata[4][3] = {	{0.0000, -0.3333, -0.9428}, { -0.8165, -0.3333,  0.4714}, { 0.8165, -0.3333,  0.4714}, {0.0000, 1.0, 0.0000}};

	// Array of face connectivities of a regular thetrahedron embeded in a unit sphere. Connectivity input in clockwise sequence.
	GLint tindices[4][3] = {{0,   3,   1}, {1,   3,   2}, {2,   3,   0}, {1,   2,   0}};

/*
	// Array of vertex coordinates
	GLfloat vdata[12][3] = {	{-X, 0.0,  Z}, { X, 0.0,  Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},
								{0.0, Z,   X}, {0.0, Z,  -X}, {0.0,-Z,   X}, {0.0,-Z, -X},
								{Z,   X, 0.0}, {-Z,  X, 0.0}, {Z,  -X, 0.0}, {-Z, -X, 0.0}};

	// Array of face connectivities
	GLint tindices[20][3] = {	{0,   4,   1}, {0,   9,   4}, {9,   5,   4}, {4,   5,   8}, {4,   8,   1},
								{8,  10,   1}, {8,   3,  10}, {5,   3,   8}, {5,   2,   3}, {2,   7,   3},
								{7,  10,   3}, {7,   6,  10}, {7,  11,   6}, {11,  0,   6}, {0,   1,   6},
								{6,   1,  10}, {9,   0,  11}, {9,  11,   2}, {9,   2,   5}, {7,   2,  11}};
*/
		  

	// Coefficients of reflexion (ksr, ksg, ksb), (kdr, kdg, kdb), (kar, kag, kab) of the faces
	GLfloat mat_specular[]   = {0.63, 0.56, 0.37, 1.0};
	GLfloat mat_diffuse[]    = {0.75, 0.61, 0.23, 1.0};
	GLfloat mat_ambient[]    = {0.25, 0.20, 0.07, 1.0};						
	
	// Exponent representing the shininess of the surface
	GLfloat mat_shininess[]  = {100.0};
	
	// Intensities (R, G, B) of the ambient, difuse and specular lights
	GLfloat light_ambient[]  = {0.3, 0.3, 0.3, 1.0};
	GLfloat light_diffuse[]  = {0.9, 0.9, 0.9, 1.0};
	GLfloat light_specular[] = {0.9, 0.9, 0.9, 1.0};

	// Position of the point light source
	GLfloat light_position[] = {0.0, 10.0, 80.0, 1.0};
	int		i;

	glClearColor (0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	//glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);

	if (NormalPerVertex == false)
	{
 
		for (i=0; i < NF; i++)
		{
			// Drawing faces with one normal vector per face
			subdivide(	&vdata[tindices[i][0]][0],
						&vdata[tindices[i][1]][0],
						&vdata[tindices[i][2]][0], DEPTH, 0);
		
			glFlush();

		};
	}
	else
	{					
		for (i=0; i < NF; i++)
		{
	
			//Drawing faces with one normal vector per vertex
			subdivide(	&vdata[tindices[i][0]][0],
						&vdata[tindices[i][1]][0],
						&vdata[tindices[i][2]][0], DEPTH, 1);
			
			glFlush();
		};
	}
		
}

void normalize(float v[3])
{
	GLfloat d = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
	
	if (d == 0.0)
	{
		//error("zero length vector");
		return;
	}
	v[0] /= d; 
	v[1] /= d;
	v[2] /= d;
}

void normcrossprod(float v1[3], float v2[3], float out[3])
{
	out[0] = v1[1]*v2[2] - v1[2]*v2[1];
	out[1] = v1[2]*v2[0] - v1[0]*v2[2];
	out[2] = v1[0]*v2[1] - v1[1]*v2[0];
	normalize(out);
}


void drawtriangle(float *v1, float *v2, float *v3, int nfv)
{
	
	float d1[3], d2[3];
	float norm[3];
	int   j;

	if (nfv == 0)
	{

		// Drawing faces with one normal vector per face
		for (j=0; j<3; j++)
		{
			d1[j] = v1[j] - v2[j]; 
			d2[j] = v3[j] - v2[j]; 
		};
		normcrossprod(d1, d2, norm);
		glNormal3fv(norm);
		glBegin(GL_POLYGON); 
			glVertex3fv(v1);
			glVertex3fv(v2);
			glVertex3fv(v3);
		glEnd();
	}
	else
	{
		glBegin(GL_POLYGON); 
			glNormal3fv(v1);
			glVertex3fv(v1);
			glNormal3fv(v2);
			glVertex3fv(v2);
			glNormal3fv(v3);
			glVertex3fv(v3);
		glEnd();
	}
	
}

void subdivide(float *v1, float *v2, float *v3, long depth, int nfv)
{
	GLfloat v12[3], v23[3], v31[3];
	GLint i;

	if (depth == 0)
	{
		drawtriangle(v1, v2, v3, nfv);
		return;
	}
	else
	{
		for (i = 0; i < 3; i++)
		{
			v12[i] = v1[i] + v2[i];
			v23[i] = v2[i] + v3[i];
			v31[i] = v3[i] + v1[i];
		}
		normalize(v12);
		normalize(v23);
		normalize(v31);
		subdivide(v1,  v12, v31, depth-1, nfv);
		subdivide(v2,  v23, v12, depth-1, nfv);
		subdivide(v3,  v31, v23, depth-1, nfv);
		subdivide(v12, v23, v31, depth-1, nfv);
	}
}

//! Initialization of all OpenGL specific parameters.
void myinit(void)
{
	glClearColor	(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
	
	glEnable		(GL_LIGHTING);
	glEnable		(GL_LIGHT0);
	glDepthFunc		(GL_LEQUAL);
	glEnable		(GL_DEPTH_TEST);
	glPolygonMode	(GL_FRONT, GL_FILL);

	glMatrixMode	(GL_MODELVIEW);
	glLoadIdentity	();

//	glShadeModel	(GL_FLAT);
}

//! This method updates the viewport when the OpenGL Window is resized.
void myReshape(GLsizei w, GLsizei h)
{
	// Adjust clipping box
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Adjust viewport and clear
	if (w >= h)
	{
		glViewport  ((w-h)/2, 0, h, h);
	}
	else 
	{
		glViewport  (0, (h-w)/2, w, w);
	}
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear     (GL_COLOR_BUFFER_BIT);
	Display();
	glFlush();

	// Set global size for use by the drawing routine
	ww = w;
	wh = h;
}

// When no event occurs the idle function is called
void idle (void)
{
	GLfloat light_position[] = {0.0, 0.0, 80.0, 1.0};
	
	theta = theta + 0.0001;
	light_position[0] = 80.0*cos(theta);
	light_position[2] = 80.0*sin(theta);
	
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	Display();
	glutSwapBuffers();
}

// This function is called when a pop-up menu is activated with the right button of the mouse.
void top_menu(int id)
{
	if (id == 1) exit(0);	
	if (id == 2) 
	{
		NormalPerVertex = true;
		Display();
		glutSwapBuffers();
	}
	if (id == 3) 
	{
		NormalPerVertex = false;
		Display();
		glutSwapBuffers();
	}
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
	glutCreateWindow("Sphere");

	// Initializing graphics
	myinit();

	// Defining the callback functions
	glutDisplayFunc(Display);  
	glutReshapeFunc(myReshape);
	glutIdleFunc(idle);

	// Creating a pop-up menu

	glutCreateMenu(top_menu);
	glutAddMenuEntry("Quit",1);
	glutAddMenuEntry("Normal Per Vertex",2);
	glutAddMenuEntry("Normal Per Face",3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// Entering the main event loop
	glutMainLoop();
}
