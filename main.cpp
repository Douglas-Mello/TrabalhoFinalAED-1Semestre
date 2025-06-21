#include <iostream>
#include <cstring>
#include <cstdlib>
#include <locale.h>
#include <math.h>
using namespace std;

// Constantes
#define MAX_LOCAIS 100
#define MAX_VEICULOS 100
#define MAX_PEDIDOS 100

// Structs básicas
class Veiculo {
private:
    char placa[10];
    char modelo[50];
    int carga; 
    int indiceLocalAtual;
public:
    Veiculo() {
        carga = 0;
        placa[0] = '\0';
        modelo[0] = '\0';
        indiceLocalAtual = -1;
    }

    void setplaca(const char p[]) {
        strncpy(placa, p, sizeof(placa));
        placa[sizeof(placa) - 1] = '\0';
    }

    void setmodelo(const char m[]) {
        strncpy(modelo, m, sizeof(modelo));
        modelo[sizeof(modelo) - 1] = '\0';
    }

    void setcarga(const int c) {
        carga = c;
    }

    const char* getplaca() const {
        return placa;
    }

    const char* getmodelo() const {
        return modelo;
    }

    int getcarga() const {
        return carga;
    }

    int getlocalAtual() const {
        return indiceLocalAtual;
    }
};

class Local {
private:
    char nome[100];
    float x, y;
public:
    Local() {
        nome[0] = '\0';
        x = 0;
        y = 0;
    }

    Local(const char n[], float x, float y) {
        setnome(n);
        setx(x);
        sety(y);
    }

    void setnome(const char n[]) {
        strncpy(nome, n, sizeof(nome) - 1);
        nome[sizeof(nome) - 1] = '\0';
    }

    void setx(float x) {
        this->x = x;
    }

    void sety(float y) {
        this->y = y;
    }

    char* getnome() {
        return nome;
    }

    float getx() {
        return x;
    }

    float gety() {
        return y;
    }      
    
};
// Vetores globais
Veiculo veiculos[MAX_VEICULOS];
int qtdVeiculos = 0;

Local locais[MAX_LOCAIS];
int qtdLocais = 0;

// Protótipos
void menu();

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    int opcao;

    do {
        menu();
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        cin.ignore(); // <-- ajuste principal: IGNORA o '\n' logo após ler a opção

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

                    cout << "Digite a carga do veiculo: ";
                    cin >> carga;
                    cin.ignore(); // limpa antes de voltar ao menu

                    v.setplaca(placa);
                    v.setmodelo(modelo);
                    v.setcarga(carga);

                    veiculos[qtdVeiculos++] = v;
                    cout << "Veículo cadastrado com sucesso!\n";
                } else {
                    cout << "Limite de veículos atingido.\n";
                }
                break;

            case 4:
                cout << "Mostrando veículos cadastrados\n";
                for (int i = 0; i < qtdVeiculos; i++) {
                    cout << "Placa: " << veiculos[i].getplaca() << "\n";
                    cout << "Modelo: " << veiculos[i].getmodelo() << "\n";
                    cout << "Carga: " << veiculos[i].getcarga() << "\n";
                    cout << "--------------------------------------------------------------------\n";
                }
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
                cout << "Opcao invalida.\n";
        }

    } while (opcao != 0);

    return 0;
}

void menu() {
    cout << "\n====== Sistema de Logistica de Entrega (SLEM) ======\n";
    cout << "1. Cadastrar Local\n";
    cout << "2. Listar Locais\n";
    cout << "3. Cadastrar Veiculo\n";
    cout << "4. Listar Veiculos\n";
    cout << "5. Cadastrar Pedido\n";
    cout << "6. Listar Pedidos\n";
    cout << "7. Calcular Rota\n";
    cout << "8. Backup de Dados\n";
    cout << "9. Restaurar Dados\n";
    cout << "0. Sair\n";
}
