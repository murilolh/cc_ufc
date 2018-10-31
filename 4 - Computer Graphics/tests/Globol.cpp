#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <math.h>
#define CARRO 1
#define RODA 2
#define ARO 3
#define CARRO3D 4


int i=0;
int l=0;
int z=1;
int k=2880;

void resize2D(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //define que a projecao vai ser ortografica, ou seja, nao perspectiva
    glOrtho(-ar, ar, -1.0, 1.0, -1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

void init(void)
{
   glClearColor(1,1,1,1);
   glEnable(GL_DEPTH_TEST);
   //glDepthRange(1, 0);  // The default z mapping
   //glDepthFunc(GL_LESS);
}

void sierpinski()
{
     
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.2, 10.2, -10.2, 10.2, -10.2, 10.2);
	glMatrixMode(GL_MODELVIEW);
    
    glNewList(RODA, GL_COMPILE);
        glBegin(GL_POLYGON);
        for(int j=0;j<100;j++)
            glVertex2d(cos(6.283158*j/100),sin(6.283158*j/100));
        glEnd();
    glEndList();
    
    glNewList(ARO, GL_COMPILE);
        glColor3d(0.7,0.7,0.7);
        for(int n=0;n<3;n++)
        {
            glPushMatrix();
            glRotated(n*120,0,0,1);
            glBegin(GL_POLYGON);
                glVertex2d(0,0.07);
                glVertex2d(0.29,0.07);
                glVertex2d(0.25,-0.07);
                glVertex2d(-0.07,0);
            glEnd();
            glPopMatrix();
        }
        glColor3d(1,1,1);
        glPushMatrix();
            glScaled(0.28,0.28,0);
            glCallList(RODA);
        glPopMatrix();
        glColor3d(0,0,0);
        glPushMatrix();
            glScaled(0.38,0.38,0);
            glCallList(RODA);
        glPopMatrix();
        glColor3d(1,1,1);
        glPushMatrix();
            glScaled(0.4,0.4,0);
            glCallList(RODA);
        glPopMatrix();
        
       
        glEndList();
    
    glNewList(CARRO, GL_COMPILE);
        glColor3d(0,0,0);
        for(int m=0;m<50;m=m+5)
        {
            glPushMatrix();
                glTranslated(-1.3,-0.5,0);
                glScaled(0.4,0.4,0);
                glBegin(GL_LINE_STRIP);
                for(int m=0;m<50;m++)
                    glVertex2d(cos(3.14156*m/50),sin(3.14156*m/50));
                glEnd();
            glPopMatrix();
            glPushMatrix();
                glTranslated(1.3,-0.5,0);
                glScaled(0.4,0.4,0);
                glBegin(GL_LINE_STRIP);
                for(int m=0;m<50;m++)
                    glVertex2d(cos(3.14156*m/50),sin(3.14156*m/50));
                glEnd();
            glPopMatrix();
        }
        glPushMatrix();
            glTranslated(1.3,-0.5,0);
            glRotated(l,0,0,1);
            glCallList(ARO);
        glPopMatrix();
        glPushMatrix();
            glTranslated(-1.3,-0.5,0);
            glRotated(l,0,0,1);
            glCallList(ARO);
        glPopMatrix();
        l=l+5;
        if(l>360)
            l=0;
        glColor3d(0,0,0);
        glBegin(GL_POLYGON);
            glVertex2d(-0.39,0.74);
            glVertex2d(-0.9,0.29);
            glVertex2d(0.25,0.29);
            glVertex2d(0.25,0.74);
        glEnd();
        glBegin(GL_POLYGON);
            glVertex2d(0.30,0.74);
            glVertex2d(0.30,0.29);
            glVertex2d(1.45,0.29);
            glVertex2d(0.99,0.74);
        glEnd();
        glColor3d(0,0.38,0);
        glBegin(GL_POLYGON);
            glVertex2d(2,-0.5);
            glVertex2d(2,0.29);
            glVertex2d(1.5,0.29);
            glVertex2d(1,0.79);
            glVertex2d(-0.4,0.79);
            glVertex2d(-0.95,0.3);
            glVertex2d(-1.65,0.23);
            glVertex2d(-1.9,0);
            glVertex2d(-2,-0.5);
        glEnd();
    glEndList();
    
    glNewList(CARRO3D, GL_COMPILE);
        glPushMatrix();
            glTranslated(0,0,1.25);
            glCallList(CARRO);
        glPopMatrix();
        glPushMatrix();
            glTranslated(0,0,-1.25);
            glCallList(CARRO);
        glPopMatrix();
    
        glColor3d(0,0,0);
        glBegin(GL_POLYGON);
            glVertex3d(1.5,0.28,1.25);
            glVertex3d(1,0.79,1.25);
            glVertex3d(1,0.79,-1.25);
            glVertex3d(1.5,0.28,-1.25);
        glEnd();
        glBegin(GL_POLYGON);
            glVertex3d(-0.5,0.79,1.25);
            glVertex3d(-1,0.36,1.25);
            glVertex3d(-1,0.36,-1.25);
            glVertex3d(-0.5,0.79,-1.25);
        glEnd();
        
        glColor3d(0,0.38,0);
        glBegin(GL_POLYGON);
            glVertex3d(2,-0.5,1.25);
            glVertex3d(2,0.28,1.25);
            glVertex3d(2,0.28,-1.25);
            glVertex3d(2,-0.5,-1.25);
        glEnd();
        glBegin(GL_POLYGON);
            glVertex3d(1.5,0.28,1.25);
            glVertex3d(1.5,0.28,-1.25);
            glVertex3d(2,0.28,-1.25);
            glVertex3d(2,0.28,1.25);
        glEnd();
        glBegin(GL_POLYGON);
            glVertex3d(1,0.79,1.25);
            glVertex3d(1,0.79,-1.25);
            glVertex3d(-0.5,0.79,-1.25);
            glVertex3d(-0.5,0.79,1.25);
        glEnd();
        glBegin(GL_POLYGON);
            glVertex3d(-1.5,0.28,1.25);
            glVertex3d(-1,0.36,1.25);
            glVertex3d(-1,0.36,-1.25);
            glVertex3d(-1.5,0.28,-1.25);
        glEnd();
        glBegin(GL_POLYGON);
            glVertex3d(-1.5,0.28,1.25);
            glVertex3d(-1.9,-0.07,1.25);
            glVertex3d(-1.9,-0.07,-1.25);
            glVertex3d(-1.5,0.28,-1.25);
        glEnd();
        glBegin(GL_POLYGON);
            glVertex3d(-1.9,-0.07,1.25);
            glVertex3d(-2,-0.5,1.25);
            glVertex3d(-2,-0.5,-1.25);
            glVertex3d(-1.9,-0.07,-1.25);
        glEnd(); 

        glColor3d(0.4,0.2,0.2);
        glBegin(GL_POLYGON);
            glVertex3d(2,-0.5,1.25);
            glVertex3d(-2,-0.5,1.25);
            glVertex3d(-2,-0.5,-1.25);
            glVertex3d(2,-0.5,-1.25);
        glEnd();
    glEndList();
    
    glColor3d(0.5,0.5,0.5);
    glPushMatrix();
        glRotated(80,1,0,0);
        glutWireSphere(10,20,20);
    glPopMatrix();
    glPushMatrix();   
        glRotated(135,0,1,0);
        glRotated(k*z/4,0,0,1);
        glTranslated(9,0,0);
        glRotated(90,0,0,1);
        glCallList(CARRO3D);
    glPopMatrix();
    k--;
    if(k<0)
        k=2880;
    glutSwapBuffers();
}

void key3D(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27:
		    exit(0);
        break;
        case '+':
		    z++;
	    break;
        case '-':
	   		if(z>1) z--;
	    break;
    }
	glutPostRedisplay();
}

void idle3D(void)
{
    glutPostRedisplay();
}

int main(int argc,char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(1024,1024);
    glutInitWindowPosition(0,0);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Esfera");
    init();
    glutReshapeFunc(resize2D);
    glutDisplayFunc(sierpinski);
    glutKeyboardFunc(key3D);
    glutIdleFunc(idle3D);
    glutMainLoop();
    return EXIT_SUCCESS;
}
