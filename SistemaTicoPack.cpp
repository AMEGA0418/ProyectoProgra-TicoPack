#include "SistemaTicoPack.h"
#include "Validador.h"

SistemaTicoPack::SistemaTicoPack() {
    centros.insertarFinal(new CentroDistribucion("CD-001", "Centro principal",
        "San Jose", "Calle 1, Avenida 2, San Jose", "2222-0000"));
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
        !Validador::textoValido(nuevoCentro->getCodigo()) ||
        !Validador::textoValido(nuevoCentro->getNombre()) ||
        !Validador::textoValido(nuevoCentro->getProvincia()) ||
        !Validador::textoValido(nuevoCentro->getDireccion()) ||
        !Validador::textoValido(nuevoCentro->getTelefono()) ||
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

Paquete* SistemaTicoPack::buscarPaqueteGlobal(const string& codigo) const {
    for (Nodo<CentroDistribucion>* nodo = centros.getPrimero();
        nodo != nullptr; nodo = nodo->getSiguiente()) {
        Paquete* encontrado = nodo->getDato()->buscarPaquete(codigo);
        if (encontrado != nullptr) return encontrado;
    }
    return nullptr;
}

SolicitudEnvio* SistemaTicoPack::buscarSolicitudGlobal(const string& codigo) const {
    for (Nodo<CentroDistribucion>* nodo = centros.getPrimero();
        nodo != nullptr; nodo = nodo->getSiguiente()) {
        SolicitudEnvio* encontrada = nodo->getDato()->buscarSolicitud(codigo);
        if (encontrada != nullptr) return encontrada;
    }
    return nullptr;
}

Despacho* SistemaTicoPack::buscarDespachoGlobal(const string& codigo) const {
    for (Nodo<CentroDistribucion>* nodo = centros.getPrimero();
        nodo != nullptr; nodo = nodo->getSiguiente()) {
        Despacho* encontrado = nodo->getDato()->buscarDespacho(codigo);
        if (encontrado != nullptr) return encontrado;
    }
    return nullptr;
}

void SistemaTicoPack::mostrarEstado() const {
    for (Nodo<CentroDistribucion>* nodo = centros.getPrimero();
        nodo != nullptr; nodo = nodo->getSiguiente()) {
        nodo->getDato()->mostrar();
    }
}
