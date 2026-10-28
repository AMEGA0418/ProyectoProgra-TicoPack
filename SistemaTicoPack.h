#pragma once
#include "CentroDistribucion.h"

class SistemaTicoPack {
private:
    CentroDistribucion* centro;

public:
    SistemaTicoPack();
    SistemaTicoPack(const string& codigoCentro, const string& nombreCentro);
    ~SistemaTicoPack();

    SistemaTicoPack(const SistemaTicoPack&) = delete;
    SistemaTicoPack& operator=(const SistemaTicoPack&) = delete;

    CentroDistribucion* getCentro() const;
    void mostrarEstado() const;
};

