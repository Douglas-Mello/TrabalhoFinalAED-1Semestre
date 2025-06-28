#ifndef HEADER_BA466E0D74729ACC
#define HEADER_BA466E0D74729ACC
class Pedido : public Local {
private:
    int codigo;
    int cargap; // SOMENTE a carga do veiculo, nao o veiculo inteiro
    bool entregue;
public:
    Pedido() {
        codigo = 0;
        cargap = 0;
        entregue = false;
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
    void setEntregue(bool status) { entregue = status; }
    bool isEntregue() const { return entregue; }
};

#endif // header guard

