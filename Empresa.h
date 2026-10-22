#pragma once
#include "Cliente.h"

class Empresa : public Cliente {
private:
    string actividadEconomica;
    double porcentajeDescuento;

public:
    // Valida el porcentaje desde el menu ANTES de crear la empresa.
    static bool esPorcentajeValido(double porcentaje);

    // Si llega un porcentaje invalido se deja en 0 solo como resguardo;
    // el menu debe haberlo rechazado antes con esPorcentajeValido().
    Empresa(const string& identificacion, const string& nombre,
        const string& telefono, const string& correo,
        const string& actividadEconomica, double porcentajeDescuento);

    string getActividadEconomica() const;
    double getPorcentajeDescuento() const;

    void setActividadEconomica(const string& nuevaActividad);
    bool setPorcentajeDescuento(double nuevoPorcentaje);

    // costo final = costo base - (costo base * descuento / 100)
    double calcularCostoFinal(double costoBase) const override;
    string getTipo() const override;
    void mostrar() const override;
};