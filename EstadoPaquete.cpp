#include "EstadoPaquete.h"

const int EstadoPaquete::RECIBIDO = 1;
const int EstadoPaquete::ALMACENADO = 2;
const int EstadoPaquete::EN_TRANSITO = 3;
const int EstadoPaquete::ENTREGADO = 4;
const int EstadoPaquete::INCIDENCIA = 5;

bool EstadoPaquete::esValido(int estado) {
    return estado >= RECIBIDO && estado <= INCIDENCIA;
}

string EstadoPaquete::toString(int estado) {
    if (estado == RECIBIDO) return "Recibido";
    if (estado == ALMACENADO) return "Almacenado";
    if (estado == EN_TRANSITO) return "En transito";
    if (estado == ENTREGADO) return "Entregado";
    if (estado == INCIDENCIA) return "Incidencia";
    return "Desconocido";
}

bool EstadoPaquete::transicionEnTabla(int actual, int nuevo) {
    if (actual == RECIBIDO) {
        return nuevo == ALMACENADO || nuevo == INCIDENCIA;
    }
    if (actual == ALMACENADO) {
        return nuevo == EN_TRANSITO || nuevo == INCIDENCIA;
    }
    if (actual == EN_TRANSITO) {
        return nuevo == ENTREGADO || nuevo == INCIDENCIA;
    }
    if (actual == INCIDENCIA) {
        return nuevo == ALMACENADO || nuevo == EN_TRANSITO;
    }
    // ENTREGADO es final y un estado invalido no tiene transiciones.
    return false;
}
