#include <iostream>
#include <cstring>
#include <cstdlib>
#include <locale.h>

using namespace std;

// Constantes
//#define MAX_LOCAIS 100
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
    void setplaca(const char p[]){
         strncpy(placa, p, sizeof(placa));
          placa[sizeof(placa) - 1] = '\0'; // Garante q a ultima casa seja um \0, fim de string

    }
    void setmodelo(const char m[]){
        strncpy(modelo, m, sizeof(modelo));
        modelo[sizeof(modelo) - 1] = '\0';
    }
    void setcarga(const int c){
        carga = c;
    }
    
    // Método para exibir os dados (só pra teste)
    const char* getplaca() const{
        return placa;
    }
    const char* getmodelo() const{
        return modelo;
    }
    int getano () const{
        return ano;
    }
    int getlocalAtual() const{
        return indiceLocalAtual;
    }
};


struct Pedido {
    int id;
    int origem;
    int destino;
    float peso;
};

// Vetores globais
/*Local locais[MAX_LOCAIS];
int qtdLocais = 0;*/

Veiculo veiculos[MAX_VEICULOS];
int qtdVeiculos = 0;

Pedido pedidos[MAX_PEDIDOS];
int qtdPedidos = 0;

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
                // cadastrarLocal();
                break;
            case 2:
                // listarLocais();
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
    cout << "\n====== Sistema de Logistica de Entrega (SLEM) ======\n";
    cout << "1. Cadastrar Local\n";
    cout << "2. Listar Locais\n";
    cout << "3. Cadastrar Veiculo\n";
    cout << "4. Listar Veículos\n";
    cout << "5. Cadastrar Pedido\n";
    cout << "6. Listar Pedidos\n";
    cout << "7. Calcular Rota\n";
    cout << "8. Backup de Dados\n";
    cout << "9. Restaurar Dados\n";
   
}


