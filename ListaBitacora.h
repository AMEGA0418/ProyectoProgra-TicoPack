#pragma once
#ifndef LISTABITACORA_H
#define LISTABITACORA_H

#include <string>
#include "Fecha.h"
#include "EstadoPaquete.h"

using namespace std;

class Colaborador;

class RegistroBitacora {
private:
    EstadoPaquete estadoAnterior;
    EstadoPaquete estadoNuevo;
    Fecha fechaCambio;
    Colaborador* responsable;

public:
    RegistroBitacora(EstadoPaquete estadoAnterior,
        EstadoPaquete estadoNuevo,
        Fecha fechaCambio,
        Colaborador* responsable);

    void mostrarDatos() const;
};

class NodoBitacora {
public:
    RegistroBitacora* dato;
    NodoBitacora* siguiente;

    NodoBitacora(RegistroBitacora* dato);
};

class ListaBitacora {
private:
    NodoBitacora* primero;

public:
    ListaBitacora();
    ~ListaBitacora();

    bool estaVacia();
    void insertarFinal(RegistroBitacora* registro);
    void mostrar();
};

#endif