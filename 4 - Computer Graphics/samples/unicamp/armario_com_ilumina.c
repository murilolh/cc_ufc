#include <GL/glut.h>
#include <stdlib.h>

static int shoulder = 0, elbow = 0, elbow2 = 0;

GLfloat chao_difusa[]    = { 0.0, 0.0, 1.0, 1.0 };
GLfloat chao_especular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat chao_brilho[]    = { 50.0 };

GLfloat arm_difusa[]    = { 1.0, 0.0, 1.0, 1.0 };
GLfloat arm_especular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat arm_brilho[]    = { 50.0 };

GLfloat porta_difusa[]    = { 1.0, 1.0, 0.0, 1.0 };
GLfloat porta_especular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat porta_brilho[]    = { 50.0 };

GLfloat macaneta_difusa[]    = { 1.0, 0.0, 0.0, 1.0 };
GLfloat macaneta_especular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat macaneta_brilho[]    = { 50.0 };

GLfloat posicao_luz[]    = { 0.0, 4.0, 0.0, 1.0};
GLfloat cor_luz[]        = { 1.0, 1.0, 1.0, 1.0};
GLfloat cor_luz_amb[]    = { 0.3, 0.3, 0.3, 1.0};

GLint gouraud=0;


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

  glRotatef ((GLfloat) shoulder, 0.0, 1.0, 0.0);

      /* propriedades do material do chao */
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, chao_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, chao_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, chao_brilho);

  /* Chao*/
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


        /* propriedades do material do armario */
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, arm_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, arm_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, arm_brilho);

  /* armario */
  glColor3f(1.0,0.0,1.0);
  glPushMatrix();
  glScalef (4.0, 6.0, 2.0);
  glutSolidCube (1.0);
  glPopMatrix();

        /* propriedades do material do porta */
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, porta_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, porta_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, porta_brilho);

  /* porta 1*/

  glPushMatrix();
  glTranslatef (-2.0, 0.0, 1.1);
  glRotatef ((GLfloat) elbow, 0.0, 1.0, 0.0);
  glTranslatef (2.0, 0.0, -1.1);
  glTranslatef (-1.0, 0.0, 1.0);
  glScalef (2.0, 6.0, 0.2);
  glutSolidCube (1.0);
        /* propriedades do material da macaneta */
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, macaneta_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, macaneta_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, macaneta_brilho);

  glPushMatrix();    /* desenha macaneta 1*/
  glTranslatef (0.4, 0.0, 1.1);
  glScalef (0.2, 0.2, 0.2);
  glutSolidCube (1.0);
  glPopMatrix();
  glPopMatrix();

        /* propriedades do material do porta */
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, porta_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, porta_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, porta_brilho);

/* porta 2*/

  glPushMatrix();
  glTranslatef (2.0, 0.0, 1.1);
  glRotatef ((GLfloat) elbow2, 0.0, 1.0, 0.0);
  glTranslatef (-2.0, 0.0, -1.1);
  glTranslatef (1.0, 0.0, 1.0);
  glScalef (2.0, 6.0, 0.2);
  glutSolidCube (1.0);
        /* propriedades do material da macaneta */
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, macaneta_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, macaneta_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, macaneta_brilho);

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
 
