#ifndef HEADER_48D71CB534F5C71
#define HEADER_48D71CB534F5C71

#include "Local.h"

class Veiculo {
private:
    char placa[10];
    char modelo[50];
    int carga;
    int indiceLocalAtual; // índice no vetor de locais

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

    void setIndiceLocal(int indice) {
        indiceLocalAtual = indice;
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

#endif // HEADER_48D71CB534F5C71
