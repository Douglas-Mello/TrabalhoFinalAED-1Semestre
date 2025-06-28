#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <math.h>
#include <vector>

#include "Veiculo.h"
#include "Local.h"
#include "Pedido.h"
using namespace std;

// Constantes
#define MAX_LOCAIS 100
#define MAX_VEICULOS 100
#define MAX_PEDIDOS 100

// Vetores globais
Veiculo veiculos[MAX_VEICULOS];
int qtdVeiculos = 0;

Local locais[MAX_LOCAIS];
int qtdLocais = 0;

Pedido pedidos[MAX_PEDIDOS];
int qtdPedidos=0;

int Rotaativa = -1;

class Rota {
public:
    Local* saida;
    Pedido* chegada;
    float distancia;

    Rota() : saida(nullptr), chegada(nullptr), distancia(999999.0f) {}

    float calcularDistancia(Local* l, Pedido* p) {
        float dx = l->getx() - p->getx();
        float dy = l->gety() - p->gety();
        return sqrt(dx * dx + dy * dy);
    }

    void tentarAtualizar(Local* l, Pedido* p) {
        float d = calcularDistancia(l, p);
        if (d < distancia) {
            distancia = d;
            saida = l;
            chegada = p;
        }
    }

    void mostrar() {
        cout << "\n== Melhor rota encontrada ==\n";
        if (saida && chegada) {
            cout << "Distancia: " << distancia << "\n";
            cout << "Saida: " << saida->getnome() << " (X: " << saida->getx() << ", Y: " << saida->gety() << ")\n";
            cout << "Chegada: " << chegada->getnome() << " (X: " << chegada->getx() << ", Y: " << chegada->gety() << ")\n";
        } else {
            cout << "Nenhuma rota encontrada.\n";
        }
    }
};

void attpedido(){
     if (Rotaativa == -1) {
        cout << "Nenhuma rota ativa para atualizar.\n";
        return;
    }
    int opc;
    do {
        cout << "[1] Concluir rota atual\n";
        cout << "[2] Retornar a ultima rota (desconcluir)\n";
        cin >> opc;
    } while (opc != 1 && opc != 2);

    if(opc == 1){
        pedidos[Rotaativa].setEntregue(true);   // marca como entregue
        cout << "Pedido " << pedidos[Rotaativa].getnome() << " marcado como entregue.\n";
        Rotaativa = -1;  // nenhuma rota ativa pois foi conclu�da
    }
    else if(opc == 2){
        pedidos[Rotaativa].setEntregue(false); //desmarca entrega
        cout << "Pedido " << pedidos[Rotaativa].getnome() << " marcado como pendente.\n";
    }
}
void peso_caminhao(){
    float cargac,soma;
    cargac=0;
    for(int i=0;i<qtdVeiculos;i++){
        while(cargac!=veiculos[i].getcarga()){
            soma=cargac+Pedido().getcargap();
            if(soma==veiculos[i].getcarga()||(soma>=900 && soma<=1000)){
                cargac=soma;
            }
        }
        veiculos[i].setcarga(cargac);
    }
} 

void menu();

int main() {
    int opcao;

    do {
        menu();
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        cin.ignore(); // <-- ajuste principal: IGNORA o '\n' logo apos ler a opcao

        switch (opcao) {
            case 1:
                if (qtdLocais < MAX_LOCAIS) {
                    char nome[100];
                    float x, y;

                    cout << "Digite o nome do local: ";
                    cin.getline(nome, sizeof(nome));

                    cout << "Digite a coordenada do local (x): ";
                    cin >> x;
                    cout << "Digite a coordenada do local (y): ";
                    cin >> y;
                    cin.ignore(); // limpa o buffer antes de voltar pro menu

                    Local l(nome, x, y);
                    locais[qtdLocais++] = l;
                    cout << "Local cadastrado com sucesso!\n";
                } else {
                    cout << "Limite de locais atingido.\n";
                }
                break;

            case 2:
                cout << "Mostrando locais cadastrados\n";
                for (int i = 0; i < qtdLocais; i++) {
                    cout << "Nome: " << locais[i].getnome() << "\n";
                    cout << "X: " << locais[i].getx() << "\n";
                    cout << "Y: " << locais[i].gety() << "\n";
                    cout << "--------------------------------------------------------------------\n";
                }
                break;

            case 3:
                if (qtdVeiculos < MAX_VEICULOS) {
                    Veiculo v;
                    char placa[20];
                    char modelo[50];
                    int carga;

                    cout << "Digite a placa do veiculo: ";
                    cin.getline(placa, sizeof(placa));

                    cout << "Digite o modelo do veiculo: ";
                    cin.getline(modelo, sizeof(modelo));

                    cout << "Digite a carga suportada pelo veiculo: ";
                    cin >> carga;
                    cin.ignore(); // limpa antes de voltar ao menu

                    v.setplaca(placa);
                    v.setmodelo(modelo);
                    v.setcarga(carga);

                    veiculos[qtdVeiculos++] = v;
                    cout << "Veiculo cadastrado com sucesso!\n";
                } else {
                    cout << "Limite de veiculos atingido.\n";
                }
                break;

            case 4:
                cout << "Mostrando veiculos cadastrados\n";
                for (int i = 0; i < qtdVeiculos; i++) {
                    cout << "Placa: " << veiculos[i].getplaca() << "\n";
                    cout << "Modelo: " << veiculos[i].getmodelo() << "\n";
                    cout << "Carga: " << veiculos[i].getcarga() << "\n";
                    cout << "--------------------------------------------------------------------\n";
                }
                break;

            case 5:
                if (qtdPedidos < MAX_PEDIDOS) {
                    Pedido p;
                    int codigo;
                    char nomeLocal[100];
                    float x, y;
                    int cargap;

                    cout << "Digite o codigo do pedido: ";
                    cin >> codigo;
                    cin.ignore();

                    cout << "Digite o nome do local de entrega: ";
                    cin.getline(nomeLocal, sizeof(nomeLocal));
                    cout << "Digite a coordenada X do local: ";
                    cin >> x;
                    cout << "Digite a coordenada Y do local: ";
                    cin >> y;

                    cout << "Digite a carga do pedido: ";
                    cin >> cargap;
                    cin.ignore();

                    // Preencher os dados
                    p.setcodigo(codigo);
                    p.setnome(nomeLocal);
                    p.setx(x);
                    p.sety(y);


                    p.setcargap(cargap);

                    pedidos[qtdPedidos++] = p;

                    cout << "Pedido cadastrado com sucesso!\n";
                    break;
                } else {
                    cout << "Limite de pedidos atingido.\n";
                    break;
                }


            case 6:
                if (qtdPedidos == 0) {
                    cout << "Nenhum pedido cadastrado ainda.\n";
                } else {
                    cout << "Lista de Pedidos:\n";
                    for (int i = 0; i < qtdPedidos; i++) {
                        cout << "Codigo do Pedido: " << pedidos[i].getcodigo() << "\n";
                        cout << "Local: " << pedidos[i].getnome() << "\n";
                        cout << "Coordenada X: " << pedidos[i].getx() << "\n";
                        cout << "Coordenada Y: " << pedidos[i].gety() << "\n";
                        cout << "Carga: " << pedidos[i].getcargap() << "\n";
                        cout << "--------------------------------------------------\n";
                    }
                }
        break;

            case 7:
            {
                Rota r;
                r.mostrar();
                peso_caminhao();
                    break;
            }
            case 8:
                // backupDados();
                break;
            case 9:
                // restaurarDados();
                break;
            case 10:
                cout <<"Atualizacao do pedido" << endl;
                attpedido();
            case 0:
                cout << "Saindo...\n";
                break;
            default:
                cout << "Opcao invalida.\n";
        }

    } while (opcao != 0);

    return 0;
}

void menu() {
    cout << "\n====== Sistema de Logistica de Entrega (SLEM) ======\n";
    cout << "1. Cadastrar Distribuidora\n";
    cout << "2. Listar Distribuidora\n";
    cout << "3. Cadastrar Veiculo\n";
    cout << "4. Listar Veiculos\n";
    cout << "5. Cadastrar Pedido\n";
    cout << "6. Listar Pedidos\n";
    cout << "7. Calcular Rota// calcular capacidade caminhao\n";
    cout << "8. Backup de Dados\n";
    cout << "9. Restaurar Dados\n";
    cout << "10. Atualizar situacao do pedido\n";
    cout << "0. Sair\n";
}
