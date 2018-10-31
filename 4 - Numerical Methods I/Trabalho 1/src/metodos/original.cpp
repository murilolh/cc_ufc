#include "original.h"
#include <iostream>
#include <cmath>

/* método construtor do N-R original */
original::original(double Po1, double E1) : newtonraphson(Po1, E1){};

/* método que calcula a raiz final, as iterações e o critério de parada*/
double* original:: newton()
{
    double fx,dfx,x,Xo;
	double* Int = new double[2];
    double* Quadro = new double[5]; //matriz onde ficam guardados os dados para o quadro
    
    int k=0; //numero de iterações
    
    Int = isolamento(); //matriz que recebe intervalo da raiz

    Xo = (Int[0]+Int[1])/2; //aproximaçao inicial da raiz
    
    delete Int;
    
    Quadro[0] = Xo;
    Quadro[2] = k;
	
    fx = getfx(Xo);
    dfx = getdfx(Xo);

    while (1)
    {
       x = Xo -(fx/dfx);         
       if ((fabs(fx)<E1) || (fabs(x - Xo)<E1)) //encontrada a raiz pelos criterios de parada
       {
           Quadro[1] = x;
           Quadro[2] = k;
           Quadro[3] = fabs(fx);
           Quadro[4] = fabs(x - Xo);
           return Quadro;              
       }   	
       else //mais uma iteraçao deve ser realizada
       {
           Xo = x;
           fx = getfx(Xo);
           dfx = getdfx(Xo);
       }
       k++;	//incrementa o numero de iteraçoes			
    }
}
