#pragma once
#include <iostream>
#include "Cliente.h"

using namespace std;

class PersonaFisica : public Cliente {
public:
    PersonaFisica(const string& identificacion, const string& nombre,
        const string& telefono, const string& correo);

    // La persona fisica no tiene descuento: el costo final es el costo base.
    double calcularCostoFinal(double costoBase) const override;
    string getTipo() const override;
    void mostrar() const override;
};