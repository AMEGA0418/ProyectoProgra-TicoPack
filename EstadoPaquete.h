#pragma once
#include <string>

enum class EstadoPaquete {
    RECIBIDO,
    ALMACENADO,
    EN_TRANSITO,
    ENTREGADO,
    INCIDENCIA
};

inline std::string estadoPaqueteToString(EstadoPaquete e) {
    switch (e) {
    case EstadoPaquete::RECIBIDO:    return "Recibido";
    case EstadoPaquete::ALMACENADO:  return "Almacenado";
    case EstadoPaquete::EN_TRANSITO: return "En transito";
    case EstadoPaquete::ENTREGADO:   return "Entregado";
    case EstadoPaquete::INCIDENCIA:  return "Incidencia";
    }
    return "Desconocido";
}

// Tabla de transiciones del enunciado (seccion 5). Solo dice si el cambio
// esta permitido en la tabla; las reglas "solo mediante la operacion que la
// origina" (almacenar, aprobar, finalizar) las controla cada operacion.
inline bool transicionPaqueteEnTabla(EstadoPaquete actual, EstadoPaquete nuevo) {
    switch (actual) {
    case EstadoPaquete::RECIBIDO:
        return nuevo == EstadoPaquete::ALMACENADO || nuevo == EstadoPaquete::INCIDENCIA;
    case EstadoPaquete::ALMACENADO:
        return nuevo == EstadoPaquete::EN_TRANSITO || nuevo == EstadoPaquete::INCIDENCIA;
    case EstadoPaquete::EN_TRANSITO:
        return nuevo == EstadoPaquete::ENTREGADO || nuevo == EstadoPaquete::INCIDENCIA;
    case EstadoPaquete::ENTREGADO:
        return false;
    case EstadoPaquete::INCIDENCIA:
        return nuevo == EstadoPaquete::ALMACENADO || nuevo == EstadoPaquete::EN_TRANSITO;
    }
    return false;
}