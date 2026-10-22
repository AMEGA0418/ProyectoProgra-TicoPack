#pragma once
#include <string>

using namespace std;

// Estados de un paquete. Se guardan como int usando estas constantes
// (EstadoPaquete::RECIBIDO, etc.).
class EstadoPaquete {
public:
    static const int RECIBIDO;
    static const int ALMACENADO;
    static const int EN_TRANSITO;
    static const int ENTREGADO;
    static const int INCIDENCIA;

    // true si el valor es un estado definido.
    static bool esValido(int estado);

    // Texto para mostrar. Si el valor no es valido devuelve "Desconocido".
    static string toString(int estado);

    // Tabla de transiciones del enunciado (seccion 5). Solo dice si el cambio
    // esta permitido en la tabla; las reglas "solo mediante la operacion que
    // la origina" (almacenar, aprobar, finalizar) las controla cada operacion.
    static bool transicionEnTabla(int actual, int nuevo);
};