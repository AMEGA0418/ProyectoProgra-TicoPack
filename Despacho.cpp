#include "Despacho.h"
#include "CentroDistribucion.h"
#include <iostream>

using namespace std;

Despacho::Despacho(string cod, SolicitudEnvio* sol)
    : codigo(cod), solicitud(sol), paquete(sol->getPaquete()),
    cliente(sol->getCliente()), responsable(sol->getResponsable()),
    centroOrigen(sol->getCentroOrigen()), destino(sol->getDestino()),
    fechaDespacho(), estado(EN_PROCESO) {}

bool Despacho::puedeFinalizar() {
    return estado == EN_PROCESO && paquete != nullptr
        && paquete->getEstado() == EN_TRANSITO;
}

bool Despacho::finalizar() {
    if (!puedeFinalizar()) return false;
    if (!paquete->cambiarEstado(ENTREGADO, responsable)) return false;
    estado = FINALIZADO;
    return true;
}

void Despacho::mostrar() {
    cout << "Despacho: " << codigo << endl;
    cout << "  Solicitud: " << (solicitud ? solicitud->getCodigo() : "N/A") << endl;
    cout << "  Paquete: " << (paquete ? paquete->getCodigo() : "N/A") << endl;
    cout << "  Cliente: " << (cliente ? cliente->getNombre() : "N/A") << endl;
    cout << "  Responsable: " << (responsable ? responsable->getNombreCompleto() : "N/A") << endl;
    cout << "  Centro origen: " << (centroOrigen ? centroOrigen->getNombre() : "N/A") << endl;
    cout << "  Destino: " << destino << endl;
    cout << "  Fecha: " << fechaDespacho.toString() << endl;
    cout << "  Estado: " << (estado == EN_PROCESO ? "EN_PROCESO" : "FINALIZADO") << endl;
}