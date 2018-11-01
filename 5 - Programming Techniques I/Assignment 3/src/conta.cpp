#include "conta.hpp"

//Construtor
conta::conta(char dir_conta[20])
{
    int i;
    FILE* fconta = fopen(dir_conta, "r");
    fscanf(fconta,"%d",&this->uso);
    fseek (fconta, 2, SEEK_SET);
    fscanf(fconta,"%d",&this->n_titulares);
    for(i=0;i<this->n_titulares;i++)
    {
        fseek (fconta, i*61 + 6, SEEK_SET);
        fscanf(fconta,"%s",&this->vet_senha[i]);
    }
    fseek (fconta, this->n_titulares*61 + 6, SEEK_SET); 
    fscanf(fconta,"%f",&this->saldo);
    fclose(fconta);
}

conta::~conta()
{
}

//Realiza a operacao de saque
int conta::saque(float valor)
{
    if( (this->saldo - valor) >= 0 )//Verifica se o saldo e maior que o valor
    {
        this->saldo -= valor;
        return 1;
    }
    else
        return 0;
}

//Realiza a operacao de deposito
int conta::deposito(float valor)
{
    this->saldo += valor;
    return 1;
}

//Realiza a operacao de extrato
float conta::extrato()
{
    return (this->saldo);
}

//Libera a conta
void conta::liberar_conta()
{
    this->uso = 0;
}
