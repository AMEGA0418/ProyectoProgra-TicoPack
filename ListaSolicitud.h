#pragma once
#ifndef LISTASOLICITUD_H
#define LISTASOLICITUD_H

#include <string>
#include "Fecha.h"
#include "EstadoSolicitud.h"
#include "ListaCliente.h"
#include "ListaPaquete.h"
#include "ListaColaborador.h"
#include "ListaCentros.h"
using namespace std;


class Solicitud {
private:
    string codigo;
    Cliente* cliente;
    Paquete* paquete;
    Colaborador* responsable;
    Centro* centroOrigen;
    string destino;
    Fecha fechaSolicitud;
    float costoEstimado;
    EstadoSolicitud estado;

public:
    Solicitud(string codigo, Cliente* cliente, Paquete* paquete,
        Colaborador* responsable, Centro* centroOrigen,
        string destino, Fecha fechaSolicitud, float costoEstimado);

    string getCodigo() const;
    EstadoSolicitud getEstado() const;
    Paquete* getPaquete() const;
    void setEstado(EstadoSolicitud nuevoEstado);
    void mostrarDatos() const;
};

class NodoSolicitud {
public:
    Solicitud* dato;
    NodoSolicitud* siguiente;

    NodoSolicitud(Solicitud* dato);
};

class ListaSolicitud {
private:
    NodoSolicitud* primero;

public:
    ListaSolicitud();
    ~ListaSolicitud();

    bool estaVacia();
    void insertarFinal(Solicitud* solicitud);
    Solicitud* buscar(string codigo);
    void mostrar();
};

#endif

