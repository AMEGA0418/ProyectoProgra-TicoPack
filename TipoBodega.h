#pragma once
#include <string>

using namespace std;

// Tipos de bodega. Se guardan como int usando estas constantes. Los valores
// numericos coinciden con la tabla del enunciado (codigo de tipo 1 a 4).
class TipoBodega {
public:
    static const int GENERAL;
    static const int FRAGIL;
    static const int TECNOLOGIA;
    static const int DOCUMENTOS;

    // true si el codigo es un tipo definido (1 a 4).
    static bool esValido(int tipo);

    // Texto para mostrar. Si el valor no es valido devuelve "Desconocido".
    static string toString(int tipo);

    // Compatibilidad directa con la categoria del paquete:
    // General-General, Fragil-Fragil, Tecnologia-Tecnologia, Documentos-Documentos.
    static bool esCompatible(int tipo, int categoria);
};
