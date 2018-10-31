
/* Copyright (c) Mark J. Kilgard, 1994. */

/* This program is a modification of Mark J. Kilgard's program
   freely distributable without licensing fees and is provided 
   without guarantee or warrantee expressed or implied. This 
   program is -not- in the public domain. 
   It involves an animated sequence of the Stroke Font rotating in
   three dimensions.   
*/
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <GL/glut.h>
 
float spin = 0.0;

// This is a simplified form of the stroke_output function

void stroke_output(GLfloat x, GLfloat y, char *string)
{
  int len, i;	// Length of string, and loop variables
  glPushMatrix();
  glTranslatef(x, y, 0);
  glScalef(0.005, 0.005, 0.005);  // Stroke Fonts are BIG, so scale them down!
  len = (int) strlen(string);
  for (i=0; i<len; i++)
     // Send Character to print out in stroke font
    glutStrokeCharacter(GLUT_STROKE_ROMAN, string[i]);  
  glPopMatrix();
}

void
display(void)
{
 glClear(GL_COLOR_BUFFER_BIT);
  spin += 5.0;
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluPerspective(40.0, 1.0, 0.1, 20.0);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  gluLookAt(0.0, 0.0, 4.0,  /* eye is at (0,0,4) */
    0.0, 0.0, 0.0,      /* center is at (0,0,0) */
    0.0, 1.0, 0.);      /* up is in postivie Y direction */
  glPushMatrix();
  glTranslatef(0, 0, -4);
  glRotatef(spin, 0, 1, 0);  // Rotate around Y axis
  stroke_output(-2.5, 1.1, "  This is written in a");
  stroke_output(-2.5, 0, " GLUT stroke font.");
  stroke_output(-2.5, -1.1, "using 3D perspective.");
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glFlush();
  glutSwapBuffers();
  glutPostRedisplay();
}

void
reshape(int w, int h)
{
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, w, 0, h);
  glScalef(1, -1, 1);
  glTranslatef(0, -h, 0);
  glMatrixMode(GL_MODELVIEW);
}

int
main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(465, 250);
  glutCreateWindow("GLUT bitmap & stroke font example");
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glColor3f(0, 0, 0);
  glLineWidth(3.0);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMainLoop();
  return 0;             /* ANSI C requires main to return int. */
}
