#include <GL/glut.h>


#define SKYFRONT 0
#define SKYBACK  1
#define SKYLEFT  2
#define SKYRIGHT 3
#define SKYUP    4
#define SKYDOWN  5


class Cenario : public Objeto {

	private:
		float x, y, z, width, height, length;
		char desenharSkyBox;
		char desenharGrid;

		void drawGrid();
		void drawSkybox(float x, float y, float z, float width, float height, float length);
		
	public:
		void iniciarListas();
		void setSkySize(float x, float y, float z, float width, float height, float length);
		void ligarCeu(char valor);
		void ligarGrid(char valor);
		void draw();
		Cenario();
		Cenario(float x, float y, float z, float width, float height, float length);
};
