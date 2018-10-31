#include "Objeto.h"
#include "carregabmp.h"
#include "Pista.h"
#include "uteis.h"
#include <stdio.h>

		//GLfloat PistaAmbient[] = {1.6, 1.6, 1.6, 1.0};
		GLfloat PistaAmbient[] = {2.2, 2.2, 2.2, 1.0};
		GLfloat PistaSpecular[] = {0.2, 0.2, 0.2, 1.0}; 
		GLfloat PistaDiffuse[] = {0.8, 0.8, 0.8, 1.0}; 
		GLfloat PistaShininess = 10.0;

		GLfloat MuroAmbient[] = {0.3, 0.3, 0.3, 1.0};
		GLfloat MuroSpecular[] = {0.3, 0.3, 0.3, 1.0}; 
		GLfloat MuroDiffuse[] = {0.8, 0.8, 0.8, 1.0}; 
		GLfloat MuroShininess = 100.0;
		

GLuint torcida;




void Pista :: calcularSenoCos(){
	float i;
	int k = 0;
	
	for(i = 0; i < 2.094 ; i += 0.196){
		seno[k] = sin(i);
		coseno[k] = cos(i);
		k++;
	}
	
	for(; i < 3.1415 ; i += 0.196){
		seno[k] = sin(i);
		coseno[k] = cos(i);
		k++;
	}
}

void Pista :: iniciarListas(){
	float i;
	int l = 0;
	
	double grande = 2;

	glMaterialfv(GL_FRONT, GL_SPECULAR, PistaSpecular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, PistaAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, PistaDiffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, PistaShininess);
			
	glNewList(CURVA, GL_COMPILE);
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glBegin(GL_QUAD_STRIP);
			calculaNormal(0.0, 22.0, 0.157, 0.0, 2.0, 0.0, 300.0, 22.0, 0.157);
			
			glColor3f(0.1, 0.1, 0.1);
			glVertex3f(0.0, 22.0, 0.157);
			glColor3f(0.25, 0.25, 0.25);
			glVertex3f(0.0, 2.0, 0.0);
			
			glColor3f(0.1, 0.1, 0.1);
			glVertex3f(300.0, 22.0, 0.157);
			glColor3f(0.25, 0.25, 0.25);
			glVertex3f(300.0, 2.0, 0.0);
			
			calculaNormal(300.0, 22.0, 0.157,300.0, 2.0, 0.0, 310.0, 22.0, 2.387);
			
			glColor3f(0.1, 0.1, 0.1);
			glVertex3f(310.0, 22.0, 2.387);
			glColor3f(0.25, 0.25, 0.25);
			glVertex3f(310.0, 2.0, 0.0);
			
			
			calculaNormal(310.0, 22.0, 2.387, 310.0, 2.0, 0.0, 320 + 272*seno[0], 272*coseno[0] - 250, 4.617);
			
			for(l = 0; l < 10; l++){
				glColor3f(0.1, 0.1, 0.1);
				glVertex3f(320 + 272*seno[l], 272*coseno[l] - 250, 4.617);
				glColor3f(0.25, 0.25, 0.25);
				glVertex3f(320 + 252*seno[l], 252*coseno[l] - 250, 0.0);
				if(l < 9)
					calculaNormal(320 + 272*seno[l], 272*coseno[l] - 250, 4.617, 320 + 252*seno[l], 252*coseno[l] - 250, 0.0, 320 + 272*seno[l + 1], 272*coseno[l + 1] - 250, 4.617);	
			}
			
			calculaNormal(320 + 272*seno[10], 272*coseno[10] - 250, 4.617, 320 + 252*seno[10], 252*coseno[10] - 250, 0.0, 673*seno[11], 673*coseno[11], 3.888);
			
			for(l = 11; l < 17; l++){
				glColor3f(0.1, 0.1, 0.1);
				glVertex3f(673*seno[l], 673*coseno[l], 3.888);
				glColor3f(0.25, 0.25, 0.25);
				glVertex3f(653*seno[l], 653*coseno[l], 0.0);
				if(l < 16)
					calculaNormal(673*seno[l], 673*coseno[l], 3.888, 653*seno[l], 653*coseno[l], 0.0, 673*seno[l + 1], 673*coseno[l + 1], 3.888);
			}
			
			calculaNormal(673*seno[17], 673*coseno[17], 3.888, 653*seno[17], 653*coseno[17], 0.0, 0.0, -673.0, 3.888);
						
			glColor3f(0.1, 0.1, 0.1);
			glVertex3f(0.0, -673.0, 3.888);
			glColor3f(0.25, 0.25, 0.25);
			glVertex3f(0.0, -653.0, 0.0);
		glEnd();
		glPopAttrib();
	glEndList();

/*------------------------------------------------------------------------------------------*/
	
	glNewList(POSTE, GL_COMPILE);
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glPushMatrix();
			glColor3f(0.1, 0.1, 0.1);
			glTranslatef(0, 0, 5);
			glScalef(0.2, 0.2, 10);
			glutSolidCube(1);
		glPopMatrix();
		glPopAttrib();
	glEndList();

/*------------------------------------------------------------------------------------------*/

	glMaterialfv(GL_FRONT, GL_SPECULAR, MuroSpecular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, MuroAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MuroDiffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, MuroShininess);


	glNewList(MURO, GL_COMPILE);
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glColor3f(0.5, 0.5, 0.5);
		// parte superior do muro
		glBegin(GL_QUAD_STRIP);
			// reta oposta
			
			calculaNormal(0.0, 26.0, grande + 0.657 , 0.0, 22.0, grande + 0.657, 300.0, 26.0, grande + 0.657);
						
			glVertex3f(0.0, 26.0, grande + 0.657); // externo
			glVertex3f(0.0, 22.0, grande + 0.657); // interno
			
			calculaNormal(300.0, 26.0, grande + 0.657, 300.0, 22.0, grande + 0.657, 310.0, 26.0, grande + 2.887);
			
			glVertex3f(300.0, 26.0, grande + 0.657); // externo
			glVertex3f(300.0, 22.0, grande + 0.657); // interno
			
			calculaNormal(310.0, 26.0, grande + 2.887, 310.0, 22.0, grande + 2.887, 320 + 276*seno[0], 276*coseno[0] - 250, grande + 5.117);
			
			// inicia a inclinacao para a curva
			glVertex3f(310.0, 26.0, grande + 2.887); // externo
			glVertex3f(310.0, 22.0, grande + 2.887); // interno
			
			// curva menor => maior inclinacao
			for(l = 0; l < 10; l++){
				glVertex3f(320 + 276*seno[l], 276*coseno[l] - 250, grande + 5.117); // externo
				glVertex3f(320 + 272*seno[l], 272*coseno[l] - 250, grande + 5.117); // interno
				if(l < 9)
					calculaNormal(320 + 276*seno[l], 276*coseno[l] - 250, grande + 5.117, 320 + 272*seno[l], 272*coseno[l] - 250, grande + 5.117, 320 + 276*seno[l + 1], 276*coseno[l + 1] - 250, grande + 5.117);
			}
			
			calculaNormal(320 + 276*seno[10], 276*coseno[10] - 250, grande + 5.117, 320 + 272*seno[10], 272*coseno[10] - 250, grande + 5.117, 677*seno[11], 677*coseno[11], grande + 4.388);
						
			// curva maior => menor inclinacao
			for(l = 11; l < 17; l++){
				glVertex3f(677*seno[l], 677*coseno[l], grande + 4.388); // externo
				glVertex3f(673*seno[l], 673*coseno[l], grande + 4.388); // interno
				if(l < 16)
					calculaNormal(677*seno[l], 677*coseno[l], grande + 4.388, 673*seno[l], 673*coseno[l], grande + 4.388, 677*seno[l + 1], 677*coseno[l + 1], grande + 4.388);
			}
			
			calculaNormal(677*seno[17], 677*coseno[17], grande + 4.388, 673*seno[17], 673*coseno[17], grande + 4.388, 0.0, -677.0, grande+4.388);
			
			// linha de chegada
			glVertex3f(0.0, -677.0, grande+4.388); // externo
			glVertex3f(0.0, -673.0, grande+4.388); // interno
		glEnd();

		// lateral externa
		glBegin(GL_QUAD_STRIP);
			glColor3f(0.3, 0.3, 0.3);
			// reta oposta
			glVertex3f(0.0, 26.0, grande+0.657); // externo
			glVertex3f(0.0, 26.0, 0.0); // interno
			
			glVertex3f(300.0, 26.0, grande+0.657); // externo
			glVertex3f(300.0, 26.0, 0.0); // interno
			
			// inicia a inclinacao para a curva
			glVertex3f(310.0, 26.0, grande+2.887); // externo
			glVertex3f(310.0, 26.0, 0.0); // interno
			
			// curva menor => maior inclinacao
			for(l = 0; l < 10; l++){
				glVertex3f(320 + 276*seno[l], 276*coseno[l] - 250, grande+5.117); // externo
				glVertex3f(320 + 276*seno[l], 276*coseno[l] - 250, 0.0); // interno
			}
			
			// curva maior => menor inclinacao
			for(l = 11; l < 17; l++){
				glVertex3f(677*seno[l], 677*coseno[l], grande+4.388); // externo
				glVertex3f(677*seno[l], 677*coseno[l], 0.0); // interno
			}
			
			// linha de chegada
			glVertex3f(0.0, -677.0, grande+4.388); // externo
			glVertex3f(0.0, -677.0, 0.0); // interno
		glEnd();
	
		// lateral interna
		glBegin(GL_QUAD_STRIP);
			glColor3f(0.3 , 0.3, 0.3);
			// reta oposta
			
			calculaNormal(0.0, 22.0, grande + 0.657, 0.0, 22.0, 0.157, 300.0, 22.0, grande+0.657);
			
			glVertex3f(0.0, 22.0, grande+0.657); // externo
			glVertex3f(0.0, 22.0, 0.157); // interno
			
			
			calculaNormal(300.0, 22.0, grande+0.657 , 300.0, 22.0, 0.157, 310.0, 22.0, grande+2.887);
			
			glVertex3f(300.0, 22.0, grande+0.657); // externo
			glVertex3f(300.0, 22.0, 0.157); // interno
			
			calculaNormal(310.0, 22.0, grande+2.887, 310.0, 22.0, 2.387, 320 + 272*seno[l], 272*coseno[l] - 250, grande+5.117);
						
			// inicia a inclinacao para a curva
			glVertex3f(310.0, 22.0, grande+2.887); // externo
			glVertex3f(310.0, 22.0, 2.387); // interno
			
			// curva menor => maior inclinacao
			for(l = 0; l < 10; l++){
				glVertex3f(320 + 272*seno[l], 272*coseno[l] - 250, grande+5.117); // externo
				glVertex3f(320 + 272*seno[l], 272*coseno[l] - 250, 4.617); // interno
				if(l < 9)
					calculaNormal(320 + 272*seno[l], 272*coseno[l] - 250, grande+5.117, 320 + 272*seno[l], 272*coseno[l] - 250, 4.617, 320 + 272*seno[l + 1], 272*coseno[l + 1] - 250, grande+5.117);
			}
			
			calculaNormal(320 + 272*seno[10], 272*coseno[10] - 250, grande+5.117, 320 + 272*seno[10], 272*coseno[10] - 250, 4.617, 673*seno[11], 673*coseno[11], grande+4.388);
			
			// curva maior => menor inclinacao
			for(l = 11; l < 17; l++){
				glVertex3f(673*seno[l], 673*coseno[l], grande+4.388); // externo
				glVertex3f(673*seno[l], 673*coseno[l], 3.888); // interno
				if(l < 16)
					calculaNormal(673*seno[l], 673*coseno[l], grande+4.388, 673*seno[l], 673*coseno[l], 3.888, 673*seno[l + 1], 673*coseno[l + 1], grande+4.388);
			}
			
			calculaNormal(673*seno[17], 673*coseno[17], grande+4.388, 673*seno[17], 673*coseno[17], 3.888,0.0, -673.0, grande+4.388);
			
			// linha de chegada
			glVertex3f(0.0, -673.0, grande+4.388); // externo
			glVertex3f(0.0, -673.0, 3.888); // interno
		glEnd();
		glPopAttrib();
	glEndList();
		
/*--------------------------------------------------------------------------------------------*/	
		
	// astes das grades		
	glNewList(HASTE, GL_COMPILE);
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		for(i = 0; i <= 310; i+=10){
			glPushMatrix();
				glTranslatef(i, 26.0, grande+0.657);
				glCallList(POSTE);
			glPopMatrix();
		}
				
		// inicia a inclinacao para a curva
		glPushMatrix();
			glTranslatef(310.0, 26.0, grande+0.657);
			glCallList(POSTE);
		glPopMatrix();
				
		// curva menor => maior inclinacao
		for(l = 0; l < 10; l++){
			glPushMatrix();
				glTranslatef(320 + 276*seno[l], 276*coseno[l] - 250, grande+0.657);
				glCallList(POSTE);
			glPopMatrix();
		}
			
		// curva maior => menor inclinacao
		for(l = 11; l < 17; l++){
			glPushMatrix();
				glTranslatef(677*seno[l], 677*coseno[l], grande+0.657);
				glCallList(POSTE);
			glPopMatrix();
		}
				
		// linha de chegada
		glPushMatrix();
			glTranslatef(0.0, -677.0, grande+0.657);
			glCallList(POSTE);
		glPopMatrix();
		glPopAttrib();
	glEndList();
	
/*-----------------------------------------------------------------------------------------------*/	
	
	glNewList(GRADE, GL_COMPILE);
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		float k;
		for(k = 0.657; k <= 12; k+= 1){
			glColor3f(0.3, 0.3, 0.3);
			glBegin(GL_LINES);
				glVertex3f(0, 26.0, k + 0.657);
				glVertex3f(310.0, 26.0, k + 0.657);
				glVertex3f(310.0, 26.0, k + 0.657);
				for(l = 0; l < 10; l++){
					glVertex3f(320 + 276*seno[l], 276*coseno[l] - 250, k + 0.657);
					glVertex3f(320 + 276*seno[l], 276*coseno[l] - 250, k + 0.657);
				}
			
				for(l = 11; l < 17; l++){
					glVertex3f(677*seno[l], 677*coseno[l], k + 0.657);
					glVertex3f(677*seno[l], 677*coseno[l], k + 0.657);
				}
				
				glVertex3f(0.0, -677.0, k + 0.657);
			glEnd();
		}
		glPopAttrib();
	glEndList();
	
	

/*------------------------------------------------------------------------------------------*/


	
	

	glNewList(ARQUIBANCADA, GL_COMPILE);
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glColor3f(0.35, 0.35, 0.35);
		glBegin(GL_QUAD_STRIP);
			for(l = 11; l < 17; l++){
				if(l < 16)
					calculaNormal(707*seno[l], 707*coseno[l], grande + 18.388, 707*seno[l], 707*coseno[l], 0.0, 707*seno[l + 1], 707*coseno[l + 1], grande + 18.388);
				glVertex3f(707*seno[l], 707*coseno[l], grande + 18.388);
				glVertex3f(707*seno[l], 707*coseno[l], 0.0);
			}
			
			calculaNormal(707*seno[17], 707*coseno[17], grande + 18.388, 707*seno[17], 707*coseno[17], 0.0, 0.0, -707.0, grande + 18.388);
						
			glVertex3f(0.0, -707.0, grande + 18.388);
			glVertex3f(0.0, -707.0, 0.0);
		glEnd();

		glEnable(GL_TEXTURE_2D);


		glBindTexture(GL_TEXTURE_2D, torcida);
		
		glColor3f(0.35, 0.35, 0.35);
		glBegin(GL_QUADS);
			for(l = 11; l < 16; l++){
				
				calculaNormal(677*seno[l], 677*coseno[l], grande+4.388, 707*seno[l], 707*coseno[l], grande+18.388, 677*seno[l + 1], 677*coseno[l + 1], grande+4.388);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(677*seno[l], 677*coseno[l], grande+4.388);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(677*seno[l + 1], 677*coseno[l + 1], grande+4.388);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(707*seno[l + 1], 707*coseno[l + 1], grande+18.388);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(707*seno[l], 707*coseno[l], grande+18.388);
				
			}
			
			glTexCoord2f(1.0f, 1.0f); glVertex3f(677*seno[l], 677*coseno[l], grande+4.388);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0, -677.0, grande+4.388);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, -707.0, grande+18.388);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(707*seno[l], 707*coseno[l], grande+18.388);
				
			
			//calculaNormal(677*seno[17], 677*coseno[17], grande+4.388, 707*seno[17], 707*coseno[17], grande+18.388, 0.0, -677.0, grande+4.388);
						
			//glVertex3f(0.0, -677.0, grande+4.388);
			//glVertex3f(0.0, -707.0, grande+18.388);
		glEnd();
		glPopAttrib();
	glEndList();

	glDisable(GL_TEXTURE_2D);

}


void Pista :: draw(){
	glPushMatrix();
	glCallList(CURVA);
	glCallList(MURO);
	glCallList(HASTE);
	glCallList(GRADE);
	glCallList(ARQUIBANCADA);
	glPushMatrix();
		glScalef(-1.0, 1.0, 1.0);
		glCallList(CURVA);
		glCallList(MURO);
		glCallList(HASTE);
		glCallList(GRADE);
		glCallList(ARQUIBANCADA);
	glPopMatrix();
	glPopMatrix();
}

Pista :: Pista(){
	carregaTextura("texturas/torcida.bmp", torcida);
	calcularSenoCos();
	iniciarListas();
}
