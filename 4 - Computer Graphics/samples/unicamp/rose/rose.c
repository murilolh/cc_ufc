#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "image.h"

#define PI 3.1415

#define COORD_TEXTURA_PLANO 1.0
#define COORD_TEXTURA_rosie 1.0
#define COR_DO_PLANO 0.52,0.52,0.78,1.0
#define COR_DO_rosie 0.8,0.52,0.18,1.0
#define TEXTURA_DO_PLANO "montanhas.rgb"
#define TEXTURA_DO_rosie "camuflagem.rgb"

GLint WIDTH =800;
GLint HEIGHT=600;

GLfloat rosie_difusa[]    = { 0.32, 0.40, 0.47, 1.0 };
GLfloat rosie_especular[] = { 0.32, 0.40, 0.47, 1.0 };
GLfloat rosie_brilho[]    = { 50.0 };

GLfloat rosie_vermelho_difusa[]    = { 1.0, 0.0, 0.0, 1.0 };
GLfloat rosie_preto_difusa[]    = { 0.0, 0.0, 0.0, 1.0 };

//GLfloat rosie_especular[] = { 0.0, 0.0, 1.0, 1.0 };
//GLfloat rosie_brilho[]    = { 50.0 };

GLfloat posicao_luz0[]    = { 0.0, 12.0, 0.0, 1.0};
GLfloat cor_luz0[]        = { 1.0, 1.0, 1.0, 1.0};
GLfloat cor_luz0_amb[]    = { 1.0, 1.0, 1.0, 1.0};

GLfloat sem_cor[]         = { 0.0, 0.0, 0.0, 1.0};


GLfloat obs[3]={0.0,7.0,0.0};
GLfloat look[3]={0.0,3.0,0.0};
GLuint  textura_plano;
GLuint  textura_rosie;

GLshort texturas=1;
GLfloat tetaxz=0;
GLfloat raioxz=15;
GLuint  rosie;
int cabeca = 0;
int corpo = 0;
int ombro_dir=45;
int braco_dir=0;
int ombro_esq=0;
int braco_esq=0;
int rodas = 0;

GLfloat ctp[4][2]={
  {-COORD_TEXTURA_PLANO,-COORD_TEXTURA_PLANO},
  {+COORD_TEXTURA_PLANO,-COORD_TEXTURA_PLANO},
  {+COORD_TEXTURA_PLANO,+COORD_TEXTURA_PLANO},
  {-COORD_TEXTURA_PLANO,+COORD_TEXTURA_PLANO}
};

GLfloat cta[4][2]={
  {-COORD_TEXTURA_rosie,-COORD_TEXTURA_rosie},
  {+COORD_TEXTURA_rosie,-COORD_TEXTURA_rosie},
  {+COORD_TEXTURA_rosie,+COORD_TEXTURA_rosie},
  {-COORD_TEXTURA_rosie,+COORD_TEXTURA_rosie}
};


void reshape(int width, int height){
  WIDTH=width;
  HEIGHT=height;
  glViewport(0,0,(GLint)width,(GLint)height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70.0,width/(float)height,0.1,70.0);
  glMatrixMode(GL_MODELVIEW);
}

void compoe_rosie(void){
  GLUquadricObj *quadric;
  
    GLfloat laco[][3]={
    {-1.0,0.0,1.0},
    {+1.0,0.0,1.0},
    {0.0,0.0,4.0}
    };
      
  /* inicia a composicao de rosie */
  rosie = glGenLists(1);
  glNewList(rosie, GL_COMPILE);
  
  /* cor para a cabeça */

  glMaterialfv(GL_FRONT, GL_DIFFUSE, rosie_difusa);
  glMaterialfv(GL_FRONT, GL_SPECULAR, rosie_especular);  
  glMaterialfv(GL_FRONT, GL_SHININESS, rosie_brilho);  
  
  /* esfera luz */
  glPushMatrix();
  glTranslatef(posicao_luz0[0],posicao_luz0[1],posicao_luz0[2]);
  glutSolidSphere(0.3,5,5);
  glPopMatrix();


 
  glPushMatrix();
  
    glRotatef((GLfloat) cabeca, 0, 1, 0);
    
    /* cabeça */  
  
    glPushMatrix();
        quadric = gluNewQuadric();
        glTranslatef(0,10,-2);
        gluQuadricTexture(quadric, GL_TRUE);
        gluCylinder(quadric, 1, 1, 4, 12, 3);
        gluDisk(quadric, 0, 1, 30,30);
        glTranslatef(0,0,4);
        gluDisk(quadric, 0, 1, 30,30);
    glPopMatrix();    
      
    /* cor para os olhos */
    glMaterialfv(GL_FRONT, GL_DIFFUSE, rosie_vermelho_difusa);
    
      /* olho direito */
    
    glPushMatrix();      
        glRotatef(90, 0, 1, 0);
        glTranslatef(0.8,10,1);
        quadric = gluNewQuadric();
        gluQuadricTexture(quadric, GL_TRUE);
        gluCylinder(quadric, 0.3, 0.3, 0.2, 12, 3);
        glTranslatef(0,0,0.2);
        gluDisk(quadric, 0, 0.3, 30,30);  
    glPopMatrix();
      
    /* olho esquerdo */
    
    glPushMatrix();      
        glRotatef(90, 0, 1, 0);
        glTranslatef(-0.8,10,1);
        quadric = gluNewQuadric();
        gluQuadricTexture(quadric, GL_TRUE);
        gluCylinder(quadric, 0.3, 0.3, 0.2, 12, 3);
        glTranslatef(0,0,0.2);
        gluDisk(quadric, 0, 0.3, 30,30);  
    glPopMatrix();
    
    /* orelha esquerda */
    
    glPushMatrix();
        quadric = gluNewQuadric();        
        glTranslatef(0,10,2.0);        
        glRotatef(90, 0, 0, 1);
        gluQuadricTexture(quadric, GL_TRUE);
        gluCylinder(quadric, 0.3, 0.3, 0.2, 20, 3);
        glTranslatef(0,0,0.2);
        gluDisk(quadric, 0, 0.3, 30,30);
    glPopMatrix();
        
    /* orelha direita */
    
    glPushMatrix();
        quadric = gluNewQuadric();
        glTranslatef(0,10,-2.2);
        glRotatef(90, 0, 0, 1);
        gluQuadricTexture(quadric, GL_TRUE);        
        gluCylinder(quadric, 0.3, 0.3, 0.2, 20, 3);
        gluDisk(quadric, 0, 0.3, 30,30);
    glPopMatrix();

    glMaterialfv(GL_FRONT, GL_DIFFUSE, rosie_difusa);
    glMaterialfv(GL_FRONT, GL_SPECULAR, rosie_especular);  
    glMaterialfv(GL_FRONT, GL_SHININESS, rosie_brilho);  

    /* antena esquerda */
    
    glPushMatrix();
        quadric = gluNewQuadric();        
        glTranslatef(0,10,2.2);        
        glRotatef(90, 0, 0, 1);
        gluQuadricTexture(quadric, GL_TRUE);
        gluCylinder(quadric, 0.1, 0.1, 1, 20, 3);
        glTranslatef(0,0,1);
        glutSolidSphere(0.25,10,10); 
    glPopMatrix();
        
    /* antena direita */
        
    glPushMatrix();
        quadric = gluNewQuadric();
        glTranslatef(0,10,-3);
        glRotatef(90, 0, 0, 1);
        gluQuadricTexture(quadric, GL_TRUE);
        gluCylinder(quadric, 0.1, 0.1, 1, 20, 3);
        glTranslatef(0,0,-0.2);
        glutSolidSphere(0.25,10,10);        
    glPopMatrix();
          
  glPopMatrix();
 
  glPushMatrix();

    glRotatef((GLfloat) corpo, 0, 1, 0);
    
    /* corpo */
    
    glPushMatrix();
        quadric = gluNewQuadric();
        glTranslatef(0,9,0);        
        glRotatef(45, 0, 1, 0);
        glRotatef(90, 1, 0, 0);
        gluQuadricTexture(quadric, GL_TRUE);
        gluCylinder(quadric, 1, 4, 4, 4, 3);
    glPopMatrix();
        
    /* botão cima */
    
    glPushMatrix();      
        glMaterialfv(GL_FRONT, GL_DIFFUSE, rosie_vermelho_difusa);
        glRotatef(90, 0, 1, 0);
        glTranslatef(0, 8.0, 1.2);
        glRotatef(-25, 1, 0, 0);
        quadric = gluNewQuadric();
        gluQuadricTexture(quadric, GL_TRUE);
        gluCylinder(quadric, 0.3, 0.3, 0.2, 12, 3);
        glTranslatef(0,0,0.2);
        gluDisk(quadric, 0, 0.3, 30,30);
    glPopMatrix();
    
    
    /* botão meio */
    
    glPushMatrix();      
        glMaterialfv(GL_FRONT, GL_DIFFUSE, rosie_vermelho_difusa);
        glRotatef(90, 0, 1, 0);
        glTranslatef(0, 7.3, 1.6);
        glRotatef(-30, 1, 0, 0);
        quadric = gluNewQuadric();
        gluQuadricTexture(quadric, GL_TRUE);
        gluCylinder(quadric, 0.3, 0.3, 0.2, 12, 3);
        glTranslatef(0,0,0.2);
        gluDisk(quadric, 0, 0.3, 30,30);  
    glPopMatrix();
    
    /* botão baixo */
    
    glPushMatrix();      
        glMaterialfv(GL_FRONT, GL_DIFFUSE, rosie_vermelho_difusa);
        glRotatef(90, 0, 1, 0);
        glTranslatef(0, 6.5, 2.0);
        glRotatef(-30, 1, 0, 0);
        quadric = gluNewQuadric();
        gluQuadricTexture(quadric, GL_TRUE);
        gluCylinder(quadric, 0.3, 0.3, 0.2, 12, 3);
        glTranslatef(0,0,0.2);
        gluDisk(quadric, 0, 0.3, 30,30);  
    glPopMatrix();
          
    /* perna */
    
    glPushMatrix();
        quadric = gluNewQuadric();
        glTranslatef(0,3,0);
        glRotatef(45, 0, 1, 0); 
        glRotatef(270, 1, 0, 0);        
        gluQuadricTexture(quadric, GL_TRUE);
        gluCylinder(quadric, 3, 4, 2, 4, 10);
    glPopMatrix();
    
     /* perna */
  
    glPushMatrix();
        quadric = gluNewQuadric();
        glTranslatef(0,4,0);
        glRotatef(45, 0, 1, 0);
        glRotatef(90, 1, 0, 0);
        gluQuadricTexture(quadric, GL_TRUE);
        gluCylinder(quadric, 1, 2, 2, 4, 10);
    glPopMatrix();
    
    /* roda da frente*/
    
    glPushMatrix();
        quadric = gluNewQuadric();
        glTranslatef(1, 2, -1);
        gluQuadricTexture(quadric, GL_TRUE);
        gluCylinder(quadric, 0.5, 0.5, 2, 10, 10);
    glPopMatrix();
    
     /* roda de trás */
    
    glPushMatrix();
        quadric = gluNewQuadric();
        glTranslatef(-1, 2, -1);
        gluQuadricTexture(quadric, GL_TRUE);
        gluCylinder(quadric, 0.5, 0.5, 2, 10, 10);
    glPopMatrix();
    
    /* laço */
    
    glPushMatrix();
        quadric = gluNewQuadric();
        glTranslatef(-2.9, 2.3, 1);
        gluQuadricTexture(quadric, GL_TRUE);
        glColor3f(1, 0, 0);
       // glRotatef(90, 0, 0, 1);
//        glRotatef(60, 0, 1, 0);
        glBegin(GL_TRIANGLES); 
          glVertex3fv(laco[0]);
          glVertex3fv(laco[1]);
          glVertex3fv(laco[2]);
        glEnd();
    glPopMatrix();
        
  glPopMatrix();
     
  /* termina a composicao do rosie*/
  glEndList();
}

void display(void){
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glDepthMask(GL_TRUE);
  glClearColor(1.0,1.0,1.0,1.0);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  compoe_rosie(); 
  glPushMatrix();

  /* calcula a posicao do observador */
  obs[0]=raioxz*cos(2*PI*tetaxz/360);
  obs[2]=raioxz*sin(2*PI*tetaxz/360);
  gluLookAt(obs[0],obs[1],obs[2],look[0],look[1],look[2],0.0,1.0,0.0);

  /* habilita/desabilita uso de texturas*/

  glColor4f(COR_DO_PLANO);
  glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
  glBindTexture(GL_TEXTURE_2D,textura_plano);
          
  glEnable(GL_TEXTURE_2D);  
  glBegin(GL_QUADS);
  glTexCoord2fv(ctp[0]);  glVertex3f(-10,1,10);
  glTexCoord2fv(ctp[1]);  glVertex3f(10,1,10);
  glTexCoord2fv(ctp[2]);  glVertex3f(10,1,-10);
  glTexCoord2fv(ctp[3]);  glVertex3f(-10,1,-10);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  //glTranslatef(0.0,2.0,-3.0);  

  glColor4f(COR_DO_rosie);
  glBindTexture(GL_TEXTURE_2D,textura_rosie);
  glCallList(rosie);

  glPopMatrix();
  glutSwapBuffers();
}


void special(int key, int x, int y){
  switch (key) {
  case GLUT_KEY_UP:
    obs[1]=obs[1]+1;
    glutPostRedisplay();
    break;
  case GLUT_KEY_DOWN:
    obs[1] =obs[1]-1;
    glutPostRedisplay();
    break;
  case GLUT_KEY_LEFT:
    tetaxz=tetaxz+2;
    glutPostRedisplay();
    break;
  case GLUT_KEY_RIGHT:
    tetaxz=tetaxz-2;
    glutPostRedisplay();
    break;
  }
}

void keyboard(unsigned char key, int x, int y){
  switch (key) {
  case 27:
    exit(0);
    break;
  case 't':
    texturas = !texturas;
    glutPostRedisplay();
    break;
  case 'r':
    raioxz=raioxz+1;
    glutPostRedisplay();
    break;
  case 'c':
    cabeca = (cabeca + 5) % 360;
    glutPostRedisplay();
    break;
  case 'b':
    corpo = (corpo + 5) % 360;
    rodas = (rodas + 5) % 360;
    glutPostRedisplay();
    break;    
  case 'q':
    ombro_dir = (ombro_dir + 5) % 360;
    glutPostRedisplay();
    break;
  case 'R':
    raioxz=raioxz-1;
    if(raioxz==0){
      raioxz=1;
    }
    glutPostRedisplay();
    break;
  }
}

void carregar_texturas(void){
 /* IMAGE *img;
  GLenum gluerr;

  /* textura do plano 
  glGenTextures(1, &textura_plano);
  glBindTexture(GL_TEXTURE_2D, textura_plano);
  
  if(!(img=ImageLoad(TEXTURA_DO_PLANO))) {
    fprintf(stderr,"Error reading a texture.\n");
    exit(-1);
  }

  gluerr=gluBuild2DMipmaps(GL_TEXTURE_2D, 3, 
			   img->sizeX, img->sizeY, 
			   GL_RGB, GL_UNSIGNED_BYTE, 
			   (GLvoid *)(img->data));
  if(gluerr){
    fprintf(stderr,"GLULib%s\n",gluErrorString(gluerr));
    exit(-1);
  }

  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);

  /* textura do  
  glGenTextures(1, &textura_rosie);
  glBindTexture(GL_TEXTURE_2D, textura_rosie);

  
  if(!(img=ImageLoad(TEXTURA_DO_rosie))) {
    fprintf(stderr,"Error reading a texture.\n");
    exit(-1);
  }

  gluerr=gluBuild2DMipmaps(GL_TEXTURE_2D, 3, 
			   img->sizeX, img->sizeY, 
			   GL_RGB, GL_UNSIGNED_BYTE, 
			   (GLvoid *)(img->data));
  if(gluerr){
    fprintf(stderr,"GLULib%s\n",gluErrorString(gluerr));
    exit(-1);
  }

  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
  */
  
}

void init(){
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

  glLightfv(GL_LIGHT0, GL_DIFFUSE, cor_luz0);
  glLightfv(GL_LIGHT0, GL_SPECULAR, cor_luz0);
  glLightfv(GL_LIGHT0, GL_AMBIENT, cor_luz0_amb);
  glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz0);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_AUTO_NORMAL);
  glEnable(GL_NORMALIZE);

  carregar_texturas();
  glEnable(GL_TEXTURE_2D);
  compoe_rosie();
  
  
}

int main(int argc,char **argv){
  glutInitWindowPosition(0,0);
  glutInitWindowSize(WIDTH,HEIGHT);
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH|GLUT_DOUBLE);

  if(!glutCreateWindow("Rosie")) {
    fprintf(stderr,"Error opening a window.\n");
    exit(-1);
  }

  init();
  
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMainLoop();

  return(0);
}

