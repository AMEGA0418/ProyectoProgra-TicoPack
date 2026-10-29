#include "SistemaTicoPack.h"

SistemaTicoPack::SistemaTicoPack() {
    centros.insertarFinal(new CentroDistribucion("CD-001", "Centro principal"));
}

SistemaTicoPack::SistemaTicoPack(const string& codigoCentro,
    const string& nombreCentro) {
    centros.insertarFinal(new CentroDistribucion(codigoCentro, nombreCentro));
}

SistemaTicoPack::~SistemaTicoPack() {
}

CentroDistribucion* SistemaTicoPack::getCentro() const {
    Nodo<CentroDistribucion>* nodo = centros.getPrimero();
    return nodo == nullptr ? nullptr : nodo->getDato();
}

CentroDistribucion* SistemaTicoPack::buscarCentro(const string& codigo) const {
    for (Nodo<CentroDistribucion>* nodo = centros.getPrimero();
        nodo != nullptr; nodo = nodo->getSiguiente()) {
        if (nodo->getDato()->getCodigo() == codigo) return nodo->getDato();
    }
    return nullptr;
}

bool SistemaTicoPack::agregarCentro(CentroDistribucion* nuevoCentro) {
    if (nuevoCentro == nullptr ||
        buscarCentro(nuevoCentro->getCodigo()) != nullptr) return false;
    centros.insertarFinal(nuevoCentro);
    return true;
}

bool SistemaTicoPack::eliminarCentro(const string& codigo) {
    CentroDistribucion* encontrado = buscarCentro(codigo);
    if (encontrado == nullptr || encontrado->tieneDependencias()) return false;
    return centros.eliminar(encontrado);
}

const ListaEnlazada<CentroDistribucion>& SistemaTicoPack::getCentros() const {
    return centros;
}

void SistemaTicoPack::mostrarEstado() const {
    for (Nodo<CentroDistribucion>* nodo = centros.getPrimero();
        nodo != nullptr; nodo = nodo->getSiguiente()) {
        nodo->getDato()->mostrar();
    }
}
