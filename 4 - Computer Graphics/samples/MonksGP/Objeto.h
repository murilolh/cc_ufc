class Objeto{
	protected:
		float x, y, z; // posicao do objeto
		float rx, ry, rz;
		
		virtual void iniciarListas() = 0; // inicia as listas
	public:
		virtual void draw() = 0; // desenha o objeto
		void setPosicao(float x, float y, float z);
		void setRotacao(float rx, float ry, float rz);
		float* getPosicao();
};
