#include "Objeto.h"
#include "Carro.h"
#include "uteis.h"
#include <math.h>

// cores para o carro
void Carro :: setVelocidade(float v){
	this->velocidade = v;
}

void Carro :: setCorLateral(float r, float g, float b){
	this->corLateral[0] = r;
	this->corLateral[1] = g;
	this->corLateral[2] = b;
}

void Carro :: setCorListras(float r, float g, float b){
	this->corListras[0] = r;
	this->corListras[1] = g;
	this->corListras[2] = b;
}

void Carro :: setCorTopo(float r, float g, float b){
	this->corTopo[0] = r;
	this->corTopo[1] = g;
	this->corTopo[2] = b;
}

void Carro :: setCorDetalhes(float r, float g, float b){
	this->corDetalhes[0] = r;
	this->corDetalhes[1] = g;
	this->corDetalhes[2] = b;
}

void Carro :: setCorPainel(float r, float g, float b){
	this->corPainel[0] = r;
	this->corPainel[1] = g;
	this->corPainel[2] = b;
}

void Carro :: setCorSuporte(float r, float g, float b){
	this->corSuporte[0] = r;
	this->corSuporte[1] = g;
	this->corSuporte[2] = b;
}

// cores para o capacete
void Carro :: setCorViseiraLateral(float r, float g, float b){
	this->corViseiraLateral[0] = r;
	this->corViseiraLateral[1] = g;
	this->corViseiraLateral[2] = b;
}

void Carro :: setCorCentroCapacete(float r, float g, float b){
	this->corCentroCapacete[0] = r;
	this->corCentroCapacete[1] = g;
	this->corCentroCapacete[2] = b;
}

void Carro :: setCorViseira(float r, float g, float b){
	this->corViseira[0] = r;
	this->corViseira[1] = g;
	this->corViseira[2] = b;
}

void Carro :: setCorTopoCapacete(float r, float g, float b){
	this->corTopoCapacete[0] = r;
	this->corTopoCapacete[1] = g;
	this->corTopoCapacete[2] = b;
}

void Carro :: setCorListraCapacete(float r, float g, float b){
	this->corListraCapacete[0] = r;
	this->corListraCapacete[1] = g;
	this->corListraCapacete[2] = b;
}

void Carro :: setCorCapacete(float r, float g, float b){
	this->corCapacete[0] = r;
	this->corCapacete[1] = g;
	this->corCapacete[2] = b;
}

float Carro :: getVelocidade(){
	return this->velocidade;
}

void Carro :: iniciarListas(){

	float i;

	// pontos do carro
    GLfloat P1[3] = {-16, -40, 106};
    GLfloat P2[3] = {-16, -112, 100};
    GLfloat P3[3] = {0, -400, -36};
    GLfloat P4[3] = {0, 480, -100};
    GLfloat P5[3] = {-20, 420, -84};
    GLfloat P6[3] = {-160, 480, -100};
    GLfloat P7[3] = {-160, 376, -54};
    GLfloat P8[3] = {-48, 104, 4};
    GLfloat P9[3] = {-48, 104, -96};
    GLfloat P10[3] = {-48, -44, -8};
    GLfloat P11[3] = {-160, 0, -20};
    GLfloat P12[3] = {-160, 0, -106};
    GLfloat P13[3] = {-160, -236, -20};
    GLfloat P14[3] = {-160, -236, -106};
    GLfloat P15[3] = {-84, -432, -40};
    GLfloat P16[3] = {-84, -432, -90};
    GLfloat P17[3] = {-68, -236, -20};
    GLfloat P18[3] = {-104, -400, 88};
    GLfloat P19[3] = {-104, -400, 52};
    GLfloat P20[3] = {-104, -400, 20};
    GLfloat P21[3] = {-104, -480, 88};
    GLfloat P22[3] = {-104, -480, 20};
    GLfloat P46[3] = {-160, 376, -100};
    GLfloat P48[3] = {-48, -236, -8};
    GLfloat P50[3] = {-104, -480, 64};
    GLfloat P54[3] = {0, -344, -8};
    GLfloat P66[3] = {-68, 52, -106};
    GLfloat P67[3] = {-68, 52, -20};
    GLfloat P68[3] = {-16, 104, 16};
    GLfloat P70[3] = {-40, 264, -20};
    GLfloat P72[3] = {-16, 264, -15};
    GLfloat P74[3] = {-36 ,328, -35};
    GLfloat P76[3] = {-16, 328, -35};
    GLfloat P78[3] = {-40, 264, -96};
    GLfloat P80[3] = {-36, 328, -96};
    GLfloat P83[3] = {-48, 52, -8};
    GLfloat P84[3] = {-84, -328, -30};
    GLfloat P85[3] = {-84, -328, -106};
    GLfloat P88[3] = {-24, -52, 52};
    GLfloat P90[3] = {0, -236, 52};
    GLfloat P92[3] = {-160, 480, -78};
    GLfloat P95[3] = {-24, -112, 52};
    GLfloat P96[3] = {-48, -112, -8};
    GLfloat P97[3] = {-32, -456, 60};
    GLfloat P98[3] = {-32, -400, 52};
    GLfloat P101[3] = {-32, -432, -40};
    GLfloat P117[3] = {-32, -432, -90};
    GLfloat P119[3] = {-32, -456, -90};
    GLfloat P124[3] = {-160, 400, -80};
    GLfloat P125[3] = {-104, 400, -80};
    GLfloat P126[3] = {-116, 376, -54};
    GLfloat P127[3] = {-104, -456, 64};
    GLfloat P131[3] = {-32, -480, 64};
    GLfloat P133[3] = {0, -432, -40};
    GLfloat P135[3] = {-32, -456, -66};
    GLfloat P137[3] = {-84, -400, -106};
    GLfloat P181[3] = {-68, -112, -20};
    
    // pontos do capacete
    GLfloat CP1[3] = {-31, 0, 47};
    GLfloat CP2[3] = {-33, 7, 24};
    GLfloat CP3[3] = {-23, 21, 48};
    GLfloat CP4[3] = {-26, 29, 24};
    GLfloat CP5[3] = {-10, 31, 49};
    
    GLfloat CP6[3] = {-10, 42, 24};
    GLfloat CP7[3] = {-25, -21, 47};
    GLfloat CP8[3] = {-26, -19, 24};
    GLfloat CP9[3] = {-9, -33, 47};
    GLfloat CP10[3] = {-9, -33, 24};
    
    GLfloat CP11[3] = {-10, 42, 17};
    GLfloat CP12[3] = {-25, 29, 17};
    GLfloat CP13[3] = {-31, 7, 17};
    GLfloat CP14[3] = {-25, -18, 17};
    GLfloat CP15[3] = {-9, -31, 17};
     
    GLfloat CP16[3] = {-9, 39, 3};
    GLfloat CP17[3] = {-25, 25, 3};
    GLfloat CP18[3] = {-29, 7, 3};
    GLfloat CP19[3] = {-24, -15, 3};
    GLfloat CP20[3] = {-10, -26, 3};
        
    GLfloat CP21[3] = {-9, 22, 60};
    GLfloat CP22[3] = {-18, 15, 60};
    GLfloat CP23[3] = {-23, 0, 60};
    GLfloat CP24[3] = {-18, -16, 60};
    GLfloat CP25[3] = {-9, -24, 60};
    
    GLfloat CP26[3] = {-8, 11, 66};
    GLfloat CP27[3] = {-7, 0, 67};
    
	// define a lateral do carro
	glNewList(ESQUERDA, GL_COMPILE);
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glColor3fv(corLateral);
		glBegin(GL_TRIANGLES);
            calculaNormal(P4, P74, P80); 
			glColor3fv(corDetalhes);
			glVertex3fv(P4);
			glColor3fv(corLateral);
			glVertex3fv(P74);
			glVertex3fv(P80);
		glEnd();
		glBegin(GL_QUAD_STRIP);
		    calculaNormal(P74, P80, P70);
			glVertex3fv(P74);
			glVertex3fv(P80);
			calculaNormal(P70, P78, P8);
			glVertex3fv(P70);
			glVertex3fv(P78);
			calculaNormal(P8, P9, P67);
			glVertex3fv(P8);
			glVertex3fv(P9);
			calculaNormal(P67, P66, P11);
			glVertex3fv(P67);
			glVertex3fv(P66);
			calculaNormal(P11, P12, P13);
			glVertex3fv(P11);
			glColor3fv(corTopo);
			glVertex3fv(P12);
			calculaNormal(P13, P14, P84);
			glVertex3fv(P13);
			glVertex3fv(P14);
			calculaNormal(P84, P85, P137);
			glVertex3fv(P84);
			glColor3fv(corLateral);
			glVertex3fv(P85);
			glVertex3f(P137[0], P137[1], P84[2]);
			glVertex3fv(P137);
			calculaNormal(P137, P15, P16);
			glVertex3fv(P15);
			glVertex3fv(P16);
		glEnd();
		glPopAttrib();
	glEndList();
		
	// define a diagonal do carro
	glNewList(DIAGONAL, GL_COMPILE);
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glBegin(GL_TRIANGLES);
		    calculaNormal(P4, P74, P76);
			glColor3fv(corDetalhes);
			glVertex3fv(P4);
			glColor3fv(corListras);
			glVertex3fv(P74);
			glVertex3fv(P76);
		glEnd();
		glColor3fv(corListras);
		glBegin(GL_TRIANGLES);
		    calculaNormal(P8, P68, P83);
			glVertex3fv(P8);
			glVertex3fv(P68);
			glVertex3fv(P83);
		glEnd();
		glBegin(GL_TRIANGLES);
		    calculaNormal(P8, P67, P83);
			glVertex3fv(P8);
			glVertex3fv(P67);
			glVertex3fv(P83);
		glEnd();
		glBegin(GL_QUAD_STRIP);
		    calculaNormal(P74, P76, P70);
			glVertex3fv(P74);
			glVertex3fv(P76);
			calculaNormal(P70, P72, P8);
			glVertex3fv(P70);
			glVertex3fv(P72);
			calculaNormal(P72, P8, P68);
			glVertex3fv(P8);
			glVertex3fv(P68);
		glEnd();
		glBegin(GL_QUAD_STRIP);
		    calculaNormal(P83, P67, P96);
			glVertex3fv(P83);
			glVertex3fv(P67);
			calculaNormal(P96, P181, P48);
			glVertex3fv(P96);
			glVertex3fv(P181);
			calculaNormal(P48, P17, P54);
			glColor3fv(corLateral);
			glVertex3fv(P48);
			glVertex3fv(P17);
			calculaNormal(P17, P54, P3);
			glVertex3fv(P54);
			glVertex3fv(P3);
		glEnd();
		glPopAttrib();
	glEndList();
		
	// define a traseira do carro
	glNewList(TRASEIRA, GL_COMPILE);
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_QUADS);
        	calculaNormal(P15[0], P15[1], P15[2], P16[0], P16[1], P16[2], -P16[0], P16[1], P16[2]);
            glVertex3fv(P15);
			glVertex3fv(P16);
			glVertex3f(-P16[0], P16[1], P16[2]);
			glVertex3f(-P15[0], P15[1], P15[2]);
		glEnd();
		glPopAttrib();
	glEndList();
	
	// define a parte superior da lateral do carro
 	glNewList(TAMPA, GL_COMPILE);
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glColor3fv(corListras);
		glBegin(GL_QUADS);
		    calculaNormal(P1, P2, P95);
			glVertex3fv(P1);
			glVertex3fv(P2);
			glVertex3fv(P95);
			glVertex3fv(P88);			
		glEnd();
		glBegin(GL_TRIANGLES);
		    calculaNormal(P2, P95, P90);
			glVertex3fv(P2);
			glVertex3fv(P95);
			glVertex3fv(P90);			
		glEnd();
		glColor3fv(corTopo);
		glBegin(GL_QUADS);
            calculaNormal(P88, P95, P96);
			glVertex3fv(P88);
			glVertex3fv(P95);
			glVertex3fv(P96);
			glVertex3fv(P10);			
		glEnd();
		glBegin(GL_TRIANGLES);
		    calculaNormal(P95, P96, P48);
			glVertex3fv(P95);
			glVertex3fv(P96);
			glVertex3fv(P48);			
		glEnd();
		glBegin(GL_TRIANGLES);
		    calculaNormal(P95, P90, P48);
			glVertex3fv(P95);
			glVertex3fv(P90);
			glVertex3fv(P48);			
		glEnd();
		glBegin(GL_TRIANGLES);
		    calculaNormal(P90, P48, P54);
			glVertex3fv(P90);
			glVertex3fv(P48);
			glVertex3fv(P54);
		glEnd();
		glPopAttrib();
	glEndList();
	
	glNewList(ASA, GL_COMPILE);
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glBegin(GL_QUADS);
		    calculaNormal(P67, P11, P13);
			glColor3fv(corTopo);
			glVertex3fv(P67);
			glVertex3fv(P11);
			glVertex3fv(P13);
			glVertex3fv(P17);
		glEnd();
		glBegin(GL_QUADS);
		    calculaNormal(P3, P84, P15);
			glColor3fv(corLateral);
			glVertex3fv(P3);
			glVertex3fv(P84);
			glVertex3fv(P15);
			glVertex3fv(P133);
		glEnd();
		glBegin(GL_TRIANGLES);
		    calculaNormal(P13, P17, P84);
			glColor3fv(corTopo);
			glVertex3fv(P13);
			glVertex3fv(P17);
			glVertex3fv(P84);
		glEnd();
		glBegin(GL_TRIANGLES);
		    calculaNormal(P3, P17, P84);
			glColor3fv(corLateral);
			glVertex3fv(P3);
			glVertex3fv(P17);
			glVertex3fv(P84);
		glEnd();
		glPopAttrib();
	glEndList();
	
 	glNewList(BICO, GL_COMPILE);
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glBegin(GL_POLYGON);
		    calculaNormal(P5, P4, P125);
			glColor3fv(corTopo);
			glVertex3fv(P4);
			glColor3fv(corDetalhes);
			glVertex3fv(P5);
			glColor3fv(corDetalhes);
			glVertex3fv(P125);
			glColor3fv(corTopo);
			glVertex3fv(P124);
			glColor3fv(corTopo);
			glVertex3fv(P6);
		glEnd();
  		glBegin(GL_QUADS);
  		    calculaNormal(P6, P92, P7);
			glColor3fv(corLateral);
			glVertex3fv(P6);
			glVertex3fv(P92);
			glVertex3fv(P7);
			glVertex3fv(P46);
		glEnd();
  		glBegin(GL_QUADS);
  		    calculaNormal(P124, P125, P126);
			glColor3fv(corDetalhes);
			glVertex3fv(P124);
			glVertex3fv(P125);
			glVertex3fv(P126);
			glVertex3fv(P7);
		glEnd();
		glPopAttrib();
	glEndList();
	
 	glNewList(AEROFOLIO_A, GL_COMPILE);
		glPushAttrib(GL_ALL_ATTRIB_BITS);
  		glBegin(GL_QUADS);
  		    calculaNormal(P18, P20, P22);
			glColor3fv(corLateral);
			glVertex3fv(P18);
			glVertex3fv(P20);
			glVertex3fv(P22);
			glVertex3fv(P21);
		glEnd();
		glBegin(GL_POLYGON);
		    calculaNormal(P101, P97, P117);
			glColor3fv(corSuporte);
			glVertex3fv(P97);
			glVertex3fv(P101);
			glVertex3fv(P117);
			glVertex3fv(P119);
			glVertex3fv(P131);
		glEnd();
		glBegin(GL_TRIANGLES);
		    calculaNormal(P97, P98, P101);
			glColor3fv(corSuporte);
			glVertex3fv(P97);
			glVertex3fv(P98);
			glVertex3fv(P101);
		glEnd();
		glPopAttrib();
	glEndList();
 	
 	glNewList(AEROFOLIO_B, GL_COMPILE); // nao deve ser escalonado!
		glPushAttrib(GL_ALL_ATTRIB_BITS);
  		glBegin(GL_QUADS);
  		    calculaNormal(P13, P17, P84);
			glColor3fv(corTopo);
			glVertex3fv(P19);
			glVertex3f(-P19[0], P19[1], P19[2]);
			glVertex3f(-P50[0], P50[1], P50[2]);
			glVertex3fv(P50);
		glEnd();
  		glBegin(GL_QUADS);
  		    calculaNormal(P21[0], P21[1], P21[2], -P21[0], P21[1], P21[2], -P127[0], P127[1], P127[2]);
			glColor3fv(corLateral);
			glVertex3fv(P21);
			glVertex3f(-P21[0], P21[1], P21[2]);
			glVertex3f(-P127[0], P127[1], P127[2]);
			glVertex3fv(P127);
		glEnd();
  		glBegin(GL_QUADS);
			glColor3fv(corTopo);
			calculaNormal(P117[0], P117[1], P117[2], -P117[0], P117[1], P117[2], -P135[0], P135[1], P135[2]);
			
			glVertex3fv(P117);
			glVertex3f(-P117[0], P117[1], P117[2]);
			glVertex3f(-P135[0], P135[1], P135[2]);
			glVertex3fv(P135);
		glEnd();
		glPopAttrib();
	glEndList();
 	
 	glNewList(TOPO, GL_COMPILE); // nao deve ser escalonado!
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glBegin(GL_TRIANGLES);
		    calculaNormal(P4[0], P4[1], P4[2], P76[0], P76[1], P76[2], -P76[0], P76[1], P76[2]);
			
			glColor3fv(corDetalhes);
			glVertex3fv(P4);
			glColor3fv(corLateral);
			glVertex3fv(P76);
			glVertex3f(-P76[0], P76[1], P76[2]);
		glEnd();
		glBegin(GL_QUAD_STRIP);
		    calculaNormal(P76[0], P76[1], P76[2], -P76[0], P76[1], P76[2], P72[0], P72[1], P72[2]);
			glVertex3fv(P76);
			glVertex3f(-P76[0], P76[1], P76[2]);
			calculaNormal(P72[0], P72[1], P72[2], -P72[0], P72[1], P72[2], -P68[0], P68[1], P68[2]);
			
			glVertex3fv(P72);
			glVertex3f(-P72[0], P72[1], P72[2]);
			calculaNormal(-P72[0], P72[1], P72[2], P68[0], P68[1], P68[2], -P68[0], P68[1], P68[2]);
			
			glVertex3fv(P68);
			glVertex3f(-P68[0], P68[1], P68[2]);
		glEnd();
  		glBegin(GL_QUADS);
  		    calculaNormal(-P68[0], P68[1], P68[2], P68[0], P68[1], P68[2], P83[0], P83[1], P83[2]);
			
			glColor3fv(corPainel);
			glVertex3f(-P68[0], P68[1], P68[2]);
			glVertex3fv(P68);
			glVertex3fv(P83);
			glVertex3f(-P83[0], P83[1], P83[2]);
		glEnd();
  		glBegin(GL_QUADS);
  		    calculaNormal(P83[0], P83[1], P83[2], -P83[0], P83[1], P83[2], -P10[0], P10[1], P10[2]);
			
			glColor3f(0.0, 0.0, 0.0);
			glVertex3fv(P83);
			glVertex3f(-P83[0], P83[1], P83[2]);
			glVertex3f(-P10[0], P10[1], P10[2]);
			glVertex3fv(P10);
		glEnd();
  		glBegin(GL_QUADS);
  		    calculaNormal(P10[0], P10[1], P10[2], -P10[0], P10[1], P10[2], -P88[0], P88[1], P88[2]);
			
			glColor3fv(corTopo);
			glVertex3fv(P10);
			glVertex3f(-P10[0], P10[1], P10[2]);
			glVertex3f(-P88[0], P88[1], P88[2]);
			glVertex3fv(P88);
		glEnd();
  		glBegin(GL_QUADS);
  		    calculaNormal(-P88[0], P88[1], P88[2], -P1[0], P1[1], P1[2], P1[0], P1[1], P1[2]);
			
			glColor3f(0.0, 0.0, 0.0);
			glVertex3fv(P88);
			glVertex3f(-P88[0], P88[1], P88[2]);
			glVertex3f(-P1[0], P1[1], P1[2]);
			glVertex3fv(P1);
		glEnd();
  		glBegin(GL_QUADS);
  		    calculaNormal(P1[0], P1[1], P1[2], -P1[0], P1[1], P1[2], -P2[0], P2[1], P2[2]);
			
			glColor3fv(corListras);
			glVertex3fv(P1);
			glVertex3f(-P1[0], P1[1], P1[2]);
			glVertex3f(-P2[0], P2[1], P2[2]);
			glVertex3fv(P2);
		glEnd();
		glBegin(GL_TRIANGLES);
		    calculaNormal(P2[0], P2[1], P2[2], -P2[0], P2[1], P2[2], P90[0], P90[1], P90[2]);
			
			glColor3fv(corListras);
			glVertex3fv(P2);
			glVertex3f(-P2[0], P2[1], P2[2]);
			glVertex3fv(P90);
		glEnd();
		glPopAttrib();
	glEndList();
 	
 	glNewList(FUNDO, GL_COMPILE); // nao deve ser escalonado!
		glPushAttrib(GL_ALL_ATTRIB_BITS);
  		glBegin(GL_QUAD_STRIP);
			glColor3f(0.4, 0.3, 0.2);
			calculaNormal(P80[0], P80[1], P80[2], -P80[0], P80[1], P80[2], P78[0], P78[1], P78[2]);
			
			glVertex3fv(P80);
			glVertex3f(-P80[0], P80[1], P80[2]);
			calculaNormal(P78[0], P78[1], P78[2], -P78[0], P78[1], P78[2], P9[0], P9[1], P9[2]);						
			glVertex3fv(P78);
			glVertex3f(-P78[0], P78[1], P78[2]);
			calculaNormal(P9[0], P9[1], P9[2], -P9[0], P9[1], P9[2], P66[0], P66[1], P66[2]);
			glVertex3fv(P9);
			glVertex3f(-P9[0], P9[1], P9[2]);
			calculaNormal(P66[0], P66[1], P66[2], -P66[0], P66[1], P66[2], P12[0], P12[1], P12[2]);
			glVertex3fv(P66);
			glVertex3f(-P66[0], P66[1], P66[2]);
			calculaNormal(P12[0], P12[1], P12[2], -P12[0], P12[1], P12[2], P14[0], P14[1], P14[2]);
			glVertex3fv(P12);
			glVertex3f(-P12[0], P12[1], P12[2]);
			calculaNormal(P14[0], P14[1], P14[2], -P14[0], P14[1], P14[2], P85[0], P85[1], P85[2]);
			glVertex3fv(P14);
			glVertex3f(-P14[0], P14[1], P14[2]);
			calculaNormal(P85[0], P85[1], P85[2], -P85[0], P85[1], P85[2], P137[0], P137[1], P137[2]);
			glVertex3fv(P85);
			glVertex3f(-P85[0], P85[1], P85[2]);
			calculaNormal(P137[0], P137[1], P137[2], -P137[0], P137[1], P137[2], P16[0], P16[1], P16[2]);
			glVertex3fv(P137);
			glVertex3f(-P137[0], P137[1], P137[2]);
			calculaNormal(-P137[0], P137[1], P137[2], P16[0], P16[1], P16[2], -P16[0], P16[1], P16[2]);
			glVertex3fv(P16);
			glVertex3f(-P16[0], P16[1], P16[2]);
		glEnd();
		glBegin(GL_TRIANGLES);
			glColor3f(0.4, 0.3, 0.2);
			glVertex3fv(P4);
			glVertex3fv(P80);
			glVertex3f(-P80[0], P80[1], P80[2]);
		glEnd();
		glPopAttrib();
	glEndList();
	
	//define o carro
 	glNewList(CARRO, GL_COMPILE);
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glCallList(TOPO);
		glCallList(FUNDO);
		glCallList(TRASEIRA);
		glCallList(AEROFOLIO_B);
		glCallList(AEROFOLIO_A);
		glCallList(BICO);
		glCallList(ASA);
		glCallList(TAMPA);
		glCallList(ESQUERDA);
		glCallList(DIAGONAL);
		glPushMatrix();
			glScalef(-1.0, 1.0, 1.0);
			glCallList(AEROFOLIO_A);
			glCallList(BICO);
			glCallList(ASA);
			glCallList(TAMPA);
			glCallList(ESQUERDA);
			glCallList(DIAGONAL);
		glPopMatrix();
		glPopAttrib();
	glEndList();
	
	// define o capacete
	glNewList(VISEIRA, GL_COMPILE);
		glPushAttrib(GL_ALL_ATTRIB_BITS);
    	glBegin(GL_QUAD_STRIP);
    		glColor3fv(corViseiraLateral);
    		glVertex3fv(CP1);
    		glVertex3fv(CP2);
    		glColor3fv(corViseira);
    		glVertex3fv(CP3);
    		glVertex3fv(CP4);
    		glVertex3fv(CP5);
    		glColor3f(1.0, 1.0, 1.0);
    		glVertex3fv(CP6);
    		glVertex3f(-CP5[0], CP5[1], CP5[2]);
    		glColor3fv(corViseira);
    		glVertex3f(-CP6[0], CP6[1], CP6[2]);
    		glVertex3f(-CP3[0], CP3[1], CP3[2]);
    		glVertex3f(-CP4[0], CP4[1], CP4[2]);
    		glColor3fv(corViseiraLateral);
    		glVertex3f(-CP1[0], CP1[1], CP1[2]);
    		glVertex3f(-CP2[0], CP2[1], CP2[2]);
    	glEnd();
		glPopAttrib();
    glEndList();
    
    //meio
    glNewList(CAPACETE, GL_COMPILE);
		glPushAttrib(GL_ALL_ATTRIB_BITS);
    	glBegin(GL_QUAD_STRIP);
    		glColor3fv(corCentroCapacete);
    		glVertex3fv(CP1);
    		glVertex3fv(CP2);
    		glVertex3fv(CP7);
    		glVertex3fv(CP8);
    		glVertex3fv(CP9);
    		glVertex3fv(CP10);
    		glVertex3f(-CP9[0], CP9[1], CP9[2]);
    		glVertex3f(-CP10[0], CP10[1], CP10[2]);
    		glVertex3f(-CP7[0], CP7[1], CP7[2]);
    		glVertex3f(-CP8[0], CP8[1], CP8[2]);
    		glVertex3f(-CP1[0], CP1[1], CP1[2]);
    		glVertex3f(-CP2[0], CP2[1], CP2[2]);
    	glEnd();
    	
    	//um pouco abaixo
    	glBegin(GL_QUAD_STRIP);
    		glColor3fv(corListraCapacete);
    		glVertex3fv(CP6);
    		glVertex3fv(CP11);
    		glVertex3fv(CP4);
    		glVertex3fv(CP12);
    		glVertex3fv(CP2);
    		glVertex3fv(CP13);
    		glVertex3fv(CP8);
    		glVertex3fv(CP14);
    		glVertex3fv(CP10);
    		glVertex3fv(CP15);
    		glVertex3f(-CP10[0], CP10[1], CP10[2]);
    		glVertex3f(-CP15[0], CP15[1], CP15[2]);
    		glVertex3f(-CP8[0], CP8[1], CP8[2]);
    		glVertex3f(-CP14[0], CP14[1], CP14[2]);
    		glVertex3f(-CP2[0], CP2[1], CP2[2]);
    		glVertex3f(-CP13[0], CP13[1], CP13[2]);
    		glVertex3f(-CP4[0], CP4[1], CP4[2]);
    		glVertex3f(-CP12[0], CP12[1], CP12[2]);
    		glVertex3f(-CP6[0], CP6[1], CP6[2]);
    		glVertex3f(-CP11[0], CP11[1], CP11[2]);
    		glVertex3fv(CP6);
    		glVertex3fv(CP11);
    	glEnd();
    	
    	//abaixo
    	glBegin(GL_QUAD_STRIP);
    		glColor3fv(corCapacete);
    		glVertex3fv(CP11);
    		glVertex3fv(CP16);
    		glVertex3fv(CP12);
    		glVertex3fv(CP17);
    		glVertex3fv(CP13);
    		glVertex3fv(CP18);
    		glVertex3fv(CP14);
    		glVertex3fv(CP19);
    		glVertex3fv(CP15);
    		glVertex3fv(CP20);
    		glVertex3f(-CP15[0], CP15[1], CP15[2]);
    		glVertex3f(-CP20[0], CP20[1], CP20[2]);
    		glVertex3f(-CP14[0], CP14[1], CP14[2]);
    		glVertex3f(-CP19[0], CP19[1], CP19[2]);
    		glVertex3f(-CP13[0], CP13[1], CP13[2]);
    		glVertex3f(-CP18[0], CP18[1], CP18[2]);
    		glVertex3f(-CP12[0], CP12[1], CP12[2]);
    		glVertex3f(-CP17[0], CP17[1], CP17[2]);
    		glVertex3f(-CP11[0], CP11[1], CP11[2]);
    		glVertex3f(-CP16[0], CP16[1], CP16[2]);
    		glVertex3fv(CP11);
    		glVertex3fv(CP16);
    	glEnd();
    	
    	//logo acima
    	glBegin(GL_QUAD_STRIP);
    		glColor3fv(corCapacete);
    		glVertex3fv(CP5);
    		glVertex3fv(CP21);
    		glVertex3fv(CP3);
    		glVertex3fv(CP22);
    		glVertex3fv(CP1);
    		glVertex3fv(CP23);
    		glVertex3fv(CP7);
    		glVertex3fv(CP24);
    		glVertex3fv(CP9);
    		glVertex3fv(CP25);
    		glVertex3f(-CP9[0], CP9[1], CP9[2]);
    		glVertex3f(-CP25[0], CP25[1], CP25[2]);
    		glVertex3f(-CP7[0], CP7[1], CP7[2]);
    		glVertex3f(-CP24[0], CP24[1], CP24[2]);
    		glVertex3f(-CP1[0], CP1[1], CP1[2]);
    		glVertex3f(-CP23[0], CP23[1], CP23[2]);
    		glVertex3f(-CP3[0], CP3[1], CP3[2]);
    		glVertex3f(-CP22[0], CP22[1], CP22[2]);
    		glVertex3f(-CP5[0], CP5[1], CP5[2]);
    		glVertex3f(-CP21[0], CP21[1], CP21[2]);
    		glVertex3fv(CP5);
    		glVertex3fv(CP21);
    	glEnd();
    	
    	//acima
    	glBegin(GL_QUAD_STRIP);
    		glColor3fv(corTopoCapacete);
    		glVertex3fv(CP26);
    		glVertex3fv(CP21);
    		glVertex3fv(CP26);
    		glVertex3fv(CP22);
    		glVertex3fv(CP27);
    		glVertex3fv(CP23);
    		glVertex3f(CP26[0], -CP26[1], CP26[2]);
    		glVertex3fv(CP24);
    		glVertex3f(CP26[0], -CP26[1], CP26[2]);
    		glVertex3fv(CP25);
    		glVertex3f(-CP26[0], -CP26[1], CP26[2]);
    		glVertex3f(-CP25[0], CP25[1], CP25[2]);
    		glVertex3f(-CP26[0], -CP26[1], CP26[2]);
    		glVertex3f(-CP24[0], CP24[1], CP24[2]);
    		glVertex3f(-CP27[0], CP27[1], CP27[2]);
    		glVertex3f(-CP23[0], CP23[1], CP23[2]);
    		glVertex3f(-CP26[0], CP26[1], CP26[2]);
    		glVertex3f(-CP22[0], CP22[1], CP22[2]);
    		glVertex3f(-CP26[0], CP26[1], CP26[2]);
    		glVertex3f(-CP21[0], CP21[1], CP21[2]);
    		glVertex3fv(CP26);
    		glVertex3fv(CP21);
    	glEnd();
    	
    	//topo
    	glBegin(GL_POLYGON);
    		glColor3fv(corTopoCapacete);
    		glVertex3fv(CP26);
    		glVertex3fv(CP27);
    		glVertex3f(CP26[0], -CP26[1], CP26[2]);
    		glVertex3f(-CP26[0], -CP26[1], CP26[2]);
    		glVertex3f(-CP26[0], CP26[1], CP26[2]);
    		glVertex3f(-CP27[0], CP27[1], CP27[2]);
    		glVertex3f(-CP26[0], CP26[1], CP26[2]);
    	glEnd();
		glPopAttrib();
    glEndList();
    
    float raio = 50;
    float largura = 100;
	float incAngulo = 3.1415/8;
    
    glNewList(RODA, GL_COMPILE);
    	glPushAttrib(GL_ALL_ATTRIB_BITS);
    	glBegin(GL_TRIANGLE_FAN);
    	    
    		glColor3f(0.0, 0.0, 0.0);
    		calculaNormal(largura/2, 0.0, 0.0, largura/2, raio*cos(0), raio*sin(0), largura/2, raio*cos(incAngulo), raio*sin(incAngulo));
			
    		glVertex3f(largura/2, 0.0, 0.0);
    		for(i = 0; i < 2*3.1415; i+=incAngulo){
    			glVertex3f(largura/2, raio*cos(i), raio*sin(i));
    		}
    	glEnd();
    	glBegin(GL_TRIANGLE_FAN);
    		glColor3f(0.0, 0.0, 0.0);
    		calculaNormal(-largura/2, 0.0, 0.0, -largura/2, raio*cos(0), raio*sin(0), -largura/2, raio*cos(incAngulo), raio*sin(incAngulo));
			
    		glVertex3f(-largura/2, 0.0, 0.0);
    		for(i = 0; i < 2*3.1415; i+=incAngulo){
    			glVertex3f(-largura/2, raio*cos(i), raio*sin(i));
    		}
    	glEnd();
    	glBegin(GL_QUAD_STRIP);
    		glColor3f(0.1, 0.1, 0.1);
    		calculaNormal(-largura/2, 0.0, 0.0, largura/2, 0.0, 0.0, -largura/2, raio*cos(0), raio*sin(0));
    		glVertex3f(-largura/2, 0.0, 0.0);
    		glVertex3f(largura/2, 0.0, 0.0);
    		for(i = 0; i < 2*3.1415; i+=incAngulo){
                if(i == 0){
                     calculaNormal(largura/2, 0.0, 0.0, -largura/2, raio*cos(i), raio*sin(i), largura/2, raio*cos(i), raio*sin(i));
                }
                calculaNormal(-largura/2, raio*cos(i - incAngulo), raio*sin(i - incAngulo), -largura/2, raio*cos(i), raio*sin(i), largura/2, raio*cos(i), raio*sin(i));
    			glVertex3f(-largura/2, raio*cos(i), raio*sin(i));
    			glVertex3f(largura/2, raio*cos(i), raio*sin(i));
    		}
    	glEnd();
    	glPopAttrib();
    glEndList();

	
}

void Carro :: draw(){

	glPushMatrix();
		glCallList(CARRO);
		glCallList(CAPACETE);
		glCallList(VISEIRA);
		glPushMatrix();
		glTranslatef(-160.0, 230.0, -50.0);
		glScalef(0.8, 1.1, 1.1);
		glCallList(RODA);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(160.0, 230.0, -50.0);
		glScalef(0.8, 1.1, 1.1);
		glCallList(RODA);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(-165.0, -368.0, -50.0);
		glScalef(1.18, 1.23, 1.23);
		glCallList(RODA);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(165.0, -368.0, -50.0);
		glScalef(1.18, 1.23, 1.23);
		glCallList(RODA);
		glPopMatrix();
	glPopMatrix();
	//glutSwapBuffers();
	//glFlush();
}

Carro :: Carro(){
	
	setCorLateral(0.0, 0.45, 0.0);
	setCorListras(0.0, 0.0, 0.5);
	setCorTopo(1.0, 1.0, 1.0);
	setCorDetalhes(1, 1, 0.0);
	setCorViseira(0.2, 0.2, 0.2);
	setCorPainel(0.2, 0.2, 0.2);
	setCorSuporte(0.0, 0.0, 0.0);
	
	setCorViseiraLateral(0, 0, 0); // lateral da viseira [defaul: preto]
	setCorCentroCapacete(1, 1, 1); // centro do capacete [defaul: branco]
	setCorViseira(0.5, 0.5, 0.5); // centro da Viseira [defaul: cinza]
	setCorTopoCapacete(0.0, 0.0, 0.5); // topo do capacete [defaul: azul]
	setCorListraCapacete(1, 1, 0); // listra do capacete [defaul: amarelo]
	setCorCapacete(0,0.45, 0);
	velocidade = 0.0;
	iniciarListas();
}


Carro :: Carro(float posicao[3]){
	
	setCorLateral(0.0, 0.45, 0.0);
	setCorListras(0.0, 0.0, 0.5);
	setCorTopo(1.0, 1.0, 1.0);
	setCorDetalhes(1, 1, 0.0);
	setCorViseira(0.2, 0.2, 0.2);
	setCorPainel(0.2, 0.2, 0.2);
	setCorSuporte(0.0, 0.0, 0.0);
	
	setCorViseiraLateral(0, 0, 0); // lateral da viseira [defaul: preto]
	setCorCentroCapacete(1, 1, 1); // centro do capacete [defaul: branco]
	setCorViseira(0.5, 0.5, 0.5); // centro da Viseira [defaul: cinza]
	setCorTopoCapacete(0.0, 0.0, 0.5); // topo do capacete [defaul: azul]
	setCorListraCapacete(1, 1, 0); // listra do capacete [defaul: amarelo]
	setCorCapacete(0,0.45, 0);
	setPosicao(posicao[0], posicao[1], posicao[2]);
	velocidade = 0.0;
	iniciarListas();
}
