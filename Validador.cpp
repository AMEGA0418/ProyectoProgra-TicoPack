#include "Validador.h"

using namespace std;

bool Validador::textoValido(const string& texto) {
    for (size_t i = 0; i < texto.size(); i++) {
        char caracter = texto[i];
        if (caracter != ' ' && caracter != '\t' && caracter != '\n' &&
            caracter != '\r' && caracter != '\f' && caracter != '\v') {
            return true;
        }
    }
    return false;
}

bool Validador::numeroPositivo(double numero) {
    return numero > 0;
}

bool Validador::enteroNoNegativo(int numero) {
    return numero >= 0;
}

bool Validador::fechaValida(const Fecha& fecha) {
    return fecha.esValida();
}

bool Validador::correoValido(const string& correo) {
    size_t arroba = correo.find('@');
    if (arroba == string::npos || arroba == 0 || arroba + 1 >= correo.size()) {
        return false;
    }

    size_t punto = correo.find('.', arroba + 1);
    return punto != string::npos && punto > arroba + 1 && punto + 1 < correo.size();
}
