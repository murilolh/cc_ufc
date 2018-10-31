#include <iostream>
#include <string>
#include <cstdio>
#include <GL/glut.h>

using namespace std;

struct Imagem {
    unsigned long tamX;
    unsigned long tamY;
    char *data;
};


int CarregaBMP(const char *nomearq, Imagem *imagem);
void carregaTextura(string arq_nome, GLuint &onde);


