#include <GL/glut.h>
#include <stdlib.h>

void init(void){
  glClearColor (0.0, 0.0, 0.0, 0.0);
}

void display(void){
  glClear (GL_COLOR_BUFFER_BIT);
  glPushMatrix();

  /* Cubo 1 */
  glPushMatrix();
  glTranslatef (-2.0, 0.0, 0.0);
  glScalef (2.0, 1.0, 4.0);
  glutWireCube (1.0);
  glPopMatrix();
   
  /* Cubo 2 */
  glPushMatrix();
  glRotatef (25.0, 0.0, 0.0, 1.0);
  glTranslatef (2.0, 0.0, 0.0);
  glScalef (2.0, 1.0, 4.0);
  glutWireCube (1.0);
  glPopMatrix();

   /* Cubo 3 */
  glPushMatrix();
  glTranslatef (0.0, 2.0, 0.0);
  glScalef (2.0, 1.0, 4.0);
  glutWireCube (1.0);
  glPopMatrix();

     /* Cubo 4 */
  glPushMatrix();
  glTranslatef (0.0, -2.0, 0.0);
  glScalef (2.0, 1.0, 4.0);
  glutWireCube (1.0);
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

int main(int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
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
