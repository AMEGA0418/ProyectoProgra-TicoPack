#include "Despacho.h"
#include <iostream>
//Poner listaDespacho
using namespace std;

Despacho::Despacho(string codigo, Solicitud* solicitud, Paquete* paquete,
    Cliente* cliente, Colaborador* responsable,
    Centro* centroOrigen, string destino,
    Fecha fechaDespacho, string hora)
    : fechaDespacho(fechaDespacho) {
    this->codigo = codigo;
    this->solicitud = solicitud;
    this->paquete = paquete;
    this->cliente = cliente;
    this->responsable = responsable;
    this->centroOrigen = centroOrigen;
    this->destino = destino;
    this->hora = hora;
    estado = EN_PROCESO;
}

string Despacho::getCodigo() const { return codigo; }
EstadoDespacho Despacho::getEstado() const { return estado; }
Paquete* Despacho::getPaquete() const { return paquete; }

void Despacho::setEstado(EstadoDespacho nuevoEstado) {
    estado = nuevoEstado;
}

void Despacho::mostrarDatos() const {
    cout << "Despacho: " << codigo << endl;
    cout << "Destino: " << destino << endl;
    cout << "Hora: " << hora << endl;
    cout << "Estado: " << estado << endl;
}

NodoDespacho::NodoDespacho(Despacho* dato) {
    this->dato = dato;
    siguiente = nullptr;
}

ListaDespacho::ListaDespacho() {
    primero = nullptr;
}

ListaDespacho::~ListaDespacho() {
    NodoDespacho* actual = primero;

    while (actual != nullptr) {
        NodoDespacho* temporal = actual;
        actual = actual->siguiente;
        delete temporal;
    }
}

bool ListaDespacho::estaVacia() {
    return primero == nullptr;
}

void ListaDespacho::insertarFinal(Despacho* despacho) {
    if (despacho == nullptr) return;

    NodoDespacho* nuevo = new NodoDespacho(despacho);

    if (estaVacia()) {
        primero = nuevo;
    }
    else {
        NodoDespacho* actual = primero;

        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }

        actual->siguiente = nuevo;
    }
}

Despacho* ListaDespacho::buscar(string codigo) {
    NodoDespacho* actual = primero;

    while (actual != nullptr) {
        if (actual->dato->getCodigo() == codigo) {
            return actual->dato;
        }

        actual = actual->siguiente;
    }

    return nullptr;
}

void ListaDespacho::mostrar() {
    NodoDespacho* actual = primero;

    while (actual != nullptr) {
        actual->dato->mostrarDatos();
        actual = actual->siguiente;
    }
}