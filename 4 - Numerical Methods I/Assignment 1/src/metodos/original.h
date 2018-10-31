#ifndef ORIGINAL_H_
#define ORIGINAL_H_

#include "newtonraphson.h"

/* definição da classe ORIGINAL derivada da classe NEWTONRAPHSON*/
class original : public newtonraphson {
public:
	original(double Po1, double E1); /* construtor */ 
	
	double* newton();
	
	inline ~original() { } /* destrutor */
	
};

#endif /*ORIGINAL_H_*/
