#include "Matriz.h"
#include "Vetor.h"
#include <GL/glut.h>

void calculaNormal(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3){
	
	Vetor v1 = Vetor(3);
	Vetor v2 = Vetor(3);
	Vetor vn = Vetor(3);

	v1.setVetor(x2 -x1, y2 -y1, z2 - z1);
	v2.setVetor(x3 -x1, y3 -y1, z3 - z1);
	vn = v1*v2;
	vn = vn.unitario();
	glNormal3f(vn.A[0][0], vn.A[1][0], vn.A[2][0]);
}

void calculaNormal(float p1[], float p2[], float p3[]){
	
	Vetor v1 = Vetor(3);
	Vetor v2 = Vetor(3);
	Vetor vn = Vetor(3);

	v1.setVetor(p2[0] - p1[0], p2[1] - p1[1], p2[2] - p1[2]);
	v2.setVetor(p3[0] - p1[0], p3[1] - p1[1], p3[2] - p1[2]);
	vn = v1*v2;
	vn = vn.unitario();
	glNormal3f(vn.A[0][0], vn.A[1][0], vn.A[2][0]);
}
