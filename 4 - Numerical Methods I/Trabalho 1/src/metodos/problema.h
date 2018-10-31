#ifndef problema_H_
#define problema_H_

#include "original.h"
#include "modificado.h"

#define MAX 30

/* definição da classe base problema*/
class problema {
public:
	problema(int n, double e); /* construtor */ 
	
	int simulacao();
	
	void interface();
	
	void comparativo();
	
	void resposta();
	
 	inline ~problema(){};  /* destrutor */
 	
private:
	
	int N;
	double E;
	original *o;
	modificado *m;
	double (*Matriz)[MAX];
};

#endif /*problema_H_*/
