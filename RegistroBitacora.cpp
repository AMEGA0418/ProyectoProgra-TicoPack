#include "RegistroBitacora.h"
#include "Colaborador.h"
#include <iostream>

using namespace std;

RegistroBitacora::RegistroBitacora(int estadoAnterior,
    int nuevoEstado,
    const Fecha& fechaCambio,
    Colaborador* responsable)
    : fechaCambio(fechaCambio) {
    this->estadoAnterior = estadoAnterior;
    this->nuevoEstado = nuevoEstado;
    this->responsable = responsable;
}

int RegistroBitacora::getEstadoAnterior() const { return estadoAnterior; }
int RegistroBitacora::getNuevoEstado() const { return nuevoEstado; }
Fecha RegistroBitacora::getFechaCambio() const { return fechaCambio; }
Colaborador* RegistroBitacora::getResponsable() const { return responsable; }

void RegistroBitacora::mostrar() const {
    cout << EstadoPaquete::toString(estadoAnterior) << " -> "
        << EstadoPaquete::toString(nuevoEstado)
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