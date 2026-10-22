#pragma once
#include <string>

using namespace std;

// Estados de una solicitud de envio. Se guardan como int usando estas
// constantes (EstadoSolicitud::PENDIENTE, etc.).
class EstadoSolicitud {
public:
    static const int PENDIENTE;
    static const int APROBADA;
    static const int RECHAZADA;
    static const int ANULADA;

    // true si el valor es un estado definido.
    static bool esValido(int estado);

    // Texto para mostrar. Si el valor no es valido devuelve "Desconocido".
    static string toString(int estado);

    // Aprobada, Rechazada y Anulada son estados finales.
    static bool esFinal(int estado);
};