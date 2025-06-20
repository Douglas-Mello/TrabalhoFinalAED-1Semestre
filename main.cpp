#include <iostream>
#include <cstring>
#include <cstdlib>
#include <locale.h>

using namespace std;

// Constantes
#define MAX_LOCAIS 100
#define MAX_VEICULOS 100
#define MAX_PEDIDOS 100

// Structs básicas
class Local {
private:
    char nome[100];
    float x, y;

public:
    char* getnome() { return nome; }
    float getx() { return x; }
    float gety() { return y; }

    void setnome(const char n[]) {
        // Copia no máximo 99 caracteres, e garante o '\0' final
        strncpy(nome, n, sizeof(nome) - 1);
        nome[sizeof(nome) - 1] = '\0';
    }

    void setx(float x) {
        this->x = x;
    }

    void sety(float y) {
        this->y = y;
    }

    Local(const char n[], float x, float y) {
        setnome(n);
        setx(x);
        sety(y);
    }

    Local() {
        nome[0] = '\0';
        x = 0;
        y = 0;
    }
};

// Vetores globais
Local locais[MAX_LOCAIS];
int qtdLocais = 0;

// Protótipos (a serem implementados aos poucos)
void menu();

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    int opcao;
    do {
        menu();
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                if (qtdLocais < MAX_LOCAIS) {
                    char nome[100];
                    float x, y;

                    cout << "Digite o nome do local: ";
                    cin.ignore(); // limpar o buffer antes de getline
                    cin.getline(nome, sizeof(nome));

                    cout << "Digite a coordenada do local (x): ";
                    cin >> x;

                    cout << "Digite a coordenada do local (y): ";
                    cin >> y;

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
                // cadastrarVeiculo();
                break;
            case 4:
                // listarVeiculos();
                break;
            case 5:
                // cadastrarPedido();
                break;
            case 6:
                // listarPedidos();
                break;
            case 7:
                // calcularRota();
                break;
            case 8:
                // backupDados();
                break;
            case 9:
                // restaurarDados();
                break;
            case 0:
                cout << "Saindo...\n";
                break;
            default:
                cout << "Opção inválida.\n";
        }

    } while (opcao != 0);

    return 0;
}

void menu() {
    cout << "\n====== Sistema de Logística de Entrega (SLEM) ======\n";
    cout << "1. Cadastrar Local\n";
    cout << "2. Listar Locais\n";
    cout << "3. Cadastrar Veículo\n";
    cout << "4. Listar Veículos\n";
    cout << "5. Cadastrar Pedido\n";
    cout << "6. Listar Pedidos\n";
    cout << "7. Calcular Rota\n";
    cout << "8. Backup de Dados\n";
    cout << "9. Restaurar Dados\n";
    cout << "0. Sair\n";
}


