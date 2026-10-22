#include "RegistroBitacora.h"
#include "Colaborador.h"
#include <iostream>

using namespace std;

RegistroBitacora::RegistroBitacora(EstadoPaquete estadoAnterior,
    EstadoPaquete nuevoEstado,
    const Fecha& fechaCambio,
    Colaborador* responsable)
    : fechaCambio(fechaCambio) {
    this->estadoAnterior = estadoAnterior;
    this->nuevoEstado = nuevoEstado;
    this->responsable = responsable;
}

EstadoPaquete RegistroBitacora::getEstadoAnterior() const { return estadoAnterior; }
EstadoPaquete RegistroBitacora::getNuevoEstado() const { return nuevoEstado; }
Fecha RegistroBitacora::getFechaCambio() const { return fechaCambio; }
Colaborador* RegistroBitacora::getResponsable() const { return responsable; }

void RegistroBitacora::mostrar() const {
    cout << estadoPaqueteToString(estadoAnterior) << " -> "
        << estadoPaqueteToString(nuevoEstado)
        << " | " << fechaCambio.toString() << " " << fechaCambio.horaToString()
        << " | ";

    if (responsable != nullptr) {
        cout << responsable->getNombreCompleto()
            << " (" << responsable->getIdentificacion() << ")";
    }
    else {
        cout << "(sin responsable)";
    }
    cout << endl;
}