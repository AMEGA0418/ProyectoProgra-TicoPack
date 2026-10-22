#pragma once
#include "Fecha.h"
#include "EstadoPaquete.h"

class Colaborador;

// Un cambio de estado de un paquete. Una vez creado no se modifica ni se elimina.
class RegistroBitacora {
private:
    EstadoPaquete estadoAnterior;
    EstadoPaquete nuevoEstado;
    Fecha fechaCambio;
    Colaborador* responsable;

public:
    RegistroBitacora(EstadoPaquete estadoAnterior, EstadoPaquete nuevoEstado,
        const Fecha& fechaCambio, Colaborador* responsable);

    EstadoPaquete getEstadoAnterior() const;
    EstadoPaquete getNuevoEstado() const;
    Fecha getFechaCambio() const;
    Colaborador* getResponsable() const;

    void mostrar() const;
};