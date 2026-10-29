#pragma once
#include "SistemaTicoPack.h"
#include "Reportes.h"
#include <iostream>

using namespace std;

class Menu {
private:
    SistemaTicoPack* sistema;

public:
    explicit Menu(SistemaTicoPack* sistema);

    void mostrarTitulo() const;
    void mostrarOpciones() const;
    void ejecutar();
};

