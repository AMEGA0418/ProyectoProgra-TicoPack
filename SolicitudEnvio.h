#ifndef SOLICITUDENVIO_H
#define SOLICITUDENVIO_H

#include <string>
#include "Enumeraciones.h"
#include "Fecha.h"
#include "Cliente.h"
#include "Paquete.h"
#include "Colaborador.h"

class CentroDistribucion;

class SolicitudEnvio {
private:
    std::string codigo;
    Cliente* cliente;
    Paquete* paquete;
    Colaborador* responsable;          // se asigna al aprobar
    CentroDistribucion* centroOrigen;
    std::string destino;
    Fecha fechaSolicitud;
    double costoEstimado;
    EstadoSolicitud estado;

public:
    SolicitudEnvio(std::string cod, Cliente* cli, Paquete* paq,
        CentroDistribucion* origen, std::string destino);

    double calcularCosto();            // peso * tarifa -> descuento del cliente
    bool aprobar();                    // PENDIENTE -> APROBADA
    bool rechazar();                   // PENDIENTE -> RECHAZADA
    bool anular();                     // PENDIENTE/APROBADA -> ANULADA
    bool esFinal();                    // RECHAZADA o ANULADA
    void mostrar();

    std::string getCodigo() const { return codigo; }
    Cliente* getCliente() const { return cliente; }
    Paquete* getPaquete() const { return paquete; }
    Colaborador* getResponsable() const { return responsable; }
    CentroDistribucion* getCentroOrigen() const { return centroOrigen; }
    std::string getDestino() const { return destino; }
    Fecha getFechaSolicitud() const { return fechaSolicitud; }
    double getCostoEstimado() const { return costoEstimado; }
    EstadoSolicitud getEstado() const { return estado; }
    void setResponsable(Colaborador* r) { responsable = r; }
};

#endif