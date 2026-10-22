#include "Empresa.h"
#include <iostream>

using namespace std;

Empresa::Empresa(string identificacion, string nombre,
    string telefono, string correo,
    string actividadEconomica,
    double porcentajeDescuento)
    : Cliente(identificacion, nombre, telefono, correo) {

    this->actividadEconomica = actividadEconomica;

    if (porcentajeDescuento >= 0 &&
        porcentajeDescuento <= 100) {
        this->porcentajeDescuento = porcentajeDescuento;
    }
    else {
        this->porcentajeDescuento = 0;
    }
}

string Empresa::getActividadEconomica() const {
    return actividadEconomica;
}

double Empresa::getPorcentajeDescuento() const {
    return porcentajeDescuento;
}

void Empresa::setActividadEconomica(string nuevaActividad) {
    actividadEconomica = nuevaActividad;
}

bool Empresa::setPorcentajeDescuento(double nuevoPorcentaje) {
    if (nuevoPorcentaje >= 0 && nuevoPorcentaje <= 100) {
        porcentajeDescuento = nuevoPorcentaje;
        return true;
    }

    return false;
}

void Empresa::mostrarDatos() const {
    cout << "--- EMPRESA ---" << endl;
    Cliente::mostrarDatos();

    cout << "Actividad economica: "
        << actividadEconomica << endl;

    cout << "Porcentaje de descuento: "
        << porcentajeDescuento << "%" << endl;
}