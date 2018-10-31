#include "Objeto.h"
#include "Cenario.h"
#include "Carro.h"
#include "Pista.h"
#include "Camera.h"
#include "Balao.h"
#include <math.h>
#include <iostream>
#include <GL/glut.h>
#include <stdio.h>


#define WIDTH 600
#define HEIGHT 600

float aprox = 0;
float side = 0;
int perspectiva = 45;


GLfloat sunAmbient[] = {1.6, 1.6, 1.6, 1.0};
GLfloat sunSpecular[] = {1.0, 1.0, 1.0, 1.0}; 
GLfloat sunDiffuse[] = {1.0, 1.0, 1.0, 1.0};
GLfloat sunPosition[] = {400.0, -700.0, 700.0, 0.0}; 

GLfloat refAmbient[] = {1.5, 1.5, 1.5, 1.0};
GLfloat refSpecular[] = {1.0, 1.0, 1.0, 1.0}; 
GLfloat refDiffuse[] = {1.0, 1.0, 1.0, 1.0};

GLfloat ref1Position[] = {0.0, 0.0, 220.0, 1.0};
GLfloat ref1Direction[] = {0.0, 0.0, -1.0, 1.0};

GLfloat ref2Position[] = {310.0, 15.0, 220.0, 1.0};
GLfloat ref2Direction[] = {0.0, 0.0, -1.0, 1.0};

GLfloat ref3Position[] = {-310.0, 15.0, 220.0, 1.0};
GLfloat ref3Direction[] = {0.0, 0.0, -1.0, 1.0};

GLfloat ref4Position[] = {0.0, 0.0, 220.0, 1.0};
GLfloat ref4Direction[] = {0.0, 0.0, -1.0, 1.0};


float expoente = 100;
float angulo = 70;

float quadratica = 0.0;
float constante = 0.0;
float linear = 0.0;


char dia = 1;

void atualizarLuz(){
    if(dia){
        glEnable(GL_LIGHT0); 
        glDisable(GL_LIGHT1);
        glDisable(GL_LIGHT2);
        glDisable(GL_LIGHT3);
        glDisable(GL_LIGHT4);
        
        glLightfv(GL_LIGHT0, GL_AMBIENT, sunAmbient); 
	    glLightfv(GL_LIGHT0, GL_SPECULAR, sunSpecular); 
	    glLightfv(GL_LIGHT0, GL_DIFFUSE, sunDiffuse); 
	    glLightfv(GL_LIGHT0, GL_POSITION, sunPosition);
	                     
             
     }else{
        glDisable(GL_LIGHT0); 
        glEnable(GL_LIGHT1);
        glEnable(GL_LIGHT2);
        glEnable(GL_LIGHT3);
        glEnable(GL_LIGHT4);
        
        glLightfv(GL_LIGHT1, GL_AMBIENT, refAmbient); 
	    glLightfv(GL_LIGHT1, GL_SPECULAR, refSpecular); 
	    glLightfv(GL_LIGHT1, GL_DIFFUSE, refDiffuse); 
	    glLightfv(GL_LIGHT1, GL_POSITION, ref1Position);
	    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, ref1Direction);
	    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, expoente);
	    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, angulo);
	    /*glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, quadratica);
	    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, linear);
	    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, constante);
        */
        	    
	    glLightfv(GL_LIGHT2, GL_AMBIENT, refAmbient); 
	    glLightfv(GL_LIGHT2, GL_SPECULAR, refSpecular); 
	    glLightfv(GL_LIGHT2, GL_DIFFUSE, refDiffuse); 
	    glLightfv(GL_LIGHT2, GL_POSITION, ref2Position);
	    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, ref2Direction);
	    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, expoente);
	    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, angulo);	    
	    /*glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, quadratica);
	    glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, linear);
	    glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, constante);
	    */
	    
	    glLightfv(GL_LIGHT3, GL_AMBIENT, refAmbient); 
	    glLightfv(GL_LIGHT3, GL_SPECULAR, refSpecular); 
	    glLightfv(GL_LIGHT3, GL_DIFFUSE, refDiffuse); 
	    glLightfv(GL_LIGHT3, GL_POSITION, ref3Position);
	    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, ref3Direction);
	    glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, expoente);
	    glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, angulo);	    
	    /*glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, quadratica);
	    glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, linear);
	    glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, constante);
	    */
        /*
	    glLightfv(GL_LIGHT4, GL_AMBIENT, refAmbient); 
	    glLightfv(GL_LIGHT4, GL_SPECULAR, refSpecular); 
	    glLightfv(GL_LIGHT4, GL_DIFFUSE, refDiffuse); 
	    glLightfv(GL_LIGHT4, GL_POSITION, ref4Position);
        glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, ref4Direction);
	    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, expoente);
	    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, angulo);
          */ 
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
     }     

} 


Pista *p;
Cenario *s;
Balao *b;
Carro *car;

Camera *c[14];

int cameraCorrente;

float x = 2000;
float teta = 3.1415;

float carx = 0;
float cary = -655;
float carz = 1.55;


//float camera[9] = {0,0,0,0,0,0,0,0,0};

float rx = 1;
float ry = -13;
float rz = 0;

void animacao(int i){
	float carx2 = 0;
	float cary2 = 0;

	
	if((x >= -310) && (x <= 310)){
		ry = -3;

		carx = x;
		cary = 5;
		carz = 1.2;
		
	
		
		x -= 4;
		carx2 = x; 
		cary2 = cary; 
		rz = 90 +((180/3.1415)*atan((cary2 - cary)/(carx2 - carx)));
		if(x <= -310){
			x = -1000; 
			rx = 1;
                        }
	}else if(x == -1000){
		ry = -13;
		carx = -320 - 255*sin(teta); 
		cary = 255*cos(teta) - 250; 
		carz = 2.16;
		teta += 0.01;
		carx2 = -320 - 255*sin(teta); 
		cary2 = 255*cos(teta) - 250; 
		
		if(teta < 1.57)
			rz = 90 +((180/3.1415)*atan((cary2 - cary)/(carx2 - carx)));
		else{
			carz = 2.8;
               rz = -90 +((180/3.1415)*atan((cary2 - cary)/(carx2 - carx)));
          }
		if(teta > 2.1){
			x = -2000;
			teta = 2.1850;
			
		}	
	}else if(x == -2000){
		ry = -13;
		carx = -655*sin(teta); 
		cary = 655*cos(teta); 
		carz = 2.16;
		
		teta += 0.005;
		carx2 = -655*sin(teta); 
		cary2 = 655*cos(teta); 
		
		rz = -90 +((180/3.1415)*atan((cary2 - cary)/(carx2 - carx)));
		if(teta > 3.1415){
			x = 2000;
		}
	}else if(x == 2000){
		ry = -13;
		carx = 655*sin(teta); 
		cary = 655*cos(teta); 
		carz = 2.16;
		
		teta -= 0.005;
		
		carx2 = 655*sin(teta); 
		cary2 = 655*cos(teta); 
		
		rz = -90 +((180/3.1415)*atan((cary2 - cary)/(carx2 - carx)));		
		if (teta < 2.150){
			carz = 3.2;
			//rx = 3;
                 }
		if(teta < 2.094){
			x = 1000;
			teta = 1.8815;
		}
	}else if(x == 1000){
		ry = -13;
		carx = 320 + 255*sin(teta); 
		cary = 255*cos(teta) - 250; 
		carz = 2.16;
		
		teta -= 0.01;
				
		carx2 = 320 + 255*sin(teta); 
		cary2 = 255*cos(teta) - 250; 
		
		if(teta < 1.57)
			rz = 90 +((180/3.1415)*atan((cary2 - cary)/(carx2 - carx)));
		else
			rz = -90 +((180/3.1415)*atan((cary2 - cary)/(carx2 - carx)));
		if(teta < 0){
			x = 310;
			teta = 0.0;
			rx = -1;
		}
	}
	
   	glutTimerFunc(	16, animacao, 5);
    glutPostRedisplay(); 
	
}
//funcao de reshape de ambos
void reshape(int width, int height){ 
    const float ar = (float) width / (float) height; 
 
    glViewport(0, 0, width, height); 

    glLoadIdentity(); 
    gluPerspective(45,(float)width/height ,1,800);
	
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glutPostRedisplay();    
} 


//funcao de keyboard de ambos
void keyboard(unsigned char key, int x, int y){
     int i; 
    switch (key){ 
    case 'q': 
    case 'Q': 
    	delete c[1];
    	exit(0); 
        break; 
    
    case '1':
	    perspectiva = 60;
    	cameraCorrente = 1;    	 
    	break;
    case '2':
	    perspectiva = 45;
    	cameraCorrente = 3;
    	break;
    case '3':
	    perspectiva = 45;
    	cameraCorrente = 6; 
    	break; 
    case '4':
	    perspectiva = 45;
         cameraCorrente = 8;        
    	break;
    case '5': 
	    perspectiva = 45;
    	cameraCorrente = 7;
    	break;
    case '6': 
	    perspectiva = 45;
    	cameraCorrente = 5;
    	break;
   	case '7':
   		perspectiva = 90; 
       	cameraCorrente = 4;
    	break;
    case '8':
	    perspectiva = 90; 
       	cameraCorrente = 9;
    	break;
    case '9':
    	perspectiva = 45;
  		cameraCorrente = 11; 
    	break;
    case 'a':
	    perspectiva = 45;
    	cameraCorrente = 12;
    	break;
	case 'c':
	    perspectiva = 45;
    	    cameraCorrente = 10;
    	break;
    case 's':
	    perspectiva = 45;
    	    cameraCorrente = 13;
    	break;
   	
    case 'l':
	    if(dia == 0)
               dia = 1;
        else
               dia = 0;
    	
    	atualizarLuz();
     break;
    }
    glutPostRedisplay(); 
} 
 
//Movimentacao no condominio
void special(int key, int x, int y){ 
 
    switch (key) 
    { 
    case GLUT_KEY_UP: 
        aprox += 10; 
        break; 
 
    case GLUT_KEY_DOWN: 
        aprox -= 10; 
        break; 
 
    case GLUT_KEY_LEFT:
    	if(cameraCorrente == 1){
		    perspectiva = 50;
    		cameraCorrente = 0;
    		break;
    	}
    	else if(cameraCorrente == 0)
    		break;
    	else if(cameraCorrente == 2){
		    perspectiva = 60;
    		cameraCorrente = 1;
    		break;
    	}
    		    	 
        side -= 10; 
        break;
 
    case GLUT_KEY_RIGHT:
    	if(cameraCorrente == 1){
		    perspectiva = 50;
    		cameraCorrente = 2;
    		break;
    	}
    	else if(cameraCorrente == 2)
    		break;
    	else if(cameraCorrente == 0){
		    perspectiva = 60;
    		cameraCorrente = 1;
    		break;
    	}
    	 
        side += 10; 
        break;
    } 
 
    glutPostRedisplay(); 
} 

void myinit(void){
	glClearColor(0, 0, 0, 0);
	//Iluminacao
	glEnable(GL_NORMALIZE); 
	glEnable(GL_COLOR_MATERIAL); 
	glEnable(GL_LIGHTING); 
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glDepthMask(GL_TRUE);
	
	atualizarLuz();
	
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	
	
	c[0] = new Camera(0.0, -707, 23, -310.0, -500, 0 , 0, 0, 1);// camera na linha de chegada (esquerda)
	c[1] = new Camera(0.0, -707, 23, 0.0, -653.0, 0.0, 0, 0.0, 1.0);// camera na linha de chegada (meio)
	c[2] = new Camera(0.0, -707, 23, 310.0, -500, 0 , 0.0, 0, 1);// camera na linha de chegada (direita)
	c[3] = new Camera(310.0, -610, 12, 0.0, -590, 0 , 0.0, 0, 1);// camera na curva 4
	c[4] = new Camera(-310.0, -610, 12, 0.0, -590, 0 , 0.0, 0, 1);// camera na curva 3
	c[5] = new Camera(-310.0, 24.5, 12, -370.0, 0, 0 , 0.0, 0, 1);// camera na curva 2
	c[6] = new Camera(310.0, 24.5, 12, 370.0, 0, 0 , 0.0, 0, 1);// camera na curva 1
	c[7] = new Camera(-310.0, 24.5, 12, 0.0, 0, 0.0 , 0.0, 0, 1);// camera na reta
	c[8] = new Camera(310.0, 24.5, 12, 0.0, 0, 0.0 , 0.0, 0, 1);// camera na reta
	c[9] = new Camera(0.0, -345, 620.0, 0.0, -345.0, 0.0, 0.0, 1.0, 0.0);// camera do balao/ camera do carro
//	c[10] = new Camera(carx, cary - 15,carz + 5, carx, cary, carz, 0, 0, 1);
    c[11] = new Camera(-20, -360, 645, 0.0, -345.0, 650.0, 0.0, 0.0, 1.0);
	
	perspectiva = 50;
	cameraCorrente = 1;
	
	p = new Pista();

	car = new Carro();
	s = new Cenario();
	//s->ligarCeu(0);
	
	b = new Balao();

}

void display (void){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
 
	
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	gluPerspective(perspectiva,(float)WIDTH/HEIGHT,1,10000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
     
     if ( cameraCorrente == 10)
	    gluLookAt( carx + 15*cos(80 + rz*(3.1415/180)), cary  + 15*sin(80 + rz*(3.1415/180)), carz + 3, carx, cary, carz + 3, 0, 0, 1);
      else if ( cameraCorrente == 12) 
	    gluLookAt( carx + 15*cos(90 + rz*(3.1415/180)), cary  + 15*sin(90 + rz*(3.1415/180)), carz + 3, carx, cary, carz + 3, 0, 0, 1);
	 else if( cameraCorrente == 13)
          gluLookAt( carx, cary, carz + 5, carx + 5*cos(80 + rz*(3.1415/180)), cary  + 5*sin(80 + rz*(3.1415/180)), carz + 3, 0, 0, 1);
	else if(cameraCorrente != 10)
		gluLookAt(c[cameraCorrente]->ox, c[cameraCorrente]->oy, c[cameraCorrente]->oz, c[cameraCorrente]->ax, c[cameraCorrente]->ay, c[cameraCorrente]->az, c[cameraCorrente]->nx, c[cameraCorrente]->ny, c[cameraCorrente]->nz);
	
     if(cameraCorrente == 9)
		s->ligarCeu(0);
		
	if(cameraCorrente == 11){
		s->setSkySize(0, 500, 0, 2600, 2600, 2600);
	}
	glPushMatrix();
		glTranslatef(carx, cary, carz);		
		glScalef(0.01, 0.01, 0.01);
		glRotatef(rz, 0, 0, 1);
		glRotatef(ry, 0, 1, 0);
		glRotatef(rx, 1, 0, 0);       
		car->draw();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0, -345,650);
		glRotatef(90,0,0,1);
		b->draw();
	glPopMatrix();
	glPushMatrix();
		p->draw();
	glPopMatrix();
	s->draw();
	
	s->ligarCeu(1);	
	s->setSkySize(0, 500, 0, 1600, 1600, 600);
	
	glFlush();
	glutSwapBuffers();
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Super Monks GP");
	myinit();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc( 16, animacao, 5); 
	glutKeyboardFunc(keyboard); 
    	glutSpecialFunc(special);
	glutMainLoop();
	return 0;
}
