#pragma once
#include "ListaBodega.h"
#include "ListaPaquete.h"
#include <iostream>

using namespace std;

Bodega::Bodega(string codigo, string nombre, TipoBodega tipo,
    int filas, int columnas) {
    this->codigo = codigo;
    this->nombre = nombre;
    this->tipo = tipo;

    if (filas <= 0 || columnas <= 0) {
        this->filas = 0;
        this->columnas = 0;
        matriz = nullptr;
        return;
    }

    this->filas = filas;
    this->columnas = columnas;

    matriz = new Paquete * *[filas];

    for (int i = 0; i < filas; i++) {
        matriz[i] = new Paquete * [columnas];

        for (int j = 0; j < columnas; j++) {
            matriz[i][j] = nullptr;
        }
    }
}

Bodega::~Bodega() {
    for (int i = 0; i < filas; i++) {
        delete[] matriz[i];
    }

    delete[] matriz;
}

string Bodega::getCodigo() const { return codigo; }
string Bodega::getNombre() const { return nombre; }
TipoBodega Bodega::getTipo() const { return tipo; }
int Bodega::getFilas() const { return filas; }
int Bodega::getColumnas() const { return columnas; }

void Bodega::mostrarDatos() const {
    cout << "Codigo: " << codigo << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Filas: " << filas << endl;
    cout << "Columnas: " << columnas << endl;
}

Paquete* Bodega::consultarCelda(int fila, int columna) {
    if (fila < 0 || fila >= filas ||
        columna < 0 || columna >= columnas) {
        return nullptr;
    }

    return matriz[fila][columna];
}

bool Bodega::asignarPaquete(Paquete* paquete,
    int fila, int columna) {
    if (paquete == nullptr || fila < 0 || fila >= filas ||
        columna < 0 || columna >= columnas) {
        return false;
    }

    if (matriz[fila][columna] != nullptr) {
        return false;
    }

    matriz[fila][columna] = paquete;
    return true;
}

bool Bodega::liberarCelda(int fila, int columna) {
    if (fila < 0 || fila >= filas ||
        columna < 0 || columna >= columnas) {
        return false;
    }

    matriz[fila][columna] = nullptr;
    return true;
}

bool Bodega::estaDisponible(int fila, int columna) {
    if (fila < 0 || fila >= filas ||
        columna < 0 || columna >= columnas) {
        return false;
    }

    return matriz[fila][columna] == nullptr;
}

float Bodega::porcentajeOcupacion() {
    if (filas == 0 || columnas == 0) {
        return 0;
    }

    float ocupadas = 0;

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (matriz[i][j] != nullptr) {
                ocupadas++;
            }
        }
    }

    return ocupadas / (filas * columnas) * 100;
}

NodoBodega::NodoBodega(Bodega* dato) {
    this->dato = dato;
    siguiente = nullptr;
}

ListaBodega::ListaBodega() {
    primero = nullptr;
}

ListaBodega::~ListaBodega() {
    NodoBodega* actual = primero;

    while (actual != nullptr) {
        NodoBodega* temporal = actual;
        actual = actual->siguiente;
        delete temporal;
    }
}

bool ListaBodega::estaVacia() {
    return primero == nullptr;
}

void ListaBodega::insertarFinal(Bodega* bodega) {
    if (bodega == nullptr) return;

    NodoBodega* nuevo = new NodoBodega(bodega);

    if (estaVacia()) {
        primero = nuevo;
    }
    else {
        NodoBodega* actual = primero;

        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }

        actual->siguiente = nuevo;
    }
}

Bodega* ListaBodega::buscar(string codigo) {
    NodoBodega* actual = primero;

    while (actual != nullptr) {
        if (actual->dato->getCodigo() == codigo) {
            return actual->dato;
        }

        actual = actual->siguiente;
    }

    return nullptr;
}

void ListaBodega::mostrar() {
    NodoBodega* actual = primero;

    while (actual != nullptr) {
        actual->dato->mostrarDatos();
        actual = actual->siguiente;
    }
}

bool ListaBodega::eliminar(string codigo) {
    NodoBodega* actual = primero;
    NodoBodega* anterior = nullptr;

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