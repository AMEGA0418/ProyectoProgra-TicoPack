#include "EstadoSolicitud.h"

const int EstadoSolicitud::PENDIENTE = 1;
const int EstadoSolicitud::APROBADA = 2;
const int EstadoSolicitud::RECHAZADA = 3;
const int EstadoSolicitud::ANULADA = 4;

bool EstadoSolicitud::esValido(int estado) {
    return estado >= PENDIENTE && estado <= ANULADA;
}

string EstadoSolicitud::toString(int estado) {
    if (estado == PENDIENTE) return "Pendiente";
    if (estado == APROBADA) return "Aprobada";
    if (estado == RECHAZADA) return "Rechazada";
    if (estado == ANULADA) return "Anulada";
    return "Desconocido";
}

bool EstadoSolicitud::esFinal(int estado) {
    return esValido(estado) && estado != PENDIENTE;
}
