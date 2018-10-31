#ifndef GAUSSJACOB_H_
#define GAUSSJACOB_H_

#include "metodo.h"

using namespace std;

/* definição da classe GAUSSJACOB derivada da classe METODO*/
class gaussjacob : public metodo {
	public:
        gaussjacob(double (*M)[MAX], double B[], int N, double E);

		int inversa();
	
		inline ~gaussjacob() {delete []M;} /* destrutor */
	
};

#endif /*GAUSSJACOB_H_*/
