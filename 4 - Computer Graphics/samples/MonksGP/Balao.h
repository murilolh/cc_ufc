#include <GL/glut.h>

#define BALAO 31

class Balao : public Objeto{
	public:
		void iniciarListas();
		void draw();
		Balao();
};
