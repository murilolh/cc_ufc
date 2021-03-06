#include <GL/glut.h>
#include <stdlib.h>

GLsizei wh = 500, ww = 500; 
GLfloat xm=0, ym=0, xmm=0, ymm=0;
GLint   first;

void myinit(void) 
{
	glViewport(0, 0, ww, wh);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1.0, 0.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_COLOR_LOGIC_OP);	
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);	
}

void move(int x, int y)
{
        glLogicOp(GL_XOR);
	if(first == 1)
	{
		glBegin(GL_LINES);
			glVertex2f(xm, ym);
			glVertex2f(xmm, ymm);
		glEnd();
		glFlush();
	}        
	xmm = (GLfloat)x/ww;
	ymm = (GLfloat)(wh - y)/wh;
	glBegin(GL_LINES);
		glVertex2f(xm, ym);
		glVertex2f(xmm, ymm);
	glEnd();
	glFlush();
	first = 1;
        glLogicOp(GL_COPY);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void mouse (int btn, int state, int x, int y)
{
        glColor3f(0.0, 1.0, 0.0);
	if (btn == GLUT_LEFT_BUTTON		&& 	state == GLUT_DOWN) 
	{                
		xm = (GLfloat)x/ww;
		ym = (GLfloat)(wh - y)/wh;		
		first = 0;	 
	}
	else if (btn == GLUT_LEFT_BUTTON		&& 	state == GLUT_UP) 
	{
		xmm = (GLfloat)x/ww;
		ymm = (GLfloat)(wh - y)/wh;
		glBegin(GL_LINES);
			glVertex2f(xm, ym);
			glVertex2f(xmm, ymm);
		glEnd();
		glFlush();
	}	
} 

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0,0);
        glutCreateWindow("Desenhando Rubberband Lines");
        myinit();
	glutDisplayFunc(display);  
	glutMouseFunc(mouse);
	glutMotionFunc(move);		
	glutMainLoop();	
}
