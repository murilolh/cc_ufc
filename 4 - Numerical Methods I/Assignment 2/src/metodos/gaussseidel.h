#ifndef GAUSSSEIDEL_H_
#define GAUSSSEIDEL_H_

#include "metodo.h"

using namespace std;

/* definição da classe GAUSSSEIDEL derivada da classe METODO*/
class gaussseidel : public metodo {
	public:
        gaussseidel(double (*M)[MAX], double B[], int N, double E);

		int inversa();
	
		inline ~gaussseidel() {delete []M;} /* destrutor */
	
};

#endif /*GAUSSSEIDEL_H_*/
