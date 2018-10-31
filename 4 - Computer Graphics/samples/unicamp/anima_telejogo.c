/* programa TELEJOGO */
/* Prof. Marco Antonio G. de Carvalho, UNICAMP-2006 */
/* EXEMPLO DE ANIMACAO */

#include <GL/glut.h>
#include <stdlib.h>

GLint movebola=0;
GLint direcao=1;

void init(void);
void display(void);
void bola(int passo);
void keyboard(unsigned char key, int x, int y);

int main(int argc, char** argv){
  glutInit(&argc, argv);
//  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize (600, 400);
  glutInitWindowPosition (100, 100); 
  glutCreateWindow ("TELEJOGO");
  init();
  glutDisplayFunc(display);
  glutTimerFunc(10,bola,1);
  glutKeyboardFunc(keyboard);
  //glutMouseFunc(mouse);
  glutMainLoop();
  return 0;
}

void init(void){
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glOrtho (0, 600, 0, 400, -1 ,1);
}

void display(void){
  glClear(GL_COLOR_BUFFER_BIT);

 // glPolygonMode(GL_BACK, GL_LINE);
  glColor3f(1.0, 1.0, 1.0);
  glLineWidth(15.0);
  glBegin(GL_LINE_LOOP);
  glVertex2i(2,2);  glVertex2i(599,2);
  glVertex2i(599,399); glVertex2i(2,399);
  glEnd();

  glBegin(GL_LINES);
  glVertex2i(100,190);  glVertex2i(100,240);
  glVertex2i(500,190);  glVertex2i(500,240);
  glEnd();

  glPointSize(15.0);
  glBegin(GL_POINTS);
  glVertex2i(movebola+200,210);
  glEnd();

//  glFlush();
  glutSwapBuffers();
 }

void keyboard(unsigned char key, int x, int y){
  switch (key) {
  case 27:
	exit(0);
	break;
  }
}

void bola(int passo)
{
if(direcao==1)
{
movebola += 1;
if(movebola==290) direcao = 0;
}

else
{
movebola -= 1;
if(movebola==-90) direcao = 1;
}
glutPostRedisplay();
glutTimerFunc(10,bola, 1);

}

