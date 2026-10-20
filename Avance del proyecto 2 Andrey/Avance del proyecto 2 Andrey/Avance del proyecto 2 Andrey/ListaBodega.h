#pragma once
#ifndef LISTABODEGA_H
#define LISTABODEGA_H

#include <string>
#include "TipoBodega.h"

using namespace std;

class Paquete;

class Bodega {
private:
    string codigo;
    string nombre;
    TipoBodega tipo;
    int filas;
    int columnas;
    Paquete*** matriz;

public:
    Bodega(string codigo, string nombre, TipoBodega tipo,
        int filas, int columnas);
    ~Bodega();

    string getCodigo() const;
    string getNombre() const;
    TipoBodega getTipo() const;
    int getFilas() const;
    int getColumnas() const;

    void mostrarDatos() const;
    Paquete* consultarCelda(int fila, int columna);
    bool asignarPaquete(Paquete* paquete, int fila, int columna);
    bool liberarCelda(int fila, int columna);
    bool estaDisponible(int fila, int columna);
    float porcentajeOcupacion();
};

class NodoBodega {
public:
    Bodega* dato;
    NodoBodega* siguiente;

    NodoBodega(Bodega* dato);
};

class ListaBodega {
private:
    NodoBodega* primero;

public:
    ListaBodega();
    ~ListaBodega();

    bool estaVacia();
    void insertarFinal(Bodega* bodega);
    Bodega* buscar(string codigo);
    void mostrar();
    bool eliminar(string codigo);
};

#endif