#pragma once
#ifndef LISTACOLABORADOR_H
#define LISTACOLABORADOR_H

#include <string>
#include "Fecha.h"

using namespace std;

class Colaborador {
private:
    string identificacion;
    string nombreCompleto;
    Fecha fechaIngreso;
    string puesto;

public:
    Colaborador(string identificacion, string nombreCompleto,
        Fecha fechaIngreso, string puesto);

    string getIdentificacion() const;
    string getNombreCompleto() const;
    Fecha getFechaIngreso() const;
    string getPuesto() const;

    void mostrarDatos() const;
};

class NodoColaborador {
public:
    Colaborador* dato;
    NodoColaborador* siguiente;

    NodoColaborador(Colaborador* dato);
};

class ListaColaborador {
private:
    NodoColaborador* primero;

public:
    ListaColaborador();
    ~ListaColaborador();

    bool estaVacia();
    void insertarFinal(Colaborador* colaborador);
    Colaborador* buscar(string identificacion);
    void mostrar();
    bool eliminar(string identificacion);
};

#endif