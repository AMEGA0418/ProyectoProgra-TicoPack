#pragma once
#ifndef PERSONAFISICA_H
#define PERSONAFISICA_H

#include "ListaCliente.h"
#include <string>

class PersonaFisica : public Cliente {
public:
    PersonaFisica(string identificacion, string nombre,
        string telefono, string correo);

    void mostrarDatos() const override;
};

#endif