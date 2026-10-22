#include "PersonaFisica.h"
#include <iostream>

using namespace std;

PersonaFisica::PersonaFisica(string identificacion, string nombre,
    string telefono, string correo)
    : Cliente(identificacion, nombre, telefono, correo) {
}

void PersonaFisica::mostrarDatos() const {
    cout << "--- PERSONA FISICA ---" << endl;
    Cliente::mostrarDatos();
}