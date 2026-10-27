#ifndef DESPACHO_H
#define DESPACHO_H

#include <string>
#include "Enumeraciones.h"
#include "Fecha.h"
#include "Cliente.h"
#include "Paquete.h"
#include "Colaborador.h"
#include "SolicitudEnvio.h"

class CentroDistribucion;

class Despacho {
private:
    std::string codigo;
    SolicitudEnvio* solicitud;
    Paquete* paquete;
    Cliente* cliente;
    Colaborador* responsable;
    CentroDistribucion* centroOrigen;
    std::string destino;
    Fecha fechaDespacho;
    EstadoDespacho estado;

public:
    // Los datos se toman de la solicitud aprobada.
    Despacho(std::string cod, SolicitudEnvio* sol);

    bool finalizar();        // EN_PROCESO -> FINALIZADO, paquete -> ENTREGADO
    bool puedeFinalizar();
    void mostrar();

    std::string getCodigo() const { return codigo; }
    SolicitudEnvio* getSolicitud() const { return solicitud; }
    Paquete* getPaquete() const { return paquete; }
    Cliente* getCliente() const { return cliente; }
    Colaborador* getResponsable() const { return responsable; }
    EstadoDespacho getEstado() const { return estado; }
};

#endif