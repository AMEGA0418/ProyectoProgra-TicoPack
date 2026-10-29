#pragma once
#include <string>
#include <iostream>

using namespace std;

class Fecha {
private:
    int dia;
    int mes;
    int anio;
    int hora;
    int minuto;

public:
    // La hora y el minuto son opcionales (por defecto 00:00).
    Fecha(int dia, int mes, int anio, int hora = 0, int minuto = 0);

    int getDia() const;
    int getMes() const;
    int getAnio() const;
    int getHora() const;
    int getMinuto() const;

    void setDia(int nuevoDia);
    void setMes(int nuevoMes);
    void setAnio(int nuevoAnio);
    void setHora(int nuevaHora);
    void setMinuto(int nuevoMinuto);

    // true si dia/mes/anio forman una fecha real y la hora esta en 0-23, minuto 0-59.
    bool esValida() const;

    string toString() const;      // dd/mm/aaaa
    string horaToString() const;  // hh:mm

    void mostrarFecha() const;    // imprime toString() con salto de linea
};