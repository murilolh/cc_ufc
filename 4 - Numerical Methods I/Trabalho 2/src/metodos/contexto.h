#ifndef CONTEXTO_H_
#define CONTEXTO_H_

#include "metodo.h"

#define MAX 30


class contexto {
    public:
        contexto(metodo *escolhido);
 
        void executar();
        
        inline ~contexto() { delete[] abstrato;} /* destrutor */       
     
    private:
        metodo *abstrato;    
};


#endif /*CONTEXTO_H_*/
