#pragma once

class SistemaTicoPack;

class Menu {
private:
    SistemaTicoPack* sistema;

public:
    explicit Menu(SistemaTicoPack* sistema);

    void mostrarTitulo() const;
    void mostrarOpciones() const;
    void ejecutar();
};

