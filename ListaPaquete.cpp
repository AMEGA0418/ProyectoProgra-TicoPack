#include "ListaPaquete.h"
#include <iostream>

using namespace std;

Paquete::Paquete(string codigo, string descripcion, float peso,
    Categoria categoria, Cliente* cliente, Centro* centro) {
    this->codigo = codigo;
    this->descripcion = descripcion;
    this->peso = peso;
    this->categoria = categoria;
    this->cliente = cliente;
    this->centro = centro;
    estado = RECIBIDO;
    bodega = nullptr;
    fila = -1;
    columna = -1;
}

string Paquete::getCodigo() const { return codigo; }
string Paquete::getDescripcion() const { return descripcion; }
float Paquete::getPeso() const { return peso; }
Categoria Paquete::getCategoria() const { return categoria; }
EstadoPaquete Paquete::getEstado() const { return estado; }
Cliente* Paquete::getCliente() const { return cliente; }
Bodega* Paquete::getBodega() const { return bodega; }
int Paquete::getFila() const { return fila; }
int Paquete::getColumna() const { return columna; }

void Paquete::setEstado(EstadoPaquete nuevoEstado) {
    estado = nuevoEstado;
}

void Paquete::setUbicacion(Bodega* nuevaBodega, int nuevaFila,
    int nuevaColumna) {
    bodega = nuevaBodega;
    fila = nuevaFila;
    columna = nuevaColumna;
}

void Paquete::mostrarDatos() const {
    cout << "Codigo: " << codigo << endl;
    cout << "Descripcion: " << descripcion << endl;
    cout << "Peso: " << peso << endl;
    cout << "Estado: " << estado << endl;
    cout << "Fila: " << fila << endl;
    cout << "Columna: " << columna << endl;
}

NodoPaquete::NodoPaquete(Paquete* dato) {
    this->dato = dato;
    siguiente = nullptr;
}

ListaPaquete::ListaPaquete() {
    primero = nullptr;
}

ListaPaquete::~ListaPaquete() {
    NodoPaquete* actual = primero;

    while (actual != nullptr) {
        NodoPaquete* temporal = actual;
        actual = actual->siguiente;
        delete temporal;
    }
}

bool ListaPaquete::estaVacia() {
    return primero == nullptr;
}

void ListaPaquete::insertarFinal(Paquete* paquete) {
    if (paquete == nullptr) return;

    NodoPaquete* nuevo = new NodoPaquete(paquete);

    if (estaVacia()) {
        primero = nuevo;
    }
    else {
        NodoPaquete* actual = primero;

        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }

        actual->siguiente = nuevo;
    }
}

Paquete* ListaPaquete::buscar(string codigo) {
    NodoPaquete* actual = primero;

    while (actual != nullptr) {
        if (actual->dato->getCodigo() == codigo) {
            return actual->dato;
        }

        actual = actual->siguiente;
    }

    return nullptr;
}

void ListaPaquete::mostrar() {
    NodoPaquete* actual = primero;

    while (actual != nullptr) {
        actual->dato->mostrarDatos();
        actual = actual->siguiente;
    }
}

bool ListaPaquete::eliminar(string codigo) {
    NodoPaquete* actual = primero;
    NodoPaquete* anterior = nullptr;

    while (actual != nullptr) {
        if (actual->dato->getCodigo() == codigo) {
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

    return false;
}