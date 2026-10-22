#include "Empresa.h"
#include <iostream>

using namespace std;

bool Empresa::esPorcentajeValido(double porcentaje) {
    return porcentaje >= 0 && porcentaje <= 100;
}

Empresa::Empresa(const string& identificacion, const string& nombre,
    const string& telefono, const string& correo,
    const string& actividadEconomica, double porcentajeDescuento)
    : Cliente(identificacion, nombre, telefono, correo) {

    this->actividadEconomica = actividadEconomica;
    this->porcentajeDescuento = 0;
    setPorcentajeDescuento(porcentajeDescuento);
}

string Empresa::getActividadEconomica() const { return actividadEconomica; }
double Empresa::getPorcentajeDescuento() const { return porcentajeDescuento; }

void Empresa::setActividadEconomica(const string& nuevaActividad) {
    actividadEconomica = nuevaActividad;
}

bool Empresa::setPorcentajeDescuento(double nuevoPorcentaje) {
    if (!esPorcentajeValido(nuevoPorcentaje)) {
        return false;
    }
    porcentajeDescuento = nuevoPorcentaje;
    return true;
}

double Empresa::calcularCostoFinal(double costoBase) const {
    return costoBase - (costoBase * porcentajeDescuento / 100);
}

string Empresa::getTipo() const {
    return "Empresa";
}

void Empresa::mostrar() const {
    cout << "--- EMPRESA ---" << endl;
    Cliente::mostrar();
    cout << "Actividad economica: " << actividadEconomica << endl;
    cout << "Porcentaje de descuento: " << porcentajeDescuento << "%" << endl;
}