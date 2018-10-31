#include <GL/glut.h>
#include <stdlib.h>

void display(void){
  glEnable(GL_DEPTH_TEST);

  glClearColor(1.0,1.0,1.0,1.0);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


  glPushMatrix();

  glColor3f(1.0, 0.0, 0.0);
  /* Cubo 1 */
  glPushMatrix();
  glTranslatef (-2.0, 0.0, 0.0);
  glScalef (2.0, 1.0, 4.0);
  glutSolidCube (1.0);
  glPopMatrix();


  glColor3f(0.0, 1.0, 0.0);
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
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glClearColor(1.0,1.0,1.0,1.0);

}

int main(int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
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
