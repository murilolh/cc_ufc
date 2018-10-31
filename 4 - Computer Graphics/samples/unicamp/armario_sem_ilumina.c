#include <GL/glut.h>
#include <stdlib.h>

static int shoulder = 0, elbow = 0, elbow2 = 0;

void init(void){

  glClearColor (1.0, 1.0, 1.0, 0.0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
}

void display(void){
  //glClear (GL_COLOR_BUFFER_BIT);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glPushMatrix();

  glRotatef ((GLfloat) shoulder, 0.0, 1.0, 0.0);

  /* Chao*/
  glColor3f(0.0,0.0,1.0);
  glPushMatrix();
  glTranslatef (0.0, -3.4, 0.0);
  glScalef (10.0, 0.2, 10.0);
  glutSolidCube (1.0);
  glPopMatrix();


/* Espelho
  glColor3f(1.0,1.0,1.0);
  glPushMatrix();
  glTranslatef (0.0, 6.0, -2.2);
  glScalef (4.6, 5.6, 0.2);
  glutSolidCube (1.0);
  glPopMatrix();

  glColor3f(0.0,0.0,0.7);
  glPushMatrix();
  glTranslatef (0.0, 6.0, -2.0);
  glScalef (4.0, 5.0, 0.2);
  glutSolidCube (1.0);
  glPopMatrix(); */


  /* armario */
  glColor3f(1.0,0.0,1.0);
  glPushMatrix();
  glScalef (4.0, 6.0, 2.0);
  glutSolidCube (1.0);
  glPopMatrix();

  /* porta 1*/

  glColor3f(1.0,1.0,0.0);
  glPushMatrix();
  glTranslatef (-2.0, 0.0, 1.1);
  glRotatef ((GLfloat) elbow, 0.0, 1.0, 0.0);
  glTranslatef (2.0, 0.0, -1.1);
  glTranslatef (-1.0, 0.0, 1.0);
  glScalef (2.0, 6.0, 0.2);
  glutSolidCube (1.0);
  glColor3f(1.0,0.0,0.0);
  glPushMatrix();    /* desenha macaneta 1*/
  glTranslatef (0.4, 0.0, 1.1);
  glScalef (0.2, 0.2, 0.2);
  glutSolidCube (1.0);
  glPopMatrix();
  glPopMatrix();

/* porta 2*/

  glColor3f(1.0,1.0,0.0);
  glPushMatrix();
  glTranslatef (2.0, 0.0, 1.1);
  glRotatef ((GLfloat) elbow2, 0.0, 1.0, 0.0);
  glTranslatef (-2.0, 0.0, -1.1);
  glTranslatef (1.0, 0.0, 1.0);
  glScalef (2.0, 6.0, 0.2);
  glutSolidCube (1.0);
  glColor3f(1.0,0.0,0.0);
  glPushMatrix();    /* desenha macaneta 2*/
  glTranslatef (-0.4, 0.0, 1.1);
  glScalef (0.2, 0.2, 0.2);
  glutSolidCube (1.0);
  glPopMatrix();
  glPopMatrix();

  /* origem volta para o sistema de coordenadas original */
  glPopMatrix();
  glutSwapBuffers();
}

void reshape (int w, int h){
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 30.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef (0.0, 0.0, -15.0);
}

void keyboard (unsigned char key, int x, int y){
  switch (key) {
  case 's':
    shoulder = (shoulder + 5) % 360;
    glutPostRedisplay();
    break;
  case 'S':
    shoulder = (shoulder - 5) % 360;
    glutPostRedisplay();
    break;
  case 'e':
    elbow = (elbow + 5) % 360;
    glutPostRedisplay();
    break;
  case 'E':
    elbow = (elbow - 5) % 360;
    glutPostRedisplay();
    break;
  case 'p':
    elbow2 = (elbow2 + 5) % 360;
    glutPostRedisplay();
    break;
  case 'P':
    elbow2 = (elbow2 - 5) % 360;
    glutPostRedisplay();
    break;
  case 27:
    exit(0);
    break;
  default:
    break;
  }
}

int main(int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  //glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
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
 
