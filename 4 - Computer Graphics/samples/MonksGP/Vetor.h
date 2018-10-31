class Vetor : public Matriz{
	public:
		double modulo();
		friend Vetor operator* (double x, Vetor B);
		friend Vetor operator* (Matriz A, Vetor B);
		friend Vetor operator* (Vetor A, Vetor B);
		friend Vetor operator+ (Vetor A, Vetor B);
		void setVetor(float x, float y, float z);
		void getCol(Matriz M, int i);
		Vetor unitario();
		Vetor();
		Vetor(int);
		Vetor(float x, float y, float z);
};
