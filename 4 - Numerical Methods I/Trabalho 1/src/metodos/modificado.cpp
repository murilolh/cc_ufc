#include "modificado.h"
#include <iostream>
#include <cmath>

//metodo construtor do metodo N-R modificado
modificado::modificado(double Po1, double E1) : newtonraphson(Po1, E1){};		

/* método que calcula a raiz final, as iterações e o critério de parada*/
double* modificado:: newton()
{
    double fx,dfx,x,Xo;
    double* Int = new double[2];
    double* Quadro = new double[5];
	
    int k=0; //numero de iterações
    
    Int = isolamento();//matriz que recebe o intervalo onde a raiz esta contida
			
    Xo = (Int[0]+Int[1])/2; //aprox. inicial
	
	delete Int;
	
	Quadro[0] = Xo;
    Quadro[2] = k;
	
    fx = getfx(Xo); //valor da funçao para a aprox. inicial
    dfx = getdfx(Xo); //valor da derivada da funçao para a aprox. inicial
        
    while (1)
    {
        x = Xo -(fx/dfx); 
        if ((fabs(fx)<E1) || (fabs(x - Xo)<E1)) //se encontrada a raiz pelos criterios de parada
        {
            Quadro[1] = x;
            Quadro[2] = k++;
            Quadro[3] = fabs(fx);
            Quadro[4] = fabs(x - Xo);
            return Quadro;
        }   	
        else //realizar mais uma iteraçao ; nesse caso, o valor da derivada e constante
        {
            Xo=x;
            fx = getfx(Xo); 
        }
        k++; //incrementa numero de iteraçoes
    }           
}
