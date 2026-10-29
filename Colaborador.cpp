#include "Colaborador.h"

Colaborador::Colaborador(const string& identificacion,
    const string& nombreCompleto,
    const Fecha& fechaIngreso, const string& puesto)
    : fechaIngreso(fechaIngreso) {
    this->identificacion = identificacion;
    this->nombreCompleto = nombreCompleto;
    this->puesto = puesto;
}

string Colaborador::getIdentificacion() const { return identificacion; }
string Colaborador::getNombreCompleto() const { return nombreCompleto; }
Fecha Colaborador::getFechaIngreso() const { return fechaIngreso; }
string Colaborador::getPuesto() const { return puesto; }

void Colaborador::mostrar() const {
    cout << "Identificacion: " << identificacion << endl;
    cout << "Nombre: " << nombreCompleto << endl;
    cout << "Puesto: " << puesto << endl;
    cout << "Fecha de ingreso: " << fechaIngreso.toString() << endl;
}