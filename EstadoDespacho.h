#pragma once
#include <string>

using namespace std;

// Estados de un despacho. Se guardan como int usando estas constantes
// (EstadoDespacho::EN_PROCESO, etc.).
class EstadoDespacho {
public:
    static const int EN_PROCESO;
    static const int FINALIZADO;

    // true si el valor es un estado definido.
    static bool esValido(int estado);

    // Texto para mostrar. Si el valor no es valido devuelve "Desconocido".
    static string toString(int estado);
};
