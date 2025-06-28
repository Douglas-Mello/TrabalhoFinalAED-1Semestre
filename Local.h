#ifndef HEADER_52458137291F9A67
#define HEADER_52458137291F9A67
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

#endif // header guard

