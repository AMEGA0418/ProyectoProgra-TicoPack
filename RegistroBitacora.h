#pragma once

#include <iostream>
#include "Fecha.h"
#include "EstadoPaquete.h"
#include "Colaborador.h"

using namespace std;

// Un cambio de estado de un paquete. Una vez creado no se modifica ni se elimina.
class RegistroBitacora {
private:
    int estadoAnterior;   // valor de EstadoPaquete
    int nuevoEstado;      // valor de EstadoPaquete
    Fecha fechaCambio;
    Colaborador* responsable;

public:
    RegistroBitacora(int estadoAnterior, int nuevoEstado,
        const Fecha& fechaCambio, Colaborador* responsable);

    int getEstadoAnterior() const;
    int getNuevoEstado() const;
    Fecha getFechaCambio() const;
    Colaborador* getResponsable() const;

    void mostrar() const;
};