//**************************************************************
//                                                             *
// 2º Trabalho - Técnicas de Programação 2009.1                *
// Equipe:                                                     *
// Murilo Lima de Holanda(líder)                Mat:0286740    *
// Leandro Monteiro Guimarães                   Mat:0286756    *
// Leidiane Nascimento de Freitas               Mat:0272980    *
// Victor Pessoa de Azevedo Lia Fook            Mat:0261424    *
//                                                             *
//**************************************************************
#include <iostream>
#include <cstring>
#include "lista.h"
#include "figura.h"
#include "circulo.h"
#include "quadrado.h"
#include "triangulo.h"
#include "trapezio.h"

using namespace std;

int main()
{
    system("clear");
    lista *l = new lista();//Lista usada no programa
    int menu = -1;
    char nome[30],cor[20];
    int i;
    while(menu!=9)
    {
        cout << "\n\n-------------------------------------------------" << endl;
        cout << "\t\tEscolha a opcao:"         << endl;
        cout << " 1-Inserir figura"            << endl;
        cout << " 2-Remover figura"            << endl;
        cout << " 3-Area total das figuras"    << endl;
        cout << " 4-Ordenar por Area"          << endl;
        cout << " 5-Ordenar por Nome"          << endl;
        cout << " 6-Imprimir figuras"          << endl;
        cout << " 7-Agrupar figuras por tipo e ordenar por area" << endl;
        cout << " 8-Agrupar figuras por tipo e ordenar por nome" << endl;
        cout << " 9-Sair"                      << endl;
        cout << "\nEntre valor: "              << endl;
        cin >> menu;   
        system("clear");     
        switch(menu)
        {
            case 1://Insere a figura desejada
                cout << "Digite o tipo de figura a ser inserido:"    << endl;
                cout <<" 1-Circulo"      << endl;
                cout <<" 2-Quadrado"     << endl;
                cout <<" 3-Triangulo"    << endl;
                cout <<" 4-Trapezio"    << endl;
                cout <<"\nEntre valor: "         << endl;
                cin  >> i;
                if (i<1 || i>4)
                {
                  cout << "Opcao Invalida" << endl;
                  break;
                }                   
                cout << "\nDigite o nome: "<< endl;
                cin >> nome;
                cout << "Digite a cor: "<< endl;
                cin >> cor;
                switch (i)
                {
                    case 1:
                    {
                        float raio;
                        cout << "Digite o raio do Circulo: ";
                        cin >> raio;
                        circulo *circ = new circulo(raio);
                        circ->setAtrib(nome,cor,circ->getArea(),1);
                        l->inserir(circ);                        
                        break;
                    }
                    case 2:
                    {
                        float lado;
                        cout << "Digite o lado do Quadrado: ";
                        cin >> lado;
                        quadrado *quad = new quadrado(lado);
                        quad->setAtrib(nome,cor,quad->getArea(),2);
                        l->inserir(quad);                       
                        break; 
                    }
                    case 3:
                    {
                        float base;
                        float altura;
                        cout << "Digite a base do Triangulo: ";
                        cin >> base;
                        cout << "Digite a altura do Triangulo: ";
                        cin >> altura;
                        triangulo *tri = new triangulo(base,altura);
                        tri->setAtrib(nome,cor,tri->getArea(),3);
                        l->inserir(tri);                         
                        break;
                    }
                    case 4:
                    {
                        float bas1;
                        float bas2;
                        float altura;
                        cout << "Digite a base 1 do Trapezio: ";
                        cin >> bas1;
                        cout << "Digite a base 2 do Trapezio: ";
                        cin >> bas2;
                        cout << "Digite a altura do Trapezio: ";
                        cin >> altura;
                        trapezio *tra = new trapezio(bas1,bas2,altura);
                        tra->setAtrib(nome,cor,tra->getArea(),4);
                        l->inserir(tra);                        
                        break;  
                    }                                 
                }
                system("clear");
                cout << "\nFigura "<< nome << " inserida com sucesso!\n" << endl;
            break;            
            
            case 2:
                cout << "Digite o nome da figura a ser removida: "<< endl;
                cin >> nome;
                system("clear");
                l->remover(nome);//Remove a figura ou informa a inexitencia da mesma
            break;
            
            case 3:
                l->areaTotal();//Imprime a area total das figuras
            break;
              
            case 4:
                l->ordena(1);//Ordena as figuras por area
                l->listar();//Lista os elementos                                      
            break;
                
            case 5:
                l->ordena(2);//Ordena as figuras por area
                l->listar();//Lista os elementos      
            break;
            
            case 6:            
                l->listar();//Lista as figuras
            break;
            
            case 7:
                cout << "Digite o tipo da figura: "<< endl;
                cout <<" 1-Circulo"      << endl;
                cout <<" 2-Quadrado"     << endl;
                cout <<" 3-Triangulo"    << endl;
                cout <<" 4-Trapezio"    << endl;
                cout <<"\nEntre valor: "         << endl;
                cin  >> i;
                system("clear");
                l->listartipo(1,i);//Ordena e Lista os elementos por area               
            break;
            
            case 8:
                cout << "Digite o tipo da figura: "<< endl;
                cout <<" 1-Circulo"      << endl;
                cout <<" 2-Quadrado"     << endl;
                cout <<" 3-Triangulo"    << endl;
                cout <<" 4-Trapezio"    << endl;
                cout <<"\nEntre valor: "         << endl;
                cin  >> i;
                system("clear");
                l->listartipo(2,i);//Ordena e Lista os elementos por nome
            break;
            
            case 9:
                l->~lista();//Destroi a lista e encerra o programa
            break;            

            default :
                cout << "\nOpcao Invalida\n" << endl;
            break;
        }        
    }
    return 0;
}
