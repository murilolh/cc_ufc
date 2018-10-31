#include "carregabmp.h"
#include "Objeto.h"
#include "Cenario.h"

GLuint texturaSkyBox[6];


void Cenario :: drawGrid(){															

	for(float i = -500; i <= 500; i += 5)
	{
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glBegin(GL_LINES);
			glColor3ub(150, 190, 150);						
			glVertex3f(-500, 0, i);					
			glVertex3f(500, 0, i);
			glVertex3f(i, 0,-500);							
			glVertex3f(i, 0, 500);
		glEnd();
		glPopAttrib();
	}
}

void Cenario :: setSkySize(float x, float y, float z, float width, float height, float length){
	this->x = x;
	this->y = z;
	this->z = y;
	this->width = width;
	this->height = length;
	this->length = height;
}

void Cenario :: ligarCeu(char valor){
	desenharSkyBox = valor;
}
void Cenario :: ligarGrid(char valor){
	desenharGrid = valor;
}

void Cenario :: iniciarListas(){
}

void Cenario :: drawSkybox(float x, float y, float z, float width, float height, float length){
	// Center the Skybox around the given x,y,z position
	x = this->x - width  / 2;
	y = this->y - height / 2;
	z = this->z - length / 2;

	glEnable(GL_TEXTURE_2D);

	// Draw Front side
	glBindTexture(GL_TEXTURE_2D, texturaSkyBox[SKYFRONT]);
	glBegin(GL_QUADS);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height, z+length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y+height, z+length); 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y,		z+length);
	glEnd();

	// Draw Back side
	glBindTexture(GL_TEXTURE_2D, texturaSkyBox[SKYBACK]);
	glBegin(GL_QUADS);		
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y,		z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y+height, z); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z);
	glEnd();

	// Draw Left side
	glBindTexture(GL_TEXTURE_2D, texturaSkyBox[SKYLEFT]);
	glBegin(GL_QUADS);		
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height,	z);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z+length); 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z+length);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z);		
	glEnd();

	// Draw Right side
	glBindTexture(GL_TEXTURE_2D, texturaSkyBox[SKYRIGHT]);
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y,		z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y,		z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y+height,	z+length); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y+height,	z);
	glEnd();

	// Draw Up side
	glBindTexture(GL_TEXTURE_2D, texturaSkyBox[SKYUP]);
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y+height, z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y+height, z+length); 
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height,	z+length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z);
	glEnd();

	// Draw Down side
	glBindTexture(GL_TEXTURE_2D, texturaSkyBox[SKYDOWN]);
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y,		z+length); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y,		z);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}


void Cenario :: draw(){
	if(desenharSkyBox){
		glPushAttrib(GL_ALL_ATTRIB_BITS);		
		glPushMatrix();
			glRotatef(90.0, 1.0, 0.0, 0.0);
			drawSkybox(x, y, z, width, height, length);
		glPopMatrix();
		glPopAttrib();
	
	}
	if(desenharGrid)
		drawGrid();
		
	glPushAttrib(GL_ALL_ATTRIB_BITS);		
		glPushMatrix();
			glColor3f(0, 0.1, 0.0);
			glTranslatef(0.0, -500.0, -5.5);
			//glRotatef(90.0, 1.0, 0.0, 0.0);
			glScalef(2000, 2000, 10.0);
			glutSolidCube(1);
		glPopMatrix();
	glPopAttrib();
	
}

Cenario :: Cenario(){
	
	desenharSkyBox = 1;
	desenharGrid = 0;
	setSkySize(0, 500, 0, 1600, 1600, 600);
	//Carrega as texturas
	carregaTextura("texturas/front.bmp", texturaSkyBox[SKYFRONT]);
	carregaTextura("texturas/back.bmp", texturaSkyBox[SKYBACK]);
	carregaTextura("texturas/left.bmp", texturaSkyBox[SKYLEFT]);
	carregaTextura("texturas/right.bmp", texturaSkyBox[SKYRIGHT]);
	carregaTextura("texturas/up.bmp", texturaSkyBox[SKYUP]);
	carregaTextura("texturas/down.bmp", texturaSkyBox[SKYDOWN]);

}

Cenario :: Cenario(float x, float y, float z, float width, float height, float length){
	
	desenharSkyBox = 1;
	desenharGrid = 0;
	setSkySize(x, y, z, width, height, length);
	//Carrega as texturas
	carregaTextura("texturas/front.bmp", texturaSkyBox[SKYFRONT]);
	carregaTextura("texturas/back.bmp", texturaSkyBox[SKYBACK]);
	carregaTextura("texturas/left.bmp", texturaSkyBox[SKYLEFT]);
	carregaTextura("texturas/right.bmp", texturaSkyBox[SKYRIGHT]);
	carregaTextura("texturas/up.bmp", texturaSkyBox[SKYUP]);
	carregaTextura("texturas/down.bmp", texturaSkyBox[SKYDOWN]);

}
