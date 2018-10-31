#include <GL/glut.h>
#include <stdlib.h>

void init(void)
{
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glClearColor (0.0, 0.0, 0.0, 0.0);
  glShadeModel (GL_FLAT);
}

void displayObjects(void) 
{
   glColor3f(0.0, 0.0, 1.0);
   glPushMatrix ();
   glRotatef (30.0, 1.0, 0.0, 0.0);
   glPushMatrix ();
   glTranslatef (-0.80, 0.35, 0.0); 
   glRotatef (100.0, 1.0, 0.0, 0.0);
//   glutSolidTorus (0.275, 0.85, 16, 16);
   glutWireTorus (0.275, 0.85, 16, 16);
   glPopMatrix ();

   glColor3f(1.0, 0.0, 0.0);
   glPushMatrix ();
   glTranslatef (-0.75, -0.50, 0.0); 
   glRotatef (10.0, 0.0, 0.0, 1.0);
   glRotatef (10.0, 1.0, 0.0, 0.0);
//   glutSolidCube (1.5);
   glutWireCube (1.5);
   glPopMatrix ();

   glColor3f(0.0, 1.0, 0.0);
   glPushMatrix ();
   glTranslatef (0.75, 0.60, 0.0); 
   glRotatef (30.0, 1.0, 0.0, 0.0);
//   glutSolidSphere (1.0, 16, 16);
   glutWireSphere (1.0, 16, 16);
   glPopMatrix ();

   glColor3f(1.0, 1.0, 0.0);
   glPushMatrix ();
   glTranslatef (0.70, -0.90, 0.25); 
//   glutSolidOctahedron ();
   glutWireOctahedron ();
   glPopMatrix ();

   glPopMatrix ();
   glutSwapBuffers();
}


void display(void)
{

  glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  displayObjects ();
}

void reshape(int w, int h)
{

   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
/*   if (w <= h)
      glOrtho (-2.25, 2.25, -2.25*h/w, 2.25*h/w, -10.0, 10.0);
   else 
      glOrtho (-2.25*w/h, 2.25*w/h, -2.25, 2.25, -10.0, 10.0);*/
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef (0.0, 0.0, -5.0);

}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
   }
}


int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (250, 250);
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init();
   glutReshapeFunc(reshape);
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0; 
}
