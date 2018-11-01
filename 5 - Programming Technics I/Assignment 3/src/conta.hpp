#ifndef CONTA_HPP
#define CONTA_HPP

#include <iostream>
#include <cstring>

using namespace std;

class conta
{
    public:
        int uso;//Indica se a conta esta em uso
        int n_titulares;//Numero de titulares da conta
        float saldo;//Saldo da conta
        char vet_senha[10][10];//Senhas da conta
        conta(char[20]);//Construtor
        ~conta();//Destrutor
        int saque(float);//Realiza a operacao de saque
        int deposito(float);//Realiza a operacao de deposito
        float extrato();//Realiza a operacao de extrato
        void liberar_conta();//Libera a conta
};

#endif
