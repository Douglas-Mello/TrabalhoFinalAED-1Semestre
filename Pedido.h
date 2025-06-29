#ifndef HEADER_BA466E0D74729ACC
#define HEADER_BA466E0D74729ACC
#include <cstring>
class Pedido  {
private:
    int codigo;
    int cargap; 
    bool entregue;
    int x,y;
    char nome[50];
public:
    Pedido() {
        codigo = 0;
        cargap = 0;
        entregue = false;
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
    Pedido(int cod, const char nome[], float x, float y, int c) {
        setcodigo(cod);
        setnome(nome);
        setx(x);
        sety(y);
        setcargap(c);
        entregue = false;
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
    float getx() {
        return x;
    }
    char* getnome() {
        return nome;
    }
    float gety() {
        return y;

    }
    void setEntregue(bool status) { entregue = status; }
    bool isEntregue() const { return entregue; }
};

#endif // header guard

