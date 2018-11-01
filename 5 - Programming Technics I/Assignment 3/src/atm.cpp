#include "atm.hpp"

//Construtor
atm::atm()
{
    while(true)
    {
        int autentica,op,aux;
        float valor;
        central* Central = new central();
        
        this->escolherBanco();
        Central->acessarBanco(this->id_banco);
        
        this->requisicaoDados();
        autentica = Central->autenticarUsuario(this->id_banco,this->conta, this->senha); 
        while(autentica != 1)
        {
           if(autentica == 0)
             cout << "Numero de conta ou senha incorreta!" << endl;
           if(autentica == -1)
             cout << "Sua conta esta sendo utilizada no momento!" << endl;
           cout << "\n\n0 - Voltar a tela inicial" << endl;
           cout << "Qualquer tecla - Tentar novamente" << endl;
           cin >> aux;
           if (aux==0)
               atm();
           else
           {
               this->requisicaoDados();
               autentica = Central->autenticarUsuario(this->id_banco,this->conta, this->senha); 
           }
        }
        if (aux==0)
            break;
        system("clear");  
        cout << "Autenticacao efetuada com sucesso!" << endl;  
              
        op = this->escolherOperacao();
        while (op != 0)
        {
            if(op == 1 || op ==2)
            {
                cout << "\nQual o valor? " << endl;
                cin >> valor;
                if (Central->realizarOperacao(this->id_banco, op, valor, this->conta))
                    cout << "\nOperacao realizada com sucesso!\n\n" <<endl;
                else
                    cout << "\nNao foi possivel realizar a operacao!\n\n" <<endl;
            }
            else
                cout << "Voce tem R$" << Central->realizarOperacao(this->id_banco, op, this->conta) << endl;
            op = this->escolherOperacao();
        }
        Central->realizarOperacao(this->id_banco, op, this->conta);
        system("clear");
    }
}

atm::~atm()
{
}

//Entrada de dados
void atm::requisicaoDados()
{

    cout << "\n\n-------------------------------------------------" << endl;
    cout << "\tEntre com o numero da conta(6 digitos):"         << endl;
    cin >> this->conta;
    cout << "\tEntre com a senha(4 digitos):"         << endl;
    cin >> this->senha;
}

//Escolha do banco
void atm::escolherBanco()
{
    central *Central = new central();
    int num_bancos = Central->num_bancos;
    system("clear");
    do
    {
        Central->opcoesBanco();
        cout << "\nEntre valor: "              << endl;
        cin >> this->id_banco;
        system("clear");
        if (this->id_banco == 0) exit(0);   
        else if((this->id_banco<0) || (this->id_banco>6))
           cout << "\nOpcao Invalida\n" << endl;
    }while( (this->id_banco>num_bancos) || (this->id_banco<0) );
}

//Escolha da operacao
int atm::escolherOperacao()
{
    int op;
    do
    {
        cout << "\n\n-------------------------------------------------" << endl;
        cout << "\t\tO que deseja fazer?"         << endl;
        cout << " 1- Saque"                       << endl;
        cout << " 2- Deposito"                    << endl;
        cout << " 3- Extrato"                     << endl;
        cout << "\n 0- Sair da conta"             << endl;
        cout << "\nEntre valor: "                 << endl;
        cin >> op;
        system("clear");
        if ((op<0) || (op>3))
           cout << "\nOpcao Invalida\n" << endl;        
        else
           return op;             
    }while((op<0) || (op>3));
}
