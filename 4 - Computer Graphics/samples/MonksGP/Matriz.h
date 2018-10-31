class Matriz{
	public:
		int m, n;
		double **A;
	public:
		int get_m();
		int get_n();
		double getElem(int i, int j);
		friend Matriz operator* (Matriz A, Matriz B);
		friend Matriz operator* (double x, Matriz B);
		friend Matriz operator+ (Matriz A, Matriz B);
		Matriz identidade();
		void mostra();
		void trocaLinha(int i, int j);
		void trocaColuna(int i, int j);
		//void inserirCol(int j, Vetor b);
		void somaLinha(int i, int j, double coef);
		Matriz transpor();
		void setElem(int i, int j, double elem);
		Matriz(int l, int c);
		Matriz();
};
