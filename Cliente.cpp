#include "Cliente.h"

Cliente::Cliente(const string& identificacion, const string& nombre,
    const string& telefono, const string& correo) {
    this->identificacion = identificacion;
    this->nombre = nombre;
    this->telefono = telefono;
    this->correo = correo;
}

Cliente::~Cliente() {}

string Cliente::getIdentificacion() const { return identificacion; }
string Cliente::getNombre() const { return nombre; }
string Cliente::getTelefono() const { return telefono; }
string Cliente::getCorreo() const { return correo; }

void Cliente::setNombre(const string& nuevoNombre) { nombre = nuevoNombre; }
void Cliente::setTelefono(const string& nuevoTelefono) { telefono = nuevoTelefono; }
void Cliente::setCorreo(const string& nuevoCorreo) { correo = nuevoCorreo; }

void Cliente::mostrar() const {
    cout << "Identificacion: " << identificacion << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Telefono: " << telefono << endl;
    cout << "Correo: " << correo << endl;
}