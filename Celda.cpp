#include "Celda.h"

using namespace std;

Celda::Celda(const string& codigoBodega, int fila, int columna,
    bool formatoCompacto) {
    this->codigoBodega = codigoBodega;
    this->fila = fila;
    this->columna = columna;
    this->formatoCompacto = formatoCompacto;
    paquete = nullptr;
}

bool Celda::estaLibre() const {
    return paquete == nullptr;
}

void Celda::ocupar(Paquete* p) {
    paquete = p;
}

void Celda::liberar() {
    paquete = nullptr;
}

Paquete* Celda::getPaquete() const { return paquete; }
int Celda::getFila() const { return fila; }
int Celda::getColumna() const { return columna; }

string Celda::getIdentificador() const {
    if (formatoCompacto) {
        return codigoBodega + "-" + to_string(fila) + to_string(columna);
    }
    return codigoBodega + "-" + to_string(fila) + "," + to_string(columna);
}