#!/usr/bin/env python
# -*- coding: iso8859-1 -*-
"""###################################################
#
# Exemplo3DComIluminacao.py
# Um programa OpenGL simples que abre uma janela GLUT, 
# desenha um "torus" com iluminação, permite fazer 
# zoom in e zoom out com as teclas Home e End, e
# mover a posição do observador com o mouse
#
# Marcelo Cohen e Isabel H. Manssour
# Este código acompanha o livro 
# "OpenGL - Uma Abordagem Prática e Objetiva"
# 
###################################################"""
import sys
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *

# Inicializa a variável que especifica o ângulo da projeção
# perspectiva
angle=45.0

# Inicializa variável com a relação de aspecto da janela
fAspect = 1.0

# Inicializa as variáveis utilizadas para alterar
# a posição do observador
rotX = rotY = 0
obsX = obsY = 0
obsZ = 150.0
obsX_ini = obsY_ini = obsZ_ini = 0
x_ini = y_ini = bot = 0

# Função responsável pela especificação dos parâmetros de iluminação
def DefineIluminacao():
	luzAmbiente  = (0.2,0.2,0.2,1.0)
	luzDifusa    = (0.7,0.7,0.7,1.0)		# "cor" 
	luzEspecular = (1.0, 1.0, 1.0, 1.0)		# "brilho" 
	posicaoLuz   = (0.0, 50.0, 50.0, 1.0)

	# Capacidade de brilho do material
	especularidade = (1.0,1.0,1.0,1.0)
	especMaterial = 60

	# Define a refletância do material 
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade)
	# Define a concentração do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial)

	# Ativa o uso da luz ambiente 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente)

	# Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente) 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa )
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular )
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz )   

def Desenha():
	# Limpa a janela de visualização com a cor  
	# de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    
	# Chama a função que especifica os parâmetros de iluminação
	DefineIluminacao()
    
	# Altera a cor do desenho para azul
	glColor3f(0.0, 0.0, 1.0)

	# Função da GLUT para fazer o desenho de um "torus" 
	# com a cor corrente
	glutSolidTorus(20.0, 35.0, 20, 40) 

	# Executa os comandos OpenGL
	glutSwapBuffers()

# Função usada para especificar a posição do observador virtual
def PosicionaObservador():
	# Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW)
	# Inicializa sistema de coordenadas do modelo
	glLoadIdentity()
	DefineIluminacao()
	# Especifica posição do observador e do alvo
	glTranslatef(-obsX,-obsY,-obsZ)
	glRotatef(rotX,1,0,0)
	glRotatef(rotY,0,1,0)

# Função usada para especificar o volume de visualização
def EspecificaParametrosVisualizacao():
	# Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION)
	# Inicializa sistema de coordenadas de projeção
	glLoadIdentity()

	# Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)
	gluPerspective(angle,fAspect,0.5,500)

	PosicionaObservador()

# Função callback chamada para gerenciar eventos de teclas normais (ESC)
def Teclado (tecla, x, y):
	if tecla==chr(27): # ESC ?
		sys.exit()

# Função callback chamada para gerenciar eventos de teclas especiais
def TeclasEspeciais (tecla, x, y):
	global angle

	if tecla == GLUT_KEY_HOME:
		if angle>=10:	angle -=5
	elif tecla == GLUT_KEY_END:
		if angle<=150: angle +=5

	EspecificaParametrosVisualizacao()
	glutPostRedisplay()

# Função callback chamada quando o tamanho da janela é alterado 
def AlteraTamanhoJanela (w, h):
	global fAspect

	# Para previnir uma divisão por zero
	if h == 0: h = 1

	# Especifica as dimensões da viewport
	glViewport(0, 0, w, h)
 
	# Calcula a relação de aspecto
	fAspect = float(w)/h;

	EspecificaParametrosVisualizacao()

# Função callback para eventos de botões do mouse
def GerenciaMouse (button, state, x, y):
	global x_ini, y_ini, obsX_ini, obsY_ini, obsZ_ini
	global rotX_ini, rotY_ini, bot

	if state == GLUT_DOWN:
		
		# Salva os parâmetros atuais
		x_ini = x
		y_ini = y
		obsX_ini = obsX
		obsY_ini = obsY
		obsZ_ini = obsZ
		rotX_ini = rotX
		rotY_ini = rotY
		bot = button;

	else: bot = -1;

# Função callback chamada para eventos de movimento do mouse
def GerenciaMovim (x, y):
	global rotX,rotY,obsX,obsY,obsZ

	SENS_ROT	= 5.0
	SENS_OBS	= 10.0
	SENS_TRANSL	= 10.0
		
	# Botão esquerdo ?
	if bot == GLUT_LEFT_BUTTON:

		# Calcula diferenças
		deltax = x_ini - x
		deltay = y_ini - y
		# E modifica ângulos
		rotY = rotY_ini - deltax/SENS_ROT
		rotX = rotX_ini - deltay/SENS_ROT

	# Botão direito ?
	elif bot == GLUT_RIGHT_BUTTON:

		# Calcula diferença
		deltaz = y_ini - y
		# E modifica distância do observador
		obsZ = obsZ_ini + deltaz/SENS_OBS

	# Botão do meio ?
	elif bot == GLUT_MIDDLE_BUTTON:

		# Calcula diferenças
		deltax = x_ini - x;
		deltay = y_ini - y;
		# E modifica posições
		obsX = obsX_ini + deltax/SENS_TRANSL
		obsY = obsY_ini - deltay/SENS_TRANSL

	PosicionaObservador()
	glutPostRedisplay()

# Função responsável por inicializar parâmetros e variáveis
def Inicializa():

	# Define a cor de fundo da janela de visualização como branca
	glClearColor(1.0, 1.0, 1.0, 1.0)
    
	# Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL)
	# Habilita o uso de iluminação
	glEnable(GL_LIGHTING)
	# Habilita a luz de número 0
	glEnable(GL_LIGHT0)
	# Habilita o Z Buffer
	glEnable(GL_DEPTH_TEST)

	# Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_SMOOTH)

# Programa principal
if (__name__ == '__main__'):
	# Define o modo de operação da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
 
	# Especifica a posição inicial da janela GLUT
	glutInitWindowPosition(5,5) 
    
	# Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(450,450) 
 
	# Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Desenho de um torus 3D com iluminação")
 
	# Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha)
  
	# Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela)

	# Registra a função callback para eventos de botões do mouse	
	glutMouseFunc(GerenciaMouse)
	 
	# Registra a função callback para eventos de movimento do mouse	
	glutMotionFunc(GerenciaMovim)

	# Registra a função callback para tratamento das teclas normais 
	glutKeyboardFunc (Teclado)

	# Registra a função callback para tratamento das teclas especiais
	glutSpecialFunc (TeclasEspeciais)
     
	# Chama a função responsável por fazer as inicializações 
	Inicializa()
 
	# Inicia o processamento e aguarda interações do usuário
	glutMainLoop()

