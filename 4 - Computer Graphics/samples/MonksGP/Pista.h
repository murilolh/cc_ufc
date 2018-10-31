#include <GL/glut.h>
#include <math.h>

#define CURVA 20
#define MURO 21
#define POSTE 22
#define HASTE 23
#define GRADE 24
#define ARQUIBANCADA 25

class Pista : public Objeto {
	private:
		float seno[17];
		float coseno[17];

	public:	

			
		void iniciarListas(); // inicia as listas
		void calcularSenoCos(); // calcula os senos e cossenos necessarios
		void draw(); // desenha o objeto
		Pista();
};
