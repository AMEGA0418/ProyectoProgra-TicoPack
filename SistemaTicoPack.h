#pragma once
#include <iostream>
#include "CentroDistribucion.h"
#include "ListaEnlazada.h"

using namespace std;

class SistemaTicoPack {
private:
    ListaEnlazada<CentroDistribucion> centros;

public:
    SistemaTicoPack();
    SistemaTicoPack(const string& codigoCentro, const string& nombreCentro);
    ~SistemaTicoPack();

    SistemaTicoPack(const SistemaTicoPack&) = delete;
    SistemaTicoPack& operator=(const SistemaTicoPack&) = delete;

    CentroDistribucion* getCentro() const;
    CentroDistribucion* buscarCentro(const string& codigo) const;
    bool agregarCentro(CentroDistribucion* centro);
    bool eliminarCentro(const string& codigo);

    // Busquedas globales: los codigos de paquete, solicitud y despacho son
    // unicos en todo el sistema, no solo dentro de un centro.
    Paquete* buscarPaqueteGlobal(const string& codigo) const;
    SolicitudEnvio* buscarSolicitudGlobal(const string& codigo) const;
    Despacho* buscarDespachoGlobal(const string& codigo) const;

    const ListaEnlazada<CentroDistribucion>& getCentros() const;
    void mostrarEstado() const;
};

