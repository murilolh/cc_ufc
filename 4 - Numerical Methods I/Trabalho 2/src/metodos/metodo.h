#ifndef METODO_H_
#define METODO_H_

/* definição da classe base metodo*/

#define MAX 30

class metodo {
	public:
		metodo(double (*A)[MAX], double B[], int n, double e); /* construtor */ 
		
		double somatorio(double *X1,int lin);
		
		double* diferenca(double* X,double* Y);
		
		double max(double* X);
				
		int criteriodaslinhas();
		
		int criteriodesassenfeld();
		
		virtual int inversa() = 0;
	 	
	 	inline virtual ~metodo(){delete []M;} /* destrutor */

	protected:
		double (*M)[MAX]; /* atributo Matriz da classe base que será herdado pelas classes derivadas */
		double* T; /* atributo Vetor de termos da classe base que será herdado pelas classes derivadas */
		double N; /* atributo numero de particulas da classe base que será herdado pelas classes derivadas */
		double E;  /* atributo precisão da classe base que será herdado pelas classes derivadas */
};

#endif /*METODO_H_*/
