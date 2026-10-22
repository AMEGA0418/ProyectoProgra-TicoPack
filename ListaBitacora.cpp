#include "ListaBitacora.h"
#include <iostream>

using namespace std;

RegistroBitacora::RegistroBitacora(
    EstadoPaquete estadoAnterior,
    EstadoPaquete estadoNuevo,
    Fecha fechaCambio,
    Colaborador* responsable)
    : fechaCambio(fechaCambio) {

    this->estadoAnterior = estadoAnterior;
    this->estadoNuevo = estadoNuevo;
    this->responsable = responsable;
}

void RegistroBitacora::mostrarDatos() const {
    cout << "Estado anterior: " << estadoAnterior << endl;
    cout << "Estado nuevo: " << estadoNuevo << endl;
    cout << "Fecha del cambio: ";
    fechaCambio.mostrarFecha();
}

NodoBitacora::NodoBitacora(RegistroBitacora* dato) {
    this->dato = dato;
    siguiente = nullptr;
}

ListaBitacora::ListaBitacora() {
    primero = nullptr;
}

ListaBitacora::~ListaBitacora() {
    NodoBitacora* actual = primero;

    while (actual != nullptr) {
        NodoBitacora* temporal = actual;
        actual = actual->siguiente;
        delete temporal;
    }
}

bool ListaBitacora::estaVacia() {
    return primero == nullptr;
}

void ListaBitacora::insertarFinal(RegistroBitacora* registro) {
    if (registro == nullptr) return;

    NodoBitacora* nuevo = new NodoBitacora(registro);

    if (estaVacia()) {
        primero = nuevo;
    }
    else {
        NodoBitacora* actual = primero;

        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }

        actual->siguiente = nuevo;
    }
}

void ListaBitacora::mostrar() {
    NodoBitacora* actual = primero;

    while (actual != nullptr) {
        actual->dato->mostrarDatos();
        cout << "----------------------" << endl;
        actual = actual->siguiente;
    }
}