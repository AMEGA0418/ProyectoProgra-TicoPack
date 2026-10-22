#pragma once
#include <string>

enum class EstadoSolicitud {
    PENDIENTE,
    APROBADA,
    RECHAZADA,
    ANULADA
};

inline std::string estadoSolicitudToString(EstadoSolicitud e) {
    switch (e) {
    case EstadoSolicitud::PENDIENTE: return "Pendiente";
    case EstadoSolicitud::APROBADA:  return "Aprobada";
    case EstadoSolicitud::RECHAZADA: return "Rechazada";
    case EstadoSolicitud::ANULADA:   return "Anulada";
    }
    return "Desconocido";
}

// Aprobada, Rechazada y Anulada son estados finales.
inline bool estadoSolicitudEsFinal(EstadoSolicitud e) {
    return e != EstadoSolicitud::PENDIENTE;
}