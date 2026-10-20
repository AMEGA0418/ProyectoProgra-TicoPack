#include "Fecha.h"
#include <iostream>

using namespace std;

Fecha::Fecha(int dia, int mes, int anio) {
    this->dia = dia;
    this->mes = mes;
    this->anio = anio;
}

int Fecha::getDia() const {
    return dia;
}

int Fecha::getMes() const {
    return mes;
}

int Fecha::getAnio() const {
    return anio;
}

void Fecha::setDia(int nuevoDia) {
    dia = nuevoDia;
}

void Fecha::setMes(int nuevoMes) {
    mes = nuevoMes;
}

void Fecha::setAnio(int nuevoAnio) {
    anio = nuevoAnio;
}

void Fecha::mostrarFecha() const {
    cout << dia << "/" << mes << "/" << anio << endl;
}

bool Fecha::esValida() const {
    if (anio < 1 || mes < 1 || mes > 12 || dia < 1) {
        return false;
    }

    int diasMes;

    if (mes == 2) {
        // Febrero: contempla años bisiestos
        if ((anio % 400 == 0) ||
            (anio % 4 == 0 && anio % 100 != 0)) {
            diasMes = 29;
        }
        else {
            diasMes = 28;
        }
    }
    else if (mes == 4 || mes == 6 ||
        mes == 9 || mes == 11) {
        diasMes = 30;
    }
    else {
        diasMes = 31;
    }

    return dia <= diasMes;
}