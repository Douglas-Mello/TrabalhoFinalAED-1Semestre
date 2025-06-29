#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <math.h>
#include <vector>
#include <fstream>

#include "Veiculo.h"
#include "Local.h"
#include "Pedido.h"
using namespace std;

#define MAX_LOCAIS 100
#define MAX_VEICULOS 100
#define MAX_PEDIDOS 100

int Rotaativa = -1;

Veiculo veiculos[MAX_VEICULOS];
int qtdVeiculos = 0;

Local locais[MAX_LOCAIS];
int qtdLocais = 0;

Pedido pedidos[MAX_PEDIDOS];
int qtdPedidos = 0;

class Rota {
private:
    Local* saida;
    Pedido* chegada;
    float distancia;
    int indicePedido;

public:
    Rota() {
        saida = nullptr;
        chegada = nullptr;
        distancia = INFINITY;
        indicePedido = -1;
    }

    void calcular() {
        for (int i = 0; i < qtdLocais; i++) {
            for (int j = 0; j < qtdPedidos; j++) {
                if (pedidos[j].isEntregue()) continue;

                float dx = locais[i].getx() - pedidos[j].getx();
                float dy = locais[i].gety() - pedidos[j].gety();
                float d = sqrt(dx * dx + dy * dy);

                if (d < distancia) {
                    distancia = d;
                    saida = &locais[i];
                    chegada = &pedidos[j];
                    indicePedido = j;
                }
            }
        }

        if (indicePedido != -1) {
            Rotaativa = indicePedido;
        }
    }

    void mostrar() {
        cout << "\n------------------\n";
        cout << "== Melhor rota encontrada ==\n";
        if (saida && chegada) {
            cout << "Distancia: " << distancia << endl;
            cout << "Saida: " << saida->getnome() << " (X: " << saida->getx() << ", Y: " << saida->gety() << ")\n";
            cout << "Chegada: " << chegada->getnome() << " (X: " << chegada->getx() << ", Y: " << chegada->gety() << ")\n";
        } else {
            cout << "Nenhuma rota encontrada.\n";
        }
        cout << "------------------\n";
    }

    int getIndicePedido() const {
        return indicePedido;
    }
};

void caminhao_pd() {
    float limiteCargaMinima;
    bool pedidoAtribuido[MAX_PEDIDOS] = {false};

    for (int i = 0; i < qtdVeiculos; i++) {
        float capacidadeMax = veiculos[i].getcarga();
        float cargaAtual = 0;

        for (int j = 0; j < qtdPedidos; j++) {
            if (pedidoAtribuido[j]) continue;

            float peso = pedidos[j].getcargap();
            if (cargaAtual + peso <= capacidadeMax) {
                cargaAtual += peso;
                pedidoAtribuido[j] = true;
                cout << "Pedido " << pedidos[j].getnome() << " adicionado ao caminhao " << i + 1 << endl;
            }
        }

        veiculos[i].setcarga(cargaAtual);
        limiteCargaMinima = capacidadeMax * 0.95;

        cout << "Caminhao " << i + 1 << " carregado com " << cargaAtual << " kg de " << capacidadeMax << " kg" << endl;

        if (cargaAtual < limiteCargaMinima) {
            cout << "O caminhao " << i + 1 << " nao atingiu 95 da capacidade maxima." << endl;
        }

        cout << "------------------\n";
    }
}

void attpedido() {
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

    if (opc == 1) {
        pedidos[Rotaativa].setEntregue(true);
        cout << "Pedido " << pedidos[Rotaativa].getnome() << " marcado como entregue.\n";
        Rotaativa = -1;
    } else if (opc == 2) {
        pedidos[Rotaativa].setEntregue(false);
        cout << "Pedido " << pedidos[Rotaativa].getnome() << " marcado como pendente.\n";
    }
}

void backupDados() {
    ofstream arqLoc("locais.bin", ios::binary);
    ofstream arqVei("veiculos.bin", ios::binary);
    ofstream arqPed("pedidos.bin", ios::binary);

    // Salvar quantidade para facilitar a leitura depois
    arqLoc.write((char*)&qtdLocais, sizeof(qtdLocais));
    for (int i = 0; i < qtdLocais; i++) {
        // Grava nome fixo 100 chars
        char nome[100];
        strncpy(nome, locais[i].getnome(), 100);
        arqLoc.write(nome, sizeof(nome));
        float x = locais[i].getx();
        float y = locais[i].gety();
        arqLoc.write((char*)&x, sizeof(x));
        arqLoc.write((char*)&y, sizeof(y));
    }

    arqVei.write((char*)&qtdVeiculos, sizeof(qtdVeiculos));
    for (int i = 0; i < qtdVeiculos; i++) {
        char placa[20];
        char modelo[50];
        strncpy(placa, veiculos[i].getplaca(), 20);
        strncpy(modelo, veiculos[i].getmodelo(), 50);
        arqVei.write(placa, sizeof(placa));
        arqVei.write(modelo, sizeof(modelo));
        float carga = veiculos[i].getcarga();
        float x = veiculos[i].getxc();
        float y = veiculos[i].getyc();
        arqVei.write((char*)&carga, sizeof(carga));
        arqVei.write((char*)&x, sizeof(x));
        arqVei.write((char*)&y, sizeof(y));
    }

    arqPed.write((char*)&qtdPedidos, sizeof(qtdPedidos));
    for (int i = 0; i < qtdPedidos; i++) {
        int codigo = pedidos[i].getcodigo();
        char nome[100];
        strncpy(nome, pedidos[i].getnome(), 100);
        float x = pedidos[i].getx();
        float y = pedidos[i].gety();
        int cargap = pedidos[i].getcargap();
        bool entregue = pedidos[i].isEntregue();

        arqPed.write((char*)&codigo, sizeof(codigo));
        arqPed.write(nome, sizeof(nome));
        arqPed.write((char*)&x, sizeof(x));
        arqPed.write((char*)&y, sizeof(y));
        arqPed.write((char*)&cargap, sizeof(cargap));
        arqPed.write((char*)&entregue, sizeof(entregue));
    }

    arqLoc.close();
    arqVei.close();
    arqPed.close();

    cout << "------------------\n";
    cout << "Backup binário realizado com sucesso!\n";
    cout << "------------------\n";
}

void restaurarDados() {
    ifstream arqLoc("locais.bin", ios::binary);
    ifstream arqVei("veiculos.bin", ios::binary);
    ifstream arqPed("pedidos.bin", ios::binary);

    if (!arqLoc || !arqVei || !arqPed) {
        cout << "Arquivos binários de backup não encontrados.\n";
        return;
    }

    arqLoc.read((char*)&qtdLocais, sizeof(qtdLocais));
    for (int i = 0; i < qtdLocais; i++) {
        char nome[100];
        float x, y;
        arqLoc.read(nome, sizeof(nome));
        arqLoc.read((char*)&x, sizeof(x));
        arqLoc.read((char*)&y, sizeof(y));
        Local l(nome, x, y);
        locais[i] = l;
    }

    arqVei.read((char*)&qtdVeiculos, sizeof(qtdVeiculos));
    for (int i = 0; i < qtdVeiculos; i++) {
        char placa[20], modelo[50];
        float carga, x, y;
        arqVei.read(placa, sizeof(placa));
        arqVei.read(modelo, sizeof(modelo));
        arqVei.read((char*)&carga, sizeof(carga));
        arqVei.read((char*)&x, sizeof(x));
        arqVei.read((char*)&y, sizeof(y));
        Veiculo v;
        v.setplaca(placa);
        v.setmodelo(modelo);
        v.setcarga(carga);
        v.setlocalC(x, y);
        veiculos[i] = v;
    }

    arqPed.read((char*)&qtdPedidos, sizeof(qtdPedidos));
    for (int i = 0; i < qtdPedidos; i++) {
        int codigo, cargap;
        char nome[100];
        float x, y;
        bool entregue;

        arqPed.read((char*)&codigo, sizeof(codigo));
        arqPed.read(nome, sizeof(nome));
        arqPed.read((char*)&x, sizeof(x));
        arqPed.read((char*)&y, sizeof(y));
        arqPed.read((char*)&cargap, sizeof(cargap));
        arqPed.read((char*)&entregue, sizeof(entregue));

        Pedido p;
        p.setcodigo(codigo);
        p.setnome(nome);
        p.setx(x);
        p.sety(y);
        p.setcargap(cargap);
        p.setEntregue(entregue);
        pedidos[i] = p;
    }

    arqLoc.close();
    arqVei.close();
    arqPed.close();

    cout << "------------------\n";
    cout << "Dados restaurados do backup  com sucesso!\n";
    cout << "------------------\n";
}

void menu() {
    cout << "\n====== Sistema de Logistica de Entrega (SLEM) ======\n";
    cout << "1. Cadastrar Distribuidora\n";
    cout << "2. Listar Distribuidora\n";
    cout << "3. Cadastrar Veiculo\n";
    cout << "4. Listar Veiculos\n";
    cout << "5. Cadastrar Pedido\n";
    cout << "6. Listar Pedidos\n";
    cout << "7. Calcular Rota // calcular capacidade caminhao\n";
    cout << "8. Backup de Dados\n";
    cout << "9. Restaurar Dados\n";
    cout << "10. Atualizar situacao do pedido\n";
    cout << "0. Sair\n";
}

int main() {
    int opcao;

    do {
        menu();
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        cin.ignore();

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
                    cin.ignore();
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
                    cout << "------------------\n";
                }
                break;

            case 3:
                if (qtdVeiculos < MAX_VEICULOS) {
                    Veiculo v;
                    char placa[20], modelo[50];
                    int carga, x, y;

                    cout << "Digite a placa do veiculo: ";
                    cin.getline(placa, sizeof(placa));
                    cout << "Digite o modelo do veiculo: ";
                    cin.getline(modelo, sizeof(modelo));
                    cout << "Digite a carga suportada: ";
                    cin >> carga;
                    cout << "Digite as coordenadas do veiculo (x y): ";
                    cin >> x >> y;
                    cin.ignore();

                    v.setplaca(placa);
                    v.setmodelo(modelo);
                    v.setcarga(carga);
                    v.setlocalC(x, y);

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
                    cout << "------------------\n";
                }
                break;

            case 5:
                if (qtdPedidos < MAX_PEDIDOS) {
                    Pedido p;
                    int codigo;
                    char nomeLocal[100];
                    float x, y;
                    int cargap;

                    while (true) {
                        cout << "Digite o codigo do pedido: ";
                        cin >> codigo;
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << "Codigo invalido! Digite um numero inteiro.\n";
                        } else {
                            cin.ignore();
                            break;
                        }
                    }

                    cout << "Digite o nome do local: ";
                    cin.getline(nomeLocal, sizeof(nomeLocal));
                    cout << "Digite X e Y do local: ";
                    cin >> x >> y;
                    cin.ignore();
                    cout << "Digite a carga: ";
                    cin >> cargap;
                    cin.ignore();

                    p.setcodigo(codigo);
                    p.setnome(nomeLocal);
                    p.setx(x);
                    p.sety(y);
                    p.setcargap(cargap);

                    pedidos[qtdPedidos++] = p;
                    cout << "Pedido cadastrado com sucesso!\n";
                } else {
                    cout << "Limite de pedidos atingido.\n";
                }
                break;

            case 6:
                if (qtdPedidos == 0) {
                    cout << "Nenhum pedido cadastrado ainda.\n";
                } else {
                    for (int i = 0; i < qtdPedidos; i++) {
                        cout << "Codigo: " << pedidos[i].getcodigo() << "\n";
                        cout << "Local: " << pedidos[i].getnome() << "\n";
                        cout << "X: " << pedidos[i].getx() << " Y: " << pedidos[i].gety() << "\n";
                        cout << "Carga: " << pedidos[i].getcargap() << "\n";
                        cout << "------------------\n";
                    }
                }
                break;

            case 7: {
                Rota r;
                r.calcular();
                r.mostrar();
                caminhao_pd();
                break;
            }

            case 8:
                cout << "Realizando backup dos dados...\n";
                backupDados();
                break;

            case 9:
                cout << "Restaurando dados do backup...\n";
                restaurarDados();
                break;

            case 10:
                cout << "Atualizacao do pedido:\n";
                attpedido();
                break;

            case 0:
                cout << "Saindo...\n";
                break;

            default:
                cout << "Opcao invalida.\n";
        }

    } while (opcao != 0);

    return 0;
}
