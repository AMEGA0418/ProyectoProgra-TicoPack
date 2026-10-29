#pragma once
#include <string>
#include <iostream>
#include "Fecha.h"

using namespace std;

class Colaborador {
private:
    string identificacion;
    string nombreCompleto;
    Fecha fechaIngreso;
    string puesto;

public:
    Colaborador(const string& identificacion, const string& nombreCompleto,
        const Fecha& fechaIngreso, const string& puesto);

    string getIdentificacion() const;
    string getNombreCompleto() const;
    Fecha getFechaIngreso() const;
    string getPuesto() const;

    void mostrar() const;
};