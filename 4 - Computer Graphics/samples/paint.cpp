/* newpaint.c   */

/* E. Angel, Interactive Computer Graphics			*/
/* A Top-Down Approach with OpenGL, Third Edition	*/
/* Addison-Wesley Longman, 2003						*/


/* paint program from chapter 3  */

/* This program illustrates the use of the glut library for
interfacing with a window system */


#define NULL		0
#define LINE		1
#define RECTANGLE	2
#define TRIANGLE	3
#define POINTS		4
#define TEXT		5

#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

void mouse(int, int, int, int);
void key(unsigned char, int, int);
void display(void);
void drawSquare(int, int);
void myReshape(GLsizei, GLsizei);

void myinit(void);

void screen_box(int, int, int);
void right_menu(int);
void middle_menu(int);
void color_menu(int);
void pixel_menu(int);
void fill_menu(int);
int  pick(int, int);

/* globals */

GLsizei wh = 500, ww = 500; /* initial window size			*/
GLfloat size = 3.0;			/* half side length of square	*/
int draw_mode = 0;			/* drawing mode					*/
int rx, ry;					/* raster position				*/

GLfloat r = 1.0, g = 1.0, b = 1.0;	/* drawing color */
int fill = 0;						/* fill flag	 */

void drawSquare(int x, int y)
{
        y=wh-y;
        glColor3ub( (char) rand()%256, (char) rand()%256, (char) rand()%256); 
        glBegin(GL_POLYGON);
                glVertex2f(x+size, y+size);
                glVertex2f(x-size, y+size);
                glVertex2f(x-size, y-size);
                glVertex2f(x+size, y-size);
        glEnd();
}


/* rehaping routine called whenever window is resized or moved */

void myReshape(GLsizei w, GLsizei h)
{

/* adjust clipping box */

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity(); 
        glOrtho(0.0, (GLdouble)w, 0.0, (GLdouble)h, -1.0, 1.0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity(); 

/* adjust viewport and  clear */

        glViewport(0,0,w,h);
		glClearColor (0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        display();
        glFlush();

/* set global size for use by drawing routine */

        ww = w;
        wh = h; 
}

void myinit(void)
{

	glViewport(0,0,ww,wh);


/* Pick 2D clipping window to match size of X window 
   This choice avoids having to scale object coordinates
   each time window is resized */

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity(); 
        glOrtho(0.0, (GLdouble) ww , 0.0, (GLdouble) wh , -1.0, 1.0);

/* set clear color to black and clear window */

        glClearColor (0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();
}



void mouse(int btn, int state, int x, int y)
{
    static int count;
    int where;
    static int xp[2],yp[2];

    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN) 
    {
       glPushAttrib(GL_ALL_ATTRIB_BITS);
       
       where = pick(x,y);
       glColor3f(r, g, b);

       if(where != 0)
       {
          count = 0;
          draw_mode = where;
       }
       else 
	   {
		   switch(draw_mode)
		   {
			case(LINE):
				  if(count==0)
				  {
					  count++;
					  xp[0] = x;
					  yp[0] = y;
				  }
				  else 
				  {
					  glBegin(GL_LINES); 
						 glVertex2i(x,wh-y);
						 glVertex2i(xp[0],wh-yp[0]);
					  glEnd();
					  draw_mode=0;
					  count=0;
				  }
				  break;
			case(RECTANGLE):
				  if(count == 0)
				  {
					  count++;
					  xp[0] = x;
					  yp[0] = y;
				  }
				  else 
				  {
					  if(fill)	glBegin(GL_POLYGON);
					  else		glBegin(GL_LINE_LOOP);
						 glVertex2i(x,wh-y);
						 glVertex2i(x,wh-yp[0]);
						 glVertex2i(xp[0],wh-yp[0]);
						 glVertex2i(xp[0],wh-y);
					  glEnd();
					  draw_mode=0;
					  count=0;
				  }
				  break;
			case (TRIANGLE):
				  switch(count)
				  {
					case(0):
					  count++;
					  xp[0] = x;
					  yp[0] = y;
					  break;
					case(1):
					  count++;
					  xp[1] = x;
					  yp[1] = y;
					  break;
					case(2): 
					  if(fill) glBegin(GL_POLYGON);
					  else glBegin(GL_LINE_LOOP);
						 glVertex2i(xp[0],wh-yp[0]);
						 glVertex2i(xp[1],wh-yp[1]);
						 glVertex2i(x,wh-y);
					  glEnd();
					  draw_mode=0;
					  count=0;
				  }
				  break;
			case(POINTS):
				  {
					 drawSquare(x,y);
					 count++;
				  }
				  break;
			case(TEXT):
				  {
					 rx=x;
					 ry=wh-y;
					 glRasterPos2i(rx,ry); 
					 count=0;
				  }
			}
	   }

       glPopAttrib();
       glFlush();
     }
}

int pick(int x, int y)
{
    y = wh - y;
    if     (y < wh-ww/10) return 0;
    else if(x < ww/10   ) return LINE;
    else if(x < ww/5    ) return RECTANGLE;
    else if(x < 3*ww/10 ) return TRIANGLE;
    else if(x < 2*ww/5  ) return POINTS;
	else if(x < ww/2    ) return TEXT;
    else return 0;
}

void screen_box(int x, int y, int s )
{
    glBegin(GL_QUADS);
      glVertex2i(x,   y  );
      glVertex2i(x+s, y  );
      glVertex2i(x+s, y+s);
      glVertex2i(x,   y+s);
    glEnd();
}

void right_menu(int id)
{
   if(id == 1) exit(0);
   else display();
}

void middle_menu(int id)
{

}

void color_menu(int id)
{
   if     (id == 1) {r = 1.0; g = 0.0; b = 0.0;}  // red
   else if(id == 2) {r = 0.0; g = 1.0; b = 0.0;}  // green
   else if(id == 3) {r = 0.0; g = 0.0; b = 1.0;}  // blue
   else if(id == 4) {r = 0.0; g = 1.0; b = 1.0;}  // cyan
   else if(id == 5) {r = 1.0; g = 0.0; b = 1.0;}  // magenta
   else if(id == 6) {r = 1.0; g = 1.0; b = 0.0;}  // yellow
   else if(id == 7) {r = 1.0; g = 1.0; b = 1.0;}  // white
   else if(id == 8) {r = 0.0; g = 0.0; b = 0.0;}  // black
}


void pixel_menu(int id)
{
   if      (id  == 1) size = 2 * size;
   else if (size > 1) size = size/2;
}

void fill_menu(int id)
{
   if (id == 1) fill = 1; 
   else         fill = 0;
}

void key(unsigned char k, int xx, int yy)
{
   if(draw_mode!=TEXT) 
   {
	   return;
   }
   else
   {
		glColor3f(1.0,1.0,0.5);
		glRasterPos2i(rx,ry);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, k);
		//glutStrokeCharacter(GLUT_STROKE_ROMAN,k);
		rx+=glutBitmapWidth(GLUT_BITMAP_9_BY_15,k);
   }
   
}

void display(void)
{
	int shift=0;
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    glClearColor (0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

	// Draw a White box for the line menu
    glColor3f(1.0, 1.0, 1.0);
    screen_box(0,wh-ww/10,ww/10);

	// Draw a Red box for the rectangle menu
    glColor3f(1.0, 0.0, 0.0);
    screen_box(ww/10,wh-ww/10,ww/10);

	// Draw a Green box for the triangle menu
    glColor3f(0.0, 1.0, 0.0);
    screen_box(ww/5,wh-ww/10,ww/10);

	// Draw a Blue box for the point menu
    glColor3f(0.0, 0.0, 1.0);
    screen_box(3*ww/10,wh-ww/10,ww/10);

    // Draw a yellow box for the point menu
	glColor3f(1.0, 1.0, 0.0);
    screen_box(2*ww/5,wh-ww/10,ww/10);

    // Draw a Black line on the line menu box
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
		glVertex2i(wh/40,wh-ww/20);
		glVertex2i(wh/40+ww/20,wh-ww/20);
    glEnd();

	// Draw a Black rectangle on the rectangle menu box
	screen_box(ww/10+ww/40,wh-ww/10+ww/40,ww/20);

	// Draw a Black triangle in the triangle menu box
    glBegin(GL_TRIANGLES);
       glVertex2i(ww/5+ww/40,wh-ww/10+ww/40);
       glVertex2i(ww/5+ww/20,wh-ww/40);
       glVertex2i(ww/5+3*ww/40,wh-ww/10+ww/40);
    glEnd();

	// Draw a Black point in the point menu	box
    glPointSize(3.0);
    glBegin(GL_POINTS);
       glVertex2i(3*ww/10+ww/20, wh-ww/20);
    glEnd();

	// Draw a Black text string on the text menu box
	glRasterPos2i(2*ww/5 + 10,wh-ww/20);
	glutBitmapCharacter  (GLUT_BITMAP_9_BY_15, 'A');
	shift=glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'A');

	glRasterPos2i(2*ww/5+ 10+shift,wh-ww/20);
	glutBitmapCharacter   (GLUT_BITMAP_9_BY_15, 'B');
	shift+=glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'B');

	glRasterPos2i(2*ww/5+ 10+shift,wh-ww/20);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'C');

    glFlush();
    glPopAttrib();
}


int main(int argc, char** argv)
{
    int c_menu, p_menu, f_menu;

	// Negotiate window session
    glutInit(&argc,argv);

	// Defines the display properties of the window to be created
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);

	// Defines the size of the window to be created
	glutInitWindowSize(500, 500);

	// Creates a window with the Title ("square")
    glutCreateWindow("square");

	// Register the Display callback function (display)
    glutDisplayFunc(display);

	// Create a color selection pop-up menu and a function associated with it
    c_menu = glutCreateMenu(color_menu);
		glutAddMenuEntry("Red",    1);
		glutAddMenuEntry("Green",  2);
		glutAddMenuEntry("Blue",   3);
		glutAddMenuEntry("Cyan",   4);
		glutAddMenuEntry("Magenta",5);
		glutAddMenuEntry("Yellow", 6);
		glutAddMenuEntry("White",  7);
		glutAddMenuEntry("Black",  8);

	// Create a pixel resize pop-up menu and a function associated with it
    p_menu = glutCreateMenu(pixel_menu);
		glutAddMenuEntry("increase pixel size", 1);
		glutAddMenuEntry("decrease pixel size", 2);

	// Create a fill selection mode pop-up menu	and function associated with it
    f_menu = glutCreateMenu(fill_menu);
		glutAddMenuEntry("fill on",  1);
		glutAddMenuEntry("fill off", 2);

	// Create a pop-up menu for clearing or quitting and function associated with it
    glutCreateMenu(right_menu);
		glutAddMenuEntry("quit", 1);
		glutAddMenuEntry("clear",2);
	// Attach the menu just created to the right mouse button
    glutAttachMenu(GLUT_RIGHT_BUTTON);

	// Create a pop-up menu for selecting color, pixel resize or fill mode
    glutCreateMenu(middle_menu);
		glutAddSubMenu("Colors",     c_menu);
		glutAddSubMenu("Pixel Size", p_menu);
		glutAddSubMenu("Fill",       f_menu);
	// Attach the menu just created to the right mouse button
    glutAttachMenu(GLUT_MIDDLE_BUTTON);

	// Initialization OpenGL commands
    myinit ();

	// Register callback function myReshape to be called when the window is resized
    glutReshapeFunc (myReshape);
	
	// Register callback function key to be called when a key is depressed
	glutKeyboardFunc(key);

	// Register callback function mouse to be called when a mouse event occurs
    glutMouseFunc (mouse);

	// Enter the event loop
    glutMainLoop();
	
	return 0;
}