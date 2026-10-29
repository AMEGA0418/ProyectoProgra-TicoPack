#include "PersonaFisica.h"

PersonaFisica::PersonaFisica(const string& identificacion, const string& nombre,
    const string& telefono, const string& correo)
    : Cliente(identificacion, nombre, telefono, correo) {}

double PersonaFisica::calcularCostoFinal(double costoBase) const {
    return costoBase;
}

string PersonaFisica::getTipo() const {
    return "Persona fisica";
}

void PersonaFisica::mostrar() const {
    cout << "--- PERSONA FISICA ---" << endl;
    Cliente::mostrar();
}