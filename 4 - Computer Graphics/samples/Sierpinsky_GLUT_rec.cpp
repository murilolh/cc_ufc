//#include <windows.h>		// Standard header for Windows
#include <GLUT/glut.h>
#include <OpenGL/gl.h>

typedef GLfloat point2[2];
int wId1, wId2;
GLsizei wh = 500, ww = 500; // Initial window size
GLfloat size = 3.0;			// 1/2 of the side length of square

void myinit(void) 
{
	/* Background to be cleared to black */
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_FLAT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void triangle(point2 a, point2 b, point2 c)
{
	glBegin(GL_TRIANGLES); 
		glVertex2fv(a);
		glVertex2fv(b);
		glVertex2fv(c);
	glEnd();
}

void divide_triangle(point2 a, point2 b, point2 c, int k)
{
	point2 ab, ac, bc;
	int    j;

	if(k > 0)
	{
		// Compute midpoints of the sides

		for(j=0; j < 2; j++) ab[j] = (a[j] + b[j])/2.0;
		for(j=0; j < 2; j++) ac[j] = (a[j] + c[j])/2.0;
		for(j=0; j < 2; j++) bc[j] = (b[j] + c[j])/2.0;

		// Subdivide all but inner triangle

		divide_triangle(a, ab, ac, k-1);
		divide_triangle(c, ac, bc, k-1);
		divide_triangle(b, bc, ab, k-1);

	}
	else
	{
		// Draw triangle at end of recursion

		triangle(a, b, c);
	}
}

void display(void)
{

	point2 vertices[3] = {{0.0, 0.0},{250.0, 500.0},{500.0, 0.0}};

		
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f (1.0, 1.0, 1.0);
	glBegin(GL_LINES);
		glVertex2i(  0, 250);
		glVertex2i(500, 250);
		glVertex2i(250,   0);
		glVertex2i(250, 500);
	glEnd();

	glColor3f (1.0, 0.0, 0.0);
 	glViewport(0, 0, 250, 250);
	divide_triangle(vertices[0], vertices[1], vertices[2], 4);
	glPushMatrix();
		glTranslatef(150.0, 190.0, 0.0);
		glScalef(0.38, 0.4, 1.0);
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, 'C');
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, 'r');
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, 'e');
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, 't');
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, 'o');
	glPopMatrix();


	glColor3f (1.0, 1.0, 0.0);
 	glViewport(250, 0, 250, 250);
	divide_triangle(vertices[0], vertices[1], vertices[2], 4);
	glPushMatrix();
		glTranslatef(190.0, 190.0, 0.0);
		glScalef(0.38, 0.4, 1.0);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, 'C');
		glutStrokeCharacter(GLUT_STROKE_ROMAN, 'r');
		glutStrokeCharacter(GLUT_STROKE_ROMAN, 'e');
		glutStrokeCharacter(GLUT_STROKE_ROMAN, 't');
		glutStrokeCharacter(GLUT_STROKE_ROMAN, 'o');
	glPopMatrix();

	glColor3f (1.0, 0.0, 1.0);
 	glViewport(0, 250, 250, 250);
	divide_triangle(vertices[0], vertices[1], vertices[2], 4);
	glPushMatrix();
		glTranslatef(150.0, 190.0, 0.0);
		glScalef(0.38, 0.4, 1.0);
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, 'C');
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, 'r');
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, 'e');
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, 't');
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, 'o');
	glPopMatrix();

	glColor3f (0.0, 1.0, 1.0);
 	glViewport(250, 250, 250, 250);
	divide_triangle(vertices[0], vertices[1], vertices[2], 4);
	glPushMatrix();
		glTranslatef(190.0, 190.0, 0.0);
		glScalef(0.38, 0.4, 1.0);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, 'C');
		glutStrokeCharacter(GLUT_STROKE_ROMAN, 'r');
		glutStrokeCharacter(GLUT_STROKE_ROMAN, 'e');
		glutStrokeCharacter(GLUT_STROKE_ROMAN, 't');
		glutStrokeCharacter(GLUT_STROKE_ROMAN, 'o');
	glPopMatrix();

	glColor3f (1.0, 1.0, 1.0);
	glViewport(0, 0, 500, 500);
	glBegin(GL_LINES);
		glVertex2i(  0, 250);
		glVertex2i(500, 250);
		glVertex2i(250,   0);
		glVertex2i(250, 500);
	glEnd();

	glColor3f (1.0, 0.0, 0.0);


	glRasterPos2i(200, 230);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'C');
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'r');
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'e');
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 't');
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'o');

	glColor3f (1.0, 0.0, 1.0);

	glRasterPos2i(200, 480);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'C');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 't');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'o');
		
	glColor3f (0.0, 1.0, 1.0);

	glRasterPos2i(450, 480);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 'C');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 'r');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 't');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 'o');
		
	glColor3f (1.0, 1.0, 0.0);

	glRasterPos2i(450, 230);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'C');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 't');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');	


	glFlush();

}

void display2(void)
{

	point2 vertices[3] = {{0.0, 0.0},{250.0, 500.0},{500.0, 0.0}};

		
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
 
	glColor3f (0.0, 1.0, 1.0);
	divide_triangle(vertices[0], vertices[1], vertices[2], 4);
	glPushMatrix();
		glTranslatef(190.0, 190.0, 0.0);
		glScalef(0.38, 0.4, 1.0);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, 'C');
		glutStrokeCharacter(GLUT_STROKE_ROMAN, 'r');
		glutStrokeCharacter(GLUT_STROKE_ROMAN, 'e');
		glutStrokeCharacter(GLUT_STROKE_ROMAN, 't');
		glutStrokeCharacter(GLUT_STROKE_ROMAN, 'o');
	glPopMatrix();

	glColor3f (1.0, 0.0, 0.0);

	glRasterPos2i(0, 480);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'C');
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'r');
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'e');
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 't');
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'o');

	glColor3f (1.0, 0.0, 1.0);

	glRasterPos2i(460, 480);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'C');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 't');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'o');
		
	glColor3f (0.0, 1.0, 1.0);

	glRasterPos2i(460, 10);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 'C');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 'r');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 't');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 'o');
		
	glColor3f (1.0, 1.0, 0.0);

	glRasterPos2i(10, 10);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'C');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 't');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');	


	glFlush();

}

void drawSquare(int x, int y)
{
	y = wh - y;
	glColor3ub((char) rand()%256, (char) rand()%256, (char) rand()%256);

	glBegin(GL_POLYGON);
		glVertex2f(x + size, y + size);
		glVertex2f(x - size, y + size);
		glVertex2f(x - size, y - size);
		glVertex2f(x + size, y - size);
	glEnd();
	glFlush();
}

void mouse1 (int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON	&& 	state == GLUT_DOWN) exit(0);

} 

void mouse2 (int btn, int state, int x, int y)
{
	if (btn == GLUT_RIGHT_BUTTON	&& 	state == GLUT_DOWN) exit(0);
	if (btn == GLUT_LEFT_BUTTON		&& 	state == GLUT_DOWN) drawSquare(x, y);
} 


void main(int argc, char **argv)
{

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0,0);

	wId1=glutCreateWindow("Sierpinski Gasket");	
	glutSetWindow(wId1);
		myinit();
		glutDisplayFunc(display);
		glutMouseFunc(mouse1);

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(500,0);

	wId2=glutCreateWindow("Sierpinski Gasket 2");
	glutSetWindow(wId2);
		myinit();
		glutDisplayFunc(display2);
		glutMouseFunc(mouse2);


	glutMainLoop();
}
