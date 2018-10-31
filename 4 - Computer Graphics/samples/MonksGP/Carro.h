#include <GL/glut.h>

#define ESQUERDA 1
#define TOPO 2	// nao deve ser escalonado!
#define CARRO 3
#define DIAGONAL 4
#define TAMPA 5
#define TRASEIRA 6	// nao deve ser escalonado!
#define ASA 7
#define AEROFOLIO_A 8
#define AEROFOLIO_B 10	// nao deve ser escalonado!
#define BICO 9
#define FUNDO 11
#define CAPACETE 12
#define VISEIRA 13
#define RODA 14

class Carro : public Objeto {
	private:
		float velocidade; // velocidade do carro na pista
		GLfloat corLateral[3]; // cor da lateral, parte do bico e do capacete [default: verde]
		GLfloat corListras[3]; // listras laterais do carro e capacete [default: azul]
		GLfloat corTopo[3]; // cor da parte de cima do carro e detalhe frontal do bico [default: branco]
		GLfloat corDetalhes[3]; // detalhes do bico e capacete [default: amarelo]
		GLfloat corPainel[3]; // cor do painel [default: cinza]
		GLfloat corSuporte[3]; // suporte da asa traseira [default: preto]
	
	    GLfloat corViseiraLateral[3]; // lateral da viseira [defaul: preto]
	    GLfloat corCentroCapacete[3]; // centro do capacete [defaul: branco]
		GLfloat corViseira[3]; // centro da Viseira [defaul: cinza]
	    GLfloat corTopoCapacete[3]; // topo do capacete [defaul: azul]
	    GLfloat corListraCapacete[3]; // listra do capacete [defaul: amarelo]
	    GLfloat corCapacete[3]; // cor do capacete [defaul: verde
		
	public:
		void setVelocidade(float v);
		void setCorLateral(float r, float g, float b);
		void setCorListras(float r, float g, float b);
		void setCorTopo(float r, float g, float b);
		void setCorDetalhes(float r, float g, float b);
		void setCorSuporte(float r, float g, float b);
		void setCorPainel(float r, float g, float b);
		
		void setCorViseiraLateral(float r, float g, float b);
	    void setCorCentroCapacete(float r, float g, float b);
		void setCorViseira(float r, float g, float b);
	    void setCorTopoCapacete(float r, float g, float b);
	    void setCorListraCapacete(float r, float g, float b);
	    void setCorCapacete(float r, float g, float b);
		
		void iniciarListas();
		void draw();
		
		float getVelocidade();
		Carro();
		Carro(float Posicao[3]);
};
