#include "newtonraphson.h"
#include <iostream>
#include <cmath>

/* método construtor do objeto newtonraphson */
newtonraphson::newtonraphson (double Po, double E)
{
    //Instancia o atributo deslocamento inicial da particula no método
    Po1 = Po;

    //Instancia o atributo precisao no método
    E1 = E;
}

//definiçao da funçao f(x)
double newtonraphson:: getfx(double x)
{
    double f;
    f = Po1*exp(x)-4*pow(x,2); 
    return(f);
}

//derivada da função
double newtonraphson:: getdfx(double x)
{
    double df;
    df = Po1*exp(x)-8*x;
    return(df);
}

//isolamento da funçao para encontrar intervalo onde a raiz se encontra           
double* newtonraphson:: isolamento()
{
    double* I = new double[2]; //matriz que guarda os dois limites do intervalo
    I[0] = 0; 	
    I[1] = 1; //atribui inicialmente o intervalo [0,1]
    while(1)
    {
	 	if (getfx(I[0])*getfx(I[1])<0) // retorna o intervalo caso o produto seja negativo
             return(I);	
           
   	 	else if (Po1 > 2.1653) // Valor crítivo da Função. O intervalo será centrado em um valor negativo nesse caso
     	{
        	if (I[0] < 0) // sendo o extremo inicial negativo
        	{
      			I[1] = I[0];   
      			I[0] = 2*I[0];  // incrementa os extremos do intervalo negativamente
        	}
        	else           // no caso inicial atribui o intervalo [-1, 0]
        	{
      			I[1] = 0;      
      			I[0] = -1;
  	    	}
  	 	}      
     	else  // caso contrário 
     	{
    	 	I[0] = I[1];    
    	 	I[1] = 2*I[0];    // incrementa os extremos do intervalo positivamente
     	}
    }
}
