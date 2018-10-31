#define LINE		1
#define RECTANGLE	2
#define TRIANGLE	3
#define BORRACHA        4
#define TEXT		5
#define LAPIS		6
#define FILLOFF         7
#define FILLON          8
#define NADA		9
#define PRETO           10
#define BRANCO          11
#define VERMELHO        12
#define CIANO           13
#define VERDE           14
#define MAGENTA         15
#define AZUL            16
#define AMARELO         17
#define ISIZE           18
#define DSIZE           19
#define CLEAR           20

#include <stdlib.h>
#include <GL/glut.h>

void myinit(void);
void myReshape(GLsizei, GLsizei);
void borralapis(int, int);
void voltar(void);
void clear(void);
int  ferramenta(int, int);
void mouse(int, int, int, int);
void key(unsigned char, int, int);
void screen_box(int, int, int, int);
void display(void);

GLsizei wh = 800, ww = 800;             // tamanho inicial da janela
GLfloat size = 1.0;			// metade do tamanho do quadrado da borracha e do lapis
int draw_mode[2];			// modo de desenho
int rx, ry;				// posição raster
GLfloat re = 0.0, ge = 0.5, be = 0.5;	// cor do fundo das opcoes
GLfloat rf = 0.0, gf = 0.9, bf = 0.9;	// cor do padrao fundo das opcoes
GLfloat rb = 1.0, gb = 1.0, bb = 1.0;	// cor do background
GLfloat r = 0.0, g = 0.0, b = 0.0;	// cor corrente do desenho
int fill = 0;				// preenchimento do desenho
int id[8];                              // estado do modo de desenho 
int count=0;                            // variavel que conta os passos do desenho do triangulo
int opcao;                              // guarda o modo de desenho corrente 
GLfloat xm,ym,xmm,ymm,xn,yn;            // guardam vertices variaveis dos modos de desenho  
GLint first, rubber;                    // variaveis usadas nos desenhos rubberband

void myinit(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); 
    gluOrtho2D(0.0, ww , 0.0, wh);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_COLOR_LOGIC_OP);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);    
    glClearColor (rb, gb, bb, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);    
    fill=0;    
    id[0]=1;
    id[1]=1;
    id[2]=1;
    id[3]=1;
    id[4]=1;
    id[5]=1;
    id[6]=2;
    id[7]=1;
}

void myReshape(GLsizei w, GLsizei h)
{        
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); 
    gluOrtho2D(0.0, w, 0.0, h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); 
    glViewport(0,0,w,h);
    glClearColor (rb, gb, bb, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);      
    wh = h;        
}

void borralapis(int x, int y)
{
    y=wh-y;
    glBegin(GL_POLYGON);
        glVertex2f(x+size, y+size);
        glVertex2f(x-size, y+size);
        glVertex2f(x-size, y-size);
        glVertex2f(x+size, y-size);
    glEnd();
    glFlush();
}

void clear(void)
{
    glClearColor (rb, gb, bb, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);       
}

int ferramenta(int x, int y)
{
    y = wh - y;
    if     (y < wh-ww/20)                                    return 0;
    else if(x < ww/20   )  				     return LINE;
    else if(x < ww/10    )                                   return RECTANGLE;
    else if(x < 3*ww/20 )                                    return TRIANGLE;
    else if(x < ww/5  )                                      return BORRACHA;
    else if(x < ww/4    )                                    return TEXT;
    else if(x < 3*ww/10)                                     return LAPIS;
    else if(x < 7*ww/10)                                     return NADA;
    else if((x < 7*ww/10 + ww/40) && (y > wh-ww/20+ ww/40))  return PRETO;
    else if((x < 7*ww/10 + ww/40) && (y < wh-ww/20+ ww/40))  return BRANCO;
    else if((x < 3*ww/4 ) && (y > wh-ww/20+ ww/40))          return VERMELHO;
    else if((x < 3*ww/4 ) && (y < wh-ww/20+ ww/40))          return CIANO;
    else if((x < 3*ww/4 + ww/40 ) && (y > wh-ww/20+ ww/40))  return VERDE; 
    else if((x < 3*ww/4 + ww/40 ) && (y < wh-ww/20+ ww/40))  return MAGENTA;
    else if((x < 4*ww/5 ) && (y > wh-ww/20+ ww/40))          return AZUL;
    else if((x < 4*ww/5 ) && (y < wh-ww/20+ ww/40))          return AMARELO;
    else if((x < 17*ww/20 ) && (y > wh-ww/20+ ww/40))        return ISIZE;
    else if((x < 17*ww/20 ) && (y < wh-ww/20+ ww/40))        return DSIZE;
    else if((x < 9*ww/10 ) && (y > wh-ww/20+ ww/40))         return FILLOFF;
    else if((x < 9*ww/10 ) && (y < wh-ww/20+ ww/40))         return FILLON;
    else if(x < 19*ww/20)                                    return CLEAR; 
    else if(x < ww)                                          exit(0);
    else return 0;
}

void move(int x, int y)
{   
    opcao = ferramenta(x,y);
    if (opcao == 0)
    {
       glLogicOp(GL_XOR);
       glColor3f(0.5, 0.5, 0.5); 
       switch(draw_mode[0])
	  {
	   case(LINE):
	      if(first == 1)
	      {
		glBegin(GL_LINES);
			glVertex2f(xm, ym);
			glVertex2f(xmm, ymm);
		glEnd();
		glFlush();
              }          
	      xmm = x;
	      ymm = (wh - y);
	      glBegin(GL_LINES);
		glVertex2f(xm, ym);
		glVertex2f(xmm, ymm);
	      glEnd();
	      glFlush();
	      first = 1;
           break;
           case(RECTANGLE):
              glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  
              if(first == 1)
	      {	
		 glRectf(xm, ym, xmm, ymm);
		 glFlush();
	      }
	      xmm = x;
	      ymm = (wh - y);
	      glRectf(xm, ym, xmm, ymm);
	      glFlush();
	      first = 1; 
              glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  
           break;
           case(TRIANGLE):
              if(count==2)
              {        
	         if(first == 1)
	         {
		    glBegin(GL_LINE_STRIP);
			glVertex2f(xm, ym);
			glVertex2f(xn, yn);
			glVertex2f(xmm, ymm); 
		    glEnd();
		    glFlush();
	         }        
	         xn = x;
	         yn = (wh - y);	
	         glBegin(GL_LINE_STRIP);
		     glVertex2f(xm, ym);
		     glVertex2f(xn, yn);
		     glVertex2f(xmm, ymm); 
		 glEnd();
	         glFlush();
	         first = 1;       
              }
           break;
           case(BORRACHA):
              glLogicOp(GL_COPY);
	      glColor3f( rb, gb, bb); 
	      borralapis(x,y);
           break;
           case(LAPIS):
              glLogicOp(GL_COPY);
              glColor3f( r, g, b); 
              borralapis(x,y);                   
	   break;
          }
       glColor3f(r, g, b);  
       glLogicOp(GL_COPY);
     }    
}


void mouse(int btn, int state, int x, int y)
{    
    glutPostRedisplay();
    glColor3f(r, g, b);
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN) 
    {
       glPushAttrib(GL_ALL_ATTRIB_BITS);
         opcao = ferramenta(x,y);         
	 if(opcao > 0) 
         {
	    int i,d;
            rubber=0;
            count=0;
            draw_mode[0] = opcao;
	    switch(draw_mode[0])
	    {
	        case(LINE):
		   d=0;                   
                   draw_mode[1] = opcao;
	        break;
		case(RECTANGLE):
		   d=1;
                   draw_mode[1] = opcao;
		break;
		case (TRIANGLE):
	  	   d=2;
                   draw_mode[1] = opcao;
	        break;
		case(BORRACHA):
		   d=3;
                   draw_mode[1] = opcao;
		break;  
		case(TEXT):
		   d=4;
                   draw_mode[1] = opcao;
		break;
                case(LAPIS):
		   d=5;
                   draw_mode[1] = opcao;
                break;                
                case(NADA):           		   
                   draw_mode[0]=draw_mode[1];
                break;
                case(PRETO):                
                   r= 0; g= 0; b= 0; 
                   draw_mode[0]=draw_mode[1];               
                break;
                case(BRANCO):    
                   r= 1; g= 1; b= 1;
                   draw_mode[0]=draw_mode[1];
                break;
                case(VERMELHO):
                   r= 1; g= 0; b= 0;
                   draw_mode[0]=draw_mode[1];
                break;
                case(CIANO):
		   r= 0; g= 1; b= 1;
                   draw_mode[0]=draw_mode[1];
		break;
                case(VERDE):
		   r= 0; g= 1; b= 0;
                   draw_mode[0]=draw_mode[1];
		break;
                case(MAGENTA):
		   r= 1; g= 0; b= 1;
                   draw_mode[0]=draw_mode[1];
		break;
                case(AZUL):
		   r= 0; g= 0; b= 1;
                   draw_mode[0]=draw_mode[1];
		break;
                case(AMARELO):
		   r= 1; g= 1; b= 0;
                   draw_mode[0]=draw_mode[1];
		break;
                case(ISIZE):
                   size = 1.2 * size;
                   draw_mode[0]=draw_mode[1];                   		    
		break;
                case(DSIZE):
                   size = size/1.2;
                   draw_mode[0]=draw_mode[1];                   	    
		break;
                case(FILLOFF):                
		   id[6]=2;
                   id[7]=1;
                   fill = 0;
                   draw_mode[0]=draw_mode[1];                   
                break;
                case(FILLON):		
		   id[6]=1;
                   id[7]=2;
                   fill = 1;
                   draw_mode[0]=draw_mode[1];                
		break;
                case(CLEAR):
                   clear();                   
                   draw_mode[0]=draw_mode[1];		    
		break;
            }
            if (opcao<7)
               for(i=0;i<6;i++)
	       {
		  if (i==d)
		    id[i]=2;
	          else
		    id[i]=1;
	       } 
         }
         else 
         {
            switch(draw_mode[0])
	    {
	        case(LINE):		
		case(RECTANGLE):
		   xm = x;
	           ym = (wh - y);		   
                   rubber = 1;
		   first = 0;
		break;
		case (TRIANGLE):
	  	   if(count==0)   
	           {          
		      xm = x;
		      ym = (wh - y);	  
		      count++;
		   }	 
	           else if (count==1) 
	           {
		      xmm = x;
		      ymm = (wh - y);
		      glBegin(GL_LINES);
			 glVertex2f(xm, ym);
			 glVertex2f(xmm, ymm);
		      glEnd();
		      glFlush();
		      count++;
		      rubber = 1;  
		      first = 0;
	           }
	        break;
		case(BORRACHA):
                   glColor3f( rb, gb, bb); 
		   borralapis(x,y);                  
		break;  
		case(TEXT):
		   rx=x;
		   ry=wh-y;           
                   glRasterPos2i(rx,ry);   		                   break;
                case(LAPIS):
                   glColor3f( r, g, b); 
		   borralapis(x,y);                   
		break;                               
            }
         }
       glPopAttrib();       
    }
    else if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN) 
    {
       glPushAttrib(GL_ALL_ATTRIB_BITS);
         int i;
         opcao = ferramenta(x,y);         
	 if(opcao > 0) 
         {  
            int m=0; 
            draw_mode[0] = opcao;
            switch(draw_mode[0])
            {
                case(PRETO):
                   rb= 0; gb= 0; bb= 0; m=1;
                break;
                case(BRANCO):    
                   rb= 1; gb= 1; bb= 1; m=1;
                break;
                case(VERMELHO):
                   rb= 1; gb= 0; bb= 0; m=1;
                break;
                case(CIANO):
		   rb= 0; gb= 1; bb= 1; m=1;
		break;
                case(VERDE):
		   rb= 0; gb= 1; bb= 0; m=1;
		break;
                case(MAGENTA):
		   rb= 1; gb= 0; bb= 1; m=1;
		break;
                case(AZUL):
		   rb= 0; gb= 0; bb= 1; m=1;
		break;
                case(AMARELO):
		   rb= 1; gb= 1; bb= 0; m=1;
		break;                            
            }
            if (m==1)
            {
                for(i=0;i<6;i++)	        
                  id[i]=1;    
                clear();   
            }      
         }    
       glPopAttrib();
    }
    else if (btn == GLUT_LEFT_BUTTON		&& 	state == GLUT_UP) 
    {
       glPushAttrib(GL_ALL_ATTRIB_BITS);
          if (rubber==1) 
          {
             switch(draw_mode[0])
             {
	         case(LINE):	            
		    xmm = x;
		    ymm = (wh - y);
		    glBegin(GL_LINES);
		       glVertex2f(xm, ym);
		       glVertex2f(xmm, ymm);
	            glEnd();
		    glFlush();
                 break;
                 case(RECTANGLE):
                    if(!fill) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  	   
		    xmm = x;
		    ymm = (wh - y);
                    glRectf(xm, ym, xmm, ymm);
                    if(fill)
                    { 
                       glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                       glRectf(xm, ym, xmm, ymm);
                    }
		    glFlush();
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
                 break;
                 case(TRIANGLE):
                    if(count==2)
                    {
                       xn = x;
	               yn = (wh - y);
	               if(fill) 
	               {
	                  glBegin(GL_POLYGON);
	                      glVertex2f(xm, ym);
			      glVertex2f(xn, yn);
			      glVertex2f(xmm, ymm); 
		          glEnd();
		          glBegin(GL_LINE_STRIP);
			      glVertex2f(xm, ym);
			      glVertex2f(xn, yn);
			      glVertex2f(xmm, ymm); 
		          glEnd();
		       }
	               else
	               {
	                  glBegin(GL_LINE_STRIP);
			      glVertex2f(xm, ym);
			      glVertex2f(xn, yn);
			      glVertex2f(xmm, ymm); 
		          glEnd();		
		       }
	               glFlush();
	               count=0;
	           }   
                 break;                 
             }
          }
       glPopAttrib();
     }	    
}

void key(unsigned char k, int xx, int yy)
{
   if(draw_mode[0]!=TEXT)
   { 
        switch (k)
        { 
	    case 'q':
            case 'x':
		exit(0);
            break;
            case 'c':
		clear();
            break;
	    case '+':
		size = 1.2 * size;
	    break;
	    case '-':
		size = size/1.2;
	    break;	
        }
        glutPostRedisplay();
   }
   else
   {
	glColor3f(r,g,b);
	glRasterPos2i(rx,ry);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, k);
	rx+=glutBitmapWidth(GLUT_BITMAP_9_BY_15,k);
	glFlush();
   }   
}

void screen_box(int x, int y, int s , int id)
{
    if (id<=1)
      glColor3f(rf, gf, bf); 
    else if (id==2)
      glColor3f(re, ge, be);
    else if (id==3)
      glColor3f(0, 0, 0);
    else if (id==4)
      glColor3f(1, 0, 0);
    else if (id==5)
      glColor3f(0, 1, 0);
    else if (id==6)
      glColor3f(0, 0, 1);
    else if (id==7)
      glColor3f(1, 1, 1);
    else if (id==8)
      glColor3f(0, 1, 1);
    else if (id==9)
      glColor3f(1, 0, 1);
    else if (id==10)
      glColor3f(1, 1, 0);
    glBegin(GL_QUADS);
      glVertex2i(x,   y  );
      glVertex2i(x+s, y  );
      glVertex2i(x+s, y+s);
      glVertex2i(x,   y+s);
    glEnd(); 
    glColor3f(0.0, 0.0, 0.0);  
    glBegin(GL_LINE_LOOP);
      glVertex2i(x,   y  );
      glVertex2i(x+s, y  );
      glVertex2i(x+s, y+s);
      glVertex2i(x,   y+s);
    glEnd();     
}

void display(void)
{
    int shift=0;
    glPushAttrib(GL_ALL_ATTRIB_BITS);
             
       screen_box(0        , wh-ww/20, ww/20, id[0]);   
       screen_box(ww/20    , wh-ww/20, ww/20, id[1]);
       screen_box(ww/10    , wh-ww/20, ww/20, id[2]);
       screen_box(3*ww/20  , wh-ww/20, ww/20, id[3]);
       screen_box(ww/5     , wh-ww/20, ww/20, id[4]);
       screen_box(ww/4     , wh-ww/20, ww/20, id[5]);
       screen_box(3*ww/10  , wh-ww/20, ww/20, 0);
       screen_box(7*ww/20  , wh-ww/20, ww/20, 0);
       screen_box(2*ww/5   , wh-ww/20, ww/20, 0);
       screen_box(9*ww/20  , wh-ww/20, ww/20, 0);
       screen_box(ww/2     , wh-ww/20, ww/20, 0);
       screen_box(11*ww/20 , wh-ww/20, ww/20, 0);
       screen_box(3*ww/5   , wh-ww/20, ww/20, 0);
       screen_box(13*ww/20 , wh-ww/20, ww/20, 0);
         screen_box(7*ww/10  , wh-ww/40, ww/40, 3);
         screen_box(7*ww/10 + ww/40 , wh-ww/40, ww/40, 4);
         screen_box(3*ww/4   , wh-ww/40, ww/40, 5);
         screen_box(3*ww/4  + ww/40 , wh-ww/40, ww/40, 6);
         screen_box(7*ww/10  , wh-ww/40 -ww/40, ww/40, 7);
         screen_box(7*ww/10 + ww/40, wh-ww/40 - ww/40, ww/40, 8);                                     
         screen_box(3*ww/4   , wh-ww/40 - ww/40, ww/40, 9);
         screen_box(3*ww/4  + ww/40 , wh-ww/40 - ww/40 , ww/40, 10);       
       screen_box(4*ww/5   , wh-ww/20, ww/20, 0);
         screen_box(17*ww/20 , wh-ww/40, ww/40, id[6]);
         screen_box(17*ww/20 + ww/40  , wh-ww/40, ww/40, id[6]);
         screen_box(17*ww/20 , wh-ww/20, ww/40, id[7]);
         screen_box(17*ww/20 + ww/40, wh-ww/20, ww/40, id[7]);
       screen_box(9*ww/10  , wh-ww/20, ww/20, 0);
       screen_box(19*ww/20 , wh-ww/20, ww/20, 0);

       glColor3f(0.0, 0.0, 0.0);	
        
       glBegin(GL_LINES);
	  glVertex2i(wh/80,wh-ww/40);
	  glVertex2i(wh/80+ww/40,wh-ww/40);
       glEnd();
       
       glBegin(GL_POLYGON);
           glVertex2i(ww/20+ww/80 , wh-ww/20+ww/80);
           glVertex2i(ww/20+ww/80 + ww/40 , wh-ww/20+ww/80);
	   glVertex2i(ww/20+ww/80 + ww/40 , wh-ww/20+ww/80 + ww/40);
           glVertex2i(ww/20+ww/80 , wh-ww/20+ww/80 + ww/40);
       glEnd();
       
       glBegin(GL_TRIANGLES);
           glVertex2i(ww/10+ww/80,wh-ww/20+ww/80);
           glVertex2i(ww/10+ww/40,wh-ww/80);
           glVertex2i(ww/10+3*ww/80,wh-ww/20+ww/80);
       glEnd();
       
       glRectf(3*ww/20 + ww/60, wh-ww/20 + ww/80,3*ww/20 + ww/30,wh-ww/20+ ww/40);
       glBegin(GL_LINE_STRIP);
          glVertex2i(3*ww/20 + ww/31, wh-ww/20+ ww/40);
          glVertex2i(3*ww/20 + ww/31, wh-ww/20+ ww/30);
	  glVertex2i(3*ww/20 + ww/55, wh-ww/20+ ww/30);
          glVertex2i(3*ww/20 + ww/55, wh-ww/20+ ww/42);        
       glEnd();
       
       glRasterPos2i(ww/5 + 6,wh-ww/40 -5);
       glutBitmapCharacter  (GLUT_BITMAP_8_BY_13, 'A');
       shift=glutBitmapWidth(GLUT_BITMAP_8_BY_13, 'A');
       glRasterPos2i(ww/5+ 6+shift,wh-ww/40 -5);
       glutBitmapCharacter   (GLUT_BITMAP_8_BY_13, 'B');
       shift+=glutBitmapWidth(GLUT_BITMAP_8_BY_13, 'B');
       glRasterPos2i(ww/5+ 6+shift,wh-ww/40 -5);
       glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'C');

       glBegin(GL_LINES);
          glVertex2i(ww/4 +ww/40-3  , wh-ww/20+ ww/70);
          glVertex2i(ww/4 +ww/40-3 , wh-ww/20+ ww/30);
          glVertex2i(ww/4 +ww/40+3  , wh-ww/20+ ww/70);
          glVertex2i(ww/4 +ww/40+3 , wh-ww/20+ ww/30);
          glVertex2i(ww/4 +ww/40-3  , wh-ww/20+ ww/70);
	  glVertex2i(ww/4 +ww/40+3  , wh-ww/20+ ww/70);		           
       glEnd(); 
       glBegin(GL_TRIANGLES);
           glVertex2f(ww/4 +ww/40-3 , wh-ww/20+ ww/30);
           glVertex2f(ww/4 +ww/40+3  , wh-ww/20+ ww/30);
           glVertex2f(ww/4 +ww/40+1.5,wh-ww/20+ ww/25);
       glEnd();      
        
       glColor3f(rb, gb, bb);
       glBegin(GL_POLYGON);
          glVertex2i(13*ww/20+ ww/40-5 , wh-ww/20 + 5);
          glVertex2i(13*ww/20+ ww/20 -5 , wh-ww/20 + 5);
          glVertex2i(13*ww/20+ ww/20 -5 , wh-ww/20 + 5 +ww/40);
          glVertex2i(13*ww/20+ ww/40-5, wh-ww/20 + 5 +ww/40);
       glEnd();
       glColor3f(0.0, 0.0, 0.0);
       glBegin(GL_LINE_LOOP);
          glVertex2i(13*ww/20+ ww/40-5 , wh-ww/20 + 5);
          glVertex2i(13*ww/20+ ww/20 -5 , wh-ww/20 + 5);
          glVertex2i(13*ww/20+ ww/20 -5 , wh-ww/20 + 5 +ww/40);
          glVertex2i(13*ww/20+ ww/40-5, wh-ww/20 + 5 +ww/40);
       glEnd();
       glColor3f(r, g, b);
       glBegin(GL_POLYGON);
          glVertex2i(13*ww/20+ 5 , wh-ww/27+ ww/30);
          glVertex2i(13*ww/20+ ww/40 +5 , wh-ww/27+ ww/30);
          glVertex2i(13*ww/20+ ww/40 +5 , wh-ww/27+ ww/30 -ww/40);
          glVertex2i(13*ww/20+ 5, wh-ww/27+ ww/30 -ww/40);
       glEnd();
       glColor3f(0.0, 0.0, 0.0);
       glBegin(GL_LINE_LOOP);
          glVertex2i(13*ww/20+ 5 , wh-ww/27+ ww/30);
          glVertex2i(13*ww/20+ ww/40 +5 , wh-ww/27+ ww/30);
          glVertex2i(13*ww/20+ ww/40 +5 , wh-ww/27+ ww/30 -ww/40);
          glVertex2i(13*ww/20+ 5, wh-ww/27+ ww/30 -ww/40);
       glEnd(); 

       glBegin(GL_LINES);
          glVertex2i(4*ww/5 , wh-ww/20+ ww/40);
          glVertex2i(17*ww/20 , wh-ww/20+ ww/40);
          glVertex2i(4*ww/5 + ww/40 , wh-ww/20+ ww/37+1);
          glVertex2i(4*ww/5 + ww/40 , wh-ww/20+ ww/21);
          glVertex2i(4*ww/5 + ww/65 , wh-ww/20+ ww/27);
          glVertex2i(4*ww/5 + ww/27 , wh-ww/20+ ww/27);
          glVertex2i(4*ww/5 + ww/65 , wh-ww/20+ ww/80);
          glVertex2i(4*ww/5 + ww/27 , wh-ww/20+ ww/80);          	      
       glEnd();
 
       if (id[6]==1)
          glColor3f(rf, gf, bf); 
       else if (id[6]==2)
          glColor3f(re, ge, be);
       glBegin(GL_LINES);
          glVertex2i(17*ww/20 +ww/40, ww);
          glVertex2i(17*ww/20 +ww/40, wh-ww/40-1);	      
       glEnd();
       if (id[7]==1)
          glColor3f(rf, gf, bf); 
       else if (id[7]==2)
          glColor3f(re, ge, be);
       glBegin(GL_LINES);
          glVertex2i(17*ww/20 +ww/40, wh-ww/40);
          glVertex2i(17*ww/20 +ww/40, wh-ww/20);	      
       glEnd();
       glColor3f(0.0, 0.0, 0.0);
       glBegin(GL_LINES);
          glVertex2i(17*ww/20 , wh-ww/20+ ww/40);
          glVertex2i(9*ww/10 , wh-ww/20+ ww/40);	      
       glEnd();
       glBegin(GL_LINE_LOOP);
          glVertex2i(17*ww/20 + ww/80 +3, wh-ww/20+ ww/25 +2);
          glVertex2i(17*ww/20 + ww/80 +3, wh-ww/20+ ww/35 +2);
          glVertex2i(17*ww/20 + ww/30 +3, wh-ww/20+ ww/35 +2);
          glVertex2i(17*ww/20 + ww/30 +3, wh-ww/20+ ww/25 +2);	      
       glEnd();
       glBegin(GL_POLYGON);
          glVertex2i(17*ww/20 + ww/80 +3, wh-ww/20+ ww/45 -2);
          glVertex2i(17*ww/20 + ww/80 +3, wh-ww/20+ ww/95 -2);
          glVertex2i(17*ww/20 + ww/30 +3, wh-ww/20+ ww/95 -2);
          glVertex2i(17*ww/20 + ww/30 +3, wh-ww/20+ ww/45 -2);	      
       glEnd();

       glRasterPos2i(9*ww/10 +6 ,wh-ww/40 -5);
       glutBitmapCharacter  (GLUT_BITMAP_8_BY_13, 'C');
       shift=glutBitmapWidth(GLUT_BITMAP_8_BY_13, 'C');
       glRasterPos2i(9*ww/10 +6 +shift ,wh-ww/40 -5);
       glutBitmapCharacter  (GLUT_BITMAP_8_BY_13, 'L');
       shift=glutBitmapWidth(GLUT_BITMAP_8_BY_13, 'L');
       glRasterPos2i(9*ww/10 +6 +2*shift ,wh-ww/40 -5);
       glutBitmapCharacter  (GLUT_BITMAP_8_BY_13, 'R');

       glBegin(GL_LINES);
          glVertex2i(19*ww/20 + ww/80 +3, wh-ww/20+ ww/80 +3);
          glVertex2i(19*ww/20 + ww/30 +3, wh-ww/20+ ww/30 +3);
	  glVertex2i(19*ww/20 + ww/30 +3, wh-ww/20+ ww/80 +3);
          glVertex2i(19*ww/20 + ww/80 +3, wh-ww/20+ ww/30 +3);        
       glEnd();
                 
    glPopAttrib();
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(ww, wh);
    glutInitWindowPosition(0, 0);    
    glutCreateWindow("PAINT");
    myinit ();
    glutDisplayFunc(display);    
    glutReshapeFunc (myReshape);
    glutKeyboardFunc(key);
    glutMouseFunc (mouse);
    glutMotionFunc(move);	    
    glutMainLoop();    
}
