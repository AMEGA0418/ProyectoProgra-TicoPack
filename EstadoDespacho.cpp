#include "EstadoDespacho.h"

const int EstadoDespacho::EN_PROCESO = 1;
const int EstadoDespacho::FINALIZADO = 2;

bool EstadoDespacho::esValido(int estado) {
    return estado >= EN_PROCESO && estado <= FINALIZADO;
}

string EstadoDespacho::toString(int estado) {
    if (estado == EN_PROCESO) return "En proceso";
    if (estado == FINALIZADO) return "Finalizado";
    return "Desconocido";
}
