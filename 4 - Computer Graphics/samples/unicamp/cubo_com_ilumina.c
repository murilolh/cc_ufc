#include <GL/glut.h>
#include <stdlib.h>
#include "image.h"

GLfloat cubo_1_difusa[]    = { 1.0, 0.0, 0.0, 1.0 };
GLfloat cubo_1_especular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat cubo_1_brilho[]    = { 50.0 };

GLfloat cubo_2_difusa[]    = { 0.0, 1.0, 0.0, 1.0 };
GLfloat cubo_2_especular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat cubo_2_brilho[]    = { 50.0 };

GLfloat posicao_luz[]    = { 0.0, 4.0, 0.0, 1.0};
GLfloat cor_luz[]        = { 1.0, 1.0, 1.0, 1.0};
GLfloat cor_luz_amb[]    = { 0.3, 0.3, 0.3, 1.0};

GLint gouraud=0;


void display(void){
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);

  glDepthMask(GL_TRUE);
  glClearColor(1.0,1.0,1.0,1.0);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  if(gouraud){
    glShadeModel(GL_SMOOTH);
  }
  else{
    glShadeModel(GL_FLAT);
  }

  glPushMatrix();

    /* propriedades do material do cubo 1 */
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cubo_1_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cubo_1_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, cubo_1_brilho);

  /* Cubo 1 */
  glPushMatrix();
  glTranslatef (-2.0, 0.0, 0.0);
  glScalef (2.0, 1.0, 4.0);
  glutSolidCube (1.0);
  glPopMatrix();

    /* propriedades do material da esfera 1 */
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cubo_2_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cubo_2_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, cubo_2_brilho);
   
  /* Esfera 1 */
  glPushMatrix();
  glTranslatef (2.0, 0.0, 0.0);
  glutSolidSphere(2.0,30,30);
  glPopMatrix();

  glPopMatrix();
  glutSwapBuffers();
}

void reshape (int w, int h){
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef (0.0, 0.0, -10.0);
}
void keyboard(unsigned char key, int x, int y){
  switch (key) {
  case 27:                                         // tecla Esc (encerra o programa)
	exit(0);
	break;
  }
}

void init(void){
  glClearColor(1.0,1.0,1.0,1.0);
  gouraud=1;
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

  glLightfv(GL_LIGHT0, GL_DIFFUSE, cor_luz);
  glLightfv(GL_LIGHT0, GL_SPECULAR, cor_luz);
  glLightfv(GL_LIGHT0, GL_AMBIENT, cor_luz_amb);
  glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz);

  
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);


  glEnable(GL_AUTO_NORMAL);
  glEnable(GL_NORMALIZE);

}

int main(int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH|GLUT_DOUBLE);
  glutInitWindowSize (500, 500); 
  glutInitWindowPosition (100, 100);
  glutCreateWindow (argv[0]);
  init ();
  glutDisplayFunc(display); 
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}
