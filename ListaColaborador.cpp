#include "ListaColaborador.h"
#include <iostream>

using namespace std;

Colaborador::Colaborador(string identificacion,
    string nombreCompleto,
    Fecha fechaIngreso, string puesto)
    : fechaIngreso(fechaIngreso) {
    this->identificacion = identificacion;
    this->nombreCompleto = nombreCompleto;
    this->puesto = puesto;
}

string Colaborador::getIdentificacion() const {
    return identificacion;
}

string Colaborador::getNombreCompleto() const {
    return nombreCompleto;
}

Fecha Colaborador::getFechaIngreso() const {
    return fechaIngreso;
}

string Colaborador::getPuesto() const {
    return puesto;
}

void Colaborador::mostrarDatos() const {
    cout << "Identificacion: " << identificacion << endl;
    cout << "Nombre: " << nombreCompleto << endl;
    cout << "Puesto: " << puesto << endl;
    cout << "Fecha de ingreso: ";
    fechaIngreso.mostrarFecha();
}

NodoColaborador::NodoColaborador(Colaborador* dato) {
    this->dato = dato;
    siguiente = nullptr;
}

ListaColaborador::ListaColaborador() {
    primero = nullptr;
}

ListaColaborador::~ListaColaborador() {
    NodoColaborador* actual = primero;

    while (actual != nullptr) {
        NodoColaborador* temporal = actual;
        actual = actual->siguiente;
        delete temporal;
    }
}

bool ListaColaborador::estaVacia() {
    return primero == nullptr;
}

void ListaColaborador::insertarFinal(Colaborador* colaborador) {
    if (colaborador == nullptr) return;

    NodoColaborador* nuevo = new NodoColaborador(colaborador);

    if (estaVacia()) {
        primero = nuevo;
    }
    else {
        NodoColaborador* actual = primero;

        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }

        actual->siguiente = nuevo;
    }
}

Colaborador* ListaColaborador::buscar(string identificacion) {
    NodoColaborador* actual = primero;

    while (actual != nullptr) {
        if (actual->dato->getIdentificacion() == identificacion) {
            return actual->dato;
        }

        actual = actual->siguiente;
    }

    return nullptr;
}

void ListaColaborador::mostrar() {
    NodoColaborador* actual = primero;

    while (actual != nullptr) {
        actual->dato->mostrarDatos();
        actual = actual->siguiente;
    }
}

bool ListaColaborador::eliminar(string identificacion) {
    NodoColaborador* actual = primero;
    NodoColaborador* anterior = nullptr;
    while (actual != nullptr) {
        if (actual->dato->getIdentificacion() == identificacion) {
            if (anterior == nullptr) {
                primero = actual->siguiente;
            }
            else {
                anterior->siguiente = actual->siguiente;
            }

            delete actual;
            return true;
        }

        anterior = actual;
        actual = actual->siguiente;
    }
}