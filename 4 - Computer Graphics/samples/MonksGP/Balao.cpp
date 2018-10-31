#include "Objeto.h"
#include "Balao.h"
#include "uteis.h"

void Balao :: iniciarListas(){
	float tam = 4.75; // comprimento do balao
	float raio1 = 1.00;
	float raio2 = 1.50;
	float raio3 = 1.75;
	float raio4 = 1.90;
	float raio5 = 2.00;
	
	float fator = 0.70;
	
	float sen45 = 0.707710;
	float sen60 = 0.866025;
	float cos60 = 0.500000;
	float sen75 = 0.965925;
	float cos75 = 0.258819;
	float sen90 = 1.000000;
	float cos90 = 0.000000;
	
	glNewList(BALAO,GL_COMPILE);
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glColor3f(0.4,0.4,0.4);
		glBegin(GL_TRIANGLE_FAN);
            calculaNormal(0, tam, 0, raio1*sen90, tam - fator, raio1*cos90, raio1*sen75, tam - fator, raio1*cos75);
			glVertex3f(0, tam, 0);
		//glColor3f(0.6,0.6,0.6);
			glVertex3f(raio1*sen90, tam - fator, raio1*cos90);
			glVertex3f(raio1*sen75, tam - fator, raio1*cos75);
			glVertex3f(raio1*sen60, tam - fator, raio1*cos60);
			
			glVertex3f(raio1*sen45, tam - fator, raio1*sen45);
		
			glVertex3f(raio1*cos60, tam - fator, raio1*sen60);
			glVertex3f(raio1*cos75, tam - fator, raio1*sen75);
			glVertex3f(raio1*cos90, tam - fator, raio1*sen90);
			glVertex3f(-raio1*cos75, tam - fator, raio1*sen75);
			glVertex3f(-raio1*cos60, tam - fator, raio1*sen60);
			
			glVertex3f(-raio1*sen45, tam - fator, raio1*sen45);
			
			glVertex3f(-raio1*sen60, tam - fator, raio1*cos60);
			glVertex3f(-raio1*sen75, tam - fator, raio1*cos75);
			glVertex3f(-raio1*sen90, tam - fator, raio1*cos90);
		glEnd();
	
	/*--------------------------------------------------------------------------------------*/	
		
		glBegin(GL_QUAD_STRIP);
		//glColor3f(0.6,0.6,0.6);
            calculaNormal(raio2*sen90, tam - 2*fator, raio2*cos90, raio1*sen90, tam - fator, raio1*cos90, raio2*sen75, tam - 2*fator, raio2*cos75);
			glVertex3f(raio2*sen90, tam - 2*fator, raio2*cos90);
		//glColor3f(0.6,0.6,0.6);
			glVertex3f(raio1*sen90, tam - fator, raio1*cos90);
		//glColor3f(0.6,0.6,0.6);
            calculaNormal(raio2*sen75, tam - 2*fator, raio2*cos75, raio1*sen75, tam - fator, raio1*cos75, raio2*sen60, tam - 2*fator, raio2*cos60); 
			glVertex3f(raio2*sen75, tam - 2*fator, raio2*cos75);
		//glColor3f(0.6,0.6,0.6);
			glVertex3f(raio1*sen75, tam - fator, raio1*cos75);
		//glColor3f(0.6,0.6,0.6);
            calculaNormal(raio2*sen60, tam - 2*fator, raio2*cos60, raio1*sen60, tam - fator, raio1*cos60, raio2*sen45, tam - 2*fator, raio2*sen45);
			glVertex3f(raio2*sen60, tam - 2*fator, raio2*cos60);
		//glColor3f(0.6,0.6,0.6);
			glVertex3f(raio1*sen60, tam - fator, raio1*cos60);
            
            calculaNormal(raio2*sen45, tam - 2*fator, raio2*sen45, raio1*sen45, tam - fator, raio1*sen45, raio2*cos60, tam - 2*fator, raio2*sen60);			
		//glColor3f(0.6,0.6,0.6);
			glVertex3f(raio2*sen45, tam - 2*fator, raio2*sen45);
		//glColor3f(0.6,0.6,0.6);
			glVertex3f(raio1*sen45, tam - fator, raio1*sen45);
			calculaNormal(raio2*cos60, tam - 2*fator, raio2*sen60, raio1*cos60, tam - fator, raio1*sen60, raio2*cos75, tam - 2*fator, raio2*sen75);
		//glColor3f(0.6,0.6,0.6);
			glVertex3f(raio2*cos60, tam - 2*fator, raio2*sen60);
		//glColor3f(0.6,0.6,0.6);
			glVertex3f(raio1*cos60, tam - fator, raio1*sen60);
		    calculaNormal(raio2*cos75, tam - 2*fator, raio2*sen75, raio1*cos75, tam - fator, raio1*sen75, raio2*cos90, tam - 2*fator, raio2*sen90);
        //glColor3f(0.6,0.6,0.6);
			glVertex3f(raio2*cos75, tam - 2*fator, raio2*sen75);
		//glColor3f(0.6,0.6,0.6);
			glVertex3f(raio1*cos75, tam - fator, raio1*sen75);
			calculaNormal(raio2*cos90, tam - 2*fator, raio2*sen90, raio1*cos90, tam - fator, raio1*sen90, -raio2*cos75, tam - 2*fator, raio2*sen75);
		//glColor3f(0.6,0.6,0.6);
			glVertex3f(raio2*cos90, tam - 2*fator, raio2*sen90);
		//glColor3f(0.6,0.6,0.6);
			glVertex3f(raio1*cos90, tam - fator, raio1*sen90);
			calculaNormal(-raio2*cos75, tam - 2*fator, raio2*sen75, -raio1*cos75, tam - fator, raio1*sen75, -raio2*cos60, tam - 2*fator, raio2*sen60);
		//glColor3f(0.6,0.6,0.6);
			glVertex3f(-raio2*cos75, tam - 2*fator, raio2*sen75);
		//glColor3f(0.6,0.6,0.6);
			glVertex3f(-raio1*cos75, tam - fator, raio1*sen75);
			calculaNormal(-raio2*cos60, tam - 2*fator, raio2*sen60, -raio1*cos60, tam - fator, raio1*sen60, -raio2*sen45, tam - 2*fator, raio2*sen45);
		//glColor3f(0.6,0.6,0.6);
			glVertex3f(-raio2*cos60, tam - 2*fator, raio2*sen60);
		//glColor3f(0.6,0.6,0.6);
			glVertex3f(-raio1*cos60, tam - fator, raio1*sen60);
			
			calculaNormal(-raio2*sen45, tam - 2*fator, raio2*sen45, -raio1*sen45, tam - fator, raio1*sen45, -raio2*sen60, tam - 2*fator, raio2*cos60);
		//glColor3f(0.6,0.6,0.6);
			glVertex3f(-raio2*sen45, tam - 2*fator, raio2*sen45);
		//glColor3f(0.6,0.6,0.6);
			glVertex3f(-raio1*sen45, tam - fator, raio1*sen45);
			
			calculaNormal(-raio2*sen60, tam - 2*fator, raio2*cos60, -raio1*sen60, tam - fator, raio1*cos60, -raio2*sen75, tam - 2*fator, raio2*cos75);
		//glColor3f(0.6,0.6,0.6);
			glVertex3f(-raio2*sen60, tam - 2*fator, raio2*cos60);
		//glColor3f(0.6,0.6,0.6);
			glVertex3f(-raio1*sen60, tam - fator, raio1*cos60);
			calculaNormal(-raio2*sen75, tam - 2*fator, raio2*cos75, -raio1*sen75, tam - fator, raio1*cos75,  -raio2*sen90, tam - 2*fator, raio2*cos90);
		//glColor3f(0.6,0.6,0.6);
			glVertex3f(-raio2*sen75, tam - 2*fator, raio2*cos75);
		//glColor3f(0.6,0.6,0.6);
			glVertex3f(-raio1*sen75, tam - fator, raio1*cos75);
			calculaNormal(-raio1*sen75, tam - fator, raio1*cos75, -raio2*sen90, tam - 2*fator, raio2*cos90, -raio1*sen90, tam - fator, raio1*cos90);
		//glColor3f(0.6,0.6,0.6);
			glVertex3f(-raio2*sen90, tam - 2*fator, raio2*cos90);
		//glColor3f(0.6,0.6,0.6);
			glVertex3f(-raio1*sen90, tam - fator, raio1*cos90);
		glEnd();
				
	/*--------------------------------------------------------------------------------------*/
		
		glBegin(GL_QUAD_STRIP);
            calculaNormal(raio3*sen90, tam - 3*fator, raio3*cos90, raio2*sen90, tam - 2*fator, raio2*cos90, raio3*sen75, tam - 3*fator, raio3*cos75);
		//glColor3f(0.4,0.4,0.4);
			glVertex3f(raio3*sen90, tam - 3*fator, raio3*cos90);
			glVertex3f(raio2*sen90, tam - 2*fator, raio2*cos90);
            calculaNormal(raio3*sen75, tam - 3*fator, raio3*cos75, raio2*sen75, tam - 2*fator, raio2*cos75, raio3*sen60, tam - 3*fator, raio3*cos60);
			glVertex3f(raio3*sen75, tam - 3*fator, raio3*cos75);
			glVertex3f(raio2*sen75, tam - 2*fator, raio2*cos75);
			calculaNormal(raio3*sen60, tam - 3*fator, raio3*cos60, raio2*sen60, tam - 2*fator, raio2*cos60, raio3*sen45, tam - 3*fator, raio3*sen45);

			glVertex3f(raio3*sen60, tam - 3*fator, raio3*cos60);

			glVertex3f(raio2*sen60, tam - 2*fator, raio2*cos60);

		
			calculaNormal(raio3*sen45, tam - 3*fator, raio3*sen45, raio2*sen45, tam - 2*fator, raio2*sen45, raio3*cos60, tam - 3*fator, raio3*sen60);
			glVertex3f(raio3*sen45, tam - 3*fator, raio3*sen45);
			glVertex3f(raio2*sen45, tam - 2*fator, raio2*sen45);
		
			calculaNormal(raio3*cos60, tam - 3*fator, raio3*sen60, raio2*cos60, tam - 2*fator, raio2*sen60, raio3*cos75, tam - 3*fator, raio3*sen75);
			glVertex3f(raio3*cos60, tam - 3*fator, raio3*sen60);
			glVertex3f(raio2*cos60, tam - 2*fator, raio2*sen60);
		    calculaNormal(raio3*cos75, tam - 3*fator, raio3*sen75, raio2*cos75, tam - 2*fator, raio2*sen75, raio3*cos90, tam - 3*fator, raio3*sen90);
			glVertex3f(raio3*cos75, tam - 3*fator, raio3*sen75);
			glVertex3f(raio2*cos75, tam - 2*fator, raio2*sen75);
			calculaNormal(raio3*cos90, tam - 3*fator, raio3*sen90, raio2*cos90, tam - 2*fator, raio2*sen90, -raio3*cos75, tam - 3*fator, raio3*sen75);

			glVertex3f(raio3*cos90, tam - 3*fator, raio3*sen90);

			glVertex3f(raio2*cos90, tam - 2*fator, raio2*sen90);
			calculaNormal(-raio3*cos75, tam - 3*fator, raio3*sen75, -raio2*cos75, tam - 2*fator, raio2*sen75, -raio3*cos60, tam - 3*fator, raio3*sen60);

			glVertex3f(-raio3*cos75, tam - 3*fator, raio3*sen75);

			glVertex3f(-raio2*cos75, tam - 2*fator, raio2*sen75);
			calculaNormal(-raio3*cos60, tam - 3*fator, raio3*sen60, -raio2*cos60, tam - 2*fator, raio2*sen60, -raio3*sen45, tam - 3*fator, raio3*sen45);

			glVertex3f(-raio3*cos60, tam - 3*fator, raio3*sen60);
			glVertex3f(-raio2*cos60, tam - 2*fator, raio2*sen60);
			
			calculaNormal(-raio3*sen45, tam - 3*fator, raio3*sen45, -raio2*sen45, tam - 2*fator, raio2*sen45, -raio3*sen60, tam - 3*fator, raio3*cos60);
			glVertex3f(-raio3*sen45, tam - 3*fator, raio3*sen45);
			glVertex3f(-raio2*sen45, tam - 2*fator, raio2*sen45);
			
			calculaNormal(-raio3*sen60, tam - 3*fator, raio3*cos60, -raio2*sen60, tam - 2*fator, raio2*cos60, -raio3*sen75, tam - 3*fator, raio3*cos75);
			glVertex3f(-raio3*sen60, tam - 3*fator, raio3*cos60);
			glVertex3f(-raio2*sen60, tam - 2*fator, raio2*cos60);
			calculaNormal(-raio3*sen75, tam - 3*fator, raio3*cos75, -raio2*sen75, tam - 2*fator, raio2*cos75, -raio3*sen90, tam - 3*fator, raio3*cos90);
            glVertex3f(-raio3*sen75, tam - 3*fator, raio3*cos75);
			glVertex3f(-raio2*sen75, tam - 2*fator, raio2*cos75);
		    calculaNormal(-raio2*sen75, tam - 2*fator, raio2*cos75, -raio3*sen90, tam - 3*fator, raio3*cos90, -raio2*sen90, tam - 2*fator, raio2*cos90);
			glVertex3f(-raio3*sen90, tam - 3*fator, raio3*cos90);
			glVertex3f(-raio2*sen90, tam - 2*fator, raio2*cos90);
		glEnd();
				
	/*--------------------------------------------------------------------------------------*/
		
		glBegin(GL_QUAD_STRIP);
		//glColor3f(0.3,0.3,0.3);
		    calculaNormal(raio4*sen90, tam - 4*fator, raio4*cos90, raio3*sen90, tam - 3*fator, raio3*cos90, raio4*sen75, tam - 4*fator, raio4*cos75);
			glVertex3f(raio4*sen90, tam - 4*fator, raio4*cos90);
			glVertex3f(raio3*sen90, tam - 3*fator, raio3*cos90);
		    calculaNormal(raio4*sen75, tam - 4*fator, raio4*cos75, raio3*sen75, tam - 3*fator, raio3*cos75, raio4*sen60, tam - 4*fator, raio4*cos60);
			glVertex3f(raio4*sen75, tam - 4*fator, raio4*cos75);
			glVertex3f(raio3*sen75, tam - 3*fator, raio3*cos75);
		    calculaNormal(raio4*sen60, tam - 4*fator, raio4*cos60, raio3*sen60, tam - 3*fator, raio3*cos60, raio4*sen45, tam - 4*fator, raio4*sen45);
			glVertex3f(raio4*sen60, tam - 4*fator, raio4*cos60);
			glVertex3f(raio3*sen60, tam - 3*fator, raio3*cos60);
			
            calculaNormal(raio4*sen45, tam - 4*fator, raio4*sen45, raio3*sen45, tam - 3*fator, raio3*sen45, raio4*cos60, tam - 4*fator, raio4*sen60);
			glVertex3f(raio4*sen45, tam - 4*fator, raio4*sen45);
			glVertex3f(raio3*sen45, tam - 3*fator, raio3*sen45);
			calculaNormal(raio4*cos60, tam - 4*fator, raio4*sen60, raio3*cos60, tam - 3*fator, raio3*sen60, raio4*cos75, tam - 4*fator, raio4*sen75);
			glVertex3f(raio4*cos60, tam - 4*fator, raio4*sen60);
			glVertex3f(raio3*cos60, tam - 3*fator, raio3*sen60);
		    calculaNormal(raio4*cos75, tam - 4*fator, raio4*sen75, raio3*cos75, tam - 3*fator, raio3*sen75, raio4*cos90, tam - 4*fator, raio4*sen90);
			glVertex3f(raio4*cos75, tam - 4*fator, raio4*sen75);
			glVertex3f(raio3*cos75, tam - 3*fator, raio3*sen75);
			glVertex3f(raio4*cos90, tam - 4*fator, raio4*sen90);
		    calculaNormal(raio4*cos90, tam - 4*fator, raio4*sen90, -raio4*cos75, tam - 4*fator, raio4*sen75, -raio3*cos75, tam - 3*fator, raio3*sen75);
			glVertex3f(raio3*cos90, tam - 3*fator, raio3*sen90);
			glVertex3f(-raio4*cos75, tam - 4*fator, raio4*sen75);
  calculaNormal(-raio3*cos75, tam - 3*fator, raio3*sen75, -raio4*cos60, tam - 4*fator, raio4*sen60, -raio3*cos60, tam - 3*fator, raio3*sen60);
			glVertex3f(-raio3*cos75, tam - 3*fator, raio3*sen75);
			glVertex3f(-raio4*cos60, tam - 4*fator, raio4*sen60);
			glVertex3f(-raio3*cos60, tam - 3*fator, raio3*sen60);
		
			calculaNormal(-raio4*sen45, tam - 4*fator, raio4*sen45, -raio3*sen45, tam - 3*fator, raio3*sen45, -raio4*sen60, tam - 4*fator, raio4*cos60);
			glVertex3f(-raio4*sen45, tam - 4*fator, raio4*sen45);
			glVertex3f(-raio3*sen45, tam - 3*fator, raio3*sen45);
			
			calculaNormal(-raio4*sen60, tam - 4*fator, raio4*cos60, -raio3*sen60, tam - 3*fator, raio3*cos60, -raio4*sen75, tam - 4*fator, raio4*cos75);
			glVertex3f(-raio4*sen60, tam - 4*fator, raio4*cos60);
			glVertex3f(-raio3*sen60, tam - 3*fator, raio3*cos60);
        calculaNormal(-raio4*sen75, tam - 4*fator, raio4*cos75, -raio3*sen75, tam - 3*fator, raio3*cos75, -raio4*sen90, tam - 4*fator, raio4*cos90);
			glVertex3f(-raio4*sen75, tam - 4*fator, raio4*cos75);
			glVertex3f(-raio3*sen75, tam - 3*fator, raio3*cos75);
		    calculaNormal(-raio3*sen75, tam - 3*fator, raio3*cos75, -raio4*sen90, tam - 4*fator, raio4*cos90, -raio3*sen90, tam - 3*fator, raio3*cos90);
			glVertex3f(-raio4*sen90, tam - 4*fator, raio4*cos90);
			glVertex3f(-raio3*sen90, tam - 3*fator, raio3*cos90);
		glEnd();
		
	/*--------------------------------------------------------------------------------------*/
		
		glBegin(GL_QUAD_STRIP);
		//glColor3f(0.2,0.2,0.2);
		    calculaNormal(raio5*sen90, tam - 5*fator, raio5*cos90, raio4*sen90, tam - 4*fator, raio4*cos90, raio5*sen75, tam - 5*fator, raio5*cos75);
			glVertex3f(raio5*sen90, tam - 5*fator, raio5*cos90);
			glVertex3f(raio4*sen90, tam - 4*fator, raio4*cos90);
		    calculaNormal(raio5*sen75, tam - 5*fator, raio5*cos75, raio4*sen75, tam - 4*fator, raio4*cos75, raio5*sen60, tam - 5*fator, raio5*cos60);
			glVertex3f(raio5*sen75, tam - 5*fator, raio5*cos75);
			glVertex3f(raio4*sen75, tam - 4*fator, raio4*cos75);
		    calculaNormal(raio5*sen60, tam - 5*fator, raio5*cos60, raio4*sen60, tam - 4*fator, raio4*cos60, raio5*sen45, tam - 5*fator, raio5*sen45);
			glVertex3f(raio5*sen60, tam - 5*fator, raio5*cos60);
			glVertex3f(raio4*sen60, tam - 4*fator, raio4*cos60);
			calculaNormal(raio5*sen45, tam - 5*fator, raio5*sen45, raio4*sen45, tam - 4*fator, raio4*sen45, raio5*cos60, tam - 5*fator, raio5*sen60);
			glVertex3f(raio5*sen45, tam - 5*fator, raio5*sen45);
			glVertex3f(raio4*sen45, tam - 4*fator, raio4*sen45);
			
			calculaNormal(raio5*cos60, tam - 5*fator, raio5*sen60, raio4*cos60, tam - 4*fator, raio4*sen60, raio5*cos75, tam - 5*fator, raio5*sen75);
			glVertex3f(raio5*cos60, tam - 5*fator, raio5*sen60);
			glVertex3f(raio4*cos60, tam - 4*fator, raio4*sen60);
		    calculaNormal(raio5*cos75, tam - 5*fator, raio5*sen75, raio4*cos75, tam - 4*fator, raio4*sen75, raio5*cos90, tam - 5*fator, raio5*sen90);
			glVertex3f(raio5*cos75, tam - 5*fator, raio5*sen75);
			glVertex3f(raio4*cos75, tam - 4*fator, raio4*sen75);
        calculaNormal(raio5*cos90, tam - 5*fator, raio5*sen90, raio4*cos90, tam - 4*fator, raio4*sen90, -raio5*cos75, tam - 5*fator, raio5*sen75);
			glVertex3f(raio5*cos90, tam - 5*fator, raio5*sen90);
			glVertex3f(raio4*cos90, tam - 4*fator, raio4*sen90);
		    calculaNormal(-raio5*cos75, tam - 5*fator, raio5*sen75, -raio4*cos75, tam - 4*fator, raio4*sen75, -raio5*cos60, tam - 5*fator, raio5*sen60);
			glVertex3f(-raio5*cos75, tam - 5*fator, raio5*sen75);
			glVertex3f(-raio4*cos75, tam - 4*fator, raio4*sen75);
		    calculaNormal(-raio5*cos60, tam - 5*fator, raio5*sen60, -raio4*cos60, tam - 4*fator, raio4*sen60, -raio5*sen45, tam - 5*fator, raio5*sen45);
			glVertex3f(-raio5*cos60, tam - 5*fator, raio5*sen60);
			glVertex3f(-raio4*cos60, tam - 4*fator, raio4*sen60);
			
			calculaNormal(-raio5*sen45, tam - 5*fator, raio5*sen45, -raio4*sen45, tam - 4*fator, raio4*sen45, -raio5*sen60, tam - 5*fator, raio5*cos60);
			glVertex3f(-raio5*sen45, tam - 5*fator, raio5*sen45);
			glVertex3f(-raio4*sen45, tam - 4*fator, raio4*sen45);
			
			calculaNormal(-raio5*sen60, tam - 5*fator, raio5*cos60, -raio4*sen60, tam - 4*fator, raio4*cos60, -raio5*sen75, tam - 5*fator, raio5*cos75);
			glVertex3f(-raio5*sen60, tam - 5*fator, raio5*cos60);
			glVertex3f(-raio4*sen60, tam - 4*fator, raio4*cos60);
		    calculaNormal(-raio5*sen75, tam - 5*fator, raio5*cos75, -raio4*sen75, tam - 4*fator, raio4*cos75, -raio5*sen90, tam - 5*fator, raio5*cos90);
			glVertex3f(-raio5*sen75, tam - 5*fator, raio5*cos75);
			glVertex3f(-raio4*sen75, tam - 4*fator, raio4*cos75);
		    calculaNormal(-raio4*sen75, tam - 4*fator, raio4*cos75, -raio5*sen90, tam - 5*fator, raio5*cos90, -raio4*sen90, tam - 4*fator, raio4*cos90);

			glVertex3f(-raio5*sen90, tam - 5*fator, raio5*cos90);

			glVertex3f(-raio4*sen90, tam - 4*fator, raio4*cos90);
		glEnd();
		
	/*--------------------------------------------------------------------------------------*/
		glBegin(GL_QUAD_STRIP);
		//glColor3f(0.1,0.1,0.1);
		    calculaNormal(raio5*sen90, 0, raio5*cos90,raio5*sen90, tam - 5*fator, raio5*cos90, raio5*sen75, 0, raio5*cos75 );
			glVertex3f(raio5*sen90, 0, raio5*cos90);
			glVertex3f(raio5*sen90, tam - 5*fator, raio5*cos90);
		    calculaNormal(raio5*sen75, 0, raio5*cos75, raio5*sen75, tam - 5*fator, raio5*cos75, raio5*sen60, 0, raio5*cos60);
			glVertex3f(raio5*sen75, 0, raio5*cos75);
			glVertex3f(raio5*sen75, tam - 5*fator, raio5*cos75);
		    calculaNormal(raio5*sen60, 0, raio5*cos60, raio5*sen60, tam - 5*fator, raio5*cos60, raio5*sen45, 0, raio5*sen45);
			glVertex3f(raio5*sen60, 0, raio5*cos60);
			glVertex3f(raio5*sen60, tam - 5*fator, raio5*cos60);
			calculaNormal(raio5*sen45, 0, raio5*sen45, raio5*sen45, tam - 5*fator, raio5*sen45, raio5*cos60, 0, raio5*sen60);
			glVertex3f(raio5*sen45, 0, raio5*sen45);
			glVertex3f(raio5*sen45, tam - 5*fator, raio5*sen45);
			
			calculaNormal(raio5*cos60, 0, raio5*sen60, raio5*cos60, tam - 5*fator, raio5*sen60, raio5*cos75, 0, raio5*sen75);
			glVertex3f(raio5*cos60, 0, raio5*sen60);

			glVertex3f(raio5*cos60, tam - 5*fator, raio5*sen60);

		    calculaNormal(raio5*cos75, 0, raio5*sen75, raio5*cos75, tam - 5*fator, raio5*sen75, raio5*cos90, 0, raio5*sen90);
			glVertex3f(raio5*cos75, 0, raio5*sen75);

			glVertex3f(raio5*cos75, tam - 5*fator, raio5*sen75);

		    calculaNormal(raio5*cos90, 0, raio5*sen90, raio5*cos90, tam - 5*fator, raio5*sen90, -raio5*cos75, 0, raio5*sen75);
			glVertex3f(raio5*cos90, 0, raio5*sen90);

			glVertex3f(raio5*cos90, tam - 5*fator, raio5*sen90);

        calculaNormal(-raio5*cos75, 0, raio5*sen75, -raio5*cos75, tam - 5*fator, raio5*sen75, -raio5*cos60, 0, raio5*sen60);
			glVertex3f(-raio5*cos75, 0, raio5*sen75);
	
			glVertex3f(-raio5*cos75, tam - 5*fator, raio5*sen75);

		    calculaNormal(-raio5*cos60, 0, raio5*sen60, -raio5*cos60, tam - 5*fator, raio5*sen60, -raio5*sen45, 0, raio5*sen45);
			glVertex3f(-raio5*cos60, 0, raio5*sen60);
	
			glVertex3f(-raio5*cos60, tam - 5*fator, raio5*sen60);
	
			
			calculaNormal(-raio5*sen45, 0, raio5*sen45, -raio5*sen45, tam - 5*fator, raio5*sen45, -raio5*sen60, 0, raio5*cos60);
			glVertex3f(-raio5*sen45, 0, raio5*sen45);

			glVertex3f(-raio5*sen45, tam - 5*fator, raio5*sen45);

			
			calculaNormal(-raio5*sen60, 0, raio5*cos60, -raio5*sen60, tam - 5*fator, raio5*cos60, -raio5*sen75, 0, raio5*cos75);
			glVertex3f(-raio5*sen60, 0, raio5*cos60);

			glVertex3f(-raio5*sen60, tam - 5*fator, raio5*cos60);

		    calculaNormal(-raio5*sen75, 0, raio5*cos75, -raio5*sen75, tam - 5*fator, raio5*cos75, -raio5*sen90, 0, raio5*cos90);
			glVertex3f(-raio5*sen75, 0, raio5*cos75);

			glVertex3f(-raio5*sen75, tam - 5*fator, raio5*cos75);
		    calculaNormal(-raio5*sen75, tam - 5*fator, raio5*cos75, -raio5*sen90, 0, raio5*cos90, -raio5*sen90, tam - 5*fator, raio5*cos90);

			glVertex3f(-raio5*sen90, 0, raio5*cos90);

			glVertex3f(-raio5*sen90, tam - 5*fator, raio5*cos90);
		glEnd();
		
	/*--------------------------------------------------------------------------------------*/
		
		glPopAttrib();
	glEndList();
	
}

void Balao :: draw(){
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();
	glCallList(BALAO);
	glPushMatrix();
		glScalef(1,1,-1);
		glCallList(BALAO);
	glPopMatrix();
	glPushMatrix();
		glScalef(1,-1,1);
		glCallList(BALAO);
	glPopMatrix();
	glPushMatrix();
		glScalef(1,-1,-1);
		glCallList(BALAO);
	glPopMatrix();
	glPushMatrix();
		glColor3f(0.2,0.2,0.2);
		glTranslatef(0, 0, -2);
		glScalef(0.75, 2.25, 1);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
		//glColor3f(0.4,0.4,0.4);
		glTranslatef(0, -3.5, 0);
		glScalef(0.05, 0.8, 1);
		glutSolidCube(3);
	glPopMatrix();
	glPushMatrix();
		//glColor3f(0.4,0.4,0.4);
		glRotatef(90,0,1,0);
		glTranslatef(0, -3.5, 0);
		glScalef(0.05, 0.8, 1);
		glutSolidCube(3);
	glPopMatrix();
	glPopMatrix();
	glPopAttrib();
}

Balao :: Balao(){
	iniciarListas();
}
