#include "central.hpp"

using namespace std;

//Construtor
central::central()
{
    num_bancos = 6;
}

//Tela de escolha do banco
void central::opcoesBanco()
{
    cout << "\n\n-------------------------------------------------" << endl;
    cout << "\t\tQual o seu banco?"         << endl;
    cout << " 1- Banco do Brasil"            << endl;
    cout << " 2- Banco do Nordeste"            << endl;
    cout << " 3- Bradesco"    << endl;
    cout << " 4- Caixa Economica Federal"          << endl;
    cout << " 5- Banco Itau"          << endl;
    cout << " 6- Banco Real"          << endl;
    cout << "\n 0- Sair"                      << endl;
}

//Acessa o banco
void central::acessarBanco(int id_banco)
{
    this->banco_atual = id_banco;
    this->Banco = new banco(id_banco);
}

//Executa operacoes que nao necessitam de um valor de entrada
float central::realizarOperacao(int id_banco, int operacao, char conta[7])
{
    if (operacao==0)
    {
        this->Banco->sairConta(conta);
        this->Banco->~banco(); 
    }
    else
        return(this->Banco->executarOperacao(conta,operacao));
}

//Executa operacoes que necessitam de um valor de entrada
int central::realizarOperacao(int id_banco, int operacao, float valor, char conta[7])
{
    return(this->Banco->executarOperacao(conta,operacao,valor));
}

//Autentica o usuario
int central::autenticarUsuario(int id_banco, char conta[7], char senha[10])
{
    return(this->Banco->autentica_usuario(conta, senha));
}

