#include "ListaSolicitud.h"
#include "ListaPaquete.h"
#include <iostream>

using namespace std;

Solicitud::Solicitud(string codigo, Cliente* cliente, Paquete* paquete,
    Colaborador* responsable, Centro* centroOrigen,
    string destino, Fecha fechaSolicitud, float costoEstimado)
    : fechaSolicitud(fechaSolicitud) {
    this->codigo = codigo;
    this->cliente = cliente;
    this->paquete = paquete;
    this->responsable = responsable;
    this->centroOrigen = centroOrigen;
    this->destino = destino;
    this->costoEstimado = costoEstimado;
    estado = PENDIENTE;
}

string Solicitud::getCodigo() const { return codigo; }
EstadoSolicitud Solicitud::getEstado() const { return estado; }
Paquete* Solicitud::getPaquete() const { return paquete; }

void Solicitud::setEstado(EstadoSolicitud nuevoEstado) {
    estado = nuevoEstado;
}

void Solicitud::mostrarDatos() const {
    cout << "Solicitud: " << codigo << endl;
    cout << "Destino: " << destino << endl;
    cout << "Costo estimado: " << costoEstimado << endl;
    cout << "Estado: " << estado << endl;
}

NodoSolicitud::NodoSolicitud(Solicitud* dato) {
    this->dato = dato;
    siguiente = nullptr;
}

ListaSolicitud::ListaSolicitud() {
    primero = nullptr;
}

ListaSolicitud::~ListaSolicitud() {
    NodoSolicitud* actual = primero;

    while (actual != nullptr) {
        NodoSolicitud* temporal = actual;
        actual = actual->siguiente;
        delete temporal;
    }
}

bool ListaSolicitud::estaVacia() {
    return primero == nullptr;
}

void ListaSolicitud::insertarFinal(Solicitud* solicitud) {
    if (solicitud == nullptr) return;

    NodoSolicitud* nuevo = new NodoSolicitud(solicitud);

    if (estaVacia()) {
        primero = nuevo;
    }
    else {
        NodoSolicitud* actual = primero;

        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }

        actual->siguiente = nuevo;
    }
}

Solicitud* ListaSolicitud::buscar(string codigo) {
    NodoSolicitud* actual = primero;

    while (actual != nullptr) {
        if (actual->dato->getCodigo() == codigo) {
            return actual->dato;
        }

        actual = actual->siguiente;
    }

    return nullptr;
}

void ListaSolicitud::mostrar() {
    NodoSolicitud* actual = primero;

    while (actual != nullptr) {
        actual->dato->mostrarDatos();
        actual = actual->siguiente;
    }
}