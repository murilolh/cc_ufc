#ifndef BANCO_HPP
#define BANCO_HPP

#include "conta.hpp"
#include <cstdlib>

using namespace std;

class banco
{
    private:
        int id_banco;//ID do banco
        char dir_conta[20];//Diretorio do banco
    public:
        conta* Conta;//Ponteiro para a conta em uso
        banco(int);//Construtor
        ~banco();//Destrutor
        int autentica_usuario(char[7], char[4]);//Autentica o usuario, bloqueando a conta em caso de sucesso
        float executarOperacao(char conta[7], int tipo);//Executa operacoes que nao necessitam de um valor de entrada
        int executarOperacao(char conta[7], int tipo, float valor);//Executa operacoes que necessitam de um valor de entrada
        void sairConta(char conta[7]);//Sai da conta, liberando-a
};

#endif
