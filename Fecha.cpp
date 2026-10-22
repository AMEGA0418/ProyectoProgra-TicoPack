#include "Fecha.h"
#include <iostream>

using namespace std;

// Convierte n a texto con al menos 'ancho' digitos (relleno con ceros).
static string conCeros(int n, int ancho) {
    string s = to_string(n);
    while ((int)s.size() < ancho) {
        s = "0" + s;
    }
    return s;
}

Fecha::Fecha(int dia, int mes, int anio, int hora, int minuto) {
    this->dia = dia;
    this->mes = mes;
    this->anio = anio;
    this->hora = hora;
    this->minuto = minuto;
}

int Fecha::getDia() const { return dia; }
int Fecha::getMes() const { return mes; }
int Fecha::getAnio() const { return anio; }
int Fecha::getHora() const { return hora; }
int Fecha::getMinuto() const { return minuto; }

void Fecha::setDia(int nuevoDia) { dia = nuevoDia; }
void Fecha::setMes(int nuevoMes) { mes = nuevoMes; }
void Fecha::setAnio(int nuevoAnio) { anio = nuevoAnio; }
void Fecha::setHora(int nuevaHora) { hora = nuevaHora; }
void Fecha::setMinuto(int nuevoMinuto) { minuto = nuevoMinuto; }

bool Fecha::esValida() const {
    if (anio < 1 || mes < 1 || mes > 12 || dia < 1) {
        return false;
    }
    if (hora < 0 || hora > 23 || minuto < 0 || minuto > 59) {
        return false;
    }

    int diasMes;

    if (mes == 2) {
        // Febrero: contempla anios bisiestos
        if ((anio % 400 == 0) || (anio % 4 == 0 && anio % 100 != 0)) {
            diasMes = 29;
        }
        else {
            diasMes = 28;
        }
    }
    else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        diasMes = 30;
    }
    else {
        diasMes = 31;
    }

    return dia <= diasMes;
}

string Fecha::toString() const {
    return conCeros(dia, 2) + "/" + conCeros(mes, 2) + "/" + conCeros(anio, 4);
}

string Fecha::horaToString() const {
    return conCeros(hora, 2) + ":" + conCeros(minuto, 2);
}

void Fecha::mostrarFecha() const {
    cout << toString() << endl;
}