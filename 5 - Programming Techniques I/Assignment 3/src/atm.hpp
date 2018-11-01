#ifndef ATM_HPP
#define ATM_HPP

#include "central.hpp"

using namespace std;

class atm
{
    private:
        char conta[7];//Numero da conta em uso
        char senha[10];//Senha
        int id_banco;//ID do banco
    public:
        atm();//Construtor
        ~atm();//Destrutor
        void requisicaoDados();//Entrada de dados
        void escolherBanco();//Escolha do banco
        int escolherOperacao();//Escolha da operacao
};

#endif
