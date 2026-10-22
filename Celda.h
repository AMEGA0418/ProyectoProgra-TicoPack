#pragma once
#include <string>

using namespace std;

class Paquete;

// Una posicion de la matriz de una bodega. Esta libre o guarda un paquete.
// La celda NO es duena del paquete (solo lo referencia).
class Celda {
private:
    string codigoBodega;
    int fila;
    int columna;
    bool formatoCompacto;   // true: "A-12"   false: "A-12,3" (indices de 2+ digitos)
    Paquete* paquete;

public:
    Celda(const string& codigoBodega, int fila, int columna,
        bool formatoCompacto = true);

    bool estaLibre() const;
    void ocupar(Paquete* p);
    void liberar();

    Paquete* getPaquete() const;
    int getFila() const;
    int getColumna() const;

    // Ej.: bodega A, fila 1, columna 2 -> "A-12". Si algun indice tiene
    // dos o mas digitos se usa "A-10,2" para distinguir fila y columna.
    string getIdentificador() const;
};