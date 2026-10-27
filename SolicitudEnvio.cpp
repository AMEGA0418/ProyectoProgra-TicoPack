#include "SolicitudEnvio.h"
#include "CentroDistribucion.h"
#include "Tarifas.h"
#include <iostream>

using namespace std;

static string estadoSolicitudToString(EstadoSolicitud e) {
    switch (e) {
    case PENDIENTE: return "PENDIENTE";
    case APROBADA:  return "APROBADA";
    case RECHAZADA: return "RECHAZADA";
    case ANULADA:   return "ANULADA";
    }
    return "?";
}

SolicitudEnvio::SolicitudEnvio(string cod, Cliente* cli, Paquete* paq,
    CentroDistribucion* origen, string dest)
    : codigo(cod), cliente(cli), paquete(paq), responsable(nullptr),
    centroOrigen(origen), destino(dest), fechaSolicitud(),
    costoEstimado(0.0), estado(PENDIENTE) {
    costoEstimado = calcularCosto();
}

double SolicitudEnvio::calcularCosto() {
    if (paquete == nullptr || cliente == nullptr) return 0.0;
    double costoBase = paquete->getPeso() * Tarifas::obtenerTarifa(paquete->getCategoria());
    return cliente->calcularCostoFinal(costoBase); // polimorfismo: Persona fisica / Empresa
}

bool SolicitudEnvio::aprobar() {
    if (estado != PENDIENTE) return false;
    estado = APROBADA;
    return true;
}

bool SolicitudEnvio::rechazar() {
    if (estado != PENDIENTE) return false;
    estado = RECHAZADA;
    return true;
}

bool SolicitudEnvio::anular() {
    if (estado != PENDIENTE && estado != APROBADA) return false;
    estado = ANULADA;
    return true;
}

bool SolicitudEnvio::esFinal() {
    return estado == RECHAZADA || estado == ANULADA;
}

void SolicitudEnvio::mostrar() {
    cout << "Solicitud: " << codigo << endl;
    cout << "  Cliente: " << (cliente ? cliente->getNombre() : "N/A") << endl;
    cout << "  Paquete: " << (paquete ? paquete->getCodigo() : "N/A") << endl;
    cout << "  Centro origen: " << (centroOrigen ? centroOrigen->getNombre() : "N/A") << endl;
    cout << "  Destino: " << destino << endl;
    cout << "  Fecha: " << fechaSolicitud.toString() << endl;
    cout << "  Costo estimado: " << costoEstimado << endl;
    cout << "  Estado: " << estadoSolicitudToString(estado) << endl;
    cout << "  Responsable: " << (responsable ? responsable->getNombreCompleto() : "Sin asignar") << endl;
}