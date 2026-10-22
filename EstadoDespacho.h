#pragma once
#include <string>

enum class EstadoDespacho {
    EN_PROCESO,
    FINALIZADO
};

inline std::string estadoDespachoToString(EstadoDespacho e) {
    switch (e) {
    case EstadoDespacho::EN_PROCESO: return "En proceso";
    case EstadoDespacho::FINALIZADO: return "Finalizado";
    }
    return "Desconocido";
}