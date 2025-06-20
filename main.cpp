#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <math.h>
#include <vector>
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
class Pedido : public Local {
private:
    int codigo;
    int cargap; // SOMENTE a carga do veículo, não o veículo inteiro
public:
    Pedido() {
        codigo = 0;
        cargap = 0;
    }

    Pedido(int cod, const char nome[], float x, float y, int c) {
        setcodigo(cod);
        setnome(nome);
        setx(x);
        sety(y);
        setcargap(c);
    }
    

    void setcodigo(int c) {
        codigo = c;
    }

    int getcodigo() const {
        return codigo;
    }

    void setcargap(int c) {
        cargap = c;
    }

    int getcargap() const {
        return cargap;
    }
};
// Vetores globais
Veiculo veiculos[MAX_VEICULOS];
int qtdVeiculos = 0;

Local locais[MAX_LOCAIS];
int qtdLocais = 0;

Pedido pedidos[MAX_PEDIDOS];
int qtdPedidos=0;

float Rota(){
    float saida[2]= locais[0];
    float chegada[2] = pedidos[0];
    int tamanho = sizeof(locais) / sizeof(locais[0]);
    for(int i = 0 ; i < tamanho; i++){
        for (int j = 0; j < tamanho ; j++){
            float dist = sqrt(pow(locais[i].getx() - pedidos[j].getx(), 2) + pow(locais[i].gety()- pedidos[j].gety(), 2));
            
        }        
        } 
    
    }


// Protótipos
void menu();

int main() {
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

                    cout << "Digite a carga suportada pelo veiculo: ";
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
                if (qtdPedidos < MAX_PEDIDOS) {
                    Pedido p;
                    int codigo;
                    char nomeLocal[100];
                    float x, y;
                    int cargap;

                    cout << "Digite o código do pedido: ";
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
                    Local l(nomeLocal, x, y);
                    locais[qtdLocais++] = l;
                    
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
                    cout << "Lista de Pedidos:\n";
                    for (int i = 0; i < qtdPedidos; i++) {
                        cout << "Código do Pedido: " << pedidos[i].getcodigo() << "\n";
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
                 vector<float> distancias = Rota();
                cout << "Distâncias calculadas (ordem crescente):\n";
                for (float d : distancias) {
                    cout << d << "\n";
                }
                    break;
            }
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
