#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

#define CAR 1
#define TIRE 2 

static float rot = 90;    //Rotação do carro
static float rod = 0;     //Rotação das rodas
static float a= 0;        //Ângulo de translação
static float v = 0.1;       //Controla a velocidade do carro
static float t = 1;       //Controla o raio do globo
static float r = 700/t;   //Raio de translação
static float d = 0.15*t;  //Distância entre as rodas

void myinit(void)
{
    float r = 50;
    float xc = 0, yc = 0;

    glClearColor(0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-800.0, 800.0, -800.0, 800.0,-800.0,800.0);
    glMatrixMode(GL_MODELVIEW);
  
    glNewList(TIRE,GL_COMPILE);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glBegin(GL_LINE_LOOP);
		for(float i = 0; i < 6.2830; i+= 3.1415/12)
			glVertex2f(xc + cos(i)*r,yc + sin(i)*r);
	glEnd();
	glBegin(GL_LINES);
		glVertex2f(xc, yc);
		glVertex2f(xc + cos(0.523)*r,yc + sin(0.523)*r);
		glVertex2f(xc, yc);							
		glVertex2f(xc + cos(2.617)*r,yc + sin(2.617)*r);
		glVertex2f(xc, yc);
		glVertex2f(xc + cos(4.712)*r,yc + sin(4.712)*r);						
	glEnd();
	glPopAttrib();					
    glEndList();
		
    glNewList(CAR,GL_COMPILE);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glBegin(GL_LINE_STRIP);
	        glVertex2f( -160.00,  0.00);
		glVertex2f( -180.00,  0.00);
		glVertex2f( -180.00, 80.00);
		glVertex2f( -105.00, 80.00);
		glVertex2f(  -40.00,130.00);
		glVertex2f(   40.00,130.00);
		glVertex2f(  105.00, 80.00);
		glVertex2f(  180.00, 80.00);
		glVertex2f(  180.00,  0.00);
		glVertex2f(  160.00,  0.00);
	glEnd();
	glBegin(GL_LINES);
                glVertex2f(   50.00,  0.00);
	        glVertex2f(  -50.00,  0.00);
		glVertex2f(   30.00, 80.00);
		glVertex2f(   40.00,100.00);
		glVertex2f( -105.00, 80.00);
		glVertex2f(  105.00, 80.00);
		glVertex2f(    0.00,  0.00);
		glVertex2f(    0.00,130.00);
	glEnd();
	glPopAttrib();
    glEndList();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glColor3f(0.0, 1.0, 0.0);
				
    glPushMatrix();
        glTranslatef((r*cos(a)), (r*sin(a)), 0);
        glRotatef(rot, 0, 0, 1);
        glCallList(CAR);
    glPopMatrix();		
		
    glPushMatrix();
        glTranslatef((r*cos(a + d)), (r*sin(a + d)), 0);
        glRotatef(-rod, 0, 0, 1);
        glCallList(TIRE);
    glPopMatrix();

    glPushMatrix();
        glTranslatef((r*cos(a - d)), (r*sin(a - d)), 0);		
        glRotatef(-rod, 0, 0, 1);
        glCallList(TIRE);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.6, 0.6, 0.6);	 
        glRotatef(90,1,0,0);
        glutWireSphere(r+50,8,25);
    glPopMatrix();

    rod += 10*v;//Controla a rotação das rodas
    rot += 3.75*v;
    a += (3.141528/48)*v;    

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
	case 'q':
		exit(0);
	break;
	case '+':
		v += 0.05;
	break;
	case '-':
		if (v>0.05) v -= 0.05;
	break;	
    }
    glutPostRedisplay();
}

void idle3D(void)
{
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize(600,600);
    glutInitWindowPosition(300, 0);    
    glutCreateWindow("CARRO");
    myinit();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle3D);    
    glutMainLoop();
}

