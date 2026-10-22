#include "ListaCliente.h"
#include <iostream>

using namespace std;


// IMPLEMENTACION DE CLIENTE
Cliente::Cliente(string identificacion, string nombre,
    string telefono, string correo) {
    this->identificacion = identificacion;
    this->nombre = nombre;
    this->telefono = telefono;
    this->correo = correo;
}

Cliente::~Cliente() {}

string Cliente::getIdentificacion() const {
    return identificacion;
}

string Cliente::getNombre() const {
    return nombre;
}

string Cliente::getTelefono() const {
    return telefono;
}

string Cliente::getCorreo() const {
    return correo;
}

void Cliente::setIdentificacion(string nuevaIdentificacion) {
    identificacion = nuevaIdentificacion;
}

void Cliente::setNombre(string nuevoNombre) {
    nombre = nuevoNombre;
}

void Cliente::setTelefono(string nuevoTelefono) {
    telefono = nuevoTelefono;
}

void Cliente::setCorreo(string nuevoCorreo) {
    correo = nuevoCorreo;
}

void Cliente::mostrarDatos() const {
    cout << "Identificacion: " << identificacion << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Telefono: " << telefono << endl;
    cout << "Correo: " << correo << endl;
}


// IMPLEMENTACION DEL NODO
NodoCliente::NodoCliente(Cliente* dato) {
    this->dato = dato;
    siguiente = nullptr;
}


// IMPLEMENTACION DE LA LISTA

ListaCliente::ListaCliente() {
    primero = nullptr;
}

ListaCliente::~ListaCliente() {
    NodoCliente* actual = primero;

    while (actual != nullptr) {
        NodoCliente* temporal = actual;
        actual = actual->siguiente;
        delete temporal;
    }
}

bool ListaCliente::estaVacia() {
    return primero == nullptr;
}

void ListaCliente::insertarFinal(Cliente* nuevoCliente) {
    if (nuevoCliente == nullptr) {
        return;
    }

    NodoCliente* nuevo = new NodoCliente(nuevoCliente);

    if (estaVacia()) {
        primero = nuevo;
    }
    else {
        NodoCliente* actual = primero;

        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }

        actual->siguiente = nuevo;
    }
}

Cliente* ListaCliente::buscar(string identificacion) {
    NodoCliente* actual = primero;

    while (actual != nullptr) {
        if (actual->dato->getIdentificacion() == identificacion) {
            return actual->dato;
        }

        actual = actual->siguiente;
    }

    return nullptr;
}

void ListaCliente::mostrar() {
    NodoCliente* actual = primero;

    while (actual != nullptr) {
        actual->dato->mostrarDatos();
        cout << "-------------------" << endl;

        actual = actual->siguiente;
    }
}