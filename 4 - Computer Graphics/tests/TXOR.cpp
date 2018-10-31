#include <GL/glut.h>
#include <stdlib.h>

GLsizei wh = 500, ww = 500; 
GLfloat xm=0, ym=0, xmm=0, ymm=0, xn=0, yn=0;
GLint   first;
GLint   count;

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
   if(count==2)
   {        
	if(first == 1)
	{
		glBegin(GL_LINE_STRIP);
			glVertex2f(xm, ym);
			glVertex2f(xn, yn);
			glVertex2f(xmm, ymm); 
		glEnd();
		glutSwapBuffers();
	}        
	xn = (GLfloat)x/ww;
	yn = (GLfloat)(wh - y)/wh;
	glBegin(GL_LINE_STRIP);
			glVertex2f(xm, ym);
			glVertex2f(xn, yn);
			glVertex2f(xmm, ymm); 
		glEnd();
	glutSwapBuffers();
	first = 1;
        glLogicOp(GL_COPY);
   }
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}

void mouse (int btn, int state, int x, int y)
{
        glColor3f(0.0, 1.0, 0.0);
	if (btn == GLUT_LEFT_BUTTON		&& 	state == GLUT_DOWN) 
	{   
	   if(count==0)   
	   {          
		  xm = (GLfloat)x/ww;
		  ym = (GLfloat)(wh - y)/wh;	  
		  count++;
		}	 
	   else if (count==1) 
	   {
		  xmm = (GLfloat)x/ww;
		  ymm = (GLfloat)(wh - y)/wh;
		  glBegin(GL_LINES);
			glVertex2f(xm, ym);
			glVertex2f(xmm, ymm);
		  glEnd();
		  glutSwapBuffers();
		  count++;
		  first = 0;
	   }	
	 }
	 else if (btn == GLUT_LEFT_BUTTON		&& 	state == GLUT_UP) 
    {
       if(count==2)
       {
       xn = (GLfloat)x/ww;
	    yn = (GLfloat)(wh - y)/wh;
	    glBegin(GL_LINE_STRIP);
			glVertex2f(xm, ym);
			glVertex2f(xn, yn);
			glVertex2f(xmm, ymm); 
		glEnd();
	    glutSwapBuffers();
	    count=0;
	    }
    }
} 

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0,0);
        glutCreateWindow("Desenhando Rubberband Lines");
        myinit();
	glutDisplayFunc(display);  
	glutMouseFunc(mouse);
	glutMotionFunc(move);		
	glutMainLoop();	
}
