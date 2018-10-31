#ifndef MODIFICADO_H_
#define MODIFICADO_H_

#include "newtonraphson.h"

/* definição da classe modificado derivada da classe newtonraphson*/
class modificado : public newtonraphson {
public:
	modificado(double Po1, double E1); /* construtor */ 	
	
	double* newton();
		
	inline ~modificado() { } /* destrutor */

};

#endif  /*MODIFICADO_H_*/
