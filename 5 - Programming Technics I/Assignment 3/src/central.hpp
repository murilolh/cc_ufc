#ifndef CENTRAL_HPP
#define CENTRAL_HPP

#include "banco.hpp"

using namespace std;

class central
{
    public: 
        int num_bancos;//Numero de bancos ligados ao sistema
        int banco_atual;//ID do banco em uso
        banco* Banco;//Ponteiro para o banco em uso  
        central();//Construtor
        ~central();//Destrutor
        void opcoesBanco();//Tela de escolha do banco
        void acessarBanco(int id_banco);//Acessa o banco
        float realizarOperacao(int id_banco, int operacao, char conta[7]);//Executa operacoes que nao necessitam de um valor de entrada
        int realizarOperacao(int id_banco, int operacao, float valor, char conta[7]);//Executa operacoes nao necessitam de um valor de entrada
        int autenticarUsuario(int id_banco, char conta[7], char senha[10]);//Autentica o usuario
};

#endif
