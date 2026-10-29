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
    const ListaEnlazada<CentroDistribucion>& getCentros() const;
    void mostrarEstado() const;
};

