//**************************************************************
//                                                             *
// TRABALHO FINAL DE MÈTODOS NUMÈRICOS II                      *
// SEMESTRE: 2009.1                                            *
// DUPLA:                                                      *
//       Cícero Antônio Cavalcante de Araújo      Mat:0286731  *
//       Murilo Lima de Holanda                   Mat:0286740  *
//                                                             *
// Implementação de Método de Diferenças Finitas               * 
//				                               *
// Controles de Movimento e Direção de Câmera:                 *
// W  -Move para frente                                        *
// S  -Move para baixo                                         *
// A  -Move para esquerda                                      * 
// D  -Move para direita                                       *
// BOTÃO ESQUERDO -controla direção da Câmera                  *
// BOTÃO DIREITO  -controla altura da Câmera                   *
//				                               *
//**************************************************************
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define BASECONTORNO  1
#define EIXOS         2
#define PONTOS        3

GLfloat rotX=20, rotY=-14, rotX_ini, rotY_ini;
GLfloat camX=12.63, camY=13, camZ=32.89, camY_ini;       
int x_ini,y_ini,bot;
float sinhor,coshor,sinver,cosver;
int deltax, deltay;

float pontos[64][3];
float adj[9][3];

int   larguraJanela = 800, alturaJanela = 800;
float faspect;
float angulo = 45;

void visualizacao(void);
void resize(int width, int height);
void myinit(void);
void display(void);
void teclado(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void move(int x, int y);
void idle(void);
void cria_vetor_X(float A[64][64], float resultado[64], float vet[64]);
void cria_matriz_C(float A[64][64], float C[64][64]);
void cria_vetor_G(float A[64][64], float resultado[64], float v_G[64]);
void mult_MV(float M[64][64], float V[64], float aux[64]);
void cria_vetor_de_iteracoes(float A[64][64], float v_G[64], float vet_x[64], float aux[64]);
void troca_V(float vet1[64], float vet2[64]);
float retorna_maior(float V[64]);
float calculo_do_delta(float vet_x[64], float vet_1[64], float vet_aux[64]);
void gauss_jacobi(float A[64][64], float solucao[64], float resultado[64]);
int ponto(int a, int b);
float contorno(int i, int j);
void get_pontos();

void visualizacao(void)
{
   faspect= larguraJanela/alturaJanela;
   glLoadIdentity ();
   glMatrixMode (GL_PROJECTION);
   gluPerspective(angulo,faspect,1,400);
   glMatrixMode (GL_MODELVIEW);
   glClearColor (0.0, 0.0, 0.0, 0.0);  
   glLoadIdentity();
}

void resize(int width, int height)
{
   larguraJanela = width;
   alturaJanela = height;   
   glLoadIdentity ();
   glMatrixMode (GL_PROJECTION);   
   glClearColor (0.0, 0.0, 0.0, 0.0);  
   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity();
   glViewport(0, 0, larguraJanela, alturaJanela);
}

void myinit(void) 
{
   visualizacao(); 
   glEnable(GL_DEPTH_TEST);
      
   glNewList(BASECONTORNO,GL_COMPILE);   glPushAttrib(GL_ALL_ATTRIB_BITS);
        glBegin(GL_QUADS);
              glColor3f (1.0, 1.0, 1.0);              
              glVertex3f(0.000000, 0.000000, 0.000000);
              glVertex3f(0.000000, 0.000000, 10.000000);
              glVertex3f(8.000000, 0.000000, 10.000000);
              glVertex3f(8.000000, 0.000000, 0.000000);  
              
              glVertex3f(0.000000, 1.000000, 10.000000);
              glVertex3f(8.000000, 1.000000, 10.000000);
              glVertex3f(8.000000, 0.000000, 10.000000);
              glVertex3f(0.000000, 0.000000, 10.000000);
              
              glVertex3f(8.000000, 0.000000, 10.000000);
              glVertex3f(8.000000, 1.000000, 10.000000);
              glVertex3f(8.000000, 1.000000, 0.000000);
              glVertex3f(8.000000, 0.000000, 0.000000);
	glEnd();	
   glPopAttrib();
   glEndList();
   
   glNewList(EIXOS,GL_COMPILE);
   glPushAttrib(GL_ALL_ATTRIB_BITS);
	glBegin(GL_LINES);
	      glColor3f (1.0, 0.0, 0.0);
	      glVertex3f(0.0, 0.0, 0.0);
	      glVertex3f(20.0, 0.0, 0.0);

	      glColor3f (0.0, 1.0, 0.0);
	      glVertex3f(0.0, 0.0, 0.0);
	      glVertex3f(0.0, 20.0, 0.0);

	      glColor3f (0.0, 0.0, 1.0);
	      glVertex3f(0.0, 0.0, 0.0);
	      glVertex3f(0.0, 0.0, 20.0);
        glEnd();
   glPopAttrib();
   glEndList(); 
   
   glNewList(PONTOS,GL_COMPILE);
   glPushAttrib(GL_ALL_ATTRIB_BITS);
   	 
             int u,point,i,j,k,l,a;
             float e = 0.1;
             //for(i=1;i<=9;i++)
              //for(j=1;j<=7;j++)
	      //{
                  i=1;j=1; a=1;
		   point = ponto(i,j);
		   for(k=-1;k<=1;k++)
            	      for(l=-1;l<=1;l++)
            	      {
                	  if((k!=0) || (l!=0))
                          {
                             u = contorno(i+k,j+l);
                             printf("\n\n\n%d      %d       %d     %d     %d\n\n\n",k,l,u,a,ponto(i+k,j+l));
               		     if(u>=0)
                             {
                                adj[a][0] = j+l;
             		        adj[a][1] = u;
             		        adj[a][2] = i+k;
                             }
                             else
                             {
                  	        adj[a][0] = pontos[ponto(i+k,j+l)][1];
             		        adj[a][1] = pontos[ponto(i+k,j+l)][2];
             		        adj[a][2] = pontos[ponto(i+k,j+l)][0];
                             }
                             a++;
                          }
            	      }
                   glColor3f (0.0, 1.0, 1.0);
                   glBegin(GL_QUADS);
	              glVertex3f(pontos[point][1],pontos[point][2],pontos[point][0]);
	              glVertex3f(adj[4][0],adj[4][1],adj[4][2]);
              	      glVertex3f(adj[1][0],adj[1][1],adj[1][2]);
	      	      glVertex3f(adj[2][0],adj[2][1],adj[2][2]);
		    		    		    
	      	      glVertex3f(pontos[point][1],pontos[point][2],pontos[point][0]);	      	      glVertex3f(adj[2][0],adj[2][1],adj[2][2]);
	      	      glVertex3f(adj[3][0],adj[3][1],adj[3][2]);
	      	      glVertex3f(adj[5][0],adj[5][1],adj[5][2]);
		     
	      	      glVertex3f(pontos[point][1],pontos[point][2],pontos[point][0]);
	      	      glVertex3f(adj[5][0],adj[5][1],adj[5][2]);
	      	      glVertex3f(adj[8][0],adj[8][1],adj[8][2]);
	      	      glVertex3f(adj[7][0],adj[7][1],adj[7][2]);
		     
	      	      glVertex3f(pontos[point][1],pontos[point][2],pontos[point][0]);
	      	      glVertex3f(adj[7][0],adj[7][1],adj[7][2]);
	      	      glVertex3f(adj[6][0],adj[6][1],adj[6][2]);
	      	      glVertex3f(adj[4][0],adj[4][1],adj[4][2]);
                   glEnd();
                   glColor3f (0.0, 0.0, 0.0);
                   glBegin(GL_LINES);
                      glVertex3f(pontos[point][1],pontos[point][2]+e,pontos[point][0]);
	              glVertex3f(adj[4][0],adj[4][1]+e,adj[4][2]);
              	      glVertex3f(adj[1][0],adj[1][1]+e,adj[1][2]);
	      	      glVertex3f(adj[2][0],adj[2][1]+e,adj[2][2]);
		    		    		    
	      	      glVertex3f(pontos[point][1],pontos[point][2]+e,pontos[point][0]);	      	      glVertex3f(adj[2][0],adj[2][1]+e,adj[2][2]);
	      	      glVertex3f(adj[3][0],adj[3][1]+e,adj[3][2]);
	      	      glVertex3f(adj[5][0],adj[5][1]+e,adj[5][2]);
		     
	      	      glVertex3f(pontos[point][1],pontos[point][2]+e,pontos[point][0]);
	      	      glVertex3f(adj[5][0],adj[5][1]+e,adj[5][2]);
	      	      glVertex3f(adj[8][0],adj[8][1]+e,adj[8][2]);
	      	      glVertex3f(adj[7][0],adj[7][1]+e,adj[7][2]);
		     
	      	      glVertex3f(pontos[point][1],pontos[point][2]+e,pontos[point][0]);
	      	      glVertex3f(adj[7][0],adj[7][1]+e,adj[7][2]);
	      	      glVertex3f(adj[6][0],adj[6][1]+e,adj[6][2]);
	      	      glVertex3f(adj[4][0],adj[4][1]+e,adj[4][2]);	              
                   glEnd();
              //}
        
   glPopAttrib();
   glEndList();   
}

void display(void)
{    
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   
   glLoadIdentity();
   glViewport(0, 0, larguraJanela, alturaJanela); 
    
   glRotatef(rotX,1,0,0);
   glRotatef(rotY,0,1,0);
   glTranslatef(-camX,-camY,-camZ);
     
   glCallList(BASECONTORNO); 
   glCallList(PONTOS); 
   glCallList(EIXOS);
 
   glutSwapBuffers();
}

void teclado(unsigned char key, int x, int y)
{
   sinhor = sin((rotY+90)*M_PI/180.0);
   coshor = cos((rotY+90)*M_PI/180.0);
   sinver = 5*sin(rotY*M_PI/180.0);
   cosver = 5*cos(rotY*M_PI/180.0);
	
   switch(key)
   {
        case 'a':	
             camX = camX - sinhor;
	     camZ = camZ + coshor;
	break;        
        case 'd':	
             camX = camX + sinhor;
	     camZ = camZ - coshor;
	break;
        case 'w':	
             camX = camX + sinver;
             camZ = camZ - cosver;
 	break;
	case 's':	
             camX = camX - sinver;
	     camZ = camZ + cosver;
	break;		
        case 'q':
             exit(0);
        break;	
   }
   glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
   if(state==GLUT_DOWN)
   {
	x_ini = x;
	y_ini = y;
	camY_ini = camY;
	rotX_ini = rotX;
	rotY_ini = rotY;
	bot = button;
   }
   else bot = -1;
}

void move(int x, int y)
{
   if(bot==GLUT_LEFT_BUTTON)
   {
     	deltax = x_ini - x;
	deltay = y_ini - y;
	rotY = rotY_ini - deltax/5;
	rotX = rotX_ini - deltay/5;
   }
   else if(bot==GLUT_RIGHT_BUTTON)
   {
	deltay = y_ini - y;
	camY = camY_ini + deltay/5;
   }
   glutPostRedisplay();
}

void idle(void)
{
   glutPostRedisplay();
}

void cria_vetor_X(float A[64][64], float resultado[64], float vet[64])
{
    int j;
    for(j=1;j<=63;j++)
	 vet[j] = resultado[j]/A[j][j];
}

void cria_matriz_C(float A[64][64], float C[64][64])
{
    int i,j;
    for(i=1;i<=63;i++)
       for(j=1;j<=63;j++)
	  if(i==j)
	    C[i][j] = 0;
          else
	    C[i][j] = -1 * (A[i][j]/A[i][i]);		
}

void cria_vetor_G(float A[64][64], float resultado[64], float v_G[64])
{
    int i;
    for(i=1;i<=63;i++)
        v_G[i] = resultado[i]/ A[i][i];
}

void mult_MV(float M[64][64], float V[64], float aux[64])
{
    int i,j;
    float coef;
    for(i=1;i<=63;i++)
    {
       coef=0;
       for(j=1;j<=63; j++)	
          coef = coef + M[i][j] * V[j];		
       aux[i] = coef;
    }
}

void cria_vetor_de_iteracoes(float A[64][64], float v_G[64], float vet_x[64], float aux[64])
{
    int i;
    mult_MV(A,vet_x,aux);
    for(i=1;i<=63;i++)
	    aux[i] = aux[i] + v_G[i];		
}

void troca_V(float vet1[64], float vet2[64])
{
    int i;
    for(i=1;i<=63;i++)
	    vet1[i] = vet2[i];
}


float retorna_maior(float V[64])
{
    int i;
    float maior = fabs(V[0]); 
    for(i=2;i<=63;i++)
	 if(maior < fabs(V[i]))
            maior = fabs(V[i]);
    return maior;
}

float calculo_do_delta(float vet_x[64], float vet_1[64], float vet_aux[64])
{
    int i,j;
    float aux_erro = 0;
    for(i=1;i<=63;i++)
	    vet_aux[i] = fabs(vet_1[i]);
    for(j=1;j<63;j++)
	    vet_aux[j] = vet_aux[j] - vet_x[j];
    aux_erro = retorna_maior(vet_aux)/retorna_maior(vet_1);
    return aux_erro;
}

void gauss_jacobi(float A[64][64], float solucao[64], float resultado[64])
{
    float vetor_x[64];
    float matrizC[64][64];
    float vetorG[64];
    float vet2[64];

    float erro = 0.00001;
    int iteracoes = 1000;	
    
    cria_vetor_X(A, resultado, vetor_x);
    cria_matriz_C(A, matrizC);
    cria_vetor_G(A, resultado, vetorG);
    cria_vetor_de_iteracoes(matrizC, vetorG, vetor_x, solucao);
    float aux = 9999;
    while(iteracoes >= 0 && aux > erro)
    {
	aux = calculo_do_delta(vetor_x, solucao, vet2);
	if(aux > erro)
        {
	   iteracoes--;
	   troca_V(vetor_x, solucao);		
	   cria_vetor_de_iteracoes(matrizC, vetorG, vetor_x, solucao);
        }
    }    	
}

int ponto(int a, int b)
{
   int p=1;
   int i,j;
   for(i=1;i<=9;i++)
      for(j=1;j<=7;j++)
      {
         if((i==a) && (j==b))
           return p;
         else
           p++;
      }       
}

float contorno(int i, int j)
{  
    if((i==10) || (j==8))
       return 1;
    else if((i==0) || (j==0))
       return 0;
    else
       return -1;
}

void get_pontos()
{
    FILE *arquivo;
    int i,j,k,l,u,p;
    float deltax, deltay;
    float mascara[3][3];
    
    float A[64][64];
    float solucao[64];
    float resultado[64];    
    
    deltax= 1;
    deltay= 1;
    
    for(i=1;i<=63;i++)
      for(j=1;j<=63;j++)
         A[i][j]=0;
      
    for(i=1;i<=9;i++)
      for(j=1;j<=7;j++)  
          resultado[ponto(i,j)] = -1; 
            
    mascara[0][0] = 3/(4*deltax*deltay);
    mascara[0][1] = 2/pow(deltay,2);
    mascara[0][2] = -3/(4*deltax*deltay);
    mascara[1][0] = 1/pow(deltax,2);
    mascara[1][1] = (-2/pow(deltax,2)) + (-4/pow(deltay,2));
    mascara[1][2] = 1/pow(deltax,2);
    mascara[2][0] = -3/(4*deltax*deltay);
    mascara[2][1] = 2/pow(deltay,2);
    mascara[2][2] = 3/(4*deltax*deltay);
        
    for(i=1;i<=9;i++)
       for(j=1;j<=7;j++)
       {
          p = ponto(i,j);
          for(k=-1;k<=1;k++)
            for(l=-1;l<=1;l++)
            {
                u = contorno(i+k,j+l);
                if(u>=0)
                  resultado[p] = resultado[p] - mascara[k+1][l+1]*u;
                else
                  A[p][ponto(i+k,j+l)] = mascara[k+1][l+1];
            }
       }
      
    gauss_jacobi(A,solucao,resultado);

    for(i=1;i<=9;i++)
       for(j=1;j<=7;j++)
       {
          pontos[ponto(i,j)][0] = i;
          pontos[ponto(i,j)][1] = j;
          pontos[ponto(i,j)][2] = solucao[ponto(i,j)];
       }
}

int main(int argc, char** argv)
{
   get_pontos();
   for(int i=1;i<=63;i++)
         printf("%5.3f    %5.3f    %5.3f\n",pontos[i][0],pontos[i][1],pontos[i][2]);   
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB| GLUT_DEPTH);
   glutInitWindowSize (800, 800);
   glutInitWindowPosition (0, 0);
   glutCreateWindow ("CENARIO");
   myinit ();      
   glutReshapeFunc(resize);    
   glutKeyboardFunc(teclado);
   glutMouseFunc(mouse);
   glutMotionFunc(move);
   glutDisplayFunc(display);  
   glutIdleFunc(idle);  
   glutMainLoop();   
}
