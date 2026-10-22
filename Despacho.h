#pragma once
#include <string>
#include "Fecha.h"
#include "EstadoDespacho.h"
#include "EstadoSolicitud.h"
#include "ListaCliente.h"
#include "ListaPaquete.h"
#include "ListaColaborador.h"
#include "ListaCentros.h"
#include "ListaSolicitud.h"
using namespace std;

class Despacho {
private:
    string codigo;
    Solicitud* solicitud;
    Paquete* paquete;
    Cliente* cliente;
    Colaborador* responsable;
    Centro* centroOrigen;
    string destino;
    Fecha fechaDespacho;
    string hora;
    EstadoDespacho estado;

public:
    Despacho(string codigo, Solicitud* solicitud, Paquete* paquete,
        Cliente* cliente, Colaborador* responsable,
        Centro* centroOrigen, string destino,
        Fecha fechaDespacho, string hora);

    string getCodigo() const;
    EstadoDespacho getEstado() const;
    Paquete* getPaquete() const;
    void setEstado(EstadoDespacho nuevoEstado);
    void mostrarDatos() const;
};

class NodoDespacho {
public:
    Despacho* dato;
    NodoDespacho* siguiente;

    NodoDespacho(Despacho* dato);
};

class ListaDespacho {
private:
    NodoDespacho* primero;

public:
    ListaDespacho();
    ~ListaDespacho();

    bool estaVacia();
    void insertarFinal(Despacho* despacho);
    Despacho* buscar(string codigo);
    void mostrar();
};

