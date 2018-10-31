//#include <windows.h>		// Standard header for Windows
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <math.h>

#define BOX 1
#define CAR 2
#define TIRE 3 

void myinit(void) 
{
	float r = 50;
	float xc = 0, yc = 0;

	/* Background to be cleared to black */
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_FLAT);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);

	// Definition of the BOX display list

	glNewList(BOX, GL_COMPILE);
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glBegin(GL_POLYGON);
			glColor3f(1.0, 0.0, 0.0);
			glVertex2f(-1.0, -1.0);
			glVertex2f( 1.0, -1.0);
			glVertex2f( 1.0,  1.0);
			glVertex2f(-1.0,  1.0);
		glEnd();
		glPopAttrib();
	glEndList();
	
	// Definition of the TIRE display list
	
	glNewList(TIRE,GL_COMPILE);
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glBegin(GL_LINE_LOOP);
			for(float i = 0; i < 6.2830; i+= 3.1415/12)
			{
				glVertex2f(xc + cos(i)*r,yc + sin(i)*r);
			}
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
				
	// Definition of the CAR display list
				
	glNewList(CAR,GL_COMPILE);
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glBegin(GL_LINE_LOOP);
			glVertex2f(-180.00, 0.00);
			glVertex2f(-180.00, 80.00);
			glVertex2f(-105.00, 80.00);
			glVertex2f( -40.00,130.00);
			glVertex2f(   0.00,130.00);
			glVertex2f(  40.00,130.00);
			glVertex2f( 105.00, 80.00);
			glVertex2f( 180.00, 80.00);
			glVertex2f( 180.00,  0.00);
			glVertex2f( 160.00,  0.00);
			glVertex2f( 155.81, 21.05);
			glVertex2f( 143.89, 38.89);
			glVertex2f( 126.05, 50.81);
			glVertex2f( 105.00, 55.00);
			glVertex2f(  83.95, 50.81);
			glVertex2f(  66.11, 38.89);
			glVertex2f(  54.19, 21.05);
			glVertex2f(  50.00,  0.00);
			glVertex2f(   0.00,  0.00);
			glVertex2f( -50.00,  0.00);
			glVertex2f( -54.19, 21.05);
			glVertex2f( -66.11, 38.89);
			glVertex2f( -83.95, 50.81);
			glVertex2f(-105.00, 55.00);
			glVertex2f(-126.05, 50.81);
			glVertex2f(-143.89, 38.89);
			glVertex2f(-155.81, 21.05);
			glVertex2f(-160.00,  0.00);
		glEnd();
		glBegin(GL_LINES);
			glVertex2f(   30.00, 80.00);
			glVertex2f(   40.00,100.00);
			glVertex2f( -105.00, 80.00);
			glVertex2f(  105.00, 80.00);
			glVertex2f(    0.00,  0.00);
			glVertex2f(    0.00,130.00);
		glEnd();
		glTranslatef(105.0,0.0,0.0);
		glCallList(TIRE);
		glTranslatef(-210.0,0.0,0.0);
		glCallList(TIRE);
		glPopAttrib();
	glEndList();

}


/*void animate(void)
{
	int j=1;

	glColor3f(1.0, 0.0, 1.0);

	while (j > 0)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		
 		for (int i=1; i < 5; i++)
		{
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				gluOrtho2D(-2.0*i, 2.0*i, -2.0*i, 2.0*i);

				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				
				if(i==1)
					glViewport(50,150,100,100);
				if(i==2)
					glViewport(150,50,100,100);
				if(i==3)
					glViewport(250,150,100,100);
				if(i==4)
					glViewport(150,250,100,100);
				glBegin(GL_LINE_LOOP);
					glVertex2f(-1.9*i, -1.9*i);
					glVertex2f( 1.9*i, -1.9*i);
					glVertex2f( 1.9*i,  1.9*i);
					glVertex2f(-1.9*i,  1.9*i);
				glEnd();

				glRotatef(j*0.25,0., 0., 1.);
				glCallList(BOX);	
				//glFlush();	
		}
		glutSwapBuffers();

		j++;
	}

}*/



/*void animate(void)
{
	int j=1;

	glColor3f(1.0, 0.0, 1.0);

	while (j > 0)
	{

		glClear(GL_COLOR_BUFFER_BIT);

 		for (int i=1; i < 5; i++)
		{
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				gluOrtho2D(-2.0*i, 2.0*i, -2.0*i, 2.0*i);

				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				glViewport((i-1)*100, (i-1)*100,  100, 100);

				glBegin(GL_LINE_LOOP);
					glVertex2f(-1.95*i, -1.95*i);
					glVertex2f( 1.95*i, -1.95*i);
					glVertex2f( 1.95*i,  1.95*i);
					glVertex2f(-1.95*i,  1.95*i);
				glEnd();

				glRotatef(j*0.5,0., 0., 1.);
				glCallList(BOX);		
		}

		glutSwapBuffers();

		j++;
	}

}*/


/*
void animate(void)
{
	int j=1;

	glColor3f(0.0, 0.0, 1.0);

	while (j > 0)
	{

		glClear(GL_COLOR_BUFFER_BIT);

 		for (int i=1; i < 5; i++)
		{
			for (int k=1; k < 5; k++)
			{
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				if (k%2 == 0)
				{
					gluOrtho2D(-2.0*i, 2.0*i, -2.0*i, 2.0*i);
				}
				else
				{
					gluOrtho2D(-2.0*(5-i), 2.0*(5-i), -2.0*(5-i), 2.0*(5-i));
				}

				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				glViewport((k-1)*100, (i-1)*100,  100, 100);

				if (k%2 == 0)
				{
					glBegin(GL_LINE_LOOP);
						glVertex2f(-1.9*i, -1.9*i);
						glVertex2f( 1.9*i, -1.9*i);
						glVertex2f( 1.9*i,  1.9*i);
						glVertex2f(-1.9*i,  1.9*i);
					glEnd();
				}
				else
				{
					glBegin(GL_LINE_LOOP);
						glVertex2f(-1.9*(5-i), -1.9*(5-i));
						glVertex2f( 1.9*(5-i), -1.9*(5-i));
						glVertex2f( 1.9*(5-i),  1.9*(5-i));
						glVertex2f(-1.9*(5-i),  1.9*(5-i));
					glEnd();
				}

				glRotatef(j*0.5,0., 0., 1.);
				glCallList(BOX);	
			}
		}

		glutSwapBuffers();

		j++;
	}

} */



void animate(void)
{
	int j=1.0;
	float t, ti, dt, rot;
	
	glClear(GL_COLOR_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-800, 800, -800, 800);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

				
	glColor3f(1.0, 0.0, 0.0);
				
	//glCallList(CAR);
	//glFlush();
	
	//glutSwapBuffers();
	
	dt = 0.5;
	ti = -800.0;
	rot = 0.;
	
	//int i = 25.0;
				
	while (j > 0)
	{

		glClear(GL_COLOR_BUFFER_BIT);

		glLoadIdentity();
				

		/*glBegin(GL_LINE_LOOP);
			glVertex2f(-2.0*i, -2.0*i);
			glVertex2f( 2.0*i, -2.0*i);
			glVertex2f( 2.0*i,  2.0*i);
			glVertex2f(-2.0*i,  2.0*i);
		glEnd();*/

        t = ti + j*dt;
		
		if (t > 800.00 || t < -800.0) 
		{
			dt = -dt;
			ti = -ti;
			j = 1;
			if (t >  800.00) rot = 180.;
			if (t < -800.00) rot = 0.;
			rot = -rot;
		}

		glTranslatef(t, 0., 0.);
		glRotatef(rot,0.,1.,0.);
		glCallList(CAR);
		//glFlush();

		glutSwapBuffers();

		j++;
	}

}


void display(void)
{
	
	glColor3f(1.0, 0.0, 1.0);
	
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i=1; i < 5; i++)
	{
		glViewport((i-1)*100,((i-1)%2)*100,100,100);
		//glClear(GL_COLOR_BUFFER_BIT);

		glColor3f(0.2*i, 0.0, 1.0);
		glLoadIdentity();

		glBegin(GL_LINE_LOOP);
			glVertex2f(-1.9, -1.9);
			glVertex2f( 1.9, -1.9);
			glVertex2f( 1.9,  1.9);
			glVertex2f(-1.9,  1.9);
		glEnd();

		glRotatef(i*30.0,0., 0., 1.);
		glCallList(BOX);	
		glFlush();	
	}
	
	glutSwapBuffers();

} 


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(0,0);
	glutCreateWindow("BOX Display List");
	myinit();
	//glutIdleFunc(animate);
	//glutDisplayFunc(display);
	glutDisplayFunc(animate);
	glutMainLoop();
	
	return 0;
}
