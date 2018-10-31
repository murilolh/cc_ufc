//**************************************************************
//                                                             *
// TRABALHO FINAL DE COMPUTAÇÃO GRÁFICA I                      *
// SEMESTRE: 2008.2                                            *
// DUPLA:                                                      *
//       Cícero Antônio Cavalcante de Araújo    Mat:0286731    *
//       Murilo Lima de Holanda                 Mat:0286740    *
//           						       *
// 							       *
// Controles de Iluminação/Rendering em geral:		       * 
// K - acende/apaga luz 1                                      *
// L - acende/apaga luz 2                                      * 
//							       *
// Controles de Movimento e Direção de Câmera:                 *
// W  -Move para frente                                        *
// S  -Move para baixo                                         *
// A  -Move para esquerda                                      * 
// D  -Move para direita                                       *
// BOTÃO ESQUERDO -controla direção da Câmera                  *
// BOTÃO DIREITO  -controla altura da Câmera                   *
//							       *
// Instruções para compilação:				       *
// -Deve-se compilar o arquivo glm.c junto com o main.cpp      *
//							       *
//**************************************************************
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "glm.h"     //Biblioteca usada para carregar objetos modelados no Blender

//Defines para os objetos
#define FRENTEFUNDO     1
#define PISO            2
#define COLUNA          3
#define PADIREITA       4
#define PAESQUERDA      5
#define TETO            6
#define TETOl           7
#define LAMPADA         8
#define COLUNATETO      9
#define COLUNATETOl     10
#define BIROCENTRAL     11
#define MESAGRANDE      12
#define BIROLATERAL     13
#define LIXEIRA1        14
#define LIXEIRA2        15
#define CADEIRA1        16
#define CADEIRA2        17
#define PORTA           18
#define JANELA          19
#define JANELAg         20
#define ARCOND          21
#define REGISTRO        22
//Defines para os materiais
#define parede          30
#define mesa            31
#define biroa           32
#define birob           33
#define biroc           34
#define lixeira1        35
#define lixeira2        36
#define cadeira1a       37
#define cadeira1b       38
#define cadeira2        39
#define birolaterala    40
#define birolateralb    41
#define birolateralc    42
#define registro1       43
#define arcondicionadoa 44 
#define arcondicionadob 45
#define porta           46
#define janelaa         47
#define janelab         48
#define janelac         49
#define janelad         50
#define piso            51
#define tetoab          52
#define tetoc           53
#define tetod           54

//Variáveis usadas na navegação pelo cenário
GLfloat rotX=0, rotY=0, rotX_ini, rotY_ini;
GLfloat camX=2, camY=15, camZ=-2, camY_ini;
int x_ini,y_ini,bot;
float sinhor,coshor,sinver,cosver;
int deltax, deltay;

//Variáveis usadas na projecão do cenário
int   larguraJanela = 800, alturaJanela = 800;
float faspect;
float angulo = 45;

//Variáveis usadas na iluminação
float emissive[]={1,1,1,1};//Emissividade das lâmpadas 
int luz1=1;//Guarda estado das lâmpadas
int luz2=1;
GLfloat L_ambiente[]    ={0.3 , 0.3 , 0.3, 1.0};//|
GLfloat L_difusa[]      ={1.0 , 1.0 , 1.0, 1.0};//|Coeficientes das lâmpadas
GLfloat L_especular[]   ={1.0 , 1.0 , 1.0, 1.0};//|
GLfloat L1_posicao[]    ={27.5, 55.0, -29, 1.0};//Posição das lâmpadas 
GLfloat L2_posicao[]    ={27.5, 29.0, -90, 1.0};

//Variáveis usadas para carregar objetos modelados no Blender
GLMmodel* TETOa 		= NULL;
GLMmodel* TETOb 		= NULL;
GLMmodel* TETOc 		= NULL;
GLMmodel* TETOd 		= NULL;
GLMmodel* LAMPADAa 		= NULL;
GLMmodel* PORTAa		= NULL;
GLMmodel* PORTAb		= NULL;
GLMmodel* JANELAa		= NULL;
GLMmodel* JANELAb		= NULL;
GLMmodel* JANELAc		= NULL;
GLMmodel* JANELAd		= NULL;
GLMmodel* ARCa 			= NULL;
GLMmodel* ARCb 			= NULL;
GLMmodel* REGISTROa		= NULL;
GLMmodel* BIROCENTRALa 		= NULL;
GLMmodel* BIROCENTRALb 		= NULL;
GLMmodel* BIROCENTRALc 		= NULL;
GLMmodel* BIROLATERALa 		= NULL;
GLMmodel* BIROLATERALb 		= NULL;
GLMmodel* BIROLATERALc 		= NULL;
GLMmodel* CADEIRA1a 		= NULL;
GLMmodel* CADEIRA1b 		= NULL;
GLMmodel* CADEIRA2a 		= NULL;
GLMmodel* LIXEIRA1a 		= NULL;
GLMmodel* LIXEIRA2a 		= NULL;
GLMmodel* MESAGRANDEa 		= NULL;

//Estrutura das propriedades dos materiais
typedef struct
{     GLfloat ambient[4];
      GLfloat diffuse[4];
      GLfloat specular[4];
      GLfloat shininess[1];
} materialStruct;   

//Propriedade de materiais usadas no programa
materialStruct Mparede = { 0.40, 0.40, 0.40, 0.2,
                           0.50, 0.50, 0.50, 0.2,
                           0.7, 0.7, 0.7, 1.0,
                           1};
                           
materialStruct Mpiso = {   0.50, 0.50, 0.35, 0.2,
                           0.60, 0.60, 0.60, 0.0,
                           0.5, 0.5, 0.5, 1.0,
                           1};
                           
materialStruct Mporta = { 0.35, 0.35, 0.35, 1.0,
                          0.90, 0.90, 0.90, 1.0,
                          0.8, 0.8, 0.8, 1.0,
                          1};
                           
materialStruct Mmesa = {  0.19, 0.09, 0.01, 1.0,
                           0.65, 0.61, 0.63, 1.0,
                           0.63, 0.56, 0.37, 1.0,
                           100};
                         
materialStruct Mcadeira1a = { 0.29, 0.23, 0.12, 1.0,
                           0.25, 0.21, 0.23, 1.0,
                           0.63, 0.56, 0.37, 1.0,
                           20};
                           
materialStruct Mcadeira1b = { 0.10, 0.10, 0.10, 1.0,
                           0.25, 0.21, 0.23, 1.0,
                           0.63, 0.56, 0.37, 1.0,
                           1.2};
                           
materialStruct Mcadeira2 = { 0.19, 0.19, 0.10, 1.0,
                           0.25, 0.21, 0.23, 1.0,
                           0.63, 0.56, 0.37, 1.0,
                           1.2};
                           
materialStruct Mbiroa = { 0.49, 0.49, 0.40, 1.0,
                         0.23, 0.23, 0.23, 1.0,
                         0.5, 0.5, 0.5, 1.0,
                         20}; 
 
materialStruct Mbirob = { 0.20, 0.22, 0.72, 1.0,
                         0.21, 0.45, 0.36, 1.0,
                         0.21, 0.45, 0.36, 1.0,
                         55}; 
                         
materialStruct Mbiroc = { 0.50, 0.50, 0.10, 1.0,
                           0.21, 0.44, 0.98, 1.0,
                           0.30, 0.50, 0.40, 1.0,
                           20};
                           
materialStruct Mlixeira1 = { 0.28, 0.38, 0.28, 1.0,
                             0.25, 0.21, 0.23, 1.0,
                             0.5, 0.5, 0.5, 1.0,
                             1};
                             
materialStruct Mlixeira2 = { 0.58, 0.58, 0.58, 1.0,
                             0.25, 0.21, 0.23, 1.0,
                             0.5, 0.5, 0.5, 1.0,
                             1};
                             
materialStruct Mbirolaterala = {0.50, 0.50, 0.50, 1.0,
                               0.56, 0.54, 0.58, 1.0,
                               0.3, 0.3, 0.3, 1.0,
                               1};
                               
materialStruct Mbirolateralb = { 0.1, 0.1, 0.1, 1.0,
                                 0.1, 0.1, 0.1, 1.0,
                                 0.1, 0.1, 0.1, 1.0,
                                 55};
                             
materialStruct Mbirolateralc = {0.50, 0.50, 0.50, 1.0,
                               0.56, 0.54, 0.58, 1.0,
                               0.3, 0.3, 0.3, 1.0,
                               1};         
                               
materialStruct Mregistro1 = { 0.23, 0.26, 0.20, 1.0,
                              0.56, 0.54, 0.58, 0.0,
                              0.3, 0.3, 0.3, 0.0,
                              1}; 
                                 
materialStruct Marcondicionadoa = {0.30, 0.30, 0.30, 1.0,
                               0.56, 0.54, 0.58, 1.0,
                               0.3, 0.3, 0.3, 1.0,
                               1};
                                                             
materialStruct Marcondicionadob = {0.50, 0.50, 0.50, 1.0,
                               0.56, 0.54, 0.58, 1.0,
                               0.3, 0.3, 0.3, 1.0,
                               1};      
                               
materialStruct Mjanelaa = { 0.35, 0.35, 0.35, 1.0,
                            0.90, 0.90, 0.90, 1.0,
                            0.8, 0.8, 0.8, 1.0,
                            1};

materialStruct Mjanelab = { 0.35, 0.35, 0.35, 1.0,
                          0.90, 0.90, 0.90, 1.0,
                          0.8, 0.8, 0.8, 1.0,
                          1};
                            
materialStruct Mjanelac = { 0.35, 0.28, 0.35, 1.0,
                            0.8, 0.8, 0.8, 1.0,
                            0.6, 0.6, 0.6, 1.0,
                            1};
                            
materialStruct Mjanelad = { 0.1, 0.1, 0.1, 1.0,
                            0.8, 0.8, 0.8, 1.0,
                            0.6, 0.6, 0.6, 1.0,
                            1};

materialStruct Mtetoab = { 0.65, 0.65, 0.65, 1.0,
                            0.8, 0.8, 0.8, 1.0,
                            0.6, 0.6, 0.6, 1.0,
                            1};

materialStruct Mtetoc = { 0.45, 0.45, 0.45, 1.0,
                            0.8, 0.8, 0.8, 1.0,
                            0.6, 0.6, 0.6, 1.0,
                            1};
                            
materialStruct Mtetod = { 0.35, 0.35, 0.35, 1.0,
                            0.8, 0.8, 0.8, 1.0,
                            0.6, 0.6, 0.6, 1.0,
                            100};

//Função que carrega materiais
void material(int obj)
{
   switch (obj)
   {
        case(parede):
           glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   Mparede.ambient);
           glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   Mparede.diffuse);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  Mparede.specular);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, Mparede.shininess);
        break;
        
        case(piso):
           glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   Mpiso.ambient);
           glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   Mpiso.diffuse);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  Mpiso.specular);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, Mpiso.shininess);
        break;
             
        case(porta):
           glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   Mporta.ambient);
           glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   Mporta.diffuse);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  Mporta.specular);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, Mporta.shininess);
        break;
        
        case(mesa):
           glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Mmesa.ambient);
           glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Mmesa.diffuse);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,Mmesa.specular);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,Mmesa.shininess);
        break;
        
        case(cadeira1a):
           glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Mcadeira1a.ambient);
           glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Mcadeira1a.diffuse);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,Mcadeira1a.specular);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,Mcadeira1a.shininess);
        break;
        
         case(cadeira1b):
           glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Mcadeira1b.ambient);
           glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Mcadeira1b.diffuse);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,Mcadeira1b.specular);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,Mcadeira1b.shininess);
        break;
        
        case(cadeira2):
           glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Mcadeira2.ambient);
           glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Mcadeira2.diffuse);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,Mcadeira2.specular);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,Mcadeira2.shininess);
        break;
        
        case(biroa):
           glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Mbiroa.ambient);
           glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Mbiroa.diffuse);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,Mbiroa.specular);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,Mbiroa.shininess);
        break;
        
        case(birob):
           glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Mbirob.ambient);
           glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Mbirob.diffuse);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,Mbirob.specular);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,Mbirob.shininess);
        break;
        
        case(biroc):
           glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Mbiroc.ambient);
           glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Mbiroc.diffuse);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,Mbiroc.specular);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,Mbiroc.shininess);
        break;
           
        case(lixeira1):
           glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT , Mlixeira1.ambient);
           glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE , Mlixeira1.diffuse);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR , Mlixeira1.specular);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS , Mlixeira1.shininess);
        break;
          
        case(lixeira2):
           glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT , Mlixeira2.ambient);
           glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE , Mlixeira2.diffuse);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR , Mlixeira2.specular);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS , Mlixeira2.shininess);
        break; 
          
        case(birolaterala):
           glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT ,Mbirolaterala.ambient);
           glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE ,Mbirolaterala.diffuse);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR ,Mbirolaterala.specular);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,Mbirolaterala.shininess);
        break; 
          
        case(birolateralb):
           glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT ,Mbirolateralb.ambient);
           glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE ,Mbirolateralb.diffuse);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR ,Mbirolateralb.specular);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,Mbirolateralb.shininess);
        break; 
                             
        case(birolateralc):
           glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT ,Mbirolateralc.ambient);
           glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE ,Mbirolateralc.diffuse);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR ,Mbirolateralc.specular);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,Mbirolateralc.shininess);
        break;   
         
        case(registro1):
           glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT ,Mregistro1.ambient);
           glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE ,Mregistro1.diffuse);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR ,Mregistro1.specular);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,Mregistro1.shininess);
        break;
        
        case(arcondicionadoa):
           glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT ,Marcondicionadoa.ambient);
           glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE ,Marcondicionadoa.diffuse);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR ,Marcondicionadoa.specular);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,Marcondicionadoa.shininess);
        break;
            
        case(arcondicionadob):
           glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT ,Marcondicionadob.ambient);
           glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE ,Marcondicionadob.diffuse);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR ,Marcondicionadob.specular);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,Marcondicionadob.shininess);
        break;
          
        case(janelaa):
           glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT ,Mjanelaa.ambient);
           glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE ,Mjanelaa.diffuse);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR ,Mjanelaa.specular);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,Mjanelaa.shininess);
        break;
          
        case(janelab):
           glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT ,Mjanelab.ambient);
           glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE ,Mjanelab.diffuse);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR ,Mjanelab.specular);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,Mjanelab.shininess);
        break;
          
        case(janelac):
           glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT ,Mjanelac.ambient);
           glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE ,Mjanelac.diffuse);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR ,Mjanelac.specular);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,Mjanelac.shininess);
        break;
          
        case(janelad):
           glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT ,Mjanelad.ambient);
           glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE ,Mjanelad.diffuse);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR ,Mjanelad.specular);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,Mjanelad.shininess);
        break;     
        case (tetoab):
           glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT ,Mtetoab.ambient);
           glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE ,Mtetoab.diffuse);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR ,Mtetoab.specular);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,Mtetoab.shininess);
        break;
                   
        case (tetoc):
           glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT ,Mtetoc.ambient);
           glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE ,Mtetoc.diffuse);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR ,Mtetoc.specular);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,Mtetoc.shininess);
        break;
        
        case (tetod):
           glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT ,Mtetod.ambient);
           glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE ,Mtetod.diffuse);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR ,Mtetod.specular);
           glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,Mtetod.shininess);
        break;   
   }   
}

//Função que carrega modelos feitos no blender
void carregarOBJs(void)
{   TETOa = glmReadOBJ("Modelos/TETO/TETOa.obj");//Carrega objeto a partir de um arquivo .obj
   glmUnitize(TETOa);//Faz com que todos os objetos caibam num modelo 1x1x1
   glmFacetNormals(TETOa);//Carrega normais das faces
   glmVertexNormals(TETOa, 90.0);//Carrega normais dos vértices
   
   TETOb = glmReadOBJ("Modelos/TETO/TETOb.obj");
   glmUnitize(TETOb);
   glmFacetNormals(TETOb);
   glmVertexNormals(TETOb, 90.0); 
   
   TETOc = glmReadOBJ("Modelos/TETO/TETOc.obj");
   glmUnitize(TETOc);
   glmFacetNormals(TETOc);
   glmVertexNormals(TETOc, 90.0); 

   TETOd = glmReadOBJ("Modelos/TETO/TETOd.obj");
   glmUnitize(TETOd);
   glmFacetNormals(TETOd);
   glmVertexNormals(TETOd, 90.0); 

   LAMPADAa = glmReadOBJ("Modelos/TETO/LAMPADAa.obj");
   glmUnitize(LAMPADAa);
   glmFacetNormals(LAMPADAa);
   glmVertexNormals(LAMPADAa, 90.0);

   PORTAa = glmReadOBJ("Modelos/PORTA/PORTAa.obj");
   glmUnitize(PORTAa);
   glmFacetNormals(PORTAa);
   glmVertexNormals(PORTAa, 90.0);

   PORTAb = glmReadOBJ("Modelos/PORTA/PORTAb.obj");
   glmUnitize(PORTAb);
   glmFacetNormals(PORTAb);
   glmVertexNormals(PORTAb, 90.0);

   JANELAa = glmReadOBJ("Modelos/JANELA/JANELAa.obj");
   glmUnitize(JANELAa);
   glmFacetNormals(JANELAa);
   glmVertexNormals(JANELAa, 90.0);

   JANELAb = glmReadOBJ("Modelos/JANELA/JANELAb.obj");
   glmUnitize(JANELAb);
   glmFacetNormals(JANELAb);
   glmVertexNormals(JANELAb, 90.0);

   JANELAc = glmReadOBJ("Modelos/JANELA/JANELAc.obj");
   glmUnitize(JANELAc);
   glmFacetNormals(JANELAc);
   glmVertexNormals(JANELAc, 90.0);

   JANELAd = glmReadOBJ("Modelos/JANELA/JANELAd.obj");
   glmUnitize(JANELAd);
   glmFacetNormals(JANELAd);
   glmVertexNormals(JANELAd, 90.0);
   
   BIROCENTRALa = glmReadOBJ("Modelos/BIROCENTRAL/BIROCENTRALa.obj");
   glmUnitize(BIROCENTRALa);
   glmFacetNormals(BIROCENTRALa);
   glmVertexNormals(BIROCENTRALa, 90.0);

   BIROCENTRALb = glmReadOBJ("Modelos/BIROCENTRAL/BIROCENTRALb.obj");
   glmUnitize(BIROCENTRALb);
   glmFacetNormals(BIROCENTRALb);
   glmVertexNormals(BIROCENTRALb, 90.0);
   
   BIROCENTRALc = glmReadOBJ("Modelos/BIROCENTRAL/BIROCENTRALc.obj");
   glmUnitize(BIROCENTRALc);
   glmFacetNormals(BIROCENTRALc);
   glmVertexNormals(BIROCENTRALc, 90.0);
 
   MESAGRANDEa = glmReadOBJ("Modelos/MESAGRANDE/MESAGRANDEa.obj");
   glmUnitize(MESAGRANDEa);
   glmFacetNormals(MESAGRANDEa);
   glmVertexNormals(MESAGRANDEa, 90.0);

   BIROLATERALa = glmReadOBJ("Modelos/BIROLATERAL/BIROLATERALa.obj");
   glmUnitize(BIROLATERALa);
   glmFacetNormals(BIROLATERALa);
   glmVertexNormals(BIROLATERALa, 90.0);
   
   BIROLATERALb = glmReadOBJ("Modelos/BIROLATERAL/BIROLATERALb.obj");
   glmUnitize(BIROLATERALb);
   glmFacetNormals(BIROLATERALb);
   glmVertexNormals(BIROLATERALb, 90.0);
   
   BIROLATERALc = glmReadOBJ("Modelos/BIROLATERAL/BIROLATERALc.obj");
   glmUnitize(BIROLATERALc);
   glmFacetNormals(BIROLATERALc);
   glmVertexNormals(BIROLATERALc, 90.0);

   LIXEIRA1a = glmReadOBJ("Modelos/LIXEIRA1/LIXEIRA1a.obj");
   glmUnitize(LIXEIRA1a);
   glmFacetNormals(LIXEIRA1a);
   glmVertexNormals(LIXEIRA1a, 90.0);
  
   LIXEIRA2a = glmReadOBJ("Modelos/LIXEIRA2/LIXEIRA2a.obj");
   glmUnitize(LIXEIRA2a);
   glmFacetNormals(LIXEIRA2a);
   glmVertexNormals(LIXEIRA2a, 90.0);

   CADEIRA1a = glmReadOBJ("Modelos/CADEIRA1/CADEIRA1a.obj");
   glmUnitize(CADEIRA1a);
   glmFacetNormals(CADEIRA1a);
   glmVertexNormals(CADEIRA1a, 90.0);
  
   CADEIRA1b = glmReadOBJ("Modelos/CADEIRA1/CADEIRA1b.obj");
   glmUnitize(CADEIRA1b);
   glmFacetNormals(CADEIRA1b);
   glmVertexNormals(CADEIRA1b, 90.0);    

   CADEIRA2a = glmReadOBJ("Modelos/CADEIRA2/CADEIRA2a.obj");
   glmUnitize(CADEIRA2a);
   glmFacetNormals(CADEIRA2a);
   glmVertexNormals(CADEIRA2a, 90.0);      

   ARCa = glmReadOBJ("Modelos/ARC/ARCa.obj");
   glmUnitize(ARCa);
   glmFacetNormals(ARCa);
   glmVertexNormals(ARCa, 90.0);      
  
   ARCb = glmReadOBJ("Modelos/ARC/ARCb.obj");
   glmUnitize(ARCb);
   glmFacetNormals(ARCb);
   glmVertexNormals(ARCb, 90.0);  

   REGISTROa = glmReadOBJ("Modelos/OUTROS/REGISTROa.obj");
   glmUnitize(REGISTROa);
   glmFacetNormals(REGISTROa);
   glmVertexNormals(REGISTROa, 90.0);       
}

//Função que carrega a iluminação do cenário
void iluminacao(void)
{
   glEnable(GL_LIGHTING);//Habilita iluminação do cenário

   glLightfv (GL_LIGHT1, GL_AMBIENT, L_ambiente);  
   glLightfv (GL_LIGHT1, GL_DIFFUSE, L_difusa);
   glLightfv (GL_LIGHT1, GL_SPECULAR, L_especular);
   glLightfv (GL_LIGHT1, GL_POSITION, L1_posicao);
      
   glLightfv (GL_LIGHT2, GL_AMBIENT, L_ambiente);
   glLightfv (GL_LIGHT2, GL_DIFFUSE, L_difusa);
   glLightfv (GL_LIGHT2, GL_SPECULAR, L_especular);
   glLightfv (GL_LIGHT2, GL_POSITION, L2_posicao);
   
   glEnable (GL_LIGHT1);//Habilita luz 1
   glEnable (GL_LIGHT2);//Habilita luz 2   
   
   
}

//Define aspectos da vizualiação do cenário
void visualizacao(void)
{
   faspect= larguraJanela/alturaJanela;
   glLoadIdentity ();
   glMatrixMode (GL_PROJECTION);
   gluPerspective(angulo,faspect,1,400);//  A projeção usada é a PERSPECTIVA 
   glMatrixMode (GL_MODELVIEW);
   glClearColor (0.0, 0.0, 0.0, 0.0);  
   glLoadIdentity();
}

//Função de redimensionamento de Janela
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
   visualizacao(); //Inicia vizualização
   
   glEnable(GL_DEPTH_TEST);// Habilita o Z-buffer

   iluminacao();
   carregarOBJs();     

   //A partir daqui são definidas as DisplayLists dos objetos
   glNewList(FRENTEFUNDO,GL_COMPILE);//DisplayList das paredes de frente e fundo da sala, desenhadas usando funções de desenho de polígonos
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glBegin(GL_QUADS);
           material(parede);//Carrega material da parede
           glVertex3f(0.000000, 0.000000, 0.000000);
      	   glVertex3f(0.000000, 30.000000, 0.000000);
           glVertex3f(55.000000, 30.000000, 0.000000);
           glVertex3f(55.000000, 0.000000, 0.000000); 
  
     	   glVertex3f(0.000000, 0.000000, 0.200000);
      	   glVertex3f(0.000000, 30.000000, 0.200000);
           glVertex3f(55.000000, 30.000000, 0.200000);
      	   glVertex3f(55.000000, 0.000000, 0.200000);
      
           glVertex3f(0.000000, 30.000000, 0.000000);
           glVertex3f(0.000000, 30.000000, 0.200000);
           glVertex3f(55.000000, 30.000000, 0.200000);
           glVertex3f(55.000000, 30.000000, 0.000000);
      
           glVertex3f(0.000000, 0.000000, 0.000000);
           glVertex3f(0.000000, 0.000000, 0.200000);
           glVertex3f(55.000000, 0.000000, 0.200000);
           glVertex3f(55.000000, 0.000000, 0.000000);
  
           glVertex3f(0.000000, 0.000000, 0.000000);
           glVertex3f(0.000000, 0.000000, 0.200000);
           glVertex3f(0.000000, 30.000000, 0.200000);
           glVertex3f(0.000000, 30.000000, 0.000000);
 
           glVertex3f(55.000000, 0.000000, 0.000000);
           glVertex3f(55.000000, 0.000000, 0.200000);
           glVertex3f(55.000000, 30.000000, 0.200000);
           glVertex3f(55.000000, 30.000000, 0.000000);     
        glEnd(); 
        glPopAttrib();
   glEndList();
   glNewList(PISO,GL_COMPILE);//DisplayList do piso, desenhado usando funções de desenho de polígonos
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glBegin(GL_QUADS);
	      material(piso);
	      glVertex3f(-2.000000, 0.000000, 0.000000);
	      glVertex3f(-2.000000, 0.000000, -115.000000);
	      glVertex3f(57.000000, 0.000000, -115.000000);
	      glVertex3f(57.000000, 0.000000, 0.000000); 	  
	      
	      glVertex3f(-2.000000, -0.200000, 0.000000);
	      glVertex3f(-2.000000, -0.200000, -115.000000);
	      glVertex3f(57.000000,-0.200000, -115.000000);
	      glVertex3f(57.000000,-0.200000, 0.000000);      
        glEnd(); 
        glBegin(GL_LINES);//Linhas que delimitam as cerâmicas do piso.
	      glVertex3f(5.000000, 0.0000100, 0.000000);
	      glVertex3f(5.000000, 0.0000100, -115.000000);
	      glVertex3f(15.000000, 0.0000100, 0.000000);
	      glVertex3f(15.000000, 0.0000100, -115.000000);
	      glVertex3f(22.500000, 0.0000100, 0.000000);
	      glVertex3f(22.500000, 0.0000100, -115.000000);
	      glVertex3f(30.000000, 0.0000100, 0.000000);
	      glVertex3f(30.000000, 0.0000100, -115.000000);
	      glVertex3f(45.000000, 0.0000100, 0.000000);
	      glVertex3f(45.000000, 0.0000100, -115.000000);
	
	      glVertex3f(0.000000, 0.0000100, -10.000000);
	      glVertex3f(55.000000, 0.0000100, -10.000000);
	      glVertex3f(0.000000, 0.0000100, -20.000000);
	      glVertex3f(55.000000, 0.0000100, -20.000000);
	      glVertex3f(0.000000, 0.0000100, -30.000000);
	      glVertex3f(55.000000, 0.0000100, -30.000000);
	      glVertex3f(0.000000, 0.0000100, -40.000000);
	      glVertex3f(55.000000, 0.0000100, -40.000000);	
	      glVertex3f(0.000000, 0.0000100, -50.000000);
	      glVertex3f(55.000000, 0.0000100, -50.000000);
	      glVertex3f(0.000000, 0.0000100, -60.000000);
	      glVertex3f(55.000000, 0.0000100, -60.000000);
	      glVertex3f(0.000000, 0.0000100, -70.000000);
	      glVertex3f(55.000000, 0.0000100, -70.000000);
	      glVertex3f(0.000000, 0.0000100, -80.000000);
	      glVertex3f(55.000000, 0.0000100, -80.000000);
	      glVertex3f(0.000000, 0.0000100, -90.000000);
	      glVertex3f(55.000000, 0.0000100, -90.000000);
	      glVertex3f(0.000000, 0.0000100, -100.000000);
	      glVertex3f(55.000000, 0.0000100, -100.000000);
	      glVertex3f(0.000000, 0.0000100, -110.000000);
	      glVertex3f(55.000000, 0.0000100, -110.000000);           
	glEnd();
        glPopAttrib();
   glEndList();
   glNewList(COLUNA,GL_COMPILE);//DisplayList das colunas,usadas nas paredes esquerda e direita, desenhada usando funções de desenho de polígonos 
        glPushAttrib(GL_ALL_ATTRIB_BITS); 
        glBegin(GL_QUADS);
              material(parede);
              glVertex3f(0.000000, 0.000000, -0.000000);
              glVertex3f(0.000000, 30.000000, -0.000000);
              glVertex3f(4.000000, 30.000000, -0.000000);
              glVertex3f(4.000000, 0.000000, 0.000000);
             
              glVertex3f(0.000000, 0.000000, -2.000000);
              glVertex3f(0.000000, 30.000000, -2.000000);
              glVertex3f(4.000000, 30.000000, -2.000000);
              glVertex3f(4.000000, 0.000000, -2.000000);

              glVertex3f(0.000000, 0.000000, 0.000000);
              glVertex3f(0.000000, 0.000000, -2.000000);
              glVertex3f(0.000000, 30.000000, -2.000000);
              glVertex3f(0.000000, 30.000000, 0.000000);

              glVertex3f(4.000000, 0.000000, 0.000000);
              glVertex3f(4.000000, 0.000000, -2.000000);
              glVertex3f(4.000000, 30.000000, -2.000000);
              glVertex3f(4.000000, 30.000000, 0.000000);

              glVertex3f(0.000000, 0.000000, 0.000000);
              glVertex3f(4.000000, 0.000000, 0.000000);
              glVertex3f(4.000000, 0.000000, -2.000000);
              glVertex3f(0.000000, 0.000000, -2.000000);

              glVertex3f(0.000000, 30.000000, 0.000000);
              glVertex3f(4.000000, 30.000000, 0.000000);
              glVertex3f(4.000000, 30.000000, -2.000000);
              glVertex3f(0.000000, 30.000000, -2.000000);
        glEnd();
        glPopAttrib(); 
   glEndList();        
   glNewList(PADIREITA,GL_COMPILE);//DisplayList da parede direita, desenhada usando funções de desenho de polígonos 
	glPushAttrib(GL_ALL_ATTRIB_BITS);
        glBegin(GL_QUADS);             
              material(parede);
              glVertex3f(0.000000, 0.000000, 0.000000);
              glVertex3f(0.000000, 13.000000, 0.000000);
              glVertex3f(113.000000, 13.000000, 0.000000);
              glVertex3f(113.000000, 0.000000, 0.000000);

              glVertex3f(0.000000, 13.000000, 0.000000);
              glVertex3f(0.000000, 30.000000, 0.000000);
              glVertex3f(1.000000, 30.000000, 0.000000);
              glVertex3f(1.000000, 13.000000, 0.000000); 

              glVertex3f(24.000000, 13.000000, 0.000000);
              glVertex3f(24.000000, 30.000000, 0.000000);
              glVertex3f(45.000000, 30.000000, 0.000000);
              glVertex3f(45.000000, 13.000000, 0.000000);
 
              glVertex3f(68.000000, 13.000000, 0.000000);
              glVertex3f(68.000000, 30.000000, 0.000000);
              glVertex3f(92.000000, 30.000000, 0.000000);
              glVertex3f(92.000000, 13.000000, 0.000000);           
  
              glVertex3f(0.000000, 0.000000, -1.750000);
              glVertex3f(0.000000, 13.000000, -1.750000);
              glVertex3f(113.000000, 13.000000, -1.750000);
              glVertex3f(113.000000, 0.000000, -1.750000);

              glVertex3f(0.000000, 13.000000, -1.750000);
              glVertex3f(0.000000, 30.000000, -1.750000);
              glVertex3f(1.000000, 30.000000, -1.750000);
              glVertex3f(1.000000, 13.000000, -1.750000); 

              glVertex3f(24.000000, 13.000000, -1.750000);
              glVertex3f(24.000000, 30.000000, -1.750000);
              glVertex3f(45.000000, 30.000000, -1.750000);
              glVertex3f(45.000000, 13.000000, -1.750000);
 
              glVertex3f(68.000000, 13.000000, -1.750000);
              glVertex3f(68.000000, 30.000000, -1.750000);
              glVertex3f(92.000000, 30.000000, -1.750000);
              glVertex3f(92.000000, 13.000000, -1.750000);    

              glVertex3f(0.000000, 13.000000, 0.000000);
              glVertex3f(0.000000, 13.000000, -1.750000);
              glVertex3f(113.000000, 13.000000, -1.750000);
              glVertex3f(113.000000, 13.000000, 0.000000); 

              glVertex3f(0.000000, 0.000000, 0.000000);
              glVertex3f(0.000000, 0.000000, -1.750000);
              glVertex3f(0.000000, 30.000000, -1.750000);
              glVertex3f(0.000000, 30.000000, 0.000000);
            
              glVertex3f(1.000000, 13.000000, 0.000000);
              glVertex3f(1.000000, 13.000000, -1.750000);
              glVertex3f(1.000000, 30.000000, -1.750000);
              glVertex3f(1.000000, 30.000000, 0.000000);

              glVertex3f(0.000000, 30.000000, 0.000000);
              glVertex3f(0.000000, 30.000000, -1.750000);
              glVertex3f(1.000000, 30.000000, -1.750000);
              glVertex3f(1.000000, 30.000000, 0.000000);
                         
              glVertex3f(113.000000, 0.000000, 0.000000);
              glVertex3f(113.000000, 0.000000, -1.750000);
              glVertex3f(113.000000, 13.000000, -1.750000);
              glVertex3f(113.000000, 13.000000, 0.000000);

              glVertex3f(45.000000, 30.000000, 0.000000);
              glVertex3f(45.000000, 30.000000, -1.750000);
              glVertex3f(45.000000, 13.000000, -1.750000);
              glVertex3f(45.000000, 13.000000, 0.000000);
 
              glVertex3f(24.000000, 30.000000, 0.000000);
              glVertex3f(24.000000, 30.000000, -1.750000);
              glVertex3f(45.000000, 30.000000, -1.750000);
              glVertex3f(45.000000, 30.000000, 0.000000);
 
              glVertex3f(92.000000, 30.000000, 0.000000);
              glVertex3f(92.000000, 30.000000, -1.750000);
              glVertex3f(92.000000, 13.000000, -1.750000);
              glVertex3f(92.000000, 13.000000, 0.000000);
 
              glVertex3f(68.000000, 30.000000, 0.000000);
              glVertex3f(68.000000, 30.000000, -1.750000);
              glVertex3f(92.000000, 30.000000, -1.750000);
              glVertex3f(92.000000, 30.000000, 0.000000);
	glEnd();	
        glPopAttrib();
   glEndList(); 
   glNewList(PAESQUERDA,GL_COMPILE);//DisplayList da parede esquerda, desenhada usando funções de desenho de polígonos 
	glPushAttrib(GL_ALL_ATTRIB_BITS);
        glBegin(GL_QUADS);             
              material(parede);
              glVertex3f(0.000000, 0.000000, 0.000000);
              glVertex3f(0.000000, 30.000000, 0.000000);
              glVertex3f(2.000000, 30.000000, 0.000000);
              glVertex3f(2.000000, 0.000000, 0.000000);
        
              glVertex3f(2.000000, 22.500000, 0.000000);
              glVertex3f(2.000000, 30.000000, 0.000000);
              glVertex3f(17.000000, 30.000000, 0.000000);
              glVertex3f(17.000000, 22.500000, 0.000000);  
    
              glVertex3f(17.000000, 0.000000, 0.000000);
              glVertex3f(17.000000, 30.000000, 0.000000);
              glVertex3f(19.000000, 30.000000, 0.000000);
              glVertex3f(19.000000, 0.000000, 0.000000);

              glVertex3f(42.000000, 13.000000, 0.000000);
              glVertex3f(42.000000, 30.000000, 0.000000);
              glVertex3f(44.000000, 30.000000, 0.000000);
              glVertex3f(44.000000, 13.000000, 0.000000);

              glVertex3f(42.000000, 13.000000, 0.000000);
              glVertex3f(42.000000, 30.000000, 0.000000);
              glVertex3f(44.000000, 30.000000, 0.000000);
              glVertex3f(44.000000, 13.000000, 0.000000);
 
              glVertex3f(88.000000, 13.000000, 0.000000);
              glVertex3f(88.000000, 30.000000, 0.000000);
              glVertex3f(90.000000, 30.000000, 0.000000);
              glVertex3f(90.000000, 13.000000, 0.000000);
    
              glVertex3f(19.000000, 0.000000, 0.000000);
              glVertex3f(19.000000, 13.000000, 0.000000);
              glVertex3f(113.000000, 13.000000, 0.000000);
              glVertex3f(113.000000, 0.000000, 0.000000);

              glVertex3f(0.000000, 0.000000, -1.750000);
              glVertex3f(0.000000, 30.000000, -1.750000);
              glVertex3f(2.000000, 30.000000, -1.750000);
              glVertex3f(2.000000, 0.000000, -1.750000);

              glVertex3f(17.000000, 0.000000, -1.750000);
              glVertex3f(17.000000, 30.000000, -1.750000);
              glVertex3f(19.000000, 30.000000, -1.750000);
              glVertex3f(19.000000, 0.000000, -1.750000);

              glVertex3f(42.000000, 13.000000, -1.750000);
              glVertex3f(42.000000, 30.000000, -1.750000);
              glVertex3f(44.000000, 30.000000, -1.750000);
              glVertex3f(44.000000, 13.000000, -1.750000);
 
              glVertex3f(88.000000, 13.000000, -1.750000);
              glVertex3f(88.000000, 30.000000, -1.750000);
              glVertex3f(90.000000, 30.000000, -1.750000);
              glVertex3f(90.000000, 13.000000, -1.750000);
             
              glVertex3f(2.000000, 22.500000, -1.750000);
              glVertex3f(2.000000, 30.000000, -1.750000);
              glVertex3f(17.000000, 30.000000, -1.750000);
              glVertex3f(17.000000, 22.500000, -1.750000);
    
              glVertex3f(19.000000, 0.000000, -1.750000);
              glVertex3f(19.000000, 13.000000, -1.750000);
              glVertex3f(113.000000, 13.000000, -1.750000);
              glVertex3f(113.000000, 0.000000, -1.750000);

              glVertex3f(0.000000, 0.000000, 0.000000);
              glVertex3f(0.000000, 0.000000, -1.750000);
              glVertex3f(0.000000, 30.000000, -1.750000);
              glVertex3f(0.000000, 30.000000, 0.000000);

              glVertex3f(2.000000, 0.000000, 0.000000);
              glVertex3f(2.000000, 0.000000, -1.750000);
              glVertex3f(2.000000, 22.500000, -1.750000);
              glVertex3f(2.000000, 22.500000, 0.000000);
    
              glVertex3f(17.000000, 0.000000, 0.000000);
              glVertex3f(17.000000, 0.000000, -1.750000);
              glVertex3f(17.000000, 22.500000, -1.750000);
              glVertex3f(17.000000, 22.500000, 0.000000);

              glVertex3f(42.000000, 30.000000, -1.750000);
              glVertex3f(42.000000, 30.000000, 0.000000);
              glVertex3f(44.000000, 30.000000, 0.000000);
              glVertex3f(44.000000, 30.000000, -1.750000);

              glVertex3f(42.000000, 13.000000, -1.750000);
              glVertex3f(42.000000, 13.000000, 0.000000);
              glVertex3f(42.000000, 30.000000, 0.000000);
              glVertex3f(42.000000, 30.000000, -1.750000);

              glVertex3f(44.000000, 13.000000, -1.750000);
              glVertex3f(44.000000, 13.000000, 0.000000);
              glVertex3f(44.000000, 30.000000, 0.000000);
              glVertex3f(44.000000, 30.000000, -1.750000);

              glVertex3f(88.000000, 13.000000, -1.750000);
              glVertex3f(88.000000, 13.000000, 0.000000);
              glVertex3f(90.000000, 30.000000, 0.000000);
              glVertex3f(90.000000, 30.000000, -1.750000);

              glVertex3f(90.000000, 13.000000, -1.750000);
              glVertex3f(90.000000, 13.000000, 0.000000);
              glVertex3f(90.000000, 30.000000, 0.000000);
              glVertex3f(90.000000, 30.000000, -1.750000);
 
              glVertex3f(88.000000, 30.000000, -1.750000);
              glVertex3f(88.000000, 30.000000, 0.000000);
              glVertex3f(90.000000, 30.000000, 0.000000);
              glVertex3f(90.000000, 30.000000, -1.750000);
              
              glVertex3f(88.000000, 13.000000, -1.750000);
              glVertex3f(88.000000, 13.000000, 0.000000);
              glVertex3f(88.000000, 30.000000, 0.000000);
              glVertex3f(88.000000, 30.000000, -1.750000);
              
              glVertex3f(19.000000, 13.000000, 0.000000);
              glVertex3f(19.000000, 13.000000, -1.750000);
              glVertex3f(113.000000, 13.000000, -1.750000);
              glVertex3f(113.000000, 13.000000, 0.000000); 

              glVertex3f(0.000000, 30.000000, 0.000000);
              glVertex3f(0.000000, 30.000000, -1.750000);
              glVertex3f(19.000000, 30.000000, -1.750000);
              glVertex3f(19.000000, 30.000000, 0.000000); 
	glEnd();	
        glPopAttrib();
   glEndList(); 
   //DisplayList de um retângulo de PVC que forma o teto
   //O teto é formado por 9x10 retangulos
   glNewList(TETO,GL_COMPILE);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
            glPushMatrix();
               material(tetoc);
               glScalef(6.15, 5.0, 5.8);// Escala geralmente necessária quando modelos vindos do blender são carregados
               glTranslatef(0.0, 0.0, -0.75);//  |Posicionamos o objeto na origem ANTES de realizar a escala
               glRotatef(180.0, 0.0, 0.0, 1.0);//|com a disposição correta para que da display seja preciso apenas posicioná-los
               glmDraw(TETOc, GLM_SMOOTH);//Desenha o modelo carregado com Shademodel Smooth
               material(tetoab);                
               glTranslatef(0.0, 0.01, 0.0);
               glmDraw(TETOa, GLM_SMOOTH); 
            glPopMatrix();
        glPopAttrib();
   glEndList(); 
   //DisplayList de um retângulo de PVC que forma o teto, porém este contém um espaço para colocação da lâmpada 
   glNewList(TETOl,GL_COMPILE);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
            glPushMatrix();
               material(tetoc);
               glScalef(6.15, 5.0, 5.8);
               glTranslatef(0.0, 0.0, -0.75);
               glRotatef(180.0, 0.0, 0.0, 1.0);
               glmDraw(TETOc, GLM_SMOOTH); 
               material(tetoab);
               glTranslatef(0.0, 0.01, 0.0);
               glmDraw(TETOb, GLM_SMOOTH); 
               material(tetod);
               glTranslatef(0.0, 0.03, 0.0);
               glmDraw(TETOd, GLM_SMOOTH); 
               glTranslatef(0.0, 0.02, 0.0);
               glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissive);
               glmDraw(LAMPADAa, GLM_SMOOTH); 
            glPopMatrix();
        glPopAttrib();
   glEndList();
   //DisplayList de um conjunto de retângulos de PVC que formam o teto, são usadas 10 "colunas" como esta para o desenho do teto 
   glNewList(COLUNATETO,GL_COMPILE);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
            glPushMatrix();
               glCallList(TETO);//Chamada a um retângulo comum  
               glTranslatef(0.0, 0.0, -11.5);        
               glCallList(TETO);
               glTranslatef(0.0, 0.0, -11.5);        
               glCallList(TETO);
               glTranslatef(0.0, 0.0, -11.5);        
               glCallList(TETO);
               glTranslatef(0.0, 0.0, -11.5);        
               glCallList(TETO);
               glTranslatef(0.0, 0.0, -11.5);        
               glCallList(TETO);
               glTranslatef(0.0, 0.0, -11.5);        
               glCallList(TETO);
               glTranslatef(0.0, 0.0, -11.5);        
               glCallList(TETO);
               glTranslatef(0.0, 0.0, -11.5);        
               glCallList(TETO);
               glTranslatef(0.0, 0.0, -11.5);        
               glCallList(TETO);
           glPopMatrix();
        glPopAttrib();
   glEndList();
   //DisplayList de um conjunto de retângulos de PVC que formam o teto, esta porém contém alguns retângulos que possuem espaço para lâmpada 
   glNewList(COLUNATETOl,GL_COMPILE);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
            glPushMatrix();
               glCallList(TETOl);//Chamada a um retângulo com espaço para lâmpada  
               glTranslatef(0.0, 0.0, -11.5);        
               glCallList(TETO);
               glTranslatef(0.0, 0.0, -11.5);        
               glCallList(TETOl);
               glTranslatef(0.0, 0.0, -11.5);        
               glCallList(TETO);
               glTranslatef(0.0, 0.0, -11.5);        
               glCallList(TETOl);
               glTranslatef(0.0, 0.0, -11.5);        
               glCallList(TETO);
               glTranslatef(0.0, 0.0, -11.5);        
               glCallList(TETOl);
               glTranslatef(0.0, 0.0, -11.5);        
               glCallList(TETO);
               glTranslatef(0.0, 0.0, -11.5);        
               glCallList(TETOl);
               glTranslatef(0.0, 0.0, -11.5);        
               glCallList(TETO);
           glPopMatrix();
        glPopAttrib();
   glEndList();
   //DisplayList da Porta. Usamos BLENDING pra tornar os vidros transparentes
   //Com a maioria dos objetos trazidos do blender, julgamos necessária a divisão dos mesmos em objetos menores,
   //tanto para ajudar na aplicação dos materiais quanto para tornar evidente qual parte do objeto está sendo desenhado
   glNewList(PORTA,GL_COMPILE);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
            glPushMatrix();
               material(porta);               
               glScalef(10.0, 10.95, 11.2); 
               glTranslatef(0.0, 1.04, 0.0); 
               glRotatef(90.0, 0.0, 1.0, 0.0);
               glRotatef(90.0, 1.0, 0.0, 0.0);  
               glEnable(GL_BLEND);//Habilita o blending
               glDepthMask(GL_FALSE);//Desabilita a máscara de profundidade
               glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//Define os valores r,g,b e alpha q geram a transparência
               glmDraw(PORTAa, GLM_SMOOTH);//Parte de vidro da porta: a própria porta e a maçaneta        
               glDepthMask(GL_TRUE);//Habilita a máscara de profundidade
               glDisable(GL_BLEND); //Desabilita o blending     
               glmDraw(PORTAb, GLM_SMOOTH);// Parte de ferro da porta          
            glPopMatrix();  
        glPopAttrib();
   glEndList();
   //DisplayList das Janelas. Usamos BLENDING pra tornar os vidros transparentes
   glNewList(JANELA,GL_COMPILE);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
            glPushMatrix();   
               material(janelaa);            
               glScalef(10.0, 11.4, 10.5); 
               glTranslatef(0.0, -0.04, 0.01);
               glRotatef(-90.0, 0.0, 0.0, 1.0);
               glRotatef(90.0, 0.0, 1.0, 0.0);  
               glmDraw(JANELAa, GLM_SMOOTH);//Armação de ferro da janela
               glEnable(GL_BLEND);
               glDepthMask(GL_FALSE);
               glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);               
               glTranslatef(-0.75, 0.0, -0.53);
               glScalef(1.3, 1.0, 1.3);
               material(janelac); 
               glmDraw(JANELAc, GLM_SMOOTH);//Vidro da parte de cima da janela. São 4
               glTranslatef(0.385, 0.0, 0.0);
               glmDraw(JANELAc, GLM_SMOOTH);
               glTranslatef(0.384, 0.0, 0.0);
               glmDraw(JANELAc, GLM_SMOOTH);
               glTranslatef(0.384, 0.0, 0.0);
               glmDraw(JANELAc, GLM_SMOOTH);
               glTranslatef(-0.01, 0.0, 0.58);
               glScalef(0.4, 0.4, 0.4);
               material(janelab); 
               glmDraw(JANELAb, GLM_SMOOTH);//Vidro da parte de baixo da janela. São 5
               glTranslatef(-0.92, 0.1, 0.0); 
               glmDraw(JANELAb, GLM_SMOOTH);  
               glTranslatef(-1.0, 0.0, 0.0); 
               glmDraw(JANELAb, GLM_SMOOTH);  
               glTranslatef(-0.92, -0.1, 0.0); 
               glmDraw(JANELAb, GLM_SMOOTH);                      
               glDepthMask(GL_TRUE);
               glDisable(GL_BLEND);                         
            glPopMatrix();  
        glPopAttrib();
   glEndList();
   //DisplayList das Janelas da parede esquerda, que têm grade na parte externa
   glNewList(JANELAg,GL_COMPILE);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
            glPushMatrix(); 
               material(janelaa);              
               glScalef(10.0, 11.4, 10.5); 
               glTranslatef(0.0, -0.04, 0.01);
               glRotatef(-90.0, 0.0, 0.0, 1.0);
               glRotatef(90.0, 0.0, 1.0, 0.0);  
               glmDraw(JANELAa, GLM_SMOOTH);
               material(janelad);
               glTranslatef(0.0, 0.1, 0.0);
               glmDraw(JANELAd, GLM_SMOOTH);//Grade da parte externa
               glTranslatef(0.0, -0.1, 0.0);
               glEnable(GL_BLEND);
               glDepthMask(GL_FALSE);
               glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);               
               glTranslatef(-0.75, 0.0, -0.53);
               glScalef(1.3, 1.0, 1.3); 
               material(janelac);
               glmDraw(JANELAc, GLM_SMOOTH);
               glTranslatef(0.385, 0.0, 0.0);
               glmDraw(JANELAc, GLM_SMOOTH);
               glTranslatef(0.384, 0.0, 0.0);
               glmDraw(JANELAc, GLM_SMOOTH);
               glTranslatef(0.384, 0.0, 0.0);
               glmDraw(JANELAc, GLM_SMOOTH);
               glTranslatef(-0.01, 0.0, 0.58);
               glScalef(0.4, 0.4, 0.4); 
               material(janelab);
               glmDraw(JANELAb, GLM_SMOOTH);
               glTranslatef(-0.92, 0.1, 0.0); 
               glmDraw(JANELAb, GLM_SMOOTH);  
               glTranslatef(-1.0, 0.0, 0.0); 
               glmDraw(JANELAb, GLM_SMOOTH);  
               glTranslatef(-0.92, -0.1, 0.0); 
               glmDraw(JANELAb, GLM_SMOOTH);                      
               glDepthMask(GL_TRUE);
               glDisable(GL_BLEND);                         
            glPopMatrix();  
        glPopAttrib();
   glEndList();
   //DisplayList dos Birôs duplos existenstes no meio da sala. Ele foi dividido em 3 partes
   glNewList(BIROCENTRAL,GL_COMPILE);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
            glPushMatrix();
               glScalef(9.5, 6.5, 5.0);
               glTranslatef(0.0, -0.55, -0.5);
               glRotatef(90.0, 1.0, 0.0, 0.0);
               glmDraw(BIROCENTRALb, GLM_SMOOTH);   
               glTranslatef(0.8863, 0.0, 0.0);
               glmDraw(BIROCENTRALb, GLM_SMOOTH);   
               glTranslatef(0.86, 0.0, 0.0);
               glmDraw(BIROCENTRALb, GLM_SMOOTH);   
            glPopMatrix(); 
            glPushMatrix();
               glScalef(5.7, 8.0, 5.0);
               glTranslatef(0.75, -0.25, 0.15);
               glRotatef(90.0, 1.0, 0.0, 0.0);
               glmDraw(BIROCENTRALc, GLM_SMOOTH);
               glTranslatef(1.41, -1.3, 0.0);
               glRotatef(180.0,0.0, 1.0, 0.0);
               glmDraw(BIROCENTRALc, GLM_SMOOTH);  
            glPopMatrix();
            glPushMatrix();   
               material(biroa);//Material diferente do resto do birô            
               glScalef(5.0, 8.0, 5.0);
               glTranslatef(0.86, -0.3, -0.4);
               glRotatef(90.0, 1.0, 0.0, 0.0);
               glmDraw(BIROCENTRALa, GLM_SMOOTH);
               glTranslatef(1.6, -0.2, 0.0);
               glRotatef(180.0,0.0, 0.0, 1.0);
               glmDraw(BIROCENTRALa, GLM_SMOOTH);  
            glPopMatrix();             
        glPopAttrib();
   glEndList();
   //DisplayList da mesa existente perto da entrada da sala
   glNewList(MESAGRANDE,GL_COMPILE);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
            glPushMatrix(); 
               material(mesa);              
               glScalef(6.5, 8.0, 6.0);
               glTranslatef(1.0, 0.42, -0.7);
               glRotatef(90.0, 1.0, 0.0, 0.0);
               glmDraw(MESAGRANDEa, GLM_SMOOTH);
            glPopMatrix();
        glPopAttrib();
   glEndList();
   //DisplayList do conjunto de birôs existente no lado oposto à entrada da sala. 
   glNewList(BIROLATERAL,GL_COMPILE);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
            glPushMatrix();
               material(birolaterala);
               glScalef(6.0, 8.0, 6.0);
               glTranslatef(0.0, 0.89, 0.0);
               glRotatef(-90.0, 0.0, 1.0, 0.0);
               glRotatef(90.0, 1.0, 0.0, 0.0);
               glmDraw(BIROLATERALa, GLM_SMOOTH);
               material(birolateralb);
               glmDraw(BIROLATERALb, GLM_SMOOTH);
               glTranslatef(-2.0, 0.0, 0.0);
               material(birolaterala);
               glmDraw(BIROLATERALa, GLM_SMOOTH);
               material(birolateralb);
               glmDraw(BIROLATERALb, GLM_SMOOTH);
               glTranslatef(-2.0, 0.0, 0.0);
               material(birolaterala);
               glmDraw(BIROLATERALa, GLM_SMOOTH);
               material(birolateralb);
               glmDraw(BIROLATERALb, GLM_SMOOTH);
               glTranslatef(-1.3, 0.0, 0.0);
               material(birolaterala);
               glmDraw(BIROLATERALa, GLM_SMOOTH);
               material(birolateralb);
               glmDraw(BIROLATERALb, GLM_SMOOTH);
               glTranslatef(-2.0, 0.0, 0.0);
               material(birolaterala);
               glmDraw(BIROLATERALa, GLM_SMOOTH);
               material(birolateralb);
               glmDraw(BIROLATERALb, GLM_SMOOTH);
               glTranslatef(-2.0, 0.0, 0.0);
               material(birolaterala);
               glmDraw(BIROLATERALa, GLM_SMOOTH);
               material(birolateralb);
               glmDraw(BIROLATERALb, GLM_SMOOTH);
               glTranslatef(-2.0, 0.0, 0.0);
               material(birolaterala);
               glmDraw(BIROLATERALa, GLM_SMOOTH);
               material(birolateralb);
               glmDraw(BIROLATERALb, GLM_SMOOTH);
            glPopMatrix();
            glPushMatrix();
               material(birolateralc);
               glScalef(6.5, 8.0, 6.7);
               glTranslatef(0.3, 0.7, -0.9);
               glRotatef(-90.0, 0.0, 1.0, 0.0);
               glRotatef(90.0, 1.0, 0.0, 0.0);               
               glmDraw(BIROLATERALc, GLM_SMOOTH);
               glTranslatef(-1.8, 0.0, 0.0);
               glmDraw(BIROLATERALc, GLM_SMOOTH);
               glTranslatef(-2.95, 0.0, 0.0);
               glmDraw(BIROLATERALc, GLM_SMOOTH);
               glTranslatef(-1.8, 0.0, 0.0);
               glmDraw(BIROLATERALc, GLM_SMOOTH);
               glTranslatef(-1.8, 0.0, 0.0);
               glmDraw(BIROLATERALc, GLM_SMOOTH);
            glPopMatrix();
        glPopAttrib();
   glEndList();
   //DisplayLists das duas lixeiras existentes na sala
   glNewList(LIXEIRA1,GL_COMPILE);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
            glPushMatrix();
               material(lixeira1);
               glScalef(2.0, 2.0, 2.0);
               glTranslatef(1.0, 1.0, -1.0);
               glRotatef(90.0, 1.0, 0.0, 0.0);
               glmDraw(LIXEIRA1a, GLM_SMOOTH);
            glPopMatrix();
        glPopAttrib();
   glEndList();
   glNewList(LIXEIRA2,GL_COMPILE);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
            glPushMatrix();
               material(lixeira2);
               glScalef(2.0, 2.0, 2.0);
               glTranslatef(1.0, 1.0, -1.0);
               glRotatef(90.0, 1.0, 0.0, 0.0);
               glmDraw(LIXEIRA2a, GLM_SMOOTH);
            glPopMatrix();
        glPopAttrib();
   glEndList();
   //DisplayLists dos dois tipos de cadeira existentes na sala. Uma com apoio(dividida em duas partes) e outra não.
   glNewList(CADEIRA1,GL_COMPILE);
	glPushAttrib(GL_ALL_ATTRIB_BITS);           
            glPushMatrix();
               material(cadeira1a);              
               glScalef(6.0, 6.0, 6.0);
               glTranslatef(0.65, 0.98, -0.75);
               glRotatef(90.0, 1.0, 0.0, 0.0);
               glmDraw(CADEIRA1a, GLM_SMOOTH);               
            glPopMatrix();
            glPushMatrix();  
               material(cadeira1b);             
               glScalef(4.0, 4.0, 4.0);
               glTranslatef(1.0, 1.0, -1.0);
               glRotatef(90.0, 1.0, 0.0, 0.0);
               glmDraw(CADEIRA1b, GLM_SMOOTH);
            glPopMatrix();            
        glPopAttrib();
   glEndList();
   glNewList(CADEIRA2,GL_COMPILE);
	glPushAttrib(GL_ALL_ATTRIB_BITS);           
            glPushMatrix();
               material(cadeira2);              
               glScalef(4.5, 4.0, 4.5);
               glTranslatef(0.65, 0.98, -0.75);
               glRotatef(90.0, 1.0, 0.0, 0.0);
               glmDraw(CADEIRA2a, GLM_SMOOTH);               
            glPopMatrix();            
        glPopAttrib();
   glEndList();
   //DisplayLists do ar-condicionado e do registro de energia
   glNewList(ARCOND,GL_COMPILE);
	glPushAttrib(GL_ALL_ATTRIB_BITS);           
            glPushMatrix(); 
               material(arcondicionadob); 
               glScalef(3.5, 3.5, 3.5);
               glTranslatef(0.0, 0.5, -1.0);
               glRotatef(90.0, 0.0, 1.0, 0.0);
               glRotatef(90.0, 1.0, 0.0, 0.0);
               glmDraw(ARCb, GLM_SMOOTH);   
               material(arcondicionadoa);
               glScalef(1.18, 1.0, 1.1);
               glTranslatef(0.24, -0.10, -0.42); 
               glmDraw(ARCa, GLM_SMOOTH);           
            glPopMatrix();            
        glPopAttrib();
   glEndList();
   glNewList(REGISTRO,GL_COMPILE);
	glPushAttrib(GL_ALL_ATTRIB_BITS);           
            glPushMatrix(); 
               material(registro1);           
               glScalef(2.0, 2.0, 2.0);
               glTranslatef(0.0, 0.5, 0.0);
               glRotatef(90.0, 1.0, 0.0, 0.0);
               glmDraw(REGISTROa, GLM_SMOOTH);               
            glPopMatrix();            
        glPopAttrib();
   glEndList();
}

void display(void)
{    
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   
   glLoadIdentity();
   glViewport(0, 0, larguraJanela, alturaJanela); 
    
   // Posiciona e orienta a Câmera
   glRotatef(rotX,1,0,0);
   glRotatef(rotY,0,1,0);
   glTranslatef(-camX,-camY,-camZ);
 
   //A partir daqui os objetos são posicionados e desenhados
   glPushMatrix();
        glCallList(FRENTEFUNDO);
        glTranslatef(0.0, 0.0, -115.0);
        glCallList(FRENTEFUNDO);
   glPopMatrix(); 
   
   glPushMatrix();
        glCallList(PISO);
   glPopMatrix(); 
   
   glPushMatrix();
        glTranslatef(55.0, 0.0, -115.0);
        glRotatef(-90.0,0.0, 1.0, 0.0);
        glCallList(PADIREITA);        
   glPopMatrix();
   glPushMatrix();
        glTranslatef(53.0, 0.0, 0.0);
        glCallList(COLUNA);  
        glTranslatef(0.0, 0.0, -47.0);
        glCallList(COLUNA);  
        glTranslatef(0.0, 0.0, -44.0);
        glCallList(COLUNA);  
   glPopMatrix();

   glPushMatrix();
        glRotatef(90.0,0.0, 1.0, 0.0);
        glCallList(PAESQUERDA);        
   glPopMatrix();
   glPushMatrix();
        glTranslatef(-3.0, 0.0, -19.0);
        glCallList(COLUNA);  
        glTranslatef(0.0, 0.0, -46.0);
        glCallList(COLUNA);         
        glTranslatef(0.0, 0.0, -46.0);
        glScalef(1.0, 1.0, 2.0);
        glCallList(COLUNA);  
   glPopMatrix();
   
   glPushMatrix();
        glTranslatef(1.5, 30.3, -1.4);        
        glCallList(COLUNATETO); 
        glTranslatef(6.5, 0.0, 0.0);
        glCallList(COLUNATETOl); //Apenas 3 das 10 "colunas" possuem lâmpadas
        glTranslatef(6.5, 0.0, 0.0);     
        glCallList(COLUNATETO); 
        glTranslatef(6.5, 0.0, 0.0);     
        glCallList(COLUNATETO); 
        glTranslatef(6.5, 0.0, 0.0);     
        glCallList(COLUNATETOl); 
        glTranslatef(6.5, 0.0, 0.0);     
        glCallList(COLUNATETO); 
        glTranslatef(6.5, 0.0, 0.0);     
        glCallList(COLUNATETO); 
        glTranslatef(6.5, 0.0, 0.0);     
        glCallList(COLUNATETOl); 
        glTranslatef(6.5, 0.0, 0.0);     
        glCallList(COLUNATETO); 
        glTranslatef(6.5, 0.0, 0.0);     
   glPopMatrix(); 
   
   glPushMatrix();
        glTranslatef(-1.0, 0.0, -9.5);        
        glCallList(PORTA);            
   glPopMatrix();
 
   glPushMatrix();
        glTranslatef(-1.0, 22.0, -31.5);        
        glCallList(JANELA);      
        glTranslatef(0.0, 0.0, -23.0);        
        glCallList(JANELA);             
        glTranslatef(0.0, 0.0, -23.0);        
        glCallList(JANELA);             
        glTranslatef(0.0, 0.0, -23.0);        
        glCallList(JANELA);      
        glTranslatef(56.2, 0.0, -3.0);        
        glCallList(JANELAg); 
        glTranslatef(0.0, 0.0, 43.8);        
        glCallList(JANELAg); 
        glTranslatef(0.0, 0.0, 47.1);        
        glCallList(JANELAg);       
   glPopMatrix(); 
   
   glPushMatrix();
        material(birob);//A cor(material) é carregada na função display, já que existem birôs azuis e amarelos
        glTranslatef(16.0, 10.0, -19.0);        
        glCallList(BIROCENTRAL);            
        glTranslatef(0.0, 0.0, -16.0);   
        glCallList(BIROCENTRAL);
        material(biroc);//Carrega o amarelo
        glTranslatef(0.0, 0.0, -16.0);   
        glCallList(BIROCENTRAL);
        glTranslatef(0.0, 0.0, -16.0);   
        glCallList(BIROCENTRAL);
        material(birob);
        glTranslatef(0.0, 0.0, -16.0);   
        glCallList(BIROCENTRAL);
        material(biroc);//Carrega o azul
        glTranslatef(0.0, 0.0, -16.0);   
        glCallList(BIROCENTRAL);
   glPopMatrix();

   glPushMatrix();
        glTranslatef(18.0, 0.0, 0.0);        
        glCallList(MESAGRANDE);            
   glPopMatrix(); 

   glPushMatrix();
        glTranslatef(48.9, 0.0, -18.0);        
        glCallList(BIROLATERAL);            
   glPopMatrix(); 
   
   glPushMatrix();
        glTranslatef(0.5, 0.0, -68.0);        
        glCallList(LIXEIRA1);            
   glPopMatrix(); 

   glPushMatrix();
        glTranslatef(38.0, 0.0, -17.0);        
        glCallList(LIXEIRA2);            
   glPopMatrix();

   //Posiciona as 23 cadeiras do cenário
   glPushMatrix();
        glTranslatef(5.0, 0.0, 0.0);        
        glCallList(CADEIRA1);    
        glTranslatef(38.0, 0.0, -2.0); 
        glRotatef(100.0, 0.0, 1.0, 0.0);      
        glCallList(CADEIRA2);
        glRotatef(180.0, 0.0, 1.0, 0.0);  
        glTranslatef(-23.0, 0.0, -3.5);         
        glCallList(CADEIRA2);     
        glTranslatef(-13.0, 0.0, -2.0);         
        glCallList(CADEIRA2);
        glTranslatef(-20.0, 0.0, -4.0);         
        glCallList(CADEIRA2);
        glTranslatef(-12.0, 0.0, -2.0);         
        glCallList(CADEIRA2);
        glTranslatef(-12.0, 0.0, -2.0);         
        glCallList(CADEIRA2);        
        glTranslatef(-1.8, 0.0, -4.0);        
        glRotatef(80.0, 0.0, 1.0, 0.0);  
        glCallList(CADEIRA2);
        glRotatef(90.0, 0.0, 1.0, 0.0);  
        glTranslatef(7.0, 0.0, 0.0);  
        glCallList(CADEIRA2);
        glTranslatef(5.0, 0.0, 9.5);  
        glCallList(CADEIRA2);
        glTranslatef(9.0, 0.0, -32.0);  
        glRotatef(80.0, 0.0, 1.0, 0.0); 
        glCallList(CADEIRA2);
        glTranslatef(-2.0, 0.0, -15.0);  
        glCallList(CADEIRA2);
        glTranslatef(-2.0, 0.0, -15.0); 
        glRotatef(20.0, 0.0, 1.0, 0.0);  
        glCallList(CADEIRA2);
        glTranslatef(7.0, 0.0, -13.0); 
        glRotatef(70.0, 0.0, 1.0, 0.0);  
        glCallList(CADEIRA2);
        glTranslatef(14.0, 0.0, -8.0); 
        glRotatef(-70.0, 0.0, 1.0, 0.0);  
        glCallList(CADEIRA2);
        glTranslatef(2.0, 0.0, -16.0); 
        glCallList(CADEIRA2);
        glTranslatef(0.0, 0.0, -16.0); 
        glCallList(CADEIRA2);
        glTranslatef(0.0, 0.0, 2.0); 
        glRotatef(-190.0, 0.0, 1.0, 0.0);  
        glCallList(CADEIRA2);
        glTranslatef(0.0, 0.0, -8.0); 
        glCallList(CADEIRA2);
        glTranslatef(0.0, 0.0, -20.0); 
        glCallList(CADEIRA2);
        glTranslatef(0.0, 0.0, -20.0); 
        glCallList(CADEIRA2);
        glTranslatef(0.0, 0.0, -15.0); 
        glCallList(CADEIRA2);
        glTranslatef(0.0, 0.0, -15.0); 
        glCallList(CADEIRA2);
   glPopMatrix();  
  
   glPushMatrix();
        glTranslatef(54.4, 15.0, -30.0);        
        glCallList(ARCOND);  
        glTranslatef(0.0, 0.0, -45.0);        
        glCallList(ARCOND);          
   glPopMatrix();
 
    glPushMatrix();
        glTranslatef(10, 15.0, -114.5);        
        glCallList(REGISTRO);                 
   glPopMatrix();
 
   glutSwapBuffers();
}

void teclado(unsigned char key, int x, int y)
{
   // Pré-calcula o seno e cosseno do ângulo
   // de direção atual + 90 graus, ou seja,
   // a direção para deslocamento lateral
   sinhor = sin((rotY+90)*M_PI/180.0);
   coshor = cos((rotY+90)*M_PI/180.0);
   // Pré-calcula o seno e cosseno do ângulo horizontal
   // (multiplicado por um fator de 5)
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
        case 'k':
	    if (luz1==1)
            {
               glDisable(GL_LIGHT1);
               luz1=0;
            }
            else   
            {
               glEnable(GL_LIGHT1);
               luz1=1;
            }            
        break;
        case 'l':
            if (luz2==1)
            {
               glDisable(GL_LIGHT2);
               luz2=0;
            }
            else   
            {
               glEnable(GL_LIGHT2);
               luz2=1;
            }            
        break;
        case 'q':
            //exit(0);
        break;	
   }
   glutPostRedisplay();
}

//Função que guardará parâmetros iniciais para mudança da direção ou altura da câmera
void mouse(int button, int state, int x, int y)
{
   if(state==GLUT_DOWN)
   {
	//Guarda os parâmetros iniciais 
	x_ini = x;
	y_ini = y;
	camY_ini = camY;
	rotX_ini = rotX;
	rotY_ini = rotY;
	bot = button;
   }
   else bot = -1;
}
//Função que modifica a direção ou a altura da câmera a partir dos parâmetros iniciais
void move(int x, int y)
{
   if(bot==GLUT_LEFT_BUTTON)
   {
 	// Calcula diferenças
	deltax = x_ini - x;
	deltay = y_ini - y;
	// E modifica ângulos da direção
	rotY = rotY_ini - deltax/5;
	rotX = rotX_ini - deltay/5;
   }
   else if(bot==GLUT_RIGHT_BUTTON)
   {
	// Calcula diferença
	deltay = y_ini - y;
	// E modifica altura da camera
	camY = camY_ini + deltay/5;
   }
   glutPostRedisplay();
}

void idle(void)
{
   glutPostRedisplay();
}

int main(int argc, char** argv)
{
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
