#include "SistemaTicoPack.h"

SistemaTicoPack::SistemaTicoPack() {
    centro = new CentroDistribucion("CD-001", "Centro principal");
}

SistemaTicoPack::SistemaTicoPack(const string& codigoCentro,
    const string& nombreCentro) {
    centro = new CentroDistribucion(codigoCentro, nombreCentro);
}

SistemaTicoPack::~SistemaTicoPack() {
    delete centro;
    centro = nullptr;
}

CentroDistribucion* SistemaTicoPack::getCentro() const {
    return centro;
}

void SistemaTicoPack::mostrarEstado() const {
    if (centro != nullptr) centro->mostrar();
}
