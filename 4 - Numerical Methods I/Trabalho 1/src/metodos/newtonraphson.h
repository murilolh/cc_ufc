#ifndef NEWTONRAPHSON_H_
#define NEWTONRAPHSON_H_

/* definição da classe base newtonraphson*/
class newtonraphson {
public:
	newtonraphson(double Po, double E); /* construtor */ 
	
	double getfx(double x);
	
	double getdfx(double x);

	double* isolamento();
	
	virtual double* newton() = 0;

 	inline virtual ~newtonraphson(){} /* destrutor */

protected:
	
	double Po1; /* atributo Po1 da classe base que será herdado pelas classes derivadas */
	double E1;  /* atributo cor da classe base que será herdado pelas classes derivadas */
};

#endif /*NEWTONRAPHSON_H_*/
