#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "image.h"
#include <GL/glut.h>

// CESET /UNICAMP / 2004
//Alunas: Jocileide Aparecida Mariano 
//        Aline Buarque de Sanatana

#define PI 3.1415

#define COORD_TEXTURA_PLANO 0.0
#define COORD_TEXTURA_PISCINA 1.0
#define COR_DO_PLANO 0.0,0.0,0.0,0.0
#define COR_DO_ESPELHO 0.3,0.52,0.18,1.0
#define COR_DA_PISCINA 1.0,0.0,0.0,1.0
#define TEXTURA_DO_PLANO "solo.rgb"
#define TEXTURA_DO_ESPELHO "espelho.rgb"
#define TEXTURA_DA_PISCINA "piscina.rgb"

static int elbow =180;
GLint WIDTH =800;
GLint HEIGHT=600;


GLfloat obs[3]={0.0,7.0,0.0};
GLfloat look[3]={0.0,3.0,0.0};
GLuint  textura_plano;
GLuint  textura_espelho;
GLuint  textura_piscina;

GLshort texturas=0;
GLfloat tetaxz=0;
GLfloat raioxz=3;

GLfloat cinzaesc_difusa[]    = { 0.5, 0.5, 0.5, 1.0 };
GLfloat cinzaesc_especular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat cinzaesc_brilho[]    = { 128.0 };

GLfloat cinzamed_difusa[]    = { 0.7, 0.7, 0.7, 1.0 };
GLfloat cinzamed_especular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat cinzamed_brilho[]    = { 120.0 };

GLfloat cinzaclaro_difusa[]    = { 0.8, 0.8, 0.8, 1.0 };
GLfloat cinzaclaro_especular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat cinzaclaro_brilho[]    = { 120.0 };

GLfloat branco_difusa[]    = { 1.0, 1.0, 1.0, 1.0 };
GLfloat branco_especular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat branco_brilho[]    = { 128.0 };

GLfloat marrom_difusa[]    = { 0.95,0.5,0.2, 1.0 };
GLfloat marrom_especular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat marrom_brilho[]    = { 128.0 };

GLfloat verde_difusa[]    = { 0.5,0.75,0.5, 1.0 };
GLfloat verde_especular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat verde_brilho[]    = { 50.0 };

GLfloat rosa_difusa[]    = { 1.0,0.0,0.2, 1.0 };
GLfloat rosa_especular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat rosa_brilho[]    = { 50.0 };

GLint gouraud=0;
GLuint  final;

GLfloat ctp[4][2]={
  {0.0,0.0},
  {0.0,COORD_TEXTURA_PLANO},
  {COORD_TEXTURA_PLANO,COORD_TEXTURA_PLANO},
  {COORD_TEXTURA_PLANO,0.0}
};

GLfloat ctpi[4][2]={
  {0.0,0.0},
  {0.0,COORD_TEXTURA_PISCINA},
  {COORD_TEXTURA_PISCINA,COORD_TEXTURA_PISCINA},
  {COORD_TEXTURA_PISCINA,0.0}
};


void reshape(int width, int height){
  WIDTH=width;
  HEIGHT=height;
  glViewport(0,0,(GLint)width,(GLint)height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70.0,width/(float)height,0.1,100.0);
  glMatrixMode(GL_MODELVIEW);
}
void compoe_final(void){

  GLUquadricObj *quadric;

  GLfloat asa[][3]={
    {-4.0,0.0,0.0},
    {+4.0,0.0,0.0},
    {0.0,0.0,3.0}
  };

  GLfloat cauda[][3]={
 
    {0.0,0.5,0.0},
    {0.0,2.0,0.0},
    {0.0,0.5,1.0},   

  };

GLfloat logo[][4]={
    {0.0,0.0,0.0},
    {0.0,0.4,0.0},
    {0.0,0.4,0.6},
    {0.0,0.0,0.6} 
  }; 

  /* inicia a composicao de final */
  final = glGenLists(1);
  glNewList(final, GL_COMPILE);
 
/* propriedades do material dos Solos */
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, marrom_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, marrom_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, marrom_brilho);
 
/* Solo Esquerdo */
  glPushMatrix();
  glColor3f(0.95,0.5,0.2);
  glTranslatef(1.21,0.3,8.3);
  glScalef(9.8,2.0,4.0);
  glutSolidCube(1.0);
  glPopMatrix();

/* propriedades do material dos Contornos */
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cinzaesc_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cinzaesc_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, cinzaesc_brilho);

/* Contorno Esquerdo */
  glPushMatrix();
  glColor3f(0.5,0.5,0.5);
  glTranslatef(0.8,0.3,10.6);
  glScalef(16.3,4.0,0.5);
  glutSolidCube(1.0);
  glPopMatrix();
 
/* propriedades do material dos Solos */
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, marrom_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, marrom_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, marrom_brilho); 

/* Solo Direito */
  glPushMatrix();
  glColor3f(0.95,0.5,0.2);
  glTranslatef(1.21,0.3,-2.3);
  glScalef(9.8,2.0,4.3);
  glutSolidCube(1.0);
  glPopMatrix();

/* propriedades do material dos Contornos */
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cinzaesc_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cinzaesc_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, cinzaesc_brilho); 

/* Contorno Direito */
  glPushMatrix();
  glColor3f(0.5,0.5,0.5);
  glTranslatef(0.8,0.3,-4.6);
  glScalef(16.3,4.0,0.5);
  glutSolidCube(1.0);
  glPopMatrix();
  
/* propriedades do material dos Solos */
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, marrom_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, marrom_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, marrom_brilho); 

/* Solo frente da camera*/ 
  glPushMatrix();
  glColor3f(0.95,0.5,0.2);
  glTranslatef(7.2,0.3,2.95);
  glScalef(3.2,2.0,14.68);
  glutSolidCube(1.0);
  glPopMatrix();

/* propriedades do material dos Contornos */
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cinzaesc_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cinzaesc_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, cinzaesc_brilho); 

/* Contorno frente */
  glPushMatrix();
  glColor3f(0.5,0.5,0.5);
  glTranslatef(9.0,0.3,3.0);
  glScalef(0.5,4.0,15.8);
  glutSolidCube(1.0);
  glPopMatrix();
 
/* propriedades do material dos Solos */
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, marrom_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, marrom_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, marrom_brilho); 

/* Solo fundo da camera */ 
  glPushMatrix();
  glColor3f(0.95,0.5,0.2);
  glTranslatef(-5.2,0.3,2.95);
  glScalef(3.2,2.0,14.68);
  glutSolidCube(1.0);
  glPopMatrix();

/* propriedades do material dos Contornos */
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cinzaesc_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cinzaesc_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, cinzaesc_brilho);  

/* Contorno fundo direito 1*/
  glPushMatrix();
  glColor3f(0.5,0.5,0.5);
  glTranslatef(-7.5,0.28,0.5);
  glScalef(0.5,4.0,10.8);
  glutSolidCube(1.0);
  glPopMatrix();
 
/* Fachando debaixo da porta */
  glPushMatrix();  
  glTranslatef(-7.5,-1.2,7.0);
  glColor3f(0.5,0.28,0.5);  
  glScalef(0.2,4.2,3.2);
  glutSolidCube(1.0);
  glPopMatrix();
  
/* propriedades do material dos Contornos */
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cinzaesc_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cinzaesc_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, cinzaesc_brilho);  

/* Contorno fundo esquerdo 2*/
  glPushMatrix();
  glColor3f(0.5,0.5,0.5);
  glTranslatef(-7.5,0.28,9.5);
  glScalef(0.5,4.0,2.8);
  glutSolidCube(1.0);
  glPopMatrix();

/* propriedades do material dos Contornos */
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, verde_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, verde_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, verde_brilho);  

/* Fazendo Porta */
  glPushMatrix();  
  glTranslatef(-7.5,1.6,8.0);
  glRotatef ((GLfloat)elbow, 0.0, 1.0, 0.0);
  glPushMatrix();  
  glColor3f(0.5,0.75,0.5);  
  glTranslatef(0,0,1);
  glScalef(0.2,1.2,2.2);
  glutSolidCube(1.0);
  glPopMatrix();
  glPopMatrix();

/* propriedades do material da Arquibancada direita 1 */
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cinzaesc_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cinzaesc_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, cinzaesc_brilho);  

/* Arquibancada direita 1 (próximo da piscina)*/
  glPushMatrix();
  glColor3f(0.5,0.5,0.5);
  glTranslatef(1.5,1.5,-1.5);
  glScalef(8.0,1.0,0.5);
  glutSolidCube(1.0);
  glPopMatrix();

/* propriedades do material da Arquibancada direita 2 */
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cinzaclaro_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cinzaclaro_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, cinzaclaro_brilho);  

/* Arquibancada direita 2 (meio)*/ 
  glPushMatrix();
  glColor3f(0.8,0.8,0.8);
  glTranslatef(1.5,1.5,-2.0);
  glScalef(8.0,2.0,0.5);
  glutSolidCube(1.0);
  glPopMatrix();

/* propriedades do material da Arquibancada direita 3 */
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cinzamed_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cinzamed_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, cinzamed_brilho);  

/* Arquibancada direita 3 (perto do muro) */ 
  glPushMatrix();
  glColor3f(0.7,0.7,0.7);
  glTranslatef(1.5,1.5,-2.5);
  glScalef(8.0,3.0,0.5);
  glutSolidCube(1.0);
  glPopMatrix();

/* propriedades do material da Arquibancada esquerda 1 */
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cinzaesc_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cinzaesc_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, cinzaesc_brilho);  

/* Arquibancada esquerda 1 (próximo da piscina)*/
  glPushMatrix();
  glColor3f(0.5,0.5,0.5);
  glTranslatef(1.5,1.5,7.5);
  glScalef(8.0,1.0,0.5);
  glutSolidCube(1.0);
  glPopMatrix();

/* propriedades do material da Arquibancada esquerda 2 */
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cinzaclaro_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cinzaclaro_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, cinzaclaro_brilho);  

/* Arquibancada esquerda 2 (meio)*/ 
  glPushMatrix();
  glColor3f(0.8,0.8,0.8);
  glTranslatef(1.5,1.5,8.0);
  glScalef(8.0,2.0,0.5);
  glutSolidCube(1.0);
  glPopMatrix();

/* propriedades do material da Arquibancada esquerda 3 */
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cinzaesc_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cinzaesc_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, cinzaesc_brilho);  

/* Arquibancada esquerda 3 (perto do muro) */ 
  glPushMatrix();
  glColor3f(0.7,0.7,0.7);
  glTranslatef(1.5,1.5,8.5);
  glScalef(8.0,3.0,0.5);
  glutSolidCube(1.0);
  glPopMatrix();

/* propriedades do material dos Gols*/
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, branco_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, branco_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, branco_brilho);  

/* Construindo o gol do fundo */ 
  glPushMatrix();//Para ambos os gols
  glTranslatef(0.0,1.7,0.0);//Para ambos os gols
  
/* Base Traseira Trave do fundo */
  glPushMatrix();
  glColor3f(1.0,1.0,1.0);
  glTranslatef(-2.95,-0.5,1.90);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluCylinder(quadric, 0.1, 0.1, 2.15, 5, 1);
  glPopMatrix();

/* Base Lateral Direita Trave do Fundo */
  glPushMatrix();
  glColor3f(1.0,1.0,1.0);
  glTranslatef(-3.0,-0.5,2.0);
  glRotatef(90,0.0,1.0,0.0);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluCylinder(quadric, 0.1, 0.1, 1, 5, 1);
  glPopMatrix();
 
/* Base Lateral Esquerda Trave Fundo*/
  glPushMatrix();
  glColor3f(1.0,1.0,1.0);
  glTranslatef(-2.9,-0.5,4.0);
  glRotatef(90,0.0,3.0,0.0);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluCylinder(quadric, 0.1, 0.1, 1,5,1);
  glPopMatrix();

/* Primeira Lateral Vertical Direita Trave do Fundo */
  glPushMatrix();
  glColor3f(1.0,1.0,1.0);
  glTranslatef(-2.0,-0.5,2.0);
  glRotatef(90,-0.1,0.0,0.0);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluCylinder(quadric, 0.1, 0.1, 1.0, 5, 1);
  glPopMatrix();

/* Segunda Lateral Vertical Direita Trave do Fundo */
  glPushMatrix();
  glColor3f(1.0,1.0,1.0);
  glTranslatef(-2.85,-0.5,1.98);
  glRotatef(90,-1.0,0.4,-0.3);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluCylinder(quadric, 0.1, 0.1, 1.4, 5, 1);
  glPopMatrix();

/* Primeira Lateral Vertical Esquerda Trave do Fundo */
  glPushMatrix();
  glColor3f(1.0,1.0,1.0);
  glTranslatef(-1.98,-0.5,4.0);
  glRotatef(90,-0.1,0.0,0.0);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluCylinder(quadric, 0.1, 0.1, 1.0, 5, 1);
  glPopMatrix();

/* Segunda Lateral Vertical Esquerda Trave do Fundo */
  glPushMatrix();
  glColor3f(1.0,1.0,1.0);
  glTranslatef(-2.85,-0.5,3.93);
  glRotatef(90,-1.0,0.4,-0.3);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluCylinder(quadric, 0.1, 0.1, 1.4, 5, 1);
  glPopMatrix();

/* Base Superior Trave do Fundo*/
  glPushMatrix();
  glColor3f(1.0,1.0,1.0);
  glTranslatef(-2.05,0.55,1.95);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluCylinder(quadric, 0.1, 0.1, 2.17, 7, 1);
  glPopMatrix();

/* Construindo a rede do gol do Fundo 
/* 1 horizontal*/
  glPushMatrix();
  glColor3f(1.0,1.0,1.0);
  glTranslatef(-2.35,0.25,1.95);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluCylinder(quadric, 0.05, 0.05, 2.07, 3, 1);
  glPopMatrix();

/* 2 horizontal*/
  glPushMatrix();
  glColor3f(1.0,1.0,1.0);
  glTranslatef(-2.6,-0.1,1.95);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluCylinder(quadric, 0.05, 0.05, 2.07, 3, 1);
  glPopMatrix();

/* 1 vertical */
  glPushMatrix();
  glColor3f(1.0,1.0,1.0);
  glTranslatef(-2.87,-0.5,3.0);
  glRotatef(90,-1.0,0.4,-0.3);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluCylinder(quadric, 0.05, 0.05, 1.4, 5, 1);
  glPopMatrix();  

/* 2 vertical*/
  glPushMatrix();
  glColor3f(1.0,1.0,1.0);
  glTranslatef(-2.87,-0.5,2.5);
  glRotatef(90,-1.0,0.4,-0.3);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluCylinder(quadric, 0.05, 0.05, 1.4, 5, 1);
  glPopMatrix(); 

/* 3 vertical*/
  glPushMatrix();
  glColor3f(1.0,1.0,1.0);
  glTranslatef(-2.87,-0.5,3.5);
  glRotatef(90,-1.0,0.4,-0.3);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluCylinder(quadric, 0.05, 0.05, 1.4, 5, 1);
  glPopMatrix();

/* Abertura Direita do Gol do Fundo */
  glPushMatrix();
  glColor3f(1.0,1.0,1.0);
  glTranslatef(-2.59,-0.5,1.95);
  glRotatef(90,-1.0,0.4,-0.3);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluCylinder(quadric, 0.05, 0.05, 1.1, 5, 1);
  glPopMatrix(); 

/* Abertura Esquerda do Gol do Fundo  */
  glPushMatrix();
  glColor3f(1.0,1.0,1.0);
  glTranslatef(-2.59,-0.5,3.95);
  glRotatef(90,-1.0,0.4,-0.3);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluCylinder(quadric, 0.05, 0.05, 1.1, 5, 1);
  glPopMatrix(); 

/* Construindo o gol da Frente */

/* Base Trave da Frente */
  glPushMatrix();
  glColor3f(1.0,1.0,1.0);
  glTranslatef(5.0,-0.5,1.90);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluCylinder(quadric, 0.1, 0.1, 2.15, 5, 1);
  glPopMatrix();

/* Base Lateral Direita Trave da Frente */
  glPushMatrix();
  glColor3f(1.0,1.0,1.0);
  glTranslatef(4.2,-0.5,2.0);
  glRotatef(90,0.0,1.0,0.0);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluCylinder(quadric, 0.1, 0.1, 0.8, 5, 1);
  glPopMatrix();

/* Base Lateral Esquerda Trave da Frente*/
  glPushMatrix();
  glColor3f(1.0,1.0,1.0);
  glTranslatef(4.28,-0.5,4.0);
  glRotatef(90,0.0,3.0,0.0);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluCylinder(quadric, 0.1, 0.1, 0.8, 5, 1);
  glPopMatrix();

/* Primeira Lateral Vertical Direita Trave da Frente *///DA POSIÇÃO FRONTAL DO OBSERVADOR
  glPushMatrix();
  glColor3f(1.0,1.0,1.0);
  glTranslatef(5.0,-0.4,1.95);
  glRotatef(90,-0.8,-1.3,-0.3);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluCylinder(quadric, 0.1, 0.1, 1.4, 5, 1);
  glPopMatrix();

/* Segunda Lateral Vertical Direita Trave da Frente */
  glPushMatrix();
  glColor3f(1.0,1.0,1.0);
  glTranslatef(4.2,-0.5,1.95);
  glRotatef(90,-2.0,-0.7,-0.3);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluCylinder(quadric, 0.1, 0.1, 1.0, 5, 1);
  glPopMatrix();

/* Primeira Lateral Vertical Esquerda Trave da Frente*/
  glPushMatrix();
  glColor3f(1.0,1.0,1.0);
  glTranslatef(5.0,-0.4,4.0);
  glRotatef(90,-0.8,-1.3,-0.3);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluCylinder(quadric, 0.1, 0.1, 1.4, 5, 1);
  glPopMatrix();

/* Segunda Lateral Vertical Esquerda Trave da Frente */
  glPushMatrix();
  glColor3f(1.0,1.0,1.0);
  glTranslatef(4.2,-0.5,4.0);
  glRotatef(90,-4.0,-0.9,-0.3);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluCylinder(quadric, 0.1, 0.1, 1.0, 5, 1);
  glPopMatrix();

/* Base Superior Trave da Frente */
  glPushMatrix();
  glColor3f(1.0,1.0,1.0);
  glTranslatef(4.0,0.53,1.92);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluCylinder(quadric, 0.1, 0.1, 2.17, 7, 1);
  glPopMatrix();

/* Abertura Direita do Gol da Frente */

  glPushMatrix();
  glColor3f(1.0,1.0,1.0);
  glTranslatef(4.65,-0.4,1.95);
  glRotatef(90,-1.0,-1.3,-0.3);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluCylinder(quadric, 0.04, 0.04, 1.0, 5, 1);
  glPopMatrix();

/* Abertura Esquerda do Gol da Frente  */

  glPushMatrix();
  glColor3f(1.0,1.0,1.0);
  glTranslatef(4.65,-0.4,4.0);
  glRotatef(90,-1.0,-1.3,-0.3);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluCylinder(quadric, 0.04, 0.04, 1.0, 5, 1);
  glPopMatrix();

/* Construindo a rede do gol da frente

/* Horizontal 2*/
  glPushMatrix();
  glColor3f(1.0,1.0,1.0);
  glTranslatef(4.3,0.2,1.95);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluCylinder(quadric, 0.05, 0.05, 2.07, 3, 1);
  glPopMatrix();

/* Horizontal 3*/
  glPushMatrix();
  glColor3f(1.0,1.0,1.0);
  glTranslatef(4.7,-0.1,1.95);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluCylinder(quadric, 0.05, 0.05, 2.07, 3, 1);
  glPopMatrix();

/* Vertical 1 */
  glPushMatrix();
  glColor3f(1.0,1.0,1.0);
  glTranslatef(5.0,-0.4,3.0);
  glRotatef(90,-1.0,-1.3,-0.3);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluCylinder(quadric, 0.05, 0.05, 1.35, 5, 1);
  glPopMatrix();
 
/* Vertical 2 */
  glPushMatrix();
  glColor3f(1.0,1.0,1.0);
  glTranslatef(5.0,-0.4,3.5);
  glRotatef(90,-1.0,-1.3,-0.3);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE); 
  gluCylinder(quadric, 0.05, 0.05, 1.35, 5, 1);
  glPopMatrix();
 
/* Vertical 3 */
  glPushMatrix();
  glColor3f(1.0,1.0,1.0);
  glTranslatef(5.0,-0.4,2.5);
  glRotatef(90,-1.0,-1.3,-0.3);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluCylinder(quadric, 0.05, 0.05, 1.35, 5, 1);
  glPopMatrix();

/*Construindo a escada da piscina */

/* propriedades do material da Escada */
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cinzaesc_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cinzaesc_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, cinzaesc_brilho);  

/*lado 1 */
  glPushMatrix();
  glColor3f(0.5,0.5,0.5);
  glTranslatef(-2.0,-0.85,6.25);
  glRotatef(90,-0.1,0.0,0.0);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluCylinder(quadric, 0.05, 0.05, 0.85, 5, 1);
  glPopMatrix();

/*lado 2 */
  glPushMatrix();
  glColor3f(0.5,0.5,0.5);
  glTranslatef(-1.5,-0.85,6.25);
  glRotatef(90,-0.1,0.0,0.0);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluCylinder(quadric, 0.05, 0.05, 0.85, 5, 1);
  glPopMatrix();

/* Degrau 1*/
  glPushMatrix();
  glColor3f(0.5,0.5,0.5);
  glTranslatef(-2.0,-0.55,6.25);
  glRotatef(90,0.0,1.0,0.0);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluCylinder(quadric, 0.05, 0.05, 0.5, 5, 1);
  glPopMatrix();

/* Degrau 2 */
  glPushMatrix();
  glColor3f(0.5,0.5,0.5);
  glTranslatef(-2.0,-0.2,6.25);
  glRotatef(90,0.0,1.0,0.0);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluCylinder(quadric, 0.05, 0.05, 0.5, 5, 1);
  glPopMatrix();

/* Fecha escada 1*/
  glPushMatrix();
  glColor3f(0.5,0.5,0.5);
  glTranslatef(-1.98,0.0,6.22);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluCylinder(quadric, 0.05, 0.05, 0.25, 7, 1);
  glPopMatrix();

/* Fecha escada 2*/
  glPushMatrix();
  glColor3f(0.5,0.5,0.5);
  glTranslatef(-1.5,0.0,6.22);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluCylinder(quadric, 0.05, 0.05, 0.25, 7, 1);
  glPopMatrix();

/* Corrimão 1 */
  glPushMatrix();
  glColor3f(0.5,0.5,0.5);
  glTranslatef(-1.97,-0.25,6.45);
  glRotatef(90,-0.1,0.0,0.0);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluCylinder(quadric, 0.05, 0.05, 0.25, 5, 1);
  glPopMatrix();

/* Corrimão 2 */
  glPushMatrix();
  glColor3f(0.5,0.5,0.5);
  glTranslatef(-1.47,-0.25,6.45);
  glRotatef(90,-0.1,0.0,0.0);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluCylinder(quadric, 0.05, 0.05, 0.25, 5, 1);
  glPopMatrix();

  glPopMatrix();

/* termina a composicao de piscina */
 
/* RESERVATÓRIO DE BOLAS */

/* propriedades do material do Reservatório*/
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cinzamed_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cinzamed_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, cinzamed_brilho);  

/* Base Reservatório Bolas */
  glPushMatrix();
  glColor3f(0.7,0.7,0.7);
  glTranslatef(-6.9,1.3,2.6);
  glRotatef(90,0,1,0);
  glScalef(6.0,0.1,1.5);
  glutSolidCube(1.0);
  glPopMatrix();

/* Base Superior Reservatório Bolas */
  glPushMatrix();
  glColor4f(0.7,0.7,0.7,0.5);
  glTranslatef(-6.9,2.1,2.6);
  glRotatef(90,0,1,0);
  glScalef(6.0,0.1,1.5);
  glutSolidCube(1.0);
  glPopMatrix();

/* Divisória 1 Reservatório Bolas */// DA ESQUERDA PRA DIREITA 
  glPushMatrix();
  glColor4f(0.7,0.7,0.7,0.5);
  glTranslatef(-6.7,1.3,5.6);
  glRotatef(90,15,1,0);
  glScalef(1.0,0.1,1.5);
  glutSolidCube(1.0);
  glPopMatrix();

/* Divisória 2 Reservatório Bolas */
  glPushMatrix();
  glColor4f(0.7,0.7,0.7,0.5);
  glTranslatef(-6.7,1.3,4.7);
  glRotatef(90,15,1,0);
  glScalef(1.0,0.1,1.5);
  glutSolidCube(1.0);
  glPopMatrix();

/* Divisória 3 Reservatório Bolas *///DA ESQUERDA PRA DIREITA 
  glPushMatrix();
  glColor4f(0.7,0.7,0.7,0.5);
  glTranslatef(-6.7,1.3,3.9);
  glRotatef(90,15,1,0);
  glScalef(1.0,0.1,1.5);
  glutSolidCube(1.0);
  glPopMatrix();

/* Divisória 4 Reservatório Bolas *///DA ESQUERDA PRA DIREITA 
  glPushMatrix();
  glColor4f(0.7,0.7,0.7,0.5);
  glTranslatef(-6.7,1.3,3.1);
  glRotatef(90,15,1,0);
  glScalef(1.0,0.1,1.5);
  glutSolidCube(1.0);
  glPopMatrix();

/* Divisória 5 Reservatório Bolas *///DA ESQUERDA PRA DIREITA 
  glPushMatrix();
  glColor4f(0.7,0.7,0.7,0.5);
  glTranslatef(-6.7,1.3,2.3);
  glRotatef(90,15,1,0);
  glScalef(1.0,0.1,1.5);
  glutSolidCube(1.0);
  glPopMatrix();

/* Divisória 6 Reservatório Bolas *///DA ESQUERDA PRA DIREITA 
  glPushMatrix();
  glColor4f(0.7,0.7,0.7,0.5);
  glTranslatef(-6.7,1.3,1.5);
  glRotatef(90,15,1,0);
  glScalef(1.0,0.1,1.5);
  glutSolidCube(1.0);
  glPopMatrix();

/* Divisória 7 Reservatório Bolas *///DA ESQUERDA PRA DIREITA 
  glPushMatrix();
  glColor4f(0.7,0.7,0.7,0.5);
  glTranslatef(-6.7,1.3,0.5);
  glRotatef(90,15,1,0);
  glScalef(1.0,0.1,1.5);
  glutSolidCube(1.0);
  glPopMatrix();

/* Divisória 8 Reservatório Bolas *///DA ESQUERDA PRA DIREITA 
  glPushMatrix();
  glColor4f(0.7,0.7,0.7,0.5);
  glTranslatef(-6.7,1.3,-0.4);
  glRotatef(90,15,1,0);
  glScalef(1.0,0.1,1.5);
  glutSolidCube(1.0);
  glPopMatrix();

/* propriedades do material da Bola */
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, rosa_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, rosa_especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, rosa_brilho);  

/* Bola 1 */
  glPushMatrix();
  glColor3f(1.0,0.0,0.2);
  glTranslatef(-7.0,1.5,5.2);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluSphere(quadric,0.2,15,15);
  glPopMatrix();

/* Bola 2 */
  glPushMatrix();
  glColor3f(1.0,0.0,0.2);
  glTranslatef(-7.0,1.5,4.3);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluSphere(quadric,0.2,15,15);
  glPopMatrix();

/* Bola 3 */
  glPushMatrix();
  glColor3f(1.0,0.0,0.2);
  glTranslatef(-7.0,1.5,3.4);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluSphere(quadric,0.2,15,15);
  glPopMatrix();

/* Bola 4 */
  glPushMatrix();
  glColor3f(1.0,0.0,0.2);
  glTranslatef(-7.0,1.5,2.7);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluSphere(quadric,0.2,15,15);
  glPopMatrix();

/* Bola 5 */
  glPushMatrix();
  glColor3f(1.0,0.0,0.2);
  glTranslatef(-7.0,1.5,1.9);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluSphere(quadric,0.2,15,15);
  glPopMatrix();

/* Bola 6 */
  glPushMatrix();
  glColor3f(1.0,0.0,0.2);
  glTranslatef(-7.0,1.5,1.0);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluSphere(quadric,0.2,15,15);
  glPopMatrix();

/* Bola 7 */
  glPushMatrix();
  glColor3f(1.0,0.0,0.2);
  glTranslatef(-7.0,1.5,0.0);
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  gluSphere(quadric,0.2,15,15);
  glPopMatrix();

/* Construindo largada de piscina conforme professor pediu pessoalmente 01/07/2004 */

/* propriedades do material dos Tranpolins */
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cinzaesc_difusa);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cinzaesc_especular);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, cinzaesc_brilho);

/* Tranpolim 1 */
  glPushMatrix();
  glColor3f(0.5,0.5,0.5);
  glTranslatef(5.90,1.7,0.35);
  glScalef(0.5,0.5,0.5);
  glutSolidCube(1.0);
  glPopMatrix();

/* Tranpolim 2 */
  glPushMatrix();
  glColor3f(0.5,0.5,0.5);
  glTranslatef(5.90,1.7,1.5);
  glScalef(0.5,0.5,0.5);
  glutSolidCube(1.0);
  glPopMatrix();

/* Tranpolim 3 */
  glPushMatrix();
  glColor3f(0.5,0.5,0.5);
  glTranslatef(5.90,1.7,4.5);
  glScalef(0.5,0.5,0.5);
  glutSolidCube(1.0);
  glPopMatrix();

/* Tranpolim 4 */
  glPushMatrix();
  glColor3f(0.5,0.5,0.5);
  glTranslatef(5.90,1.7,5.7);
  glScalef(0.5,0.5,0.5);
  glutSolidCube(1.0);
  glPopMatrix();
/* termina a composicao de piscina*/
  glEndList();

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

  /* calcula a posicao do observador */
  obs[0]=raioxz*cos(2*PI*tetaxz/360);
  obs[2]=raioxz*sin(2*PI*tetaxz/360);
  gluLookAt(obs[0],obs[1],obs[2],look[0],look[1],look[2],0.0,1.0,0.0);

  /* habilita/desabilita uso de texturas*/
  if(texturas){
    glEnable(GL_TEXTURE_2D);  
  }
  else{
    glDisable(GL_TEXTURE_2D);
  }

//plano
  glColor4f(COR_DO_PLANO);
  glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
  glBindTexture(GL_TEXTURE_2D,textura_plano);
   
  glBegin(GL_QUADS);
  glTexCoord2fv(ctp[0]);  glVertex3f(-10,0,10);
  glTexCoord2fv(ctp[1]);  glVertex3f(10,0,10);
  glTexCoord2fv(ctp[2]);  glVertex3f(10,0,-10);
  glTexCoord2fv(ctp[3]);  glVertex3f(-10,0,-10);
  glEnd();

/* Construindo a piscina */ 
/* Piscina */
  
  glEnable(GL_TEXTURE_2D);
  glTranslatef(-1.0,-1.5,1.0); 
  glColor4f(COR_DA_PISCINA);
  glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
  glBindTexture(GL_TEXTURE_2D,textura_piscina);
    
  glPushMatrix();
  glRotatef((GLfloat) 90, 0.0, 1.0, 0.0);
  glTranslatef(-0.2,4.5,1.5);  

  glBegin(GL_QUADS);
  glTexCoord2fv(ctpi[0]);  glVertex3f(-4.0,0.0,9.7);
  glTexCoord2fv(ctpi[1]);  glVertex3f(9.0,0.0,5.0);
  glTexCoord2fv(ctpi[2]);  glVertex3f(9.0,0.0,-4.0);
  glTexCoord2fv(ctpi[3]);  glVertex3f(-4.0,0.0,-4.0);
  glEnd(); 
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

/* posicionamento da piscina no plano */

  glTranslatef(2.0,3.5,-4.0);
  glColor4f(COR_DO_ESPELHO);
  glBindTexture(GL_TEXTURE_2D,textura_espelho);  
  glCallList(final);
  
glPopMatrix();

glutSwapBuffers();
}

void special(int key, int x, int y){
  switch (key) {
  case GLUT_KEY_UP:
    obs[1]=obs[1]+1;
    glutPostRedisplay();
    break;
  case GLUT_KEY_DOWN:
    obs[1] =obs[1]-1;
    glutPostRedisplay();
    break;
  case GLUT_KEY_LEFT:
    tetaxz=tetaxz+2;
    glutPostRedisplay();
    break;
  case GLUT_KEY_RIGHT:
    tetaxz=tetaxz-2;
    glutPostRedisplay();
    break;
  }
}

void keyboard(unsigned char key, int x, int y){
  switch (key) {
  case 27:
    exit(0);
    break;
  case 't':
    texturas = !texturas;
    glutPostRedisplay();
    break;
  case 'r':
    raioxz=raioxz+1;
    glutPostRedisplay();
    break;
  case 'R':
    raioxz=raioxz-1;
    if(raioxz==0){
      raioxz=1;
    }
    glutPostRedisplay();
    break;
 case 'a':
    if ((elbow <= 180)&&(elbow != 50))
    {
    elbow = (elbow - 10) ;
    compoe_final();
    }
    glutPostRedisplay();
    break;
case 'j':
    if (elbow < 180)
    {
    elbow = (elbow +10);
    compoe_final();
    }
    glutPostRedisplay();
    break; 
  }
}

void carregar_texturas(void){
  IMAGE *img;
  GLenum gluerr;

  /* textura do plano */
  glGenTextures(1, &textura_plano);
  glBindTexture(GL_TEXTURE_2D, textura_plano);
  
  if(!(img=ImageLoad(TEXTURA_DO_PLANO))) {
    fprintf(stderr,"Error reading a texture.\n");
    exit(-1);
  }

  gluerr=gluBuild2DMipmaps(GL_TEXTURE_2D, 3, 
			   img->sizeX, img->sizeY, 
			   GL_RGB, GL_UNSIGNED_BYTE, 
			   (GLvoid *)(img->data));
  if(gluerr){
    fprintf(stderr,"GLULib%s\n",gluErrorString(gluerr));
    exit(-1);
  }

  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);

/* textura da piscina */
  glGenTextures(1, &textura_piscina);
  glBindTexture(GL_TEXTURE_2D, textura_piscina);
  
  if(!(img=ImageLoad(TEXTURA_DA_PISCINA))) {
    fprintf(stderr,"Error reading a texture.\n");
    exit(-1);
  }

  gluerr=gluBuild2DMipmaps(GL_TEXTURE_2D, 3, 
			   img->sizeX, img->sizeY, 
			   GL_RGB, GL_UNSIGNED_BYTE, 
			   (GLvoid *)(img->data));
  if(gluerr){
    fprintf(stderr,"GLULib%s\n",gluErrorString(gluerr));
    exit(-1);
  }

  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
 
  /* textura da trave */
  glGenTextures(1, &textura_espelho);
  glBindTexture(GL_TEXTURE_2D, textura_espelho);

  
  if(!(img=ImageLoad(TEXTURA_DO_ESPELHO))) {
    fprintf(stderr,"Error reading a texture.\n");
    exit(-1);
  }

  gluerr=gluBuild2DMipmaps(GL_TEXTURE_2D, 3, 
			   img->sizeX, img->sizeY, 
			   GL_RGB, GL_UNSIGNED_BYTE, 
			   (GLvoid *)(img->data));
  if(gluerr){
    fprintf(stderr,"GLULib%s\n",gluErrorString(gluerr));
    exit(-1);
  }

  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
  
}

void init(){
  carregar_texturas();
  compoe_final();
  glShadeModel(GL_FLAT);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_TEXTURE_2D);

  gouraud=1;
  
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);

  glEnable(GL_AUTO_NORMAL);
  glEnable(GL_NORMALIZE);

}

int main(int argc,char **argv){
  
  glutInitWindowPosition(0,0);
  glutInitWindowSize(WIDTH,HEIGHT);
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH|GLUT_DOUBLE);


  if(!glutCreateWindow("POLO AQUATICO")) {
    fprintf(stderr,"Error opening a window.\n");
    exit(-1);
  }

  init();

  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMainLoop();

  return(0);
}
