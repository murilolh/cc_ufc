#include "banco.hpp"

//Construtor
banco::banco(int banc)
{
    this->id_banco = banc;
}

//Destrutor
banco::~banco()
{
    delete (Conta);
}

//Autentica o usuario, bloqueando a conta em caso de sucesso
int banco::autentica_usuario(char num_conta[7], char senha[10])
{
    char dirbanco[1];
    FILE *fconta;
    int i;
    
    strcpy(this->dir_conta,"");
    strcat(this->dir_conta,"arquivos/");
    sprintf(dirbanco,"%d",this->id_banco);    
    strcat(this->dir_conta,dirbanco);
    strcat(this->dir_conta,"/");
    strcat(this->dir_conta,num_conta);
    
    if (!fopen(this->dir_conta, "r"))
        return 0;
    else
    {
        this->Conta = new conta(this->dir_conta);
        
        if(Conta->uso == 1)
        {
            Conta->~conta();
            return -1;
        }
        else
        {
            for(i=0;i<Conta->n_titulares;i++)
                if (!strcmp(senha,Conta->vet_senha[i]))
                {
                    fconta = fopen(this->dir_conta, "r+");
                    fseek (fconta, 0, SEEK_SET);
                    fputs("1",fconta);
                    fclose(fconta);
                    return 1;
                }
            return 0; 
        }
    }
}

//Executa operacoes que nao necessitam de um valor de entrada
float banco::executarOperacao(char conta[7], int tipo)
{
    switch(tipo)
    {
       case 3:
          return(this->Conta->extrato());                              
       break;
    }
}

//Executa operacoes que necessitam de um valor de entrada
int banco::executarOperacao(char conta[7], int tipo, float valor)
{
    switch(tipo)
    {           
       case 1:
           this->Conta->saque(valor);    
       break;
       case 2:      
           this->Conta->deposito(valor);    
       break;
    } 
}

//Sai da conta, liberando-a
void banco::sairConta(char conta[7])
{
    Conta->liberar_conta();
    FILE *fconta = fopen(this->dir_conta, "r+");
    fseek (fconta, 0, SEEK_SET);//Modifica a flag que indica o uso para <livre> 
    fprintf(fconta,"0\n");
    fseek (fconta, 6 + Conta->n_titulares*61, SEEK_SET);
    fprintf(fconta,"%f",Conta->saldo);
    fclose(fconta);
    Conta->~conta();
}
