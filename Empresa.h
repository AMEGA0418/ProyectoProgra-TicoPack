#pragma once
#ifndef EMPRESA_H
#define EMPRESA_H

#include "ListaCliente.h"
#include <string>

class Empresa : public Cliente {
private:
    string actividadEconomica;
    double porcentajeDescuento;

public:
    Empresa(string identificacion, string nombre,
        string telefono, string correo,
        string actividadEconomica,
        double porcentajeDescuento);

    string getActividadEconomica() const;
    double getPorcentajeDescuento() const;

    void setActividadEconomica(string nuevaActividad);
    bool setPorcentajeDescuento(double nuevoPorcentaje);

    void mostrarDatos() const override;
};

#endif